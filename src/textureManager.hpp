
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP
#include <string>
#include <iostream>
#include <SOIL/SOIL.h>
#include <stdio.h>
using namespace std;

class TextureManager
{
public:
	TextureManager();
	static uint setTexture(const string& path);
};

#endif