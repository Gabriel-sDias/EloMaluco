// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2024

#include <stdlib.h>
#include <stdio.h>
#include <array>
#include "application.hpp"
#include "XMLManager.hpp"
#include "translator.hpp"


///////////////////////////////////////////////////////////////////////
// Application Class
Application::Application(int argc, char **argv, std::array<std::array<glm::vec3, 4>, 4> colors)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ELO MALUCO");
    this->colors = colors;
    Inicializa();
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
    isFaceSelection = false;
    cameraAngle = 0.0f;
    cameraRadius = 20.0f;
}

//---------------------------------------------------------------------
// void Application::DisplayFunc()
//{
//	glutDisplayFunc(Application::Desenha);
//}
//---------------------------------------------------------------------

void Application::setCamera()
{
    float cameraX = cameraRadius * cos(cameraAngle * M_PI / 180.0f);
    float cameraY = cameraRadius * sin(cameraAngle * M_PI / 180.0f);
    float cameraZ = 10.0f;

    // Define a câmera usando gluLookAt
    gluLookAt(cameraX, cameraY, cameraZ,  // Posição da câmera (rotacionando no plano XY, mantendo Z constante)
              0.0f, 0.0f, 0.0f,          // Ponto de foco da câmera (centro dos cubos)
              0.0f, 0.0f, 1.0f); 
}

void Application::draw()
{

    // LEGENDA DE EIXOS
    // Verde - Eixo Y
    // Azul - Eixo Z
    // Vermelho - Eixo X
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); 
    setCamera();
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
       this->eloMaluco[i] = Cube(basePoint + glm::vec3(0.0f, 0.0f, i * size / 1.0f), size, this->colors[i],this->eloMaluco[i].getAngle());
       if (i == this->index) {
           this->eloMaluco[i].highlight();
       }
    //    If the cube is selected, start changing the faces 

       this->eloMaluco[i].draw();
       glPopMatrix(); 
    }

    glFlush();
    glutSwapBuffers();

}

//---------------------------------------------------------------------
void Application::resize(GLsizei w, GLsizei h)
{
   // Evitar divisão por zero caso a altura seja 0
    if (h == 0) {
        h = 1;
    }

    // Configura o viewport para cobrir a nova janela
    glViewport(0, 0, w, h);

    // Inicia a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Configura uma perspectiva ajustada com a nova razão de aspecto
    float aspectRatio = (float)w / (float)h;
    gluPerspective(45.0f, aspectRatio, 1.0f, 100.0f);  // Ângulo de visão, razão de aspecto, plano de corte próximo e distante

    // Volta para o modo de modelagem
    glMatrixMode(GL_MODELVIEW);
    
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

void Application::SpecialKeyHandle(int key, int x, int y) {
    float rotationAngle = 90.0f; 

    switch (key) {
        case GLUT_KEY_LEFT:
            if(this->isFaceSelection){
                this->eloMaluco[this->index].select();
            } else {
                switchFace(2, this->index);
              
            }
            break;
        case GLUT_KEY_RIGHT:
            if(this->isFaceSelection){
                
                this->eloMaluco[this->index].select();
            } else {
                switchFace(1, this->index);
                
            }
            break;
        case GLUT_KEY_UP:
            if(this->isFaceSelection){
                this->eloMaluco[this->index].select();
            }
            else {
                if (this->index< this->eloMaluco.size() - 1) {       
                    ++this->index;
                }
            }
            break;
        case GLUT_KEY_DOWN:
            if(this->isFaceSelection){
                this->eloMaluco[this->index].select();
            }
            else{
                if (this->index > 0) {
                    --this->index;
                }
            }
            break;
    }

    glutPostRedisplay(); // Solicita a redrawing da tela
}

void Application::keyboard(unsigned char key, int x, int y)
{
    if (key == ' ') {
        this->isFaceSelection = !this->isFaceSelection;
    }
    if (key == 27) {
        exit(0);
    }
    if (key == 'a') {
        cameraAngle -= 5.0f; 
    } else if (key == 'd') {
        cameraAngle += 5.0f; 
    }

    if (cameraAngle > 360.0f) {
        cameraAngle -= 360.0f;
    } else if (cameraAngle < 0.0f) {
        cameraAngle += 360.0f;
    }

    if(key == 'p'){
        saveState();
    }

    glutPostRedisplay();
}

void Application::saveState(){
    Translator translate;
    array<std::array<glm::vec3, 4>, 4> state;
    int counter =3;
    for(Cube c : this->eloMaluco){
        state[counter] = c.getColors();
        counter--;
    }
    translate.translateRGBToState(state);
}

void Application::switchFace(int direction, int index){ 
 // direita = 1 // esquerda = 2
     if(direction == 1){
        array<glm::vec3, 4> cubeColors = this->colors[index];
        glm::vec3 firstcolor = cubeColors[0]; 
        for (int i = 1; i < 4; ++i) {
            cubeColors[i - 1] = cubeColors[i];
        }
        cubeColors[4-1] = firstcolor; // coloca o primeiro elemento no final
        this->colors[index] = cubeColors;
    }else{
          array<glm::vec3, 4> cubeColors = this->colors[index];
        glm::vec3 lastcolor = cubeColors[3]; 
        for (int i = 4-1; i > 0; --i) {
            cubeColors[i ] = cubeColors[i-1];
        }
        cubeColors[0] = lastcolor; // coloca o primeiro elemento no final
        this->colors[index] = cubeColors;
    }
}