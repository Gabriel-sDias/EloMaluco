#include "Objects.hpp"
#include <GL/glut.h>
#include <glm/glm.hpp>

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square
{
private:
    glm::vec3 leftDown;
    glm::vec3 rightTop;
    glm::vec3 color;

public:
    Square(glm::vec3 leftDown, glm::vec3 rightTop, glm::vec3 color); 
    void changePosition(glm::vec3 newLeftDown, glm::vec3 newRightTop);
    void draw();
    void destroy();
};

#endif 