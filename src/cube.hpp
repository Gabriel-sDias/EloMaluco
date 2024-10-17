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
    std::array<string, 4> textures;
    std::array<string, 4> chains;
    float angle= 0.0f;
    bool isSelected;
    int faceIndex;
    float bright;
    glm::vec3 brightColor;
    glm::vec3 baseColor;

    bool isFaceSelected(int faceIndexSelected);

public:
    Cube();
    Cube(glm::vec3 basePoint, int size, std::array<string, 4> textures, std::array<string, 4> chains, float angle); 
    void draw();
    void highlight();
    void unhighlight();
    void select();
    float getAngle();
    void setAngle(float angle);
    int getFaceIndex();
    void setFaceIndex(int faceIndex);
};


#endif