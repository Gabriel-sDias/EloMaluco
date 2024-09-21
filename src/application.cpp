// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024

#include <stdlib.h>
#include <stdio.h>
#include <array>
#include "application.hpp"
#include "reader.hpp"
#include "translator.hpp"


///////////////////////////////////////////////////////////////////////
// Application Class
Application::Application(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ELO MALUCO");
    Inicializa();
    this->camera = 1;
}

//---------------------------------------------------------------------
Application::~Application()
{
}
//---------------------------------------------------------------------
void Application::Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    xf = 50.0f;
    yf = 50.0f;
    win = 250.0f;
    time = 0;
}

//---------------------------------------------------------------------
// void Application::DisplayFunc()
//{
//	glutDisplayFunc(Application::Desenha);
//}
//---------------------------------------------------------------------

void Application::draw()
{

    // LEGENDA DE EIXOS
    // Verde - Eixo Y
    // Azul - Eixo Z
    // Vermelho - Eixo X
    const char *directory = "../data/exemplo.xml";
    Reader r(directory);
    vector<string> states = r.getStates();
    Translator translator(states);
    std::array<std::array<glm::vec3, 4>, 4> colors = translator.getColorsRGB();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*Desenha os eixos */
    glPushMatrix();

    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();
    glPopMatrix();
/*--------- fim do desenho dos eixos ---------*/

    int size = 2;
    glm::vec3 basePoint(-1.0f, -1.0f, 0.0f);
    for (int i = 0; i < 4; i++)
    {
       glPushMatrix(); 
       glRotatef(this->eloMaluco[i].getAngle(), 0.0f, 0.0f, 1.0f); 
       this->eloMaluco[i] = Cube(basePoint + glm::vec3(0.0f, 0.0f, i * size / 1.0f), size, colors[3 - i],this->eloMaluco[i].getAngle());
       if (i == this->index) {
           this->eloMaluco[i].highlight();
       }
       this->eloMaluco[i].draw();
       glPopMatrix(); 
    }

    glFlush();
    glutSwapBuffers();
}

//---------------------------------------------------------------------
void Application::resize(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-win, win, -win, win);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLdouble)view_w / view_h, 1, 100);

    double rate = 1.2;
    gluLookAt(rate * 5, camera + rate * 10, rate * 10, 0, 0, 0, 0, 0, 1);
    
}


//---------------------------------------------------------------------
void Application::update(int value, void (*func_ptr)(int))
{
    glutPostRedisplay();
    glutTimerFunc(30, func_ptr, time);
}
//---------------------------------------------------------------------
bool Application::insert_object(void)
{
    Triangle *obj;
    // Objects * node = reinterpret_cast<Objects*>(obj);
    list_.push_back(new Triangle());
    std::cout << " insert: " << list_.size() << std::endl;

    return true;
}

void Application::keyboard(int key, int x, int y) {
    float rotationAngle = 90.0f; 

    switch (key) {
        case GLUT_KEY_LEFT:
            this->eloMaluco[this->index].setAngle(eloMaluco[this->index].getAngle() - rotationAngle);
            break;
        case GLUT_KEY_RIGHT:
            this->eloMaluco[this->index].setAngle(eloMaluco[this->index].getAngle() + rotationAngle);
            break;
        case GLUT_KEY_UP:
            if (this->index< this->eloMaluco.size() - 1) {       
                ++this->index;
            }
            break;
        case GLUT_KEY_DOWN:
            if (this->index > 0) {
                --this->index;
            }
            break;
    }

    glutPostRedisplay(); // Solicita a redrawing da tela
}

/*

//---------------------------------------------------------------------
void Application::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'W':
    case 'w':
        camera += 10;
        break;
    case 'R':
    case 'r': // muda a cor corrente para vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 'G':
    case 'g': // muda a cor corrente para verde
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 'B':
    case 'b': // muda a cor corrente para azul
        glColor3f(0.0f, 0.0f, 1.0f);
        time++;
        for (list<Objects *>::const_iterator it = list_.begin(); it != list_.end(); ++it)
        {
            (*it)->update(time);
        }
        break;
    case 27: // tecla Esc (encerra o programa)
        exit(0);
        break;
    }
}

//---------------------------------------------------------------------
void Application::MouseHandle(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // Troca o tamanho do retângulo, que vai do centro da
            // janela até a posição onde o usuário clicou com o mouse
            xf = ((2 * win * x) / view_w) - win;
            yf = (((2 * win) * (y - view_h)) / -view_h) - win;
        }
    }
}

//---------------------------------------------------------------------
void Application::SpecialKeyHandle(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        // win -= 20;
        // glMatrixMode(GL_PROJECTION);
        // glLoadIdentity();
        // gluOrtho2D (-win, win, -win, win);
        insert_object();
    }
    if (key == GLUT_KEY_DOWN)
    {
        // win += 20;
        // glMatrixMode(GL_PROJECTION);
        // glLoadIdentity();
        // gluOrtho2D (-win, win, -win, win);
    }
}*/