#ifndef READER_HPP
#define READER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tinyxml2.h"


using namespace std;
using namespace tinyxml2;
class Reader
{
private:
	vector<string> states;
	const char* archive;
public:
	void fillStates();
	Reader(const char* directory);
	vector<string> getStates();

};
#endif