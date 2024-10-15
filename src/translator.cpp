#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "translator.hpp"
#include "XMLManager.hpp"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <array>
using namespace std;


void Translator::translate(){
    int counter1 = 3;
    int counter2 = 3;
    for (string i : states)
    {
        string color = i.substr(0, 2);
        if (color == "vm")
        {
            glm::vec3 red(1.0f, 0.0f, 0.0f);
            colorsRGB[counter1][counter2] = red;
        }
        else if (color == "vd")
        {
            glm::vec3 green(0.0f, 1.0f, 0.0f);
            colorsRGB[counter1][counter2] = green;
        }
        else if (color == "am")
        {
            glm::vec3 yellow(1.0f, 1.0f, 0.0f);
            colorsRGB[counter1][counter2] = yellow;
        }
        else if (color == "br")
        {
            glm::vec3 white(1.0f, 1.0f, 1.0f);
            colorsRGB[counter1][counter2] = white;
        }
        else
        {
            glm::vec3 black(0.0f, 0.0f, 0.0f);
            colorsRGB[counter1][counter2] = black;
        }

        counter2--;
        if (counter2 < 0)
        {
            counter1--;
            counter2 = 3;
        }
    }
}
Translator::Translator(vector<string> states){
    this->states = states;
    translate();
}
Translator::Translator(){}
std::array<std::array<glm::vec3, 4>, 4> Translator::getColorsRGB(){
    return this->colorsRGB;
}

void Translator::translateRGBToState(array<std::array<glm::vec3, 4>, 4> colors, bool find){
    XMLManager saveState;
    array<array<string, 4>, 4>state;
     glm::vec3 brightColor = glm::vec3(0.4f, 0.4f, 0.4f);
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            glm::vec3 colorRGB =colors[i][j];

            string color;
            if (colorRGB == glm::vec3(1.0f, 0.0f, 0.0f) || colorRGB == (glm::vec3(1.0f, 0.0f, 0.0f)-=brightColor) )
            {   
                
                if(i == 0){
                    color ="vms";
                }else if( i == 1 || i==2){
                    color ="vmm";
                }else{
                    color ="vmi";
                }
            }
            else if (colorRGB == glm::vec3(0.0f, 1.0f, 0.0f) || colorRGB == (glm::vec3(0.0f, 1.0f, 0.0f)-=brightColor))
            {
                
                if(i == 0){
                    color ="vds";
                }else if( i == 1 || i==2){
                    color ="vdm";
                }else{
                    color ="vdi";
                }
            }
            else if (colorRGB == glm::vec3(1.0f, 1.0f, 0.0f) || colorRGB == (glm::vec3(1.0f, 1.0f, 0.0f)-=brightColor))
            {
                if(i == 0){
                    color ="ams";
                }else if( i == 1 || i==2){
                    color ="amm";
                }else{  
                    color ="ami";
                }
                
            }
            else if (colorRGB == glm::vec3(1.0f, 1.0f, 1.0f) || colorRGB == (glm::vec3(1.0f, 1.0f, 1.0f)-=brightColor))
            {
                color = "br";
                if(i == 0){
                    color ="brs";
                }else if( i == 1 || i==2){
                    color ="brm";
                }else{
                    color ="bri";
                }
            }
            else
            {
              color = "vzo";
              this->vzoCubeIndex=i;
              this->vzoFaceIndex=j;
            }
            state[i][j] = color;
        }
    }
    if(!find){
        saveState.writer(state);
    }
 }
int Translator::getVzoCubeIndex(){
    return this->vzoCubeIndex;
}
int Translator::getVzoFaceIndex(){
    return this->vzoFaceIndex;
}
