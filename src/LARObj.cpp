/*
 * LARObj.cpp
 *
 *  Created on: 08 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */
#include "IOInterfaces/LARObj.h"
#include "LARcpp.h"
#include <iostream>

std::pair<std::deque<Eigen::Vector3f>,
		std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > > LAR::IO::LARObj::readModel(
		std::string filePath) {

	std::string line;
	std::ifstream myfile(filePath);

	std::deque<Eigen::Vector3f> vectorList;
	std::deque<Eigen::SparseMatrix<int, Eigen::RowMajor, int> > relationships;
	std::deque<std::vector<int> > facesList;
	if (myfile.is_open()) {
		std::vector<std::string> tokens;
		while (getline(myfile, line)) {
			tokens = tokenize(line);
			if (tokens[0] == "v") {
				// I am reading a vertex line
				vectorList.push_back(
						Eigen::Vector3f(tokens[1], tokens[2], tokens[3]));
			} else {
				// I am reading a face line
				facesList.push_back(
						vector<int>(tokens[1], tokens[2], tokens[3]));
			}
			myfile.close();
		}
	} else {
		throw "Unable to open file " + filePath;
	}

	LAR::LARcpp larcpp;
	relationships.push_back(larcpp.brcToMatrix(facesList));
	return std::pair(vectorList, relationships);
}

void LAR::IO::LARObj::writeModel(std::deque<Eigen::Vector3f> verticesList,
		Eigen::SparseMatrix<int, Eigen::RowMajor, int> topologicalRelationship,
		std::string outputPath);

/** tokenizer function for strings **/
std::vector<std::string> LAR::IO::LARObj::tokenize(const std::string& str,
		const std::string& delimiters = " ") {

	std::vector<std::string> tokens;

	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
	return tokens;
}

