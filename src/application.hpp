#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include "tinyxml2.h"
#include "cube.hpp"
#include "XMLManager.hpp"
#include "translator.hpp"

using namespace std;

class Application
{
public:
	Application(int argc, char** argv, std::array<std::array<string, 4>, 4> orderOfStates, std::array<std::array<string, 4>, 4> textures, std::array<std::array<string, 4>, 4> chains);
	~Application(void);

	void draw();
	void resize(GLsizei w, GLsizei h);
	void SpecialKeyHandle(int key, int x, int y);
	void keyboard(unsigned char key, int x, int y);
	void display();
	void setCamera();
	void saveState();
	void switchFace(int direction, int index);
	void drawMenu();
	void menuSelect();
	void newGame();
	void solution();
	void showSolutionSteps(int direction);
	void checkIfIsSolve();
	bool isSolve(int sideIndex);
private:

	int time;
	int index;
	int stepsSolution;
	int faceIndex;
	int voidFace;
	bool showMenu;
	bool showSolution;
	int menuIndex;
	array<Cube, 4> eloMaluco;
	vector<array<array<string, 4>, 4>> solutionStepsTextures;
	vector<array<array<string, 4>, 4>> solutionStepsChains;
	bool isFaceSelection;
	float cameraAngle;
	float cameraRadius; 
	array<array<string, 4>, 4> orderOfStates;
	array<array<string, 4>, 4> textures;
	array<array<string, 4>, 4> chains;
	GLfloat xf;
	GLfloat yf;
	GLfloat win;

private:
	void Inicializa (void);
};

#endif
