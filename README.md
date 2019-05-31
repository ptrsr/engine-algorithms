# Engine Algorithms

[![Build Status](https://travis-ci.com/ptrsr/engine-algorithms.svg?branch=master)](https://travis-ci.com/ptrsr/engine-algorithms)
[![Build status](https://ci.appveyor.com/api/projects/status/pcbnu8k67ex163e0/branch/master?svg=true)](https://ci.appveyor.com/project/ptrsr/engine-algorithms/branch/master)  


## Building
### Linux
Build using:
```
mkdir build
cd build
cmake ..
make -j
```
And the binaries will be built under ``engine-algorithms/bin``.

### Windows
Create a project for your IDE using CMake and everything is automatically set up.
Note that only Visual Studio 2017 has been confirmed to work. 

## Versions
### Libraries
- **[GLM](https://github.com/g-truc/glm)**: v0.9.9.5  
- **[glbinding](https://github.com/cginternals/glbinding)**: v3.0.2  
- **[SFML](https://github.com/SFML/SFML)**: v2.5.1  
- **[Google Test](https://github.com/google/googletest)**: v1.8.1

### Build tools
- **[CMake (GUI)](https://cmake.org/download/)**: v3.5.1  

#### Linux
Built and tested on **Ubuntu** v18.04 .
- **GNU Make**: v4.1  
- **G++**: v5.5.0  

#### Windows
- **[Visual Studio](https://visualstudio.microsoft.com/downloads/)**: v15.0 (2017)

