// Elo Maluco
// main.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024



#include <iostream>
#include <thread>
#include "XMLManager.hpp"
#include "translator.hpp"
#include "wraps.hpp"
#include "application.hpp"

     
// Programa Principal 
int main(int argc, char** argv)
{
     int time=0;
     const char *directory = "../data/solution.xml";
     XMLManager r(directory);
     vector<string> states = r.getStates();
     Translator translator(states);
     std::array<std::array<string, 4>, 4> orderOfStates = translator.getStatesInOrder();
     std::array<std::array<string, 4>, 4> textures = translator.getTextures();
     std::array<std::array<string, 4>, 4> chains = translator.getChains();

     Application app(argc,argv, orderOfStates, textures, chains);
     ptr_ = &app;

     
     glutDisplayFunc(draw);
     glutReshapeFunc(resize);
     glutSpecialFunc(SpecialKeyHandle);
     glutKeyboardFunc(keyboard);
     glutMainLoop();

     return 0;
}

/*
  glutKeyboardFunc(KeyboardHandle);
     glutMouseFunc(MouseHandle);
     glutSpecialFunc(SpecialKeyHandle); 
*/