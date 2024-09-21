// Elo Maluco
// main.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024



#include <iostream>
#include <thread>

#include "wraps.hpp"
#include "application.hpp"

     
// Programa Principal 
int main(int argc, char** argv)
{
     int time=0;

     Application app(argc,argv);
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