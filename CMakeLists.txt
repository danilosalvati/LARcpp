cmake_minimum_required (VERSION 2.5)
project (LARcpp)
#set(CMAKE_BUILD_TYPE Release)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

# Set the default CMAKE_BUILD_TYPE if not already specified
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING
       "Choose the type of build, options are: Debug Release"
       FORCE )
endif()

#Bring the headers into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(LARcpp SHARED ${SOURCES})

#Set the location for library installation -- i.e., /usr/local/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS LARcpp DESTINATION /usr/local/lib)

#Install headers
install(DIRECTORY include/ DESTINATION /usr/local/include/LARcpp)
    
#############
## TESTS
#############

# Load the tests sources and headers
include_directories(test/include)
file(GLOB TESTS "test/src/*.cpp")
    
#Generate the test executable
add_executable(testLAR ${TESTS})
target_link_libraries(testLAR LARcpp)