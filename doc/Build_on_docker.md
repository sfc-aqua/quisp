# installation omnetpp gui and quisp on docker (For OSX)

This is instruction for installing omnetpp and quisp on docker.  
This on MacOS Catalina (10.15.3) and Mojave(10.14).

## TL;DR
- Install docker to your host machine
- Install XQuartz and socat
- clone quisp
- `sh docker_build.sh`
- Somewhere in your host OS, run `socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"`
- Add your host machine IP address to xterm with `xhost` command.
- Run docker with `sh docker_run.sh`
- Run `omnetpp` command on the docker container

---

## Easier way (Beta)

This is just a beta version of a newer, more automated (and hopefully more robust) installation process. If it doesn't work properly for you, please open an issue on Github and/or contact us via Slack. You can also skip down lower in this file for the older, manual installation instructions.

1. Open your terminal and run

```zsh
$ git clone https://github.com/sfc-aqua/quisp.git
```

You can download quisp from github.
Enter quisp with `cd quisp`
2. Run shell script

```zsh
$ sh docker_tools.sh
```

After you have successfully installed the related tools, please reboot your laptop. (Maybe just rebooting your terminal is enough.)

3. Build docker container

Open terminal and move to the `quisp/`, 

```zsh
$ sh docker_build.sh
```

A docker image called quisp should have been created. You can check with the command `docker images`.

4. Run docker container

OK, now you can enter the container.

```zsh
$ sh docker_run_beta.sh
```

5. Try quisp!

If all of the processing completed successfully, you should see

```zsh
quisp:/root/quisp$
```

Open omnet with

```zsh
quisp:/root/quisp$ omnetpp
```

Enjoy quisp!

---

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
$ git clone https://github.com/sfc-aqua/quisp.git
$ cd quisp
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
$ socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"&
```

## 4.Start your docker container

Open the file which has Dockerfile (in quisp)

```zsh 
$ sh quisp_docker.sh
```

You can run your container and **in the container**, run
```zsh
> omnetpp
```

You can use omnetpp and quisp on docker container.

## 5.Set up your OMNET++
After the logo shows up, you will see the following tab. You can just press "Launch" button. 

![Setup](https://user-images.githubusercontent.com/45162150/74584459-e7b2a000-5015-11ea-95a0-cd811ed9b25d.png)


This is what the home screen looks like.

![](https://i.imgur.com/0eTDAQi.png)


If you go to [File] → [Open Projects from File System...], you would see the following image.

![](https://i.imgur.com/LE63EJE.png)


You will go to the following image.  Then, you have to put "/root/mdoels/quisp" as the "import source", and press "Select All" on the right side and the "Finish" on the bottom.
![](https://i.imgur.com/iEbayjS.png)


Now go back to the previous page.
The page will now look like this.
You will see the "networks" and "quisp" on the left side.


![](https://i.imgur.com/RuGLKXJ.png)

Then, you have to right click on the "quisp" and go to [Properties] (which is the VERY BOTTOM tab)


![](https://i.imgur.com/MITpLz4.png)


This is what the "Properties" page looks like. Next, you should click the "Makemake".


![](https://i.imgur.com/2njDPBi.png)


Then, you have to click \UTF{2460}~\UTF{2462} in the following image.

![](https://i.imgur.com/Zwqql8b.png)


You will go to the following page, so you should click the "Compile" tab.

![](https://i.imgur.com/wdeH3pC.png)

After you click the "Compile" tab, You will see the following page.

![](https://i.imgur.com/CTB85mk.png)

Then, you should click the small icon which is pointed by an arrow, 

![](https://i.imgur.com/Up47pD1.png)

and you should put "usr/include/eigen3" in the blank and Press "OK".

Then, you will go back to the "Compile" tab, so press "OK"

![](https://i.imgur.com/0TnZxmR.png)


After that, you will go back to its previous page, so press "Apply and Close" button.

![](https://i.imgur.com/TH3yLUM.png)


Now press the green "Run" button on the top of the page and you will see the simulation screen (if you click "OK" or "Proceed" for the random pop-ups)

## 6.Run a Simulation
If you see the following image, you came to right place. You can press "OK" if any random pop-ups show up.

![](https://i.imgur.com/lzsxTqa.png)

Click the "Set Up an Unconfigured Network".

![](https://i.imgur.com/cdi34vk.png)

You can choose what simulation you would like to perform.

![](https://i.imgur.com/oPfFUGR.png)