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
        this->chains[counter1][counter2] = i.substr(2, 3);

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

void Translator::translateToStatesInOrder(){
    int counter1 = 3;
    int counter2 = 3;
    for (string i : states)
    {
        this->statesInOrder[counter1][counter2] = i;

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
    translateToStatesInOrder();
    translateTextures();
    translateChain();
}
Translator::Translator(){}

std::array<std::array<string, 4>, 4> Translator::getStatesInOrder(){
    return this->statesInOrder;
}

std::array<std::array<string, 4>, 4> Translator::getTextures(){
    return this->textures;
}

std::array<std::array<string, 4>, 4> Translator::getChains(){
    return this->chains;
}

void Translator::findVoidFace(array<std::array<string, 4>, 4> orderOfStates){
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            if(orderOfStates[i][j] == "vzo"){
                this->vzoCubeIndex=i;
                this->vzoFaceIndex=j;
            }
        }
    }
 }

int Translator::getVzoCubeIndex(){
    return this->vzoCubeIndex;
}

int Translator::getVzoFaceIndex(){
    return this->vzoFaceIndex;
}
