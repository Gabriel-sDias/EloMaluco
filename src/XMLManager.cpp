#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XMLManager.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include <algorithm>  
#include <random>     
using namespace std;
using namespace tinyxml2;

XMLManager::XMLManager(const char *archive)
{
	this->archive = archive;
	fillStates();
}
XMLManager::XMLManager(){}

void XMLManager::fillStates()
{
	XMLDocument doc;
	XMLError result = doc.LoadFile(archive);
	if (result != XML_SUCCESS)
	{
		this->xmlError = true;
		return;
	}
	this->xmlError = false;
	XMLElement *root = doc.RootElement();
	if (root == nullptr)
	{
		std::cerr << "Error: no root element!" << std::endl;
		return;
	}

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

vector<string> XMLManager::getStates()
{
	return this->states;
}

void XMLManager::writer(array<array<string, 4>, 4>state){
	XMLDocument doc;

    XMLElement* eloMaluco = doc.NewElement("EloMaluco");
    doc.InsertFirstChild(eloMaluco);

  
    XMLElement* atualState = doc.NewElement("EstadoAtual");
    eloMaluco->InsertEndChild(atualState);

   
	for(int i = 3; i >= 0 ; i--){
    	XMLElement* row = doc.NewElement("row");
    	atualState->InsertEndChild(row);
		for(int j = 0; j<4; j++){
			XMLElement* col = doc.NewElement("col"); 
			col->SetText(state[i][j].data());
    		row->InsertEndChild(col);
		}
	}

	if (doc.SaveFile("../data/output.xml") != XML_SUCCESS) {
        std::cerr << "O jogo não pôde ser salvo!" << std::endl;
        return;
    }

    std::cout << "Jogo salvo com sucesso!" << std::endl;
    return;
}

vector<string> XMLManager::randomState(){
	vector<string> randomState ={"vms","vds","ams","brs","vmm","vdm","amm","brm","vmm","vdm","amm","bri","vmi","vdi","ami","vzo"};
	random_device rd;
    mt19937 g(rd());
    shuffle(randomState.begin(), randomState.end(), g);
	return randomState;
}

bool XMLManager::getxmlError(){
	return this->xmlError;
}
vector<string> XMLManager::getSolutionSteps(){
	return this->solutionSteps;
}
void XMLManager::solutionReader(){
	XMLDocument doc;
	XMLError result = doc.LoadFile(archive);
	if (result != XML_SUCCESS)
	{
		this->xmlError = true;
		return;
	}
	this->xmlError = false;
	XMLElement *root = doc.RootElement();
	if (root == nullptr)
	{
		std::cerr << "Error: no root element!" << std::endl;
		return;
	}
	XMLElement *steps = root->FirstChildElement("Acoes");
	if (steps == nullptr)
	{
		std::cerr << "Error: no atualState element!" << std::endl;
		return;
	}

	for (XMLElement *acoes = steps->FirstChildElement("acao"); acoes != nullptr; acoes = acoes->NextSiblingElement("acao"))
		{
			if (acoes)
			{
				const char *nextStep = acoes->GetText();
				if (nextStep)
				{
					string stepText = nextStep;
					solutionSteps.push_back(stepText);
				}
			}
		}
	
}