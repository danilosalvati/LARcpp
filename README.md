[![Build Status](https://travis-ci.org/sadan91/LARcpp.svg?branch=master)](https://travis-ci.org/sadan91/LARcpp)

# LARcpp
## A C++ porting of the LAR library

## Installation
For compilation cmake (https://cmake.org/) is required

### Eclipse project

To import this project into eclipse open a cmd prompt into the project directory and type:

    cmake -G "Eclipse CDT4 - Unix Makefiles" ./
    
Then open Eclipse and import the project as a makefile project

### Compilation and installation

Open a cmd prompt into the project directory and type:
    
    mkdir build
    cd build
    cmake ../
    make
    sudo make install
    
The library will be installed in /usr/local/lib/libLARcpp.so

The header files will be installed under /usr/local/include
