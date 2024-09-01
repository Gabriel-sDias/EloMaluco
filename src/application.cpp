// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024

#include <stdlib.h>
#include <stdio.h>
#include <array>
#include "application.hpp"


///////////////////////////////////////////////////////////////////////
// Application Class
Application::Application(int argc, char** argv)
{
	
	glutInit(&argc,argv);
     	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     	glutInitWindowSize(500,500);
   	glutInitWindowPosition(100,100);
   	glutCreateWindow("ELO MALUCO");
	Inicializa();

	
}

//---------------------------------------------------------------------
Application::~Application()
{
}
//---------------------------------------------------------------------
void Application::Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    xf=50.0f;
    yf=50.0f;
    win=250.0f;
    time = 0;
}


//---------------------------------------------------------------------
//void Application::DisplayFunc()
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
    glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
                   
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glPushMatrix();

	glLineWidth(3.0f);

        glBegin(GL_LINES);
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(10,0,0);
        glEnd();
       glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(0,10,0);
        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(0,0,10);
        glEnd();
    	glPopMatrix();

        int size = 2;
        glm::vec3 basePoint(0.0f, 0.0f, 0.0f);
        std::array<std::array<glm::vec3, 4>, 4> array2D;

        // Initialize the array
        array2D[0][0] = glm::vec3(0.0f, 0.0f, 0.0f); // yellow
        array2D[0][1] = glm::vec3(0.0f, 1.0f, 0.0f); // green
        array2D[0][2] = glm::vec3(1.0f, 1.0f, 1.0f); // white
        array2D[0][3] = glm::vec3(0.0f, 0.0f, 1.0f); // blue

        array2D[1][0] = glm::vec3(1.0f, 0.0f, 0.0f); // red
        array2D[1][1] = glm::vec3(0.0f, 0.0f, 1.0f); // blue
        array2D[1][2] = glm::vec3(0.0f, 1.0f, 1.0f); // cyan
        array2D[1][3] = glm::vec3(1.0f, 0.0f, 1.0f); // magenta

        array2D[2][0] = glm::vec3(0.0f, 1.0f, 0.0f); // green
        array2D[2][1] = glm::vec3(1.0f, 0.0f, 0.0f); // red
        array2D[2][2] = glm::vec3(1.0f, 1.0f, 1.0f); // white
        array2D[2][3] = glm::vec3(0.0f, 0.0f, 1.0f); // blue

        array2D[3][0] = glm::vec3(0.0f, 0.0f, 1.0f); // blue
        array2D[3][1] = glm::vec3(1.0f, 1.0f, 0.0f); // yellow
        array2D[3][2] = glm::vec3(1.0f, 0.0f, 0.0f); // red
        array2D[3][3] = glm::vec3(0.0f, 1.0f, 0.0f); // green

        array<Cube, 4> eloMaluco;
        for(int i = 0; i < 4; i++)
        {
            eloMaluco[i] = Cube(basePoint+glm::vec3(0.0f, 0.0f, i*size/1.0f), size, array2D[i]);
            eloMaluco[i].draw();
        }

        // TODO: Transform this into a face of the cube
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 4*size/1.0f);
        glVertex3f(size, 0.0f, 4*size/1.0f); // rightdown
        glVertex3f(size, size, 4*size/1.0f);
        glVertex3f(0.0f, size, 4*size/1.0f); // lefttop
        glEnd();

        
    glPopMatrix();

      for(list<Objects*>::const_iterator it = list_.begin(); it != list_.end(	) ;  ++it)
      {
    	   (*it)->draw();
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
    gluOrtho2D (-win, win, -win, win);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(GLdouble)view_w/view_h,1,100);

    double rate=1.2;
    gluLookAt(rate*5,rate*10,rate*10,0,0,0,0,0,1);
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity() ;
}


//---------------------------------------------------------------------
void Application::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key) {
            case 'R': 
            case 'r':// muda a cor corrente para vermelho
                     glColor3f(1.0f, 0.0f, 0.0f);
                     break;
            case 'G':
            case 'g':// muda a cor corrente para verde
                     glColor3f(0.0f, 1.0f, 0.0f);
                     break;
            case 'B':
            case 'b':// muda a cor corrente para azul
                     glColor3f(0.0f, 0.0f, 1.0f);
			time++;
			for(list<Objects*>::const_iterator it = list_.begin(); it != list_.end(	) ;  ++it)
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
    if(key == GLUT_KEY_UP) {
           //win -= 20;
           //glMatrixMode(GL_PROJECTION);
           //glLoadIdentity();
           //gluOrtho2D (-win, win, -win, win);
	   insert_object();
    }
    if(key == GLUT_KEY_DOWN) {
           //win += 20;
           //glMatrixMode(GL_PROJECTION);
           //glLoadIdentity();
           //gluOrtho2D (-win, win, -win, win);
    }
    
}
//---------------------------------------------------------------------
void Application::update(int value, void (*func_ptr)(int))
{	
	glutPostRedisplay();
	glutTimerFunc(30,func_ptr,time);

}
//---------------------------------------------------------------------
bool Application::insert_object(void)
{
	Triangle *obj;
	//Objects * node = reinterpret_cast<Objects*>(obj);
	list_.push_back(new Triangle());
	std::cout << " insert: " << list_.size() << std::endl; 

	return true;
}

