#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XMLManager.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <array>
using namespace std;
using namespace tinyxml2;

void XMLManager::fillStates()
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
XMLManager::XMLManager(const char *archive)
{
	this->archive = archive;
	fillStates();
}
XMLManager::XMLManager(){}

vector<string> XMLManager::getStates()
{
	return this->states;
}

void XMLManager::writer(array<array<string, 4>, 4>state){
	XMLDocument doc;

   
    XMLElement* eloMaluco = doc.NewElement("EloMaluco");
    doc.InsertFirstChild(eloMaluco);

  
    XMLElement* atualState = doc.NewElement("estadoAtual");
    eloMaluco->InsertEndChild(atualState);

   
	for(int i = 0; i<4; i++){
    	XMLElement* row = doc.NewElement("row");
    	atualState->InsertEndChild(row);
		for(int j = 0; j<4; j++){
			XMLElement* col = doc.NewElement("col"); 
			col->SetText(state[i][j].data());
    		row->InsertEndChild(col);
		}
	}

	if (doc.SaveFile("output.xml") != XML_SUCCESS) {
        std::cerr << "Error saving XML file!" << std::endl;
        return;
    }

    std::cout << "XML file created successfully!" << std::endl;
    return;
}
