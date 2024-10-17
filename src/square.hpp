#include "Objects.hpp"
#include "textureManager.hpp"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <string>
using namespace std;

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square
{
private:
    glm::vec3 rightDown;
    glm::vec3 leftTop;
    string texture;

public:
    Square(glm::vec3 rightDown, glm::vec3 leftTop, string texture); 
    void changePosition(glm::vec3 newRightDown, glm::vec3 newLeftTop);
    void draw();
    void destroy();
};

#endif 