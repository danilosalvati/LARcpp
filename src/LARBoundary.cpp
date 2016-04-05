/*
 * LARBoundary.cpp
 *
 *  Created on: 03 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "LARBoundary.h"
#include <vector>

Eigen::SparseMatrix<int, Eigen::RowMajor, int> LAR::LARBoundary::convexUnsignedBoundary(
		Eigen::SparseMatrix<int, Eigen::RowMajor, int> CV,
		Eigen::SparseMatrix<int, Eigen::RowMajor, int> FV) {

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> FC = FV * CV.transpose();

	// Return the binary sparse matrix of the boundary operator
	return boundaryFilter(FC);
}

Eigen::SparseMatrix<int, Eigen::RowMajor, int> LAR::LARBoundary::boundaryFilter(
		Eigen::SparseMatrix<int, Eigen::RowMajor, int> FC) {

	std::vector<Eigen::Triplet<int, int> > tripletList;
	int numberOfRows = FC.rows();

	Eigen::SparseMatrix<int, Eigen::RowMajor, int> result(numberOfRows,
			FC.cols());

	tripletList.reserve(numberOfRows);
	for (int k = 0; k < FC.outerSize(); ++k) {
		for (Eigen::SparseMatrix<int, Eigen::RowMajor, int>::InnerIterator it(
				FC, k); it; ++it) {
			int value = it.value();
			if (value == FC.innerVector(it.row()).nonZeros()) {
				int row = (int) it.row();
				int col = (int) it.col();
				tripletList.push_back(Eigen::Triplet<int, int>(row, col, 1));
			}
		}
	}

	result.setFromTriplets(tripletList.begin(), tripletList.end());

	return result;
}
