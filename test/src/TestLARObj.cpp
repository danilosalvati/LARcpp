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
        Eigen::SparseMatrix<int, Eigen::RowMajor, int> facesMatrix = model.second[0];
        
        REQUIRE(vectorList.size() == 8);
        REQUIRE(vectorList[0] == Eigen::Vector3f(0,0,0));
        REQUIRE(vectorList[1] == Eigen::Vector3f(1,0,0));
        REQUIRE(vectorList[2] == Eigen::Vector3f(0,1,0));
        REQUIRE(vectorList[3] == Eigen::Vector3f(1,1,0));
        REQUIRE(vectorList[4] == Eigen::Vector3f(0,0,1));
        REQUIRE(vectorList[5] == Eigen::Vector3f(1,0,1));
        REQUIRE(vectorList[6] == Eigen::Vector3f(0,1,1));
        REQUIRE(vectorList[7] == Eigen::Vector3f(1,1,1));
        
        
        REQUIRE(facesMatrix.nonZeros() == 12);
	REQUIRE(facesMatrix.rows() == 3);
	REQUIRE(facesMatrix.cols() == 8);
        
        REQUIRE(facesMatrix.coeff(0,0) == 1);
	REQUIRE(facesMatrix.coeff(0,1) == 1);
        REQUIRE(facesMatrix.coeff(0,2) == 1);
	REQUIRE(facesMatrix.coeff(0,3) == 1);
        
        REQUIRE(facesMatrix.coeff(1,4) == 1);
	REQUIRE(facesMatrix.coeff(1,5) == 1);
        REQUIRE(facesMatrix.coeff(1,6) == 1);
	REQUIRE(facesMatrix.coeff(1,7) == 1);
        
        REQUIRE(facesMatrix.coeff(2,0) == 1);
	REQUIRE(facesMatrix.coeff(2,1) == 1);
        REQUIRE(facesMatrix.coeff(2,4) == 1);
	REQUIRE(facesMatrix.coeff(2,5) == 1);

        
}
}

