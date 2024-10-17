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
    std::array<std::array<glm::vec3, 4>, 4> colorsRGB;
    std::array<std::array<string, 4>, 4> textures;
	vector<string> states;
public:

	Translator(vector<string> states);
    Translator();
    void translateRGBToState(array<std::array<glm::vec3, 4>, 4>);
    void translateColors();
    void translateTextures();
    std::array<std::array<glm::vec3, 4>, 4> getColorsRGB();
    std::array<std::array<string, 4>, 4> getTextures();
};
#endif

