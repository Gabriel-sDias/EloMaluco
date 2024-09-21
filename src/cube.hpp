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
    float angle= 0.0f;
    bool isSelected;

public:
    Cube();
    Cube(glm::vec3 basePoint, int size, std::array<glm::vec3, 4> colors, float angle); 
    void draw();
    void highlight();
    float getAngle();
    void setAngle(float angle);
    void rotate();
};


#endif