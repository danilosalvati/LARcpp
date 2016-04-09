/*
 * TestLARObj.cpp
 *
 *  Created on: 08 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "catch.hpp"
#include "IOInterfaces/LARObj.h"
#include <sys/stat.h>
#include <iostream>

TEST_CASE( "Read and write Obj files", "[LARObj]" ) {

	LAR::IO::LARObj larObj;

	SECTION( "Read obj file" ){
        const std::string filePath1 = "test/resources/obj/test1obj.obj"; // For Eclipse testing
        const std::string filePath2 = "../test/resources/obj/test1obj.obj"; // For Travis testing
        
        std::pair<std::deque<Eigen::Vector3f>, 
            std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > > model;
        
        struct stat buffer;
        if (stat (filePath1.c_str(), &buffer) == 0) {
            model = larObj.readModel(filePath1);
        } else {
            model = larObj.readModel(filePath2);
        }
        
        std::deque<Eigen::Vector3f> vectorList = model.first;
        std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > facesList = model.second;
        
        std::cout << vectorList[1];
        
        REQUIRE(vectorList.size() == 6);
        REQUIRE(vectorList[0] == Eigen::Vector3f(0,0,1));
}
}

