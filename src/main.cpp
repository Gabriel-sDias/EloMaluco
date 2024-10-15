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
     std::array<std::array<glm::vec3, 4>, 4> colors = translator.getColorsRGB();
     Application app(argc,argv, colors);
     ptr_ = &app;
     
     glutDisplayFunc(draw);
     glutReshapeFunc(resize);
     glutSpecialFunc(SpecialKeyHandle);
     glutKeyboardFunc(keyboard);
     //glutTimerFunc(30,update,time);/*o update fica atualizando muito rapido e sempre reseta a tela para o estado inicial*/
     glutMainLoop();

     return 0;
}
/*
  glutKeyboardFunc(KeyboardHandle);
     glutMouseFunc(MouseHandle);
     glutSpecialFunc(SpecialKeyHandle); 
*/