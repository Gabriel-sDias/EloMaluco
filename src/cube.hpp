#include <glm/glm.hpp>
#include <GL/glut.h>
#include <array>
#include "square.hpp"

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube
{
private:
    glm::vec3 basePoint;
    int size;
    std::array<glm::vec3, 4> colors;

public:
    Cube();
    Cube(glm::vec3 basePoint, int size, std::array<glm::vec3, 4> colors); 
    void draw();
    void rotate();
};


#endif