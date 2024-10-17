#include "cube.hpp"
#include <array>

Cube::Cube()
{
}

Cube::Cube(glm::vec3 basePoint, int size, std::array<string, 4> textures, std::array<float, 4> chains, float angle)
{
    this->basePoint = basePoint;
    this->size = size;
    this->angle = angle;
    this->isSelected = false;
    this->faceIndex = 0;
    this->bright = 0.5f;
    this->brightColor = glm::vec3(this->bright, this->bright, this->bright);
    this->baseColor = glm::vec3(this->bright, this->bright, this->bright);
    this->textures = textures;
    this->chains = chains;
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

void Cube::select()
{
    this->isSelected = !this->isSelected;
}

void Cube::highlight()
{
    this->baseColor += this->brightColor;
}

void Cube::unhighlight()
{
    this->baseColor -= this->brightColor;
}

void Cube::draw()
{
    // BACKFACE
    glm::vec3 rightDown = basePoint;
    glm::vec3 leftTop = basePoint + glm::vec3(size / 1.0f, 0.0f, size / 1.0f);
    glm::vec3 color = this->isFaceSelected(2) ? this->baseColor + this->brightColor : this->baseColor;
    string texture = this->textures[2];
    float chain = this->chains[2];
    Square backFace(rightDown, leftTop, texture, chain, color);
    backFace.draw();

    // RIGHTFACE
    rightDown = basePoint + glm::vec3(0.0f, size / 1.0f, 0.0f);
    leftTop = basePoint + glm::vec3(0.0f, 0.0f, size / 1.0f);
    color = this->isFaceSelected(1) ? this->baseColor + this->brightColor : this->baseColor;
    texture = this->textures[1];
    chain = this->chains[1];
    Square rightFace(rightDown, leftTop, texture, chain, color);
    rightFace.draw();

    // LEFTFACE
    rightDown = basePoint + glm::vec3(size / 1.0f, 0.0f, size / 1.0f);
    leftTop = basePoint + glm::vec3(size / 1.0f, size / 1.0f, 0.0f);
    color = this->isFaceSelected(3) ? this->baseColor + this->brightColor : this->baseColor;
    texture = this->textures[3];
    chain = this->chains[3];
    Square leftFace(leftTop, rightDown, texture, chain, color);
    leftFace.draw();

    // FRONTFACE
    rightDown = basePoint + glm::vec3(0.0f, size / 1.0f, 0.0f);
    leftTop = basePoint + glm::vec3(size / 1.0f, size / 1.0f, size / 1.0f);
    color = this->isFaceSelected(0) ? this->baseColor + this->brightColor : this->baseColor;
    texture = this->textures[0];
    chain = this->chains[0];
    Square frontFace(rightDown, leftTop, texture, chain, color);
    frontFace.draw();
}





  