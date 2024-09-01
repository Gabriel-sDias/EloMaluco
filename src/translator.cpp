#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "reader.hpp"
#include <glm/glm.hpp>
#include <array>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Translator
{
private:

	vector<string> colors;
    vector<glm::vec3> colorsRGB;
    std::array<std::array<glm::vec3, 4>, 4> colorsBGR;

    void translate (vector<string> colors){
        int counter1, counter2 = 0;

        for(string i: colors){
           string color = i.substr(0, 2);
           if(color == "vm"){
               glm::vec3 red(1.0f, 0.0f, 0.0f);
               colorsBGR [counter1][counter2] = red; 
               colorsRGB.push_back(red);
           }
           else if(color == "vd"){
               glm::vec3 green(0.0f, 1.0f, 0.0f);
               colorsBGR [counter1][counter2] = green;
               colorsRGB.push_back(green);
           }
           else if(color == "am"){
               glm::vec3 yellow(1.0f, 1.0f, 0.0f);
               colorsBGR [counter1][counter2] = yellow;
               colorsRGB.push_back(yellow);
           }
           else{
               glm::vec3 white(1.0f, 1.0f, 1.0f);
               colorsBGR [counter1][counter2] = white;
               colorsRGB.push_back(white);
           }
           if(counter2 == 3){
                counter1++;
                counter2 = 0;
            }
            counter2++;
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
    std::array<std::array<glm::vec3, 4>, 4> getColors(){
        return colorsBGR;
    } 
};



/*
	Vermelho = vm
	Verde = vd
	Amarelo = am
	Branco = br
	Superior = s
	Intermediario = m
	Inferior = i
*/