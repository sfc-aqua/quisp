# Running the OmNET++ GUI

We are working with the following installation tree.  You are assumed
to have just come from [doc/INSTALL.md](INSTALL.md).  These
instructions are geared toward native installation on a UNIX-like
system (e.g., Mac or Linux).  What is here should be of some use on
all platforms, but if you are working on Docker, you will need [docker
install doc](Build_on_docker.md).  If you are on Windows, see the
[Windows install doc](Build_on_windows.md).

```
home/
├── projects/
│   └── quisp/
│       ├── .git/
│       ├── setenv*
│       └── quisp/
└── .local/
    └── lib/
        ├── omnetpp-5.6.1/
        │   ├── setenv*
        │   └── bin/
        │       └── omnetpp*
        └── eigen-source/
```

To run the OmNET++ GUI, you need to use their `setenv` script.

```
/home/.local/lib/omnetpp-5.6.1 λ source setenv
/home/.local/lib/omnetpp-5.6.1
/home/.local/lib/omnetpp-5.6.1 λ omnetpp
Starting the OMNeT++ IDE...
```

This starts the Eclipse Launcher. When asked to select your workspace,
choose the quisp folder (here, `/home/projects/quisp`).

Then, open the Workbench. When warned that your workspace is empty, refuse
to install samples.

Finally, import the QUISP project into your workspace. You can use the
`File > Import...` menu, then select the `General > Existing Projects into Workspace`
wizard. As a root directory of the project, select the quisp folder.
In the list of suggested projects, check the only project that appears then
click `Finish`.

When you did this, the GUI created two folders, `.metadata` for the
workspace and `.settings` for the project, that are ignored by the git
repository.

```
home/
└── projects/
    └── quisp/
        ├── .git/
        ├── setenv*
        ├── .metadata/
        └── quisp/
            └── .settings/
```

## Configure building

Open `Project > Properties` for the quisp project, then in the category `OMNeT++ > Makemake`
you should get a warning.

*No makefile has been specified for this project.*

Click on the `quisp` folder below the warning, select the `Makemake` box.

Then you need to specify how to find the Eigen library. Click `Options...` below
`Makemake`, then in the `Compile` tab you will have a category called
`Include directories`.

To this list, you should add one folder.  
  
Following is how we mostly configure our directory structure for Eigen3. However, this is just our recommendation; While our 'recommended' way helps you to build your project smoothly, you can change it as long as you know what you're doing.  
For Eigen3, it's fine to install it anywhere. The core of the matter is **including Eigen3's location from OmNET++ correctly.**

> With the local Eigen installation in
> this example you can add `/home/.local/lib/eigen-source`, and with the system
> installation you can add `/usr/local/share/eigen3`.

> If you're using Mac OSX, you can put `/Users/<home directory>/.local/lib/eigen-source` or
> `/usr/local/share/eigen3`


Then, in the category `C/C++ Build`, click `Manage configurations` and make the
release configuration active.

After this, a new file `quisp/.oppbuildspec` is created by OmNET++ and ignored
by git.

```
home/
└── projects/
    └── quisp/
        ├── .git/
        ├── setenv*
        ├── .metadata/
        └── quisp/
            ├── .settings/
            └── .oppbuildspec
```

Now you should be able to build the project with `Ctrl+B` or `Project > Build all`
for example. If you got a message ' fatal error: 'PhotonicQubit_m.h' file not found `  during the build, you should add './quisp' to the Include Path in the Makemake Options →Compile

## Running interesting simulations

You should now be ready to simulate quantum networks!  Three places
you can go:

* Go to [running demos](running-demos.md).
* One good source of info for "now what?" is the [Windows install
  doc](Build_on_windows.md).  Follow that, skip the basic instructions
  and pick up where it starts working with the examples.
* Just return to [the top-level readme](../README.md) and check
  options from there.
