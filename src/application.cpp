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
Application::Application(int argc, char **argv, std::array<std::array<string, 4>, 4> orderOfStates, std::array<std::array<string, 4>, 4> textures, std::array<std::array<string, 4>, 4> chains)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ELO MALUCO");
    this->orderOfStates = orderOfStates;
    this->textures = textures;
    this->chains = chains;
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
    index = 0;
    xf = 50.0f;
    yf = 50.0f;
    win = 250.0f;
    time = 0;
    isFaceSelection = false;
    cameraAngle = 0.0f;
    cameraRadius = 20.0f;
    faceIndex = 0;
    showMenu = true;
	showPopup = false;
	showSolution =false;
    menuIndex=0;
    stepsSolution=0;
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
    gluLookAt(cameraX, cameraY, cameraZ, // Posição da câmera (rotacionando no plano XY, mantendo Z constante)
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

    setCamera();
/*Desenha os eixos */
    // glPushMatrix();

    // glLineWidth(3.0f);

    // glBegin(GL_LINES);
    // glColor3f(1, 0, 0);
    // glVertex3f(0, 0, 0);
    // glVertex3f(10, 0, 0);
    // glEnd();
    // glColor3f(0, 1, 0);
    // glBegin(GL_LINES);
    // glVertex3f(0, 0, 0);
    // glVertex3f(0, 10, 0);
    // glEnd();
    // glColor3f(0, 0, 1);
    // glBegin(GL_LINES);
    // glVertex3f(0, 0, 0);
    // glVertex3f(0, 0, 10);
    // glEnd();
    // glPopMatrix();
/*--------- fim do desenho dos eixos ---------*/
    int size = 2;
    glm::vec3 basePoint(-1.0f, -1.0f, 0.0f);

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex3f(-size / 2, size / 2, size * 4);
    glVertex3f(size / 2, size / 2, size * 4);
    glVertex3f(size / 2, -size / 2, size * 4);
    glVertex3f(-size / 2, -size / 2, size * 4);
    glEnd();

    for (int i = 0; i < 4; i++)
    {
       glPushMatrix(); 
       glRotatef(this->eloMaluco[i].getAngle(), 0.0f, 0.0f, 1.0f); 
       this->eloMaluco[i] = Cube(basePoint + glm::vec3(0.0f, 0.0f, i * size / 1.0f), size, this->textures[i], this->chains[i], this->eloMaluco[i].getAngle());
       if (i == this->index) {
           this->eloMaluco[i].highlight();
           if (this->isFaceSelection) {
            this->eloMaluco[i].unhighlight();
            this->eloMaluco[i].setFaceIndex(this->faceIndex);
            this->eloMaluco[i].select();
        }
       }
       
       this->eloMaluco[i].draw();
       glPopMatrix(); 
    }

    if (this->showMenu)
    {
        drawMenu();
    }
    if(showPopup){
        popup();
    }
    glFlush();
    glutSwapBuffers();
}

