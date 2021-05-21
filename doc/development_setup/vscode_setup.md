# Visual Studio Code Development Setup

Visual Studio Code is the editor of choice for many people (and most of our team members also use it), so we decided to make a guide on how to setup your workspace so you can get the most functionality out of VSCode (e.g. code formatting, linting, intellisense, etc) and developing QuISP is smooth as possible.

## Prerequisites

* You should have a working build of QuISP. If you haven't done so please follow this [guide](/doc/README.md) Intro & Install section.
* You should have [opp_test and unit test (googletest) working and running](/doc/development_setup/README.md). 

## Setup formatter and linter

We recommend using [clangd](https://clangd.llvm.org) since it has VSCode integration via [official extension](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd). This will enable us to format code according to `.clang-format` file and lint and give hints according to rules defined in `.clang-tidy` file. 

### Steps to setup clangd

In this guide, we use [Homebrew](https://brew.sh) as our choice of package manager. If your preference is to use other package manager (e.g. [MacPorts](https://www.macports.org)) or install it from source, we won't cover it here.

01. installing llvm (clangd is packaged with the llvm)

``` shell
$ brew install llvm
```

02. verify that your installation is successful

``` shell
$ clangd --version
```

It should print out something like this

``` shell
$ clangd version 12.0.0
```

03. Go to your VSCode and make sure to **uninstall or disable** official [C/C++ extension from Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) since this extension can have weird interaction or making some features not working properly with clangd extension.
04. Once you confirmed that C/C++ extension from Microsoft is **disabled** or **not installed**. Choose View –> Extensions, then search for “clangd” and install it.
05. At this point, clangd still won't work properly because clangd relies on a file called `compiled_command.json` which contains the information of the project should be compiled. If you navigate to the code file in VSCode now (e.g. QuantumChannel.cc), you should see errors that it does not know where `omnetpp.h` is or error indicating wrong class name.
06. In QuISP we use [GNU Make](https://www.gnu.org/software/make/) to build our project. So in order to create `compiled_command.json` we recommend using [Bear](https://github.com/rizsotto/Bear). Bear is a tool for generating compilation database which clang tools uses (including clangd).
07. Install Bear via Homebrew

``` 

$ brew install bear
```

08. Generate the compilation database `compiled_command.json`. We need to make a clean build of QuISP again. At project root.

``` 

/quisp-project-root/ $ make clean; bear -- make
```

09. After successfully rebuild QuISP, confirm that `compiled_command.json` is created successfully. The file should contain something like snippets below. It will create one compile arguments for each file as one json object in the array.

``` json
[
  {
    "arguments": [
      "/usr/local/Cellar/llvm/12.0.0/bin/clang-12",
      "-c",
      "-std=c++14",
      "-O3",
      "-DNDEBUG=1",
      "-isystem",
      "/Users/aqua/projects/omnetpp-5.6.2/tools/macosx/include",
      "-Wno-deprecated-register",
      "-Wno-unused-function",
      "-fno-omit-frame-pointer",
      "-DWITH_MPI",
      "-DXMLPARSER=libxml",
      "-DPREFER_QTENV",
      "-DWITH_QTENV",
      "-DWITH_PARSIM",
      "-DWITH_NETBUILDER",
      "-DWITH_OSG",
      "-DWITH_OSGEARTH",
      "-I.",
      "-I/usr/local/Cellar/eigen/3.3.9/include/eigen3",
      "-I/Users/aqua/projects/omnetpp-5.6.2/include",
      "-o",
      "out/clang-release//channels/QuantumChannel.o",
      "channels/QuantumChannel.cc"
    ],
    "directory": "/Users/aqua/projects/quisp/quisp",
    "file": "/Users/aqua/projects/quisp/quisp/channels/QuantumChannel.cc",
    "output": "/Users/aqua/projects/quisp/quisp/out/clang-release//channels/QuantumChannel.o"
  },
  ...
]
```

10. Navigate to code file in QuISP (e.g. QuantumChannel.cc), you should see all the errors disappear. 

### Setting up Intellisense

(TBD)
