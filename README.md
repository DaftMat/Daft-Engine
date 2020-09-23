# Daft-Engine
Cross platform 3D Engine-Editor made in C++/OpenGL/Qt.

To download this template, make sure you download the submodules as well :
```txt
$ git clone --recurse-submodules https://github.com/DaftMat/Daft-Engine.git
```

## Dependencies

### As git submodules
 - [GLAD](https://github.com/Stardust-Softwares/GLAD-Includes)
 - [random](https://github.com/effolkronium/random)
 - [stb](https://github.com/nothings/stb)
 - [ConvexHull3D](https://github.com/leomccormack/convhull_3d)

### To install
 - [OpenGL/GLSL](https://www.opengl.org/)
 - [GLM](https://github.com/g-truc/glm)
 - [Eigen3](https://eigen.tuxfamily.org/dox/)
 - [Assimp](https://github.com/assimp/assimp)
 - [Qt5](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5)
 
#### How to install deps
**Note:** For Qt5, use the link above to install it on windows or linux.

###
On **linux** using apt package manager :
```txt
$ sudo apt update
$ sudo apt install libomp-dev libgl1-mesa-dev libglu1-mesa-dev xorg-dev libxrandr-dev libxcb-randr0-dev libxinerama-dev libglm-dev libassimp-dev libeigen3-dev libglew-dev
```

On **mac** using homebrew :
```txt
$ brew update
$ brew install libomp glm eigen assimp qt
```

On **windows** using vcpkg (make sure vcpkg is [updated](https://vcpkg.readthedocs.io/en/latest/about/faq/#how-do-i-update-libraries)) :
```txt
$ vcpkg install glm:x64-windows eigen3:x64-windows assimp:x64-windows
$ vcpkg integrate install
```
**Note:** the command vcpkg integrate install will give you a path to the vcpkg toolchain, copy this path.

## Compiling & Executing
You can choose the OpenGL version you want to use by setting the variable `GLAD_VERSION` to it (from `gl33core` to `gl46core`).
If you don't specify a version, it's on `gl46core` by default.
### Compiling on Linux/MacOSX
```txt
$ mkdir build
$ cd build
$ cmake [-DGLAD_VERSION="glXYcore"] ..
$ make
```
### Compiling on Windows (from powershell)
```txt
$ mkdir build
$ cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" [-DGLAD_VERSION="glXYcore"] -G "Visual Studio 16 2019" -A x64 ..
$ cmake --build .
```
**Note:** you can use the path you copied before, but make sure the *format* is the same as before.
### Executing
Then you can go and run the project from the `bin/Release` (or `bin/Debug`) folder:
```txt 
$ ./DaftEngineApp
```

### Troubleshooting
#### Qt5 not found

For some reasons, Qt5 could be not found by cmake, which will output the following error:
```txt
Could not find a package configuration file provided by "Qt5" with any of
the following names:
    Qt5Config.cmake
    qt5-config.cmake
Add the installation prefix of "Qt5" to CMAKE_PREFIX_PATH or set "Qt5_DIR"
to a directory containing one of the above files.  If "Qt5" provides a
separate development package or SDK, be sure it has been installed.
```
The problem is solved by setting the cmake variable `Qt5_DIR` to the installation directory of Qt5.

The cmake command will then look like this:

- On **linux**:
```txt
$ cmake -DQt5_DIR="/path/to/Qt/5.x.y/gcc_64/" ..
```

- On **macos**:
```txt
$ cmake -DCMAKE_PREFIX_PATH="/usr/local/otp/qt/lib/cmake" ..
```

- On **windows**:
```txt
$ set Qt5_DIR="C:\path\to\qt\5.x.y\msvc2019_64"
$ cmake -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -G "Visual Studio 16 2019" -A x64 ..
```

## Continuous Integration
Continuous Integration and automated code review is active on this project :

| Application | Status |
| --- | --- |
| Travis | [![Build Status](https://travis-ci.com/DaftMat/Daft-Engine.svg?branch=master)](https://travis-ci.com/github/DaftMat/Daft-Engine) |
| Appveyor | [![Build status](https://ci.appveyor.com/api/projects/status/3owhtorag4mh6ox4?svg=true)](https://ci.appveyor.com/project/DaftMat/daft-engine) |
| Codacy | [![Codacy Badge](https://app.codacy.com/project/badge/Grade/b3aff8818ac34bb3a9c6a7b90fff2b9c)](https://www.codacy.com/manual/DaftMat/Daft-Engine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DaftMat/Daft-Engine&amp;utm_campaign=Badge_Grade) |