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

void Translator::translateChain(){
    int counter1 = 3;
    int counter2 = 3;
    for (string i : states)
    {
        string color = i.substr(2, 3);
        if (color == "s")
        {
            float superior = 0.75f;
            chains[counter1][counter2] = superior;
        }
        else if (color == "m")
        {
            float median = 0.5f;
            chains[counter1][counter2] = median;
        }
        else if (color == "i")
        {
            float inferior = 0.25f;
            chains[counter1][counter2] = inferior;
        }

        counter2--;
        if (counter2 < 0)
        {
            counter1--;
            counter2 = 3;
        }
    }
}

void Translator::translateTextures(){
    int counter1 = 3;
    int counter2 = 3;
    for (string i : states)
    {
        string color = i.substr(0, 2);
        if (color == "vm")
        {
            string red = "../textures/elomalucoVermelho.png";
            textures[counter1][counter2] = red;
        }
        else if (color == "vd")
        {
            string green = "../textures/elomalucoVerde.png";
            textures[counter1][counter2] = green;
        }
        else if (color == "am")
        {
            string yellow = "../textures/elomalucoAmarelo.png";
            textures[counter1][counter2] = yellow;
        }
        else if (color == "br")
        {
            string white = "../textures/elomalucoBranco.png";
            textures[counter1][counter2] = white;
        }
        else
        {
            string black = "../textures/elomalucoPreto.png";
            textures[counter1][counter2] = black;
        }

        counter2--;
        if (counter2 < 0)
        {
            counter1--;
            counter2 = 3;
        }
    }
}

void Translator::translateColors(){
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
    translateColors();
    translateTextures();
    translateChain();
}
Translator::Translator(){}

std::array<std::array<glm::vec3, 4>, 4> Translator::getColorsRGB(){
    return this->colorsRGB;
}

std::array<std::array<string, 4>, 4> Translator::getTextures(){
    return this->textures;
}

std::array<std::array<float, 4>, 4> Translator::getChains(){
    return this->chains;
}

 void Translator::translateRGBToState(array<std::array<glm::vec3, 4>, 4> colors){
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
                if(i == 0){
                     color="vzs";
                }else if( i == 1 || i==2){
                     color="vzm";
                }else{
                     color="vzi";
                }
            }
            state[i][j] = color;
        }
    }
    saveState.writer(state);
 }