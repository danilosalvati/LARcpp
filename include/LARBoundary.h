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

namespace LAR {

// Define boundary operators
class LARBoundary {
public:
	// Function for computation of unsigned boundary for convex cells
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> convexUnsignedBoundary(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> CV,
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> FV);

private:
	// Filter for the convexUnsignedBoundary function
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> boundaryFilter(
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> FC);

	int maxRowValue(Eigen::SparseMatrix<int, Eigen::RowMajor, int> matrix,
			int row);

};
}

#endif /* INCLUDE_LARBOUNDARY_H_ */
