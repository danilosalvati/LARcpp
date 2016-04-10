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
	const std::string filePath2 = "../test/resources/obj/test1obj.obj";// For Travis testing

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
	SECTION( "Error reading file" ){
	REQUIRE_THROWS(larObj.readModel("fileNotExists.obj"));
}

	SECTION( "Write obj file" ){

	Eigen::Vector3f vector1 = Eigen::Vector3f(0,0,0);
	Eigen::Vector3f vector2 = Eigen::Vector3f(0,1,0);
	Eigen::Vector3f vector3 = Eigen::Vector3f(1,1,0);
	Eigen::Vector3f vector4 = Eigen::Vector3f(1,0,0);
	Eigen::Vector3f vector5 = Eigen::Vector3f(2,0,0);
	Eigen::Vector3f vector6 = Eigen::Vector3f(2,1,0);

	Eigen::Vector3f vectors[] = {vector1, vector2, vector3, vector4, vector5, vector6};

	std::deque<Eigen::Vector3f> verticesList(vectors,
			vectors + sizeof(vectors) / sizeof(Eigen::Vector3f));

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix(2,6);

	matrix.coeffRef(0,0) = 1;
	matrix.coeffRef(0,1) = 1;
	matrix.coeffRef(0,2) = 1;
	matrix.coeffRef(0,3) = 1;

	matrix.coeffRef(1,2) = 1;
	matrix.coeffRef(1,3) = 1;
	matrix.coeffRef(1,4) = 1;
	matrix.coeffRef(1,5) = 1;

	std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > topologicalRelationships;
	topologicalRelationships.push_back(matrix);

	larObj.writeModel(verticesList, topologicalRelationships, "model.obj");

	std::pair<std::deque<Eigen::Vector3f>,
	std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > > model = larObj.readModel("model.obj");

	REQUIRE(model.first == verticesList);

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> faces = model.second[0];

	REQUIRE(faces.nonZeros() == matrix.nonZeros());
	REQUIRE(faces.rows() == matrix.rows());
	REQUIRE(faces.cols() == matrix.cols());

	REQUIRE(faces.coeff(0,0) == matrix.coeff(0,0));
	REQUIRE(faces.coeff(0,1) == matrix.coeff(0,1));
	REQUIRE(faces.coeff(0,2) == matrix.coeff(0,2));
	REQUIRE(faces.coeff(0,3) == matrix.coeff(0,3));

	REQUIRE(faces.coeff(1,4) == matrix.coeff(1,4));
	REQUIRE(faces.coeff(1,5) == matrix.coeff(1,5));
	REQUIRE(faces.coeff(1,6) == matrix.coeff(1,6));
	REQUIRE(faces.coeff(1,7) == matrix.coeff(1,7));

	remove("model.obj");

}
}

