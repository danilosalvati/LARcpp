/*
 * LARcpp.h
 *
 *  Created on: 02 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT license https://opensource.org/licenses/MIT
 */

#ifndef INCLUDE_LARCPP_H_
#define INCLUDE_LARCPP_H_

#include <deque>
#include "Eigen/SparseCore"

namespace LAR {
//Define functions for conversions between LAR representations

class LARcpp {
public:
	Eigen::SparseMatrix<int, Eigen::RowMajor, int> brcToMatrix(
			std::deque<std::vector<int> > brcList);
};

}

#endif /* INCLUDE_LARCPP_H_ */
