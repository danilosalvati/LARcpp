/*
 * TestLARBoundary.cpp
 *
 *  Created on: 04 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "catch.hpp"
#include "LARBoundary.h"
#include <iostream>

TEST_CASE( "Compute a boundary matrix", "[LARBoundary]" ) {

	LAR::LARBoundary larBoundary;

	SECTION( "Compute a 2-boundary matrix" ){
	// Building the M2 matrix
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> M2(6,8);

	M2.coeffRef(0,0) = 1;
	M2.coeffRef(0,1) = 1;
	M2.coeffRef(0,6) = 1;
	M2.coeffRef(0,7) = 1;

	M2.coeffRef(1,0) = 1;
	M2.coeffRef(1,2) = 1;
	M2.coeffRef(1,4) = 1;
	M2.coeffRef(1,6) = 1;

	M2.coeffRef(2,4) = 1;
	M2.coeffRef(2,5) = 1;
	M2.coeffRef(2,6) = 1;
	M2.coeffRef(2,7) = 1;

	M2.coeffRef(3,1) = 1;
	M2.coeffRef(3,3) = 1;
	M2.coeffRef(3,5) = 1;
	M2.coeffRef(3,7) = 1;

	M2.coeffRef(4,2) = 1;
	M2.coeffRef(4,3) = 1;
	M2.coeffRef(4,4) = 1;
	M2.coeffRef(4,5) = 1;

	M2.coeffRef(5,0) = 1;
	M2.coeffRef(5,1) = 1;
	M2.coeffRef(5,2) = 1;
	M2.coeffRef(5,3) = 1;

	REQUIRE(M2.nonZeros() == 24);
	REQUIRE(M2.rows() == 6);
	REQUIRE(M2.cols() == 8);

	// Building the M1 matrix
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> M1(12,8);

	M1.coeffRef(0,0) = 1;
	M1.coeffRef(0,1) = 1;

	M1.coeffRef(1,0) = 1;
	M1.coeffRef(1,2) = 1;

	M1.coeffRef(2,0) = 1;
	M1.coeffRef(2,6) = 1;

	M1.coeffRef(3,1) = 1;
	M1.coeffRef(3,3) = 1;

	M1.coeffRef(4,1) = 1;
	M1.coeffRef(4,7) = 1;

	M1.coeffRef(5,2) = 1;
	M1.coeffRef(5,3) = 1;

	M1.coeffRef(6,2) = 1;
	M1.coeffRef(6,4) = 1;

	M1.coeffRef(7,3) = 1;
	M1.coeffRef(7,5) = 1;

	M1.coeffRef(8,4) = 1;
	M1.coeffRef(8,5) = 1;

	M1.coeffRef(9,4) = 1;
	M1.coeffRef(9,6) = 1;

	M1.coeffRef(10,5) = 1;
	M1.coeffRef(10,7) = 1;

	M1.coeffRef(11,6) = 1;
	M1.coeffRef(11,7) = 1;

	REQUIRE(M1.nonZeros() == 24);
	REQUIRE(M1.rows() == 12);
	REQUIRE(M1.cols() == 8);

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> twoBoundary = larBoundary.convexUnsignedBoundary(M2,M1);

	REQUIRE(twoBoundary.nonZeros() == 24);
	REQUIRE(twoBoundary.rows() == 12);
	REQUIRE(twoBoundary.cols() == 6);

	REQUIRE(twoBoundary.coeff(0,0) == 1);
	REQUIRE(twoBoundary.coeff(0,5) == 1);

	REQUIRE(twoBoundary.coeff(1,1) == 1);
	REQUIRE(twoBoundary.coeff(1,5) == 1);

	REQUIRE(twoBoundary.coeff(2,0) == 1);
	REQUIRE(twoBoundary.coeff(2,1) == 1);

	REQUIRE(twoBoundary.coeff(3,3) == 1);
	REQUIRE(twoBoundary.coeff(3,5) == 1);

	REQUIRE(twoBoundary.coeff(4,0) == 1);
	REQUIRE(twoBoundary.coeff(4,3) == 1);

	REQUIRE(twoBoundary.coeff(5,4) == 1);
	REQUIRE(twoBoundary.coeff(5,5) == 1);

	REQUIRE(twoBoundary.coeff(6,1) == 1);
	REQUIRE(twoBoundary.coeff(6,4) == 1);

	REQUIRE(twoBoundary.coeff(7,3) == 1);
	REQUIRE(twoBoundary.coeff(7,4) == 1);

	REQUIRE(twoBoundary.coeff(8,2) == 1);
	REQUIRE(twoBoundary.coeff(8,4) == 1);

	REQUIRE(twoBoundary.coeff(9,1) == 1);
	REQUIRE(twoBoundary.coeff(9,2) == 1);

	REQUIRE(twoBoundary.coeff(10,2) == 1);
	REQUIRE(twoBoundary.coeff(10,3) == 1);

	REQUIRE(twoBoundary.coeff(11,0) == 1);
	REQUIRE(twoBoundary.coeff(11,2) == 1);

}

}
TEST_CASE( "Compute a boundary chain", "[LARBoundary]" ) {

	LAR::LARBoundary larBoundary;

	SECTION( "Compute the boundary chain of a complex shape" ){
	// Building the M2 matrix
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> M2(6,8);

	M2.coeffRef(0,0) = 1;
	M2.coeffRef(0,1) = 1;
	M2.coeffRef(0,6) = 1;
	M2.coeffRef(0,7) = 1;

	M2.coeffRef(1,0) = 1;
	M2.coeffRef(1,2) = 1;
	M2.coeffRef(1,4) = 1;
	M2.coeffRef(1,6) = 1;

	M2.coeffRef(2,4) = 1;
	M2.coeffRef(2,5) = 1;
	M2.coeffRef(2,6) = 1;
	M2.coeffRef(2,7) = 1;

	M2.coeffRef(3,1) = 1;
	M2.coeffRef(3,3) = 1;
	M2.coeffRef(3,5) = 1;
	M2.coeffRef(3,7) = 1;

	M2.coeffRef(4,2) = 1;
	M2.coeffRef(4,3) = 1;
	M2.coeffRef(4,4) = 1;
	M2.coeffRef(4,5) = 1;

	M2.coeffRef(5,0) = 1;
	M2.coeffRef(5,1) = 1;
	M2.coeffRef(5,2) = 1;
	M2.coeffRef(5,3) = 1;

	REQUIRE(M2.nonZeros() == 24);
	REQUIRE(M2.rows() == 6);
	REQUIRE(M2.cols() == 8);

	// Building the M1 matrix
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> M1(12,8);

	M1.coeffRef(0,0) = 1;
	M1.coeffRef(0,1) = 1;

	M1.coeffRef(1,0) = 1;
	M1.coeffRef(1,2) = 1;

	M1.coeffRef(2,0) = 1;
	M1.coeffRef(2,6) = 1;

	M1.coeffRef(3,1) = 1;
	M1.coeffRef(3,3) = 1;

	M1.coeffRef(4,1) = 1;
	M1.coeffRef(4,7) = 1;

	M1.coeffRef(5,2) = 1;
	M1.coeffRef(5,3) = 1;

	M1.coeffRef(6,2) = 1;
	M1.coeffRef(6,4) = 1;

	M1.coeffRef(7,3) = 1;
	M1.coeffRef(7,5) = 1;

	M1.coeffRef(8,4) = 1;
	M1.coeffRef(8,5) = 1;

	M1.coeffRef(9,4) = 1;
	M1.coeffRef(9,6) = 1;

	M1.coeffRef(10,5) = 1;
	M1.coeffRef(10,7) = 1;

	M1.coeffRef(11,6) = 1;
	M1.coeffRef(11,7) = 1;

	REQUIRE(M1.nonZeros() == 24);
	REQUIRE(M1.rows() == 12);
	REQUIRE(M1.cols() == 8);

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> twoBoundary = larBoundary.convexUnsignedBoundary(M2,M1);

	REQUIRE(twoBoundary.nonZeros() == 24);
	REQUIRE(twoBoundary.rows() == 12);
	REQUIRE(twoBoundary.cols() == 6);

	REQUIRE(twoBoundary.coeff(0,0) == 1);
	REQUIRE(twoBoundary.coeff(0,5) == 1);

	REQUIRE(twoBoundary.coeff(1,1) == 1);
	REQUIRE(twoBoundary.coeff(1,5) == 1);

	REQUIRE(twoBoundary.coeff(2,0) == 1);
	REQUIRE(twoBoundary.coeff(2,1) == 1);

	REQUIRE(twoBoundary.coeff(3,3) == 1);
	REQUIRE(twoBoundary.coeff(3,5) == 1);

	REQUIRE(twoBoundary.coeff(4,0) == 1);
	REQUIRE(twoBoundary.coeff(4,3) == 1);

	REQUIRE(twoBoundary.coeff(5,4) == 1);
	REQUIRE(twoBoundary.coeff(5,5) == 1);

	REQUIRE(twoBoundary.coeff(6,1) == 1);
	REQUIRE(twoBoundary.coeff(6,4) == 1);

	REQUIRE(twoBoundary.coeff(7,3) == 1);
	REQUIRE(twoBoundary.coeff(7,4) == 1);

	REQUIRE(twoBoundary.coeff(8,2) == 1);
	REQUIRE(twoBoundary.coeff(8,4) == 1);

	REQUIRE(twoBoundary.coeff(9,1) == 1);
	REQUIRE(twoBoundary.coeff(9,2) == 1);

	REQUIRE(twoBoundary.coeff(10,2) == 1);
	REQUIRE(twoBoundary.coeff(10,3) == 1);

	REQUIRE(twoBoundary.coeff(11,0) == 1);
	REQUIRE(twoBoundary.coeff(11,2) == 1);

	int values[] = {0, 1, 2, 3, 4};

	std::deque<int> brcChainList(values,
			values + sizeof(values) / sizeof(int));

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> boundaryChain = larBoundary.
	larBoundaryChain(twoBoundary,brcChainList);

	REQUIRE(boundaryChain.nonZeros() == 4);
	REQUIRE(boundaryChain.rows() == 12);
	REQUIRE(boundaryChain.cols() == 1);

	REQUIRE(boundaryChain.coeff(0,0) == 1);
	REQUIRE(boundaryChain.coeff(1,0) == 1);
	REQUIRE(boundaryChain.coeff(2,0) == 0);
	REQUIRE(boundaryChain.coeff(3,0) == 1);
	REQUIRE(boundaryChain.coeff(4,0) == 0);
	REQUIRE(boundaryChain.coeff(5,0) == 1);
	REQUIRE(boundaryChain.coeff(6,0) == 0);
	REQUIRE(boundaryChain.coeff(7,0) == 0);
	REQUIRE(boundaryChain.coeff(8,0) == 0);
	REQUIRE(boundaryChain.coeff(9,0) == 0);
	REQUIRE(boundaryChain.coeff(10,0) == 0);
	REQUIRE(boundaryChain.coeff(11,0) == 0);

}
}

