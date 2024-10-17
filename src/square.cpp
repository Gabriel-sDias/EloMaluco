#include "square.hpp"

Square::Square(glm::vec3 rightDown, glm::vec3 leftTop, string texture, float chain, glm::vec3 color)
{
    this->rightDown = rightDown;
    this->leftTop = leftTop;
    this->texture = texture;
    this->chain = chain;
    this->color = color;
}

void Square::draw()
{
    uint textureID = TextureManager::setTexture(this->texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    glColor3f(this->color.x, this->color.y, this->color.z);
    if(this->chain == 0.75){
        glTexCoord2f(0.0f, 0.75f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
        glTexCoord2f(1.0f, 0.75f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
    }
    else if(this->chain == 0.25){
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
        glTexCoord2f(1.0f, 0.25f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
        glTexCoord2f(0.0f, 0.25f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
    }
    else {
        glTexCoord2f(0.0f, 0.75f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->rightDown.z);
        glTexCoord2f(1.0f, 0.75f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->rightDown.z);
        glTexCoord2f(1.0f, 0.25f);
        glVertex3f(this->rightDown.x, this->rightDown.y, this->leftTop.z);
        glTexCoord2f(0.0f, 0.25f);
        glVertex3f(this->leftTop.x, this->leftTop.y, this->leftTop.z);
    }
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
