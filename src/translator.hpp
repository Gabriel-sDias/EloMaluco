#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "reader.hpp"
#include <glm/glm.hpp>
using namespace std;

class Translator
{
private:

	vector<string> colors;
    vector<glm::vec3> colorsRGB;

    void translate (vector<string> colors){ 
        for(string i: colors){
           string color = i.substr(0, 2);
           if(color == "vm"){
               glm::vec3 red(1.0f, 0.0f, 0.0f);
               colorsRGB.push_back(red);
           }
           else if(color == "vd"){
               glm::vec3 green(0.0f, 1.0f, 0.0f);
               colorsRGB.push_back(green);
           }
           else if(color == "am"){
               glm::vec3 yellow(1.0f, 1.0f, 0.0f);
               colorsRGB.push_back(yellow);
           }
           else{
               glm::vec3 white(1.0f, 1.0f, 1.0f);
               colorsRGB.push_back(white);
           }
        }
    }
	
public:
	Translator(vector<string> colors)
	{
		translate(colors);
	}
	
    vector<glm::vec3> getColorsRGB(){
        return colorsRGB;
    }
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