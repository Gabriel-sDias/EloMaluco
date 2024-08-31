#include "square.hpp"

Square::Square(glm::vec3 leftDown, glm::vec3 rightTop, glm::vec3 color)
{
    this->leftDown = leftDown;
    this->rightTop = rightTop;
    this->color = color;
}

void Square::draw()
{
    glColor3f(this->color.x, this->color.y, this->color.z);
    glVertex3f(this->leftDown.x, this->leftDown.y, this->leftDown.z);
    glVertex3f(this->rightTop.x, this->leftDown.y, this->leftDown.z);
    glVertex3f(this->rightTop.x, this->rightTop.y, this->leftDown.z);
    glVertex3f(this->leftDown.x, this->rightTop.y, this->leftDown.z);
}

void Square::destroy()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(this->leftDown.x, this->leftDown.y, this->leftDown.z);
    glVertex3f(this->rightTop.x, this->leftDown.y, this->leftDown.z);
    glVertex3f(this->rightTop.x, this->rightTop.y, this->leftDown.z);
    glVertex3f(this->leftDown.x, this->rightTop.y, this->leftDown.z);
}

void Square::changePosition(glm::vec3 newLeftDown, glm::vec3 newRightTop)
{
    this->destroy();
    this->leftDown = newLeftDown;
    this->rightTop = newRightTop;
    this->draw();    
}
