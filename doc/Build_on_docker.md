# installation omnetpp gui and quisp on docker (For OSX)

This is instruction for installing omnetpp and quisp on docker.  
This on MacOS Catalina (10.15.3) and Mojave(10.14).

## TL;DR
- Install docker to your host OS
- Install XQuartz and socat
- clone kaaki_quisp_master
- `sh docker_build.sh`
- Somewhere in your host OS, run `socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"`
- Add your host machine IP address to xterm with `xhost` command.
- Run docker with `sh quisp_docker.sh`
- Run `omnetpp` command on the docker container

## 1. Install docker

You need a docker hub account to pulls images. Register [here](https://hub.docker.com/).

For using docker, you need to install docker app from [here](https://hub.docker.com/editions/community/docker-ce-desktop-mac) or if you're using [`brew`](https://brew.sh/), you can install it with
```zsh
$ brew install docker
$ brew cask install docker
```
on your terminal.
After you successfully installed Docker desktop app, open docker and sign in it with your docker hub account.

#### Assign more CPUs to docker

If you have a nice spec machine, you should assign more CPUs from
> Docker > Preference > Resources

<img src=https://i.imgur.com/m5r2WMA.png width=300>

## 2. Install related tools

We need some other tools for using GUI version of quisp on docker.
Download XQuartz from [**here**](https://www.xquartz.org/).

```zsh
$ brew install socat
```

These are nessesary for building GUI version of omnet.  
If you finish installing those tools successfully, **reboot your mac** and check **$DISPLAY** like,

```zsh
$ echo $DISPLAY
>/private/tmp/com.apple.launchd.XXXXXXXX/org.macosforge.xquartz:0
```

If you can't see any values in $DISPLAY, uninstall XQuartz and install it again.(If you're using terminal attached to VScode or some other editor or IDEs, you may not be able to check it properly.)

## 3. Build docker container

Next, let's build the docker container on your Mac.  
(This might take a lot of time. Probably, about 15 min)
***!!!!!<CHANGE WHEN THIS BECOME OSS>***
```zsh
$ git clone https://<username>@bitbucket.org/sfc-aqua/kaaki_master_quisp.git
$ cd kaaki_master_quisp
$ sh docker_build.sh
```
Hopefully, you can build your docker container successfully.

## 3. Make connection between your host os to container via TCP

Open another terminal window and check your host ip address with,

```zsh
$ ifconfig en0 | grep inet | awk '$1=="inet" {print $2}'
```

You can get an ip adress of your host machine.
Open Xquartz with

```zsh
$ open -a XQuartz
```

![toolbar](https://i.imgur.com/ZGaAcFU.png)

In the top of display you can see "XQuartz" and open terminal.

![xquartz](https://i.imgur.com/lXUyrcg.png)
then you can open your terminal.

Enter on the **xterm** (not your default terminal)

```xterm
> xhost <your ip address>
```

\<your ip address> is your host ip address you checked previously.
If you have trouble with using `xhost`, and [see](./xhost_trouble_shooting.md).

Finally, open your **terminal** again, and

```zsh
$ socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"
```

## start your docker container

Open the file which has Dockerfile (in kaaki_quisp_master)

```zsh 
$ sh quisp_docker.sh
```

You can run your container and **in the container**, run
```zsh
> omnetpp
```

You can use omnetpp and quisp on docker container.