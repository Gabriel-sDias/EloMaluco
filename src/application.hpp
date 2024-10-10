// Elo Maluco
// application.hpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024
#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
#include <iostream>
#include <vector>
#include <list>

#include <GL/glut.h>

#include "tinyxml2.h"
#include "Objects.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "cube.hpp"



using namespace std;

/////////////////////////////////////////////////////////////
class Application
{
public:
	Application(int argc, char** argv, std::array<std::array<glm::vec3, 4>, 4> colors);
	~Application(void);

	void draw();
	void resize(GLsizei w, GLsizei h);
	void KeyboardHandle(unsigned char key, int x, int y);
	void MouseHandle(int button, int state, int x, int y);
	void SpecialKeyHandle(int key, int x, int y);
	void update(int value, void (*func_ptr)(int));
	void keyboard(unsigned char key, int x, int y);
	void display();
	void setCamera();
	void saveState();
	void switchFace(int direction, int index);
	void drawMenu();
	void menuSelect();
	void newGame();
	void popup();
private:

	int time;
	int index;
	int faceIndex;
	bool showMenu = true;
	bool showPopup = false;
	int menuIndex=0;
	array<Cube, 4> eloMaluco;
	bool isFaceSelection;
	float cameraAngle;
	float cameraRadius; 
	std::array<std::array<glm::vec3, 4>, 4> colors;
	GLfloat xf;
	GLfloat yf;
	GLfloat win;
	GLint view_w;
	GLint view_h;

	list<Objects*> list_;

private:
	void Inicializa (void);
	bool insert_object(void);
};

#endif
