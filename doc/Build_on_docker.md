# installation omnetpp gui and quisp on docker (For OSX)

This is instruction for installing omnetpp and quisp on docker. This is tested on MacOS Catalina (10.15.3)

## 1. Prepare Docker files and tools

Before going to build environments, we need some tools.
We're going to use [Home brew](https://brew.sh/) package manager.

```zsh
brew install docker
brew install socat
brew cask install docker
brew cask install xquartz
```

These are nessesary for building GUI version of omnet.
Reboot and checck your DISPLAY

```zsh
echo $DISPLAY
>/private/tmp/com.apple.launchd.XXXXXXXX/org.macosforge.xquartz:0
```

## 2. build docker container

Next, let's build your docker container. (This might take a lot of time.)

```zsh
cd quisp_docker
sh docker_build.sh
```

Hopefully, you can build your docker container successfully.(Please use latest version of docker)

## 3. Make connection between your host os to container via TCP

Open another terminal window and check your host ip address with,

```zsh
ifconfig en0 | grep inet | awk '$1=="inet" {print $2}'
```

You can get an ip adress of your host machine.
Open Xquartz with

```zsh
open -a XQuartz
```

![toolbar](https://i.imgur.com/ZGaAcFU.png)

In the top of display you can see "XQuartz" and open terminal.

![xquartz](https://i.imgur.com/lXUyrcg.png)
then you can open your terminal.

Enter 

```xterm
xhost <your ip address>
```

\<your ip address> is your host ip address you checked previously.

Finally, open your terminal again, and

```zsh
socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"
```

## start your docker container

Open the file which has Dockerfile.

```zsh
sh quisp_docker.sh
```

You can run your container and enter command

```zsh
omnetpp# omnetpp
```

You can use omnetpp and quisp on docker container.