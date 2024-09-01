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
    std::array<std::array<glm::vec3, 4>, 4> colorsRGB;

    void translate (vector<string> colors){
        int counter1 = 0; 
        int counter2 = 0;

        for(string i: colors){
           string color = i.substr(0, 2);
           if(color == "vm"){
               glm::vec3 red(1.0f, 0.0f, 0.0f);
               colorsRGB [counter1][counter2] = red; 
           }
           else if(color == "vd"){
               glm::vec3 green(0.0f, 1.0f, 0.0f);
               colorsRGB [counter1][counter2] = green;
           }
           else if(color == "am"){
               glm::vec3 yellow(1.0f, 1.0f, 0.0f);
               colorsRGB [counter1][counter2] = yellow;
           }
           else{
               glm::vec3 white(1.0f, 1.0f, 1.0f);
               colorsRGB [counter1][counter2] = white;
           }

            counter2++;
           if(counter2 > 3){
                counter1++;
                counter2 = 0;
            }
           
        }
    }
	
public:
	Translator(vector<string> colors)
	{
		translate(colors);
	}
    std::array<std::array<glm::vec3, 4>, 4> getColorsRGB(){
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