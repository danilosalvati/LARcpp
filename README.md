[![Build Status](https://travis-ci.org/sadan91/LARcpp.svg?branch=master)](https://travis-ci.org/sadan91/LARcpp)

# LARcpp
## A C++ porting of the LAR library

## Installation
For compilation cmake (https://cmake.org/) is required

### Eclipse project

To import this project into eclipse open a cmd prompt into the project directory and type:

    cmake -G "Eclipse CDT4 - Unix Makefiles" ./
    
Then open Eclipse and import the project as a makefile project

### Compilation and installation (Linux)

Open a cmd prompt into the project directory and type:
    
    mkdir build
    cd build
    cmake ../
    make
    sudo make install
    
The library will be installed in /usr/lib/libLARcpp.so

The header files will be installed under /usr/include

### Compilation and installation (MacOsX)

Open a cmd prompt into the project directory and type:
    
    mkdir build
    cd build
    
Now open the cmake-gui and select the source code directory (is the project directory) and the build directory (which is the one created above). Press configure and then generate.
At this point using the previous cmd prompt inside the build directory type:

    xcodebuild      -project LARcpp.xcodeproj -target ALL_BUILD  -configuration Release
    sudo xcodebuild -project LARcpp.xcodeproj -target install    -configuration Release
    
The library will be installed in /usr/lib/libLARcpp.so

The header files will be installed under /usr/include

