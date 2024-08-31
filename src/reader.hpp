#ifndef READER_HPP
#define READER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tinyxml2.h>


using namespace std;
using namespace tinyxml2;
class Reader
{
private:
	XMLDocument doc;
	string fileDirectory;
	vector<string> states;
	const char* archive;

	void fillStates()
	{
		XMLError result = doc.LoadFile(archive);
		if (result != XML_SUCCESS)
		{
			std::cerr << "Error loading XML file!" << std::endl;
			return;
		}
		// Acessa o elemento raiz
		XMLElement *root = doc.RootElement();
		if (root == nullptr)
		{
			std::cerr << "Error: no root element!" << std::endl;
			return;
		}

		// Acessa o elemento "EstadoAtual"
		XMLElement *atualState = root->FirstChildElement("EstadoAtual");
		if (atualState == nullptr)
		{
			std::cerr << "Error: no atualState element!" << std::endl;
			return;
		}

		int possition1 = 0;
		int possition2 = 0;
		
		for (XMLElement *row = atualState->FirstChildElement("row"); row != nullptr; row = row->NextSiblingElement("row"))
		{
			for (XMLElement *cols = row->FirstChildElement("col"); cols != nullptr; cols = cols->NextSiblingElement("col"))
			{
				if (cols)
				{
					const char *colummState = cols->GetText();
					if (colummState)
					{
						string columm = colummState;
						states.push_back(columm);
					}
				}
			}	
		}
	}

public:
	Reader(const char* directory)
	{
		archive = directory;
		fillStates();
	}
	vector<string> getStates()
	{
		return states;
	}

};
#endif