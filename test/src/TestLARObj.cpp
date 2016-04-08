/*
 * TestLARObj.cpp
 *
 *  Created on: 08 apr 2016
 *  Author: Salvati Danilo
 *  License: MIT License https://opensource.org/licenses/MIT
 *
 */

#include "catch.hpp"
#include "LARObj.h"

TEST_CASE( "Read and write Obj files", "[LARObj]" ) {

	LAR::IO::LARObj larObj;

	SECTION( "Read obj file" ){
	const std::string filePath = "resources/obj/test1obj.obj";
	larObj.readModel(filePath);
}
}

