#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XMLManager.hpp"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <array>
using namespace std;

class Translator
{
private:
    std::array<std::array<string, 4>, 4> statesInOrder;
    std::array<std::array<string, 4>, 4> textures;
    std::array<std::array<string, 4>, 4> chains;
	vector<string> states;
    int vzoCubeIndex;
    int vzoFaceIndex;
public:

	Translator(vector<string> states);
    Translator();
    void findVoidFace(array<std::array<string, 4>, 4> orderOfStates);
    void translateToStatesInOrder();
    void translateTextures();
    void translateChain();
    int getVzoCubeIndex();
    int getVzoFaceIndex();
    std::array<std::array<string, 4>, 4> getStatesInOrder();
    std::array<std::array<string, 4>, 4> getTextures();
    std::array<std::array<string, 4>, 4> getChains();
};
#endif

