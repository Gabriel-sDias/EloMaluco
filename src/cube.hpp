#include <glm/glm.hpp>
#include <GL/glut.h>
#include "square.hpp"

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube
{
private:
    glm::vec3 basePoint;
    int size;

public:
    Cube(glm::vec3 basePoint, int size); 
    void draw();
    void rotate();
};


#endif