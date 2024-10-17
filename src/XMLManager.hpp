#ifndef READER_HPP
#define READER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tinyxml2.h"
#include <stdlib.h>
#include <stdio.h>
#include <array>

using namespace std;
using namespace tinyxml2;
class XMLManager
{
private:
	vector<string> states;
	vector<string> solutionSteps;
	const char* archive;
	bool xmlError;

public:
	void fillStates();
	XMLManager(const char* directory);
	XMLManager();
	void writer(array<array<string, 4>, 4>state);
	vector<string> getStates();
	vector<string> getSolutionSteps();
	vector<string> randomState();
	bool getxmlError();
	void solutionReader();

};
#endif