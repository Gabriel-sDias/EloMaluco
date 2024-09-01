#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "translator.hpp"
#include "reader.hpp"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <array>
using namespace std;


void Translator::translate(){
    int counter1 = 0;
    int counter2 = 0;
    for (string i : state)
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

        counter2++;
        if (counter2 > 3)
        {
            counter1++;
            counter2 = 0;
        }
    }
}
Translator::Translator(vector<string> state){
    this->state = state;
    translate();
}
std::array<std::array<glm::vec3, 4>, 4> Translator::getColorsRGB(){
    return this->colorsRGB;
}

