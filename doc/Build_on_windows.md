# Installating Omnetpp GUI and Native Quisp on Windows OS

## TL;DR
* Before You Start
* OMNeT++ Installation
* Insall Needed Tools for the GUI
* Cloning and Building Quisp 
* Running A Simulation


## Before You Start
Before you begin installing OMNeT++ and Quisp, make sure you have a C++ compiler on computer. If you do, skip to step 1, if you don't, head to [this](https://www.tutorialspoint.com/How-do-I-set-up-C-Cplusplus-on-Eclipse-in-Windows) link and get your compiler set up and then come back and go to step 1!


## 1- OMNeT++ Installation

OMNeT++ is an extensible, modular, component-based C++ simulation library and framework and is used to simulate the network. To download it, please click [here](https://omnetpp.org/download/).

OMNeT++ will be downloaded as a zip file. Once the download is complete, extract the file, you should see these files in the extracted directory.

![](https://i.imgur.com/YuSTF1u.png)





Run *mingwenv.cmd*, which will start a console with the MSYS bash shell.

In the shell type the following commands:

```
$ ./configure
$ make
```

This might take a while to finish executing. 

**To verify** that the installation has been successful, run the following:

```
$ cd samples/aloha
$ ./aloha
```

By default, the samples will run using the graphical Qtenv environment. You should see the following GUI windows.

![](https://i.imgur.com/77vk5iY.jpg)


**Click OK**


![](https://i.imgur.com/HqdskWt.jpg)



Yay!! your installation was successful!!

**To run** the Omnetpp (OMNeT app), type the command
```
$ omnetpp
```

###### Whenever you want to run omnetpp, you will need to run from the mingwenv console.


![](https://i.imgur.com/5ROa7qu.jpg)


## 2- Install Needed Tools for the GUI
To run the simulation GUI, you will need to install *Eigen*.

In the mingwenv console, type the following command:
```
git clone https://gitlab.com/libeigen/eigen.git
```
For more information on Eigen, please visit [this](http://eigen.tuxfamily.org/index.php?title=Main_Page) site.


## 3- Cloning and Building Quisp

To clone and build Quisp, one your terminal (perferapply Cygwin) and type the follwoing commands:
```
$ git clone https://<username>@bitbucket.org/sfc-aqua/kaaki_master_quisp.git
```
The last command will take a while to build the docker (around 15 mins).

## 4- Set up OMNeT for the Simulation

*Launch* omnetpp from mingwenv console


![](https://i.imgur.com/ZU98fNh.jpg)


From File >> Open Projects from File System


![](https://i.imgur.com/2aMxfLB.jpg)


Click *Directroy* and choose the location where Quisp was cloned (usually it will be in the omnet directroy)


![](https://i.imgur.com/gTIq3ow.jpg)


Select both files and click *Finish*


![](https://i.imgur.com/IviUq2n.jpg)


That will make *kaaki-quisp-master* and *quisp* appear in your **Project Explorer** 

Select quisp, right-click on it and choose *properties*.


![](https://i.imgur.com/8HK3ddW.jpg)


In the screen that shows up, expand OMNeT++, click on Makemake.
Select quisp from the middle and on the right-habd side, choose Makemake and then click on options. 


![](https://i.imgur.com/JSHw1cO.jpg)


In the compile tab, click the add button ![](https://i.imgur.com/pvVkc8f.jpg)
and then choose the directroy for **Eigen** and click OK


![](https://i.imgur.com/koTDUzd.jpg)


In the *Project Explorer* right-click on quisp and choose *Run As* > *OMNeT++ Simulation*.


![](https://i.imgur.com/hGuJE1u.jpg)



The following window will pop up, and it will take up to 2 mins to get the simulation set up.


![](https://i.imgur.com/KIjrKvB.jpg)



Test the simulation by choosing a *Config name*


![](https://i.imgur.com/h3zut9d.jpg)



And Voilà !!! 


![](https://i.imgur.com/mH7C1gH.jpg)



## 5- Running A Simulation

From File > Set Up an Unconfigured Network...


![](https://i.imgur.com/0jFI8hB.jpg)



Choose a network and click OK.

![](https://i.imgur.com/dUOFO2n.jpg)



Enjoy the simulated results!!

![](https://i.imgur.com/ht6bIH1.jpg)


