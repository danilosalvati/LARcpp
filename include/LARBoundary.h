/*
 * LARBoundary.h
 *
 *  Created on: 02 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#ifndef INCLUDE_LARBOUNDARY_H_
#define INCLUDE_LARBOUNDARY_H_

#include "Eigen/SparseCore"
#include <deque>

namespace LAR {

// Define boundary operators
class LARBoundary {
public:
	// Function for computation of unsigned boundary for convex cells
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> convexUnsignedBoundary(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> CV,
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> FV);

	// Function for computation of boundary chain given the boundary
	// operator and the list of cells of the chain
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> larBoundaryChain(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> boundaryOperator,
			std::deque<int> chainList);

private:
	// Filter for the convexUnsignedBoundary function
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> boundaryFilter(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> FC);

	int maxRowValue(Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix,
			int row);

	// Filter for the larBoundaryChain function
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> csrBinFilter(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> boundaryChain);

};
}

#endif /* INCLUDE_LARBOUNDARY_H_ */
