/*
 * LARIO.h
 *
 *  Created on: 08 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#ifndef INCLUDE_LARIO_H_
#define INCLUDE_LARIO_H_

#include "Eigen/SparseCore"
#include <deque>

// Interface for all possible I/O classes of LARcpp
namespace LAR {
namespace IO {
class LARIO {
public:
	virtual ~LARIO() {
	}
	virtual std::pair<std::deque<Eigen::Vector3f>,
			std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > > readModel(
			std::string filePath) = 0;

	virtual void writeModel(std::deque<Eigen::Vector3f> verticesList,
			Eigen::SparseMatrix<int, Eigen::RowMajor, int> topologicalRelationship,
			std::string outputPath) = 0;
};
}
}

#endif /* INCLUDE_LARIO_H_ */
