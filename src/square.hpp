#include "Objects.hpp"
#include <GL/glut.h>
#include <glm/glm.hpp>

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square
{
private:
    glm::vec3 rightDown;
    glm::vec3 leftTop;
    glm::vec3 color;

public:
    Square(glm::vec3 rightDown, glm::vec3 leftTop, glm::vec3 color); 
    void changePosition(glm::vec3 newRightDown, glm::vec3 newLeftTop);
    void draw();
    void destroy();
};

#endif 