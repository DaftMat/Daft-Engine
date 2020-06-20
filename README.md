[![Build Status](https://travis-ci.com/Stardust-Softwares/Engine-Template.svg?branch=master)](https://travis-ci.com/Stardust-Softwares/Engine-Template)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cd80344d5a064693bd3bc9e05692b60f)](https://www.codacy.com/gh/Stardust-Softwares/Engine-Template?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Stardust-Softwares/Engine-Template&amp;utm_campaign=Badge_Grade)
[![Build status](https://ci.appveyor.com/api/projects/status/h6di0wgr2grw75ll?svg=true)](https://ci.appveyor.com/project/DaftMat/engine-template)

# Engine-Template
Template repository for any C++/OpenGL project. Uses GLFW for the context.
To download this template, make sure you download the submodules as well :
```txt
$ git clone --recurse-submodules https://github.com/Stardust-Softwares/Engine-Template.git
```

## Dependencies

### As git submodules
 - [GLAD](https://github.com/Stardust-Softwares/GLAD-Includes)
 - [random](https://github.com/effolkronium/random)
 - [stb](https://github.com/nothings/stb)

### To install
 - [OpenGL/GLSL 4.4+](https://www.opengl.org/)
 - [GLM](https://github.com/g-truc/glm)
 - [Eigen3](https://eigen.tuxfamily.org/dox/)
 - [Assimp](https://github.com/assimp/assimp)
 - [spdlog](https://github.com/gabime/spdlog)
 - [GLFW3](https://github.com/glfw/glfw)
 
#### How to install deps
On linux with apt package manager :
```txt
$ sudo apt update
$ sudo apt install libomp-dev libgl1-mesa-dev libglu1-mesa-dev xorg-dev libxrandr-dev libxcb-randr0-dev libxinerama-dev libglm-dev libassimp-dev libeigen3-dev libglew-dev libglfw3-dev
```
On mac using homebrew :
```txt
$ brew update
$ brew install libomp glm eigen assimp spdlog glfw
```

## Compiling & Executing
To compile with this project configuration, run:
```txt
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Then you can go and run the project from the `bin` folder:
```txt 
$ ./<Your_Project_Name>
```

### Troubleshooting
On some distrib, the apt package `libspdlog-dev` will be outdated. 

The `cmake ..` command will then output something like that :
```txt
CMake Error at src/CMakeLists.txt:13 (find_package):
  Could not find a configuration file for package "spdlog" that is compatible
  with requested version "1".
  The following configuration files were considered but not accepted:
    /usr/lib/x86_64-linux-gnu/cmake/spdlog/spdlogConfig.cmake, version: 0.16.2
```
To solve this problem, you have to install `spdlog` *manually* by typing these commands from some download directory on your computer :
```txt
$ git clone --recurse-submodules https://github.com/gabime/spdlog.git
$ cd spdlog && mkdir build && cd build
& cmake .. && make install
```
This will install `spdlog` last version in `/usr/local/`, you'll then be able to compile the engine.
##


(the rest of this README can be deleted after the project has been setup with this template)
## List of features:
 - 3rdPartyLibs *>* dependencies management.
 - doc
   - run `./generate.sh` from /doc/ to generate any documentation.
 - scripts
   - pre-commit-hook code formatting scripts, don't forget to set them up.
 - resources/shaders
   - your engine's assets
 - src
   - your engine's sources
   
## Setting up

### Before anything else

Open the project in an IDE, then find the `TODO` list. Don't pay attention to those in `3rdPartyLibs` and `docs` the others will give you the locations where you can set your own settings. Make sure you don't forget any.

Go in the`src` folder, delete the `Minimal-Engine` and start your own !

Make sure you don't delete the `src/Core` folder, it provides useful include headers.

### Start drawing !

Now, you just have to jump into the code. Use:
```cpp
#include <Core/OpenGL.hpp>
```
wherever you want to use OpenGL, and:
```cpp
#include <Core/Random.hpp>
```
wherever you want to generate random numbers.

As well, you can inherit from `BaseApplication` and use the engine api you made to build your own windowed abstraction. Follow the guidelines described by `AppExamples`
