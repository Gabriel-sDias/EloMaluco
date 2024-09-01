#include "cube.hpp"
#include <array>

Cube::Cube()
{
}

Cube::Cube(glm::vec3 basePoint, int size, std::array<glm::vec3, 4> colors)
{
    this->basePoint = basePoint;
    this->size = size;
    this->colors = colors;
}

void Cube::draw()
{
    glBegin(GL_QUADS);
            // BACKFACE
            glm::vec3 rightDown = basePoint;
            glm::vec3 leftTop = basePoint + glm::vec3(size/1.0f, 0.0f, size/1.0f);
            glm::vec3 color = this->colors[3];
            Square backFace(rightDown, leftTop, color);
            backFace.draw();

            // // BOTTOMFACE
            // rightDown = basePoint + glm::vec3(0.0f, size/1.0f, 0.0f);
            // leftTop = basePoint + glm::vec3(size/1.0f, 0.0f, 0.0f);
            // color = glm::vec3(1.0f, 1.0f, 1.0f);
            // Square bottomFace(rightDown, leftTop, color);
            // bottomFace.draw();

            // RIGHTFACE
            rightDown = basePoint + glm::vec3(0.0f, size/1.0f, 0.0f);
            leftTop = basePoint + glm::vec3(0.0f, 0.0f, size/1.0f);
            color = this->colors[1];
            Square rightFace(rightDown, leftTop, color);
            rightFace.draw();

            // LEFTFACE
            rightDown = basePoint + glm::vec3(size/1.0f, 0.0f, size/1.0f);
            leftTop = basePoint + glm::vec3(size/1.0f, size/1.0f, 0.0f);
            color = this->colors[2];
            Square leftFace(rightDown, leftTop, color);
            leftFace.draw();

            // // TOPFACE
            // rightDown = basePoint + glm::vec3(-size/2.0f, size/2.0f, -size/2.0f);
            // leftTop = basePoint + glm::vec3(size/2.0f, size/2.0f, size/2.0f);
            // color = glm::vec3(0.0f, 1.0f, 1.0f);
            // Square topFace(rightDown, leftTop, color);
            // topFace.draw();

            // FRONTFACE
            rightDown = basePoint + glm::vec3(0.0f, size/1.0f, 0.0f);
            leftTop = basePoint + glm::vec3(size/1.0f, size/1.0f, size/1.0f);
            color = this->colors[0];
            Square frontFace(rightDown, leftTop, color);
            frontFace.draw();
        glEnd();
}

void Cube::rotate()
{
    glRotatef(1, 1, 1, 1);
}