//---------------------------------------------------------------------
void Application::resize(GLsizei w, GLsizei h)
{
    // Evitar divisão por zero caso a altura seja 0
    if (h == 0)
    {
        h = 1;
    }

    // Configura o viewport para cobrir a nova janela
    glViewport(0, 0, w, h);

    // Inicia a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Configura uma perspectiva ajustada com a nova razão de aspecto
    float aspectRatio = (float)w / (float)h;
    gluPerspective(45.0f, aspectRatio, 1.0f, 100.0f); // Ângulo de visão, razão de aspecto, plano de corte próximo e distante

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

void Application::drawMenu()
{
    const char *menuOptions[] = {"New Game", "Continue","Show Solution", "Exit"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  

    for (int i = 0; i < numOptions; i++)
    {
        if (i == this->menuIndex)
        {
            glColor3f(1.0f, 1.0f, 0.0f); // Destaca a opção selecionada
        }
        else
        {
            glColor3f(0.0f, 0.0f, 0.0f); // Outras opções
        }

        glRasterPos2i(100, 200 - i * 30);
        const char *option = menuOptions[i];
        while (*option)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *option);
            option++;
        }
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void Application::SpecialKeyHandle(int key, int x, int y)
{
    float rotationAngle = 90.0f;

    if (showMenu)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            menuIndex = (menuIndex > 0) ? menuIndex - 1 : 2;
            break;
        case GLUT_KEY_DOWN:
            menuIndex = (menuIndex < 2) ? menuIndex + 1 : 0;
            break;
        }
            
        glutPostRedisplay();
    }
    else
    {

        switch (key)
        {
        case GLUT_KEY_LEFT:
            if (this->isFaceSelection)
            {
                if (this->faceIndex == 0)
                {
                    this->faceIndex = 3;
                }
                else
                {
                    this->faceIndex--;
                }
            }
            else
            {
                switchFace(2, this->index);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (this->isFaceSelection)
            {
                if (this->faceIndex == 3)
                {
                    this->faceIndex = 0;
                }
                else
                {
                    this->faceIndex++;
                }
            }
            else
            {
                switchFace(1, this->index);
            }
            break;
        case GLUT_KEY_UP:
            if (this->isFaceSelection && this->index < 3)
            {
                if (this->orderOfStates[index + 1][faceIndex] == "vzo")
                {
                    switchFace(3, this->index);
                }
            }
            else if (!this->isFaceSelection)
            {
                if (this->index < this->eloMaluco.size() - 1)
                {
                    ++this->index;
                }
            }
            break;
        case GLUT_KEY_DOWN:
            if (this->isFaceSelection && this->index > 0)
            {
                if (this->orderOfStates[index - 1][faceIndex] == "vzo")
                {
                    switchFace(4, this->index);
                }
            }
            else if (!this->isFaceSelection)
            {
                if (this->index > 0)
                {
                    --this->index;
                }
            }
            break;
        }

        glutPostRedisplay();
    }
}

void Application::keyboard(unsigned char key, int x, int y)
{   
    if(key =='m'){
        this->showMenu = !this->showMenu;
        glutPostRedisplay();
    }
    if(key == 13 && this->showMenu){//TECLA ENTER
        menuSelect();
    }
    else if (key == ' ' && !this->showMenu)
    {
        this->isFaceSelection = !this->isFaceSelection;
    }
    if (key == 27 && !this->showMenu)//Tecla ESC
    {
        exit(0);
    }
    if (key == 'a' && !this->showMenu)
    {
        cameraAngle -= 5.0f;
    }
    else if (key == 'd' && !this->showMenu)
    {
        cameraAngle += 5.0f;
    }

    if (cameraAngle > 360.0f && !this->showMenu)
    {
        cameraAngle -= 360.0f;
    }
    else if (cameraAngle < 0.0f && !this->showMenu)
    {
        cameraAngle += 360.0f;
    }

    if (key == 'p' && !this->showMenu)
    {
        saveState();
    }
    if(key == 'n' && this->showSolution){
        showSolutionSteps(1);
    }else if(key == 'b' && this->showSolution){
        showSolutionSteps(2);
    }

    glutPostRedisplay();
}

void Application::saveState()
{
    XMLManager manager;
    manager.writer(this->orderOfStates);
}
void Application::popup(){
    if (this->showPopup) {
        /*glPushMatrix();  // Salva o estado da matriz
        glTranslatef(-0.8f, -1.0f, 0.0f);  // Move o texto para (2.0, 1.5) no mundo
        // Desenha o texto no popup
        glColor3f(1.0f, 1.0f, 1.0f); // Cor do texto
        string text = "you do not have a save.";
        for (char c : text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        // Atualizar o tempo do popup
        for(float i =0.f; i < 1000.0; i +=0.01f ){
            if (i > 999) {
                this->showPopup = false;  // Esconde o popup após o tempo
                glutPostRedisplay();
            }
        }
        glPopMatrix();  // Restaura o estado da matriz*/
        this->showPopup = false;
        std::cerr << "Vocẽ não possui nenhum save!" << std::endl;
    }
}
void Application::switchFace(int direction, int index){

    // direita = 1 // esquerda = 2 // cima = 3 // baixo = 4

    if (direction == 1)
    {
        array<string, 4> orderOfStatesTemp = this->orderOfStates[index];
        array<string, 4> cubeTexturesTemp = this->textures[index];
        array<string, 4> chainTemp = this->chains[index];
        string firstState = orderOfStatesTemp[0];
        string firstTexture = cubeTexturesTemp[0];
        string firstChain = chainTemp[0];
        for (int i = 1; i < 4; ++i) {
            orderOfStatesTemp[i - 1] = orderOfStatesTemp[i];
            cubeTexturesTemp[i - 1] = cubeTexturesTemp[i];
            chainTemp[i - 1] = chainTemp[i];
        }
        orderOfStatesTemp[4-1] = firstState; // coloca o primeiro elemento no final
        cubeTexturesTemp[4-1] = firstTexture;
        chainTemp[4-1] = firstChain;
        this->orderOfStates[index] = orderOfStatesTemp;
        this->textures[index] = cubeTexturesTemp;
        this->chains[index] = chainTemp;
    }else if (direction == 2){
        array<string, 4> orderOfStatesTemp = this->orderOfStates[index];
        array<string, 4> cubeTexturesTemp = this->textures[index];
        array<string, 4> chainTemp = this->chains[index];
        string lastState = orderOfStatesTemp[3];
        string lastTexture = cubeTexturesTemp[3];
        string lastChain = chainTemp[3];
        for (int i = 4-1; i > 0; --i) {
            orderOfStatesTemp[i] = orderOfStatesTemp[i-1];
            cubeTexturesTemp[i] = cubeTexturesTemp[i-1];
            chainTemp[i] = chainTemp[i-1];
        }
        orderOfStatesTemp[0] = lastState; // coloca o primeiro elemento no final
        cubeTexturesTemp[0] = lastTexture;
        chainTemp[0] = lastChain;
        this->orderOfStates[index] = orderOfStatesTemp;
        this->textures[index] = cubeTexturesTemp;
        this->chains[index] = chainTemp;
    } else if (direction == 3) {
        string stateTemp = this->orderOfStates[index][faceIndex];
        this->orderOfStates[index][faceIndex] = this->orderOfStates[index+1][faceIndex];
        this->orderOfStates[index+1][faceIndex] = stateTemp;

        string textureTemp = this->textures[index][faceIndex];
        this->textures[index][faceIndex] = this->textures[index+1][faceIndex];
        this->textures[index+1][faceIndex] = textureTemp;

        string chainTemp = this->chains[index][faceIndex];
        this->chains[index][faceIndex] = this->chains[index+1][faceIndex];
        this->chains[index+1][faceIndex] = chainTemp;
    } else if (direction == 4) {
        string stateTemp = this->orderOfStates[index][faceIndex];
        this->orderOfStates[index][faceIndex] = this->orderOfStates[index-1][faceIndex];
        this->orderOfStates[index-1][faceIndex] = stateTemp;

        string textureTemp = this->textures[index][faceIndex];
        this->textures[index][faceIndex] = this->textures[index-1][faceIndex];
        this->textures[index-1][faceIndex] = textureTemp;

        string chainTemp = this->chains[index][faceIndex];
        this->chains[index][faceIndex] = this->chains[index-1][faceIndex];
        this->chains[index-1][faceIndex] = chainTemp;
    }
}
void Application::newGame(){
    XMLManager manager;
    vector<string> randomState = manager.randomState();
    Translator translator(randomState);
    this->orderOfStates = translator.getStatesInOrder();
    this->textures = translator.getTextures();
    this->chains = translator.getChains();
    this->showMenu = false;
    glutPostRedisplay();
}
void Application::menuSelect(){
    if(this->menuIndex == 0){
        //logica new game gerar um novo xml e renderizar o cubo novamente
        newGame();
    }else if(this->menuIndex == 1){
        const char *directory = "../data/output.xml";
        XMLManager r(directory);
        if(r.getxmlError()){
            this->showPopup = true;
            return;
        }
        vector<string> states = r.getStates();
        Translator translator(states);
        this->orderOfStates = translator.getStatesInOrder();
        this->textures = translator.getTextures();
        this->chains = translator.getChains();
        this->showMenu = false;
    }else if(this->menuIndex == 2){
        solution();
        this->showSolution = true;
        this->showMenu = false;
    }else{

        exit(0);
    }
}
void Application::solution(){
    this->stepsSolution =0;
    this->solutionStepsTextures.push_back(this->textures);
    this->solutionStepsChains.push_back(this->chains);
    const char *directory = "../data/solution.xml";
    XMLManager manager(directory);
    manager.solutionReader();
    vector<string> steps = manager.getSolutionSteps();
    for(string i : steps){
        if(i == "rsd"){
            switchFace(2, 3);
        }else if(i == "rse"){
            switchFace(1, 3);
        }else if(i =="rid"){
            switchFace(2, 0);
        }else if(i == "rie"){
            switchFace(1, 0);
        }else if( i =="mfc"){
            Translator translator;
            translator.findVoidFace(this->orderOfStates);
            this->faceIndex = translator.getVzoFaceIndex();
            this->index = translator.getVzoCubeIndex();
            switchFace(3, this->index -1);
        }else{
            Translator translator;
            translator.findVoidFace(this->orderOfStates);
            this->faceIndex = translator.getVzoFaceIndex();
            this->index = translator.getVzoCubeIndex();
            switchFace(4, this->index+1);
        }
        this->solutionStepsTextures.push_back(this->textures);
        this->solutionStepsChains.push_back(this->chains);
    }
}
void Application::showSolutionSteps(int direction){
    if(direction == 1 && this->stepsSolution < solutionStepsTextures.size()-1){
        this->stepsSolution++;
    }else if(direction == 2 && this->stepsSolution > 0){
        this->stepsSolution--;
    }
    this->textures = this->solutionStepsTextures[this->stepsSolution];
    this->chains = this->solutionStepsChains[this->stepsSolution];
    glutPostRedisplay();
}
bool Application::isSolve(){
    return false;
}