# Engine-Template
Template repository for any C++/OpenGL project. Uses GLFW for the context.

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

## List of features:
 - 3rdPartyLibs/cmake *>* dependencies management.
   - usage of [HunterGate](https://github.com/hunter-packages/gate) for libraries loading.
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