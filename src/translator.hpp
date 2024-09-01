#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "reader.hpp"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <array>
using namespace std;

class Translator
{
private:
    std::array<std::array<glm::vec3, 4>, 4> colorsRGB;
	vector<string> state;
public:

	Translator(vector<string> state);
    void translate ();
    std::array<std::array<glm::vec3, 4>, 4> getColorsRGB();
};
#endif

/*
	Vermelho = vm
	Verde = vd
	Amarelo = am
	Branco = br
	Superior = s
	Intermediario = m
	Inferior = i
*/