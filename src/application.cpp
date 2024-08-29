// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024

#include <stdlib.h>
#include <stdio.h>
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    glPushMatrix();
        glTranslatef(0.0f, -2.0f, -4.0f);
        glScalef(2.0f, 2.0f, 2.0f); // Increase the size of the cube
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glutSolidCube(2.0f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f); // Increase the size of the cube
        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        glutSolidCube(2.0f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -2.0f, 4.0f);
        glScalef(2.0f, 2.0f, 2.0f); // Increase the size of the cube
        glColor3f(0.0f, 0.0f, 1.0f); // Blue color
        
        // Draw the 5 square faces of the cube
        glBegin(GL_QUADS);
            // Front face
            // Front face
            glColor3f(0.5f, 0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            
            // Left face
            glColor3f(0.6f, 0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            
            // Right face
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);
            
            // Top face
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            
            // Bottom face
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
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

    double rate=1;
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

