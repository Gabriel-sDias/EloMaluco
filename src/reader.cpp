#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "reader.hpp"
using namespace std;
using namespace tinyxml2;

void Reader::fillStates()
{
	XMLDocument doc;
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
Reader::Reader(const char *archive)
{
	this->archive = archive;
	fillStates();
}

vector<string> Reader::getStates()
{
	return this->states;
}
