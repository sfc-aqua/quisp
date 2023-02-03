from typing import List, Dict
from enum import Enum
import asyncio, re, os


class WorkerStatus(Enum):
    WAINTING_FOR_TASK = "Waiting for task"
    STARTING = "Starting"
    RUNNING = "Running"
    FINISHING = "Finishing"
    FINISHED = "Finished"
    STOPPED = "Stopped"
    ERROR = "Error"


class Worker:
    working_dir: str
    error_messages: str = ""
    real_time: float = 0.0
    sys_time: float = 0.0
    user_time: float = 0.0
    lock: asyncio.Lock
    status: WorkerStatus = WorkerStatus.WAINTING_FOR_TASK
    output: str = ""
    results: Dict[str, Dict]

    def __init__(self) -> None:
        # quisp dir
        self.working_dir = os.path.abspath(
            os.path.join(os.path.basename(__file__), "..", "quisp")
        )
        self.lock = asyncio.Lock()
        self.results = dict()

    async def set_status(self, status: "WorkerStatus") -> None:
        async with self.lock:
            if self.status is not WorkerStatus.ERROR:
                self.status = status

    async def run(
        self,
        config_name: str,
        ned_file_path: str = "simulations/test.ini",
        ned_path: str = "modules:channels:networks",
    ):
        commands = [
            "./quisp",
            "-u",
            "Cmdenv",
            "--cmdenv-express-mode=true",
            "-c",
            config_name,
            "-f",
            ned_file_path,
            "-i",
            ned_path,
        ]
        proc = await asyncio.create_subprocess_shell(
            "/usr/bin/time -p -- " + " ".join(commands),
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE,
            cwd=self.working_dir,
        )
        if proc.stdout is None or proc.stderr is None:
            return
        stdout = proc.stdout
        stderr = proc.stderr
        running = False  # whether quisp's initializing phase is finished or not
        while True:
            if stdout.at_eof() and stderr.at_eof():
                break
            lines = []

            # stdout example:
            # ** Event #1225984   t=10.000104015903   Elapsed: 96.8616s (1m 36s)  76% completed  (76% total)
            #     Speed:     ev/sec=9170.57   simsec/sec=9.70194e-08   ev/simsec=9.45231e+10
            #     Messages:  created: 3759524   present: 15381   in FES: 9122

            while len(stdout._buffer) > 0:  # type: ignore
                buf = (await proc.stdout.readline()).decode().strip()
                if not buf:
                    break
                if buf.startswith("<!> Error"):
                    await self.set_status(WorkerStatus.ERROR)
                if buf.startswith("End."):
                    running = False
                    await self.set_status(WorkerStatus.FINISHING)

                if buf.startswith("** Event"):
                    if not running:
                        running = True
                        await self.set_status(WorkerStatus.RUNNING)
                    match = re.search(r"Event #(\d+)", buf)
                    if match:
                        async with self.lock:
                            self.num_events = int(match.group(1))
                if buf.startswith("Speed:"):
                    match = re.search(
                        r"ev/sec=([0-9.]+)\s+simsec/sec=([0-9.\-\+e]+)\s+ev/simsec=([0-9.\-\+e]+)",
                        buf,
                    )
                    if match:
                        async with self.lock:
                            self.ev_per_sec = float(match.group(1))
                    lines.append(re.sub(r"\s+", ",", buf))
                self.output += buf + "\n"

            while len(stderr._buffer) > 0:  # type: ignore
                buf = (await proc.stderr.readline()).decode().strip()
                # parse time command output
                if buf.startswith("real"):
                    self.real_time = parse_time(buf.split()[1])
                elif buf.startswith("sys"):
                    self.sys_time = parse_time(buf.split()[1])
                elif buf.startswith("user"):
                    self.user_time = parse_time(buf.split()[1])
                elif buf:
                    # self.context.log("[red]Err: ", buf)
                    self.error_messages += buf + "\n"
                    await self.set_status(WorkerStatus.ERROR)
            await asyncio.sleep(0.1)
        await proc.communicate()
        await self.set_status(WorkerStatus.FINISHED)
        if self.status is WorkerStatus.ERROR:
            raise RuntimeError(self.error_messages)
        for result in [parse_output(l) for l in self.output.split("\n")]:
            if result:
                self.results[result["name"]] = result


def parse_time(s: str) -> float:
    """parse `time` command result time"""

    return float(s)


def parse_output(s: str):
    if not "<-->" in s:
        return None
    channel_info, *rest = s.split(" ")
    node1, channel, node2 = channel_info.split("<-->")
    return {
        "name": f"{node1}<-->{remove_end_semi(node2)}",
        "channel": parse_object(channel[15:-2].split(";")),
        "data": parse_object(rest),
    }


def remove_end_semi(s: str) -> str:
    """remove the last semicolon if exists"""
    if s.endswith(";"):
        return s[:-1]
    return s


def parse_object(s: "List[str]") -> "Dict[str, float]":
    obj = dict()
    for kv in s:
        k, v = kv.split("=")
        v = remove_end_semi(v)
        try:
            obj[k] = float(v)
        except ValueError:
            obj[k] = v

    return obj
