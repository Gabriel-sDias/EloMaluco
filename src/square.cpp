#include "square.hpp"

Square::Square(glm::vec3 rightDown, glm::vec3 leftTop, glm::vec3 color)
{
    this->rightDown = rightDown;
    this->leftTop = leftTop;
    this->color = color;
}

void Square::draw()
{
    glColor3f(this->color.x, this->color.y, this->color.z);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
}

void Square::destroy()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
}

void Square::changePosition(glm::vec3 newRightDown, glm::vec3 newLeftTop)
{
    this->destroy();
    this->rightDown = newRightDown;
    this->leftTop = newLeftTop;
    this->draw();    
}
