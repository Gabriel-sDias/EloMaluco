#include "square.hpp"

Square::Square(glm::vec3 rightDown, glm::vec3 leftTop, string texture)
{
    this->rightDown = rightDown;
    this->leftTop = leftTop;
    this->texture = texture;
}

void Square::draw()
{
    uint textureID = TextureManager::setTexture(this->texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
    glEnd();
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
