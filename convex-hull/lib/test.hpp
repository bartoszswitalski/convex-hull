/*
*	Name:		test.hpp
*	Purpose:
*
*	@author
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
*/
#pragma once

#include "edge.hpp"
#include "face.hpp"
#include "generator.hpp"
#include <cassert>
#include <vector>

#define TEST_NUM 3

bool unitTests();
/* Run all tests. */

bool testPoint();

bool testEdge();

bool testFace();

bool testGenerator();