#include "application.hpp"

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
	showSolution =false;
    menuIndex=0;
    stepsSolution=0;
}

//---------------------------------------------------------------------

void Application::setCamera()
{
    float cameraX = cameraRadius * cos(cameraAngle * M_PI / 180.0f);
    float cameraY = cameraRadius * sin(cameraAngle * M_PI / 180.0f);
    float cameraZ = 10.0f;

    gluLookAt(cameraX, cameraY, cameraZ,
              0.0f, 0.0f, 0.0f,        
              0.0f, 0.0f, 1.0f);
}

void Application::draw()
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();
 
    int size = 2;
    glm::vec3 basePoint(-1.0f, -1.0f, 0.0f);

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex3f(-size / 2, size / 2, size * 4);
    glVertex3f(size / 2, size / 2, size * 4);
    glVertex3f(size / 2, -size / 2, size * 4);
    glVertex3f(-size / 2, -size / 2, size * 4);
    glEnd();
    glEnable(GL_TEXTURE_2D); 
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
    glDisable(GL_TEXTURE_2D);
    if (this->showMenu){
        drawMenu();
    }
    glFlush();
    glutSwapBuffers();
}

//---------------------------------------------------------------------
void Application::resize(GLsizei w, GLsizei h)
{
    if (h == 0)
    {
        h = 1;
    }

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float)w / (float)h;
    gluPerspective(45.0f, aspectRatio, 1.0f, 100.0f); 

    glMatrixMode(GL_MODELVIEW);
}
//---------------------------------------------------------------------

void Application::drawMenu()
{
    const char *menuOptions[] = {"New Game", "Continue","Show Solution", "Exit"};
    int numOptions = 4;

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
            glColor3f(0.0f, 0.0f, 0.0f);
        }
        else
        {
            glColor3f(1.0f, 1.0f, 1.0f);
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
            menuIndex = (menuIndex > 0) ? menuIndex - 1 : 3;
            break;
        case GLUT_KEY_DOWN:
            menuIndex = (menuIndex < 3) ? menuIndex + 1 : 0;
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
                if(this->index == 0 || this->index == 3){
                    switchFace(1, this->index);
                    checkIfIsSolve();
                } 
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
                if(this->index == 0 || this->index == 3){
                    switchFace(2, this->index);
                    checkIfIsSolve();
                }
            }
            break;
        case GLUT_KEY_UP:
            if (this->isFaceSelection && this->index < 3)
            {
                if (this->orderOfStates[index + 1][faceIndex] == "vzo")
                {
                    switchFace(3, this->index);
                    checkIfIsSolve();
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
                    checkIfIsSolve();
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
    else if(key == 13 && this->showMenu){//TECLA ENTER
        menuSelect();
    }
    else if (key == ' ' && !this->showMenu){
        this->isFaceSelection = !this->isFaceSelection;
    }
    else if (key == 27 && !this->showMenu){//Tecla ESC
        exit(0);
    }
    else if (key == 'a' && !this->showMenu)
    {
        cameraAngle -= 5.0f;
        if (cameraAngle < 0.0f && !this->showMenu){
            cameraAngle += 360.0f;
        }
    }
    else if (key == 'd' && !this->showMenu)
    {
        cameraAngle += 5.0f;
        if (cameraAngle > 360.0f && !this->showMenu){
            cameraAngle -= 360.0f;
        }
    }
    else if (key == 'p' && !this->showMenu)
    {
        saveState();
    }
    else if(key == 'n' && this->showSolution){
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
        orderOfStatesTemp[4-1] = firstState; 
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
        orderOfStatesTemp[0] = lastState;
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
        newGame();
    }else if(this->menuIndex == 1){
        const char *directory = "../data/output.xml";
        XMLManager r(directory);
        if(r.getxmlError()){
            std::cerr << "Você não possui um jogo salvo." << std::endl;
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
bool Application::isSolve(int sideIndex){
    string inferior= this->orderOfStates[0][sideIndex];
    string intermediario2 = this->orderOfStates[1][sideIndex];
    string intermediario = this->orderOfStates[2][sideIndex];
    string superior = this->orderOfStates[3][sideIndex];
    
    if(superior.substr(0, 2) == intermediario.substr(0, 2) && superior.substr(0, 2) == intermediario2.substr(0, 2)
    && superior.substr(0, 2) == inferior.substr(0, 2)){
        if(superior.substr(2, 3) == "s" && intermediario.substr(2, 3) == "m" && intermediario2.substr(2, 3) == "m"
        && inferior.substr(2, 3) == "i"){
            return true;
        }
    }else if(superior.substr(0, 2) == "br" && intermediario.substr(0, 2) == "br" && intermediario2.substr(0, 2) == "br"){
        if(superior.substr(2, 3) == "s" && intermediario.substr(2, 3) == "m" && intermediario2.substr(2, 3) == "i"){
            return true;
        }
    }
    
    return false;
    
}

void Application::checkIfIsSolve(){
    for(int i=0; i<4; i++){
        bool solve = isSolve(i);
        if(!solve){
            return;
        }
    }
    std::cout << "Você solucionou o Elo Maluco!" << std::endl;
    showMenu = true;
}


