/*
 * LARcpp.cpp
 *
 *  Created on: 04 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "catch.hpp"
#include "LARcpp.h"

TEST_CASE( "Convert a BRC list into a characteristic matrix", "[LARcpp]" ) {

	LAR::LARcpp larcpp;

	SECTION( "Building a matrix with two squares" ){

	// Building a brc list defining a topology
	int values1[] = {0, 1, 2, 3};
	std::vector<int> vector1(values1, values1 + sizeof(values1) / sizeof(int));

	int values2[] = {2, 3, 4, 5};
	std::vector<int> vector2(values2, values2 + sizeof(values2) / sizeof(int));

	std::vector<int> vectors[] = {vector1, vector2};
	std::deque<std::vector<int> > brcList(vectors,
			vectors + sizeof(vectors) / sizeof(std::vector<int>));

	REQUIRE(vector1.size() == 4);
	REQUIRE(vector2.size() == 4);
	REQUIRE(brcList.size() == 2);

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix = larcpp.brcToMatrix(brcList);
	REQUIRE(matrix.nonZeros() == 8);
	REQUIRE(matrix.rows() == 2);
	REQUIRE(matrix.cols() == 6);

	REQUIRE(matrix.coeff(0,0) == 1);
	REQUIRE(matrix.coeff(0,1) == 1);
	REQUIRE(matrix.coeff(0,2) == 1);
	REQUIRE(matrix.coeff(0,3) == 1);
	REQUIRE(matrix.coeff(0,4) == 0);
	REQUIRE(matrix.coeff(0,5) == 0);

	REQUIRE(matrix.coeff(1,0) == 0);
	REQUIRE(matrix.coeff(1,1) == 0);
	REQUIRE(matrix.coeff(1,2) == 1);
	REQUIRE(matrix.coeff(1,3) == 1);
	REQUIRE(matrix.coeff(1,4) == 1);
	REQUIRE(matrix.coeff(1,5) == 1);
}

	SECTION( "Building a matrix with cells of different sizes" ){

	// Building a brc list defining a topology
	int values1[] = {0, 1, 2};
	std::vector<int> vector1(values1, values1 + sizeof(values1) / sizeof(int));

	int values2[] = {1, 2, 3, 4};
	std::vector<int> vector2(values2, values2 + sizeof(values2) / sizeof(int));

	int values3[] = {1, 4, 5, 6, 7};
	std::vector<int> vector3(values3, values3 + sizeof(values3) / sizeof(int));

	std::vector<int> vectors[] = {vector1, vector2, vector3};
	std::deque<std::vector<int> > brcList(vectors,
			vectors + sizeof(vectors) / sizeof(std::vector<int>));

	REQUIRE(vector1.size() == 3);
	REQUIRE(vector2.size() == 4);
	REQUIRE(vector3.size() == 5);
	REQUIRE(brcList.size() == 3);

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix = larcpp.brcToMatrix(brcList);
	REQUIRE(matrix.nonZeros() == 12);
	REQUIRE(matrix.rows() == 3);
	REQUIRE(matrix.cols() == 8);

	REQUIRE(matrix.coeff(0,0) == 1);
	REQUIRE(matrix.coeff(0,1) == 1);
	REQUIRE(matrix.coeff(0,2) == 1);
	REQUIRE(matrix.coeff(0,3) == 0);
	REQUIRE(matrix.coeff(0,4) == 0);
	REQUIRE(matrix.coeff(0,5) == 0);
	REQUIRE(matrix.coeff(0,6) == 0);
	REQUIRE(matrix.coeff(0,7) == 0);

	REQUIRE(matrix.coeff(1,0) == 0);
	REQUIRE(matrix.coeff(1,1) == 1);
	REQUIRE(matrix.coeff(1,2) == 1);
	REQUIRE(matrix.coeff(1,3) == 1);
	REQUIRE(matrix.coeff(1,4) == 1);
	REQUIRE(matrix.coeff(1,5) == 0);
	REQUIRE(matrix.coeff(1,6) == 0);
	REQUIRE(matrix.coeff(1,7) == 0);

	REQUIRE(matrix.coeff(2,0) == 0);
	REQUIRE(matrix.coeff(2,1) == 1);
	REQUIRE(matrix.coeff(2,2) == 0);
	REQUIRE(matrix.coeff(2,3) == 0);
	REQUIRE(matrix.coeff(2,4) == 1);
	REQUIRE(matrix.coeff(2,5) == 1);
	REQUIRE(matrix.coeff(2,6) == 1);
	REQUIRE(matrix.coeff(2,7) == 1);
}
}

TEST_CASE( "Convert a characteristic matrix into a BRC list", "[LARcpp]" ) {

	LAR::LARcpp larcpp;

	SECTION( "Building list from a matrix of two squares" ){

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix(2,6);

	matrix.coeffRef(0,0) = 1;
	matrix.coeffRef(0,1) = 1;
	matrix.coeffRef(0,2) = 1;
	matrix.coeffRef(0,3) = 1;

	matrix.coeffRef(1,2) == 1;
	matrix.coeffRef(1,3) == 1;
	matrix.coeffRef(1,4) == 1;
	matrix.coeffRef(1,5) == 1;

	std::deque<std::vector<int> > brcList = larcpp.matrixToBrc(matrix);

	REQUIRE(brcList.size() == 2);
	REQUIRE(brcList[0].size() == 4);
	REQUIRE(brcList[1].size() == 4);

	int values1[] = {0, 1, 2, 3};
	std::vector<int> vector1(values1, values1 + sizeof(values1) / sizeof(int));

	int values2[] = {2, 3, 4, 5};
	std::vector<int> vector2(values2, values2 + sizeof(values2) / sizeof(int));

	REQUIRE(brcList[0] == vector1);
	REQUIRE(brcList[1] == vector2);

}

	SECTION( "Building list from a matrix with cells of different sizes" ){

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix(3,8);

	matrix.coeffRef(0,0) = 1;
	matrix.coeffRef(0,1) = 1;
	matrix.coeffRef(0,2) = 1;

	matrix.coeffRef(1,1) = 1;
	matrix.coeffRef(1,2) = 1;
	matrix.coeffRef(1,3) = 1;
	matrix.coeffRef(1,4) = 1;

	matrix.coeffRef(2,1) = 1;
	matrix.coeffRef(2,4) = 1;
	matrix.coeffRef(2,5) = 1;
	matrix.coeffRef(2,6) = 1;
	matrix.coeffRef(2,7) = 1;

	std::deque<std::vector<int> > brcList = larcpp.matrixToBrc(matrix);

	REQUIRE(brcList.size() == 3);
	REQUIRE(brcList[0].size() == 3);
	REQUIRE(brcList[1].size() == 4);
	REQUIRE(brcList[2].size() == 5);

	int values1[] = {0, 1, 2};
	std::vector<int> vector1(values1, values1 + sizeof(values1) / sizeof(int));

	int values2[] = {1, 2, 3, 4};
	std::vector<int> vector2(values2, values2 + sizeof(values2) / sizeof(int));

	int values3[] = {1, 4, 5, 6, 7};
	std::vector<int> vector3(values3, values3 + sizeof(values3) / sizeof(int));

	REQUIRE(brcList[0] == vector1);
	REQUIRE(brcList[1] == vector2);
	REQUIRE(brcList[2] == vector3);

}
}

