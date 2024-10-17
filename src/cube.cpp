#include "cube.hpp"
#include <array>

Cube::Cube()
{
}

Cube::Cube(glm::vec3 basePoint, int size, std::array<glm::vec3, 4> colors, std::array<string, 4> textures, float angle)
{
    this->basePoint = basePoint;
    this->size = size;
    this->colors = colors;
    this->angle = angle;
    this->isSelected = false;
    this->faceIndex = 0;
    this->bright = 0.4f;
    this->brightColor = glm::vec3(this->bright, this->bright, this->bright);
    this->textures = textures;
}

bool Cube::isFaceSelected(int faceIndexSelected){
    return this->isSelected && this->faceIndex == faceIndexSelected;
}

float Cube::getAngle(){
    return this->angle;
}

void Cube::setAngle(float angle){
    this->angle=angle;
}

int Cube::getFaceIndex(){
    return this->faceIndex;
}

void Cube::setFaceIndex(int faceIndex){
    this->faceIndex = faceIndex;
}

glm::vec3 Cube::getBrightColor(){
    return this->brightColor;
}

void Cube::select()
{
    this->isSelected = !this->isSelected;
}

void Cube::highlight()
{
    for (int i = 0; i < 4; i++)
    {
        this->colors[i] -= this->brightColor;
    }
}

void Cube::draw()
{
    string texturePath = "../textures/elomalucoAmarelo.png";
    // BACKFACE
    glm::vec3 rightDown = basePoint;
    glm::vec3 leftTop = basePoint + glm::vec3(size / 1.0f, 0.0f, size / 1.0f);
    glm::vec3 color = this->isFaceSelected(2) ? this->colors[2] + this->brightColor + this->brightColor : this->colors[2];
    string texture = this->textures[2];
    Square backFace(rightDown, leftTop, texture);
    backFace.draw();

    // RIGHTFACE
    rightDown = basePoint + glm::vec3(0.0f, size / 1.0f, 0.0f);
    leftTop = basePoint + glm::vec3(0.0f, 0.0f, size / 1.0f);
    color = this->isFaceSelected(1) ? this->colors[1] + this->brightColor + this->brightColor : this->colors[1];
    texture = this->textures[1];
    Square rightFace(rightDown, leftTop, texture);
    rightFace.draw();

    // LEFTFACE
    rightDown = basePoint + glm::vec3(size / 1.0f, 0.0f, size / 1.0f);
    leftTop = basePoint + glm::vec3(size / 1.0f, size / 1.0f, 0.0f);
    color = this->isFaceSelected(3) ? this->colors[3] + this->brightColor + this->brightColor : this->colors[3];
    texture = this->textures[3];
    Square leftFace(rightDown, leftTop, texture);
    leftFace.draw();

    // FRONTFACE
    rightDown = basePoint + glm::vec3(0.0f, size / 1.0f, 0.0f);
    leftTop = basePoint + glm::vec3(size / 1.0f, size / 1.0f, size / 1.0f);
    color = this->isFaceSelected(0) ? this->colors[0] + this->brightColor + this->brightColor : this->colors[0];
    texture = this->textures[0];
    Square frontFace(rightDown, leftTop, texture);
    frontFace.draw();
}

 std::array<glm::vec3, 4>Cube::getColors(){
    return this->colors;
 }





  