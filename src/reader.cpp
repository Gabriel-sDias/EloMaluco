
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
	string initialState;
	string finallState;

	void fillStates(string archive)
	{
		XMLError result = doc.LoadFile("exemplo.xml");
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

		// Acessa o elemento "person"
		XMLElement *humans = root->FirstChildElement("humans");
		if (humans == nullptr)
		{
			std::cerr << "Error: no humans element!" << std::endl;
			return;
		}

		int possition1 = 0;
		int possition2 = 0;
		
		for (XMLElement *person = humans->FirstChildElement("person"); person != nullptr; person = person->NextSiblingElement("person"))
		{
			for (XMLElement *names = person->FirstChildElement("name"); names != nullptr; names = names->NextSiblingElement("name"))
			{
				if (names)
				{
					const char *name = names->GetText();
					if (name)
					{
						std::cout << "Name: " << name << ", Counter: " << possition2 << std::endl;
					}
				}
				possition2++;
			}
			possition1++;
		}
	}

public:
	Reader(string directory)
	{
		fileDirectory = directory;
		fillStates(fileDirectory);
	}
	vector<string> getStates()
	{
		return states;
	}
	string getInitialState()
	{
		return initialState;
	}
	string getFinalState()
	{
		return finallState;
	}
};

int main()
{
	string directory = "exemplo.xml";
	Reader reader(directory);
}