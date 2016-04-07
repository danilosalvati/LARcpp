/*
 * LARcpp.cpp
 *
 *  Created on: 04 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "LARcpp.h"

Eigen::SparseMatrix<int, Eigen::RowMajor, int> LAR::LARcpp::brcToMatrix(
		std::deque<std::vector<int> > brcList) {

	std::vector<Eigen::Triplet<int, int> > tripletList;
	int numberOfVertices = 0;
	int relationLength = brcList.size();
	for (int i = 0; i < relationLength; i++) {
		for (int j = 0; j < brcList[i].size(); j++) {
			int vert = brcList[i][j];
			if (numberOfVertices < vert) {
				numberOfVertices = vert;
			}
			tripletList.push_back(Eigen::Triplet<int, int>(i, vert, 1));
		}
	}
	numberOfVertices++;
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> result(relationLength,
			numberOfVertices);
	result.setFromTriplets(tripletList.begin(), tripletList.end());
	return result;
}

std::deque<std::vector<int> > LAR::LARcpp::matrixToBrc(
		Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix) {

	int matrixRows = matrix.outerSize();

	std::deque<std::vector<int> > result;

	for (int k = 0; k < matrix.outerSize(); ++k) {
		std::vector<int> row;
		for (Eigen::SparseMatrix<int, Eigen::RowMajor, int>::InnerIterator it(
				matrix, k); it; ++it) {
			row.push_back(it.col());
		}
		result.push_back(row);
	}
	return result;
}
