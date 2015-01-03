#include "gltest.h"


GLTest::GLTest(QWidget *parent, const char *name, bool fs) :
QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    repeat = 0;
    wind.setLevel(0.0, -0.05, 0.00);
    snow.setup(40, 50, 2000);
}


void GLTest::genList(){
    //drawAxis();
    fence.draw();
}

GLuint GLTest::getTreeList(){

    if(trees.size() <= 0){
        return -1;
    }
    GLuint tempList = glGenLists(1);
    Tree thisTree = trees[trees.size() - 1];
    glNewList(tempList, GL_COMPILE);
    thisTree.draw();
    glEndList();
    return tempList;
}



void GLTest::initializeGL(){
    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0 ,0.1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    //fog.setup();
    //glutSpecialFunc(keyUpWrapper);

    if(!textureMgr.loadTextures("./Data/night.jpg", GL_LINEAR, "sky") ||
        !textureMgr.loadTextures("./Data/grass_cloud.jpg", GL_LINEAR, "grass")||
        !textureMgr.loadTextures("./Data/flake.bmp", GL_NEAREST, "flake") ||
        !textureMgr.loadTextures("./Data/groundSnow.jpg", GL_NEAREST, "groundSnow") ||
        !textureMgr.loadTextures("./Data/wood.bmp", GL_NEAREST, "fence") ||
        !textureMgr.loadTextures("./Data/leaves.bmp", GL_LINEAR, "leaves") ||
        !textureMgr.loadTextures("./Data/flower.bmp", GL_NEAREST, "flower") ||
        !textureMgr.loadTextures("./Data/flower2.jpg", GL_NEAREST, "flower2") ||
        !textureMgr.loadTextures("./Data/flower3.jpg", GL_NEAREST, "flower3") ||
        !textureMgr.loadTextures("./Data/flower4.jpg", GL_NEAREST, "flower4") ||
        !textureMgr.loadTextures("./Data/center.bmp", GL_NEAREST, "center") ||
        !textureMgr.loadTextures("./Data/tree2.bmp", GL_NEAREST, "top") ||
        !textureMgr.loadTextures("./Data/wood.bmp", GL_NEAREST, "brack") )
    {
        return ;
    }
    snow.init(textureMgr.getTexture("flake"));
    ground.setTexture(textureMgr.getTexture("grass"), textureMgr.getTexture("groundSnow"));
    flower1.setCenterTexture(textureMgr.getTexture("center"));
    flower1.setLeavesTexture(textureMgr.getTexture("leaves"));
    flower1.setFlowerTexture(textureMgr.getTexture("flower"));
    tree.setTexture(textureMgr.getTexture("brack"), textureMgr.getTexture("top"));
    fence.setTexture(textureMgr.getTexture("fence"));
    //Set up fence
    int length = fence.getLength();
    int size = fence.getSize();
    vector<double> h1, h2, h3, h4;
    int halfSize = size / 2;
    for(int i = 0 ; i <= size ; i+=length){		//Ger front height
        h1.push_back(ground.groundHeight(i - halfSize ,-halfSize, true) );
    }
    for(int i = 0 ; i <= size ; i+=length){		//Ger front height
        h2.push_back(ground.groundHeight(i - halfSize ,halfSize, true) );
    }
    for(int i = size ; i >= 0 ; i-=length){		//Ger front height
        h3.push_back(ground.groundHeight(-halfSize,i - halfSize,  true) );
    }
    for(int i = size ; i >= 0 ; i-=length){		//Ger front height
        h4.push_back(ground.groundHeight(halfSize,i - halfSize,  true) );
    }
    fence.setHeight(h1, h2, h3, h4);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    dList = glGenLists(1);
    glNewList(dList, GL_COMPILE);
    genList();
    glEndList();
    dLists.push_back(dList);


}

void GLTest::setGroundHeight(int val){
    double cx = camera.get('x');
    double cz = camera.get('z');
    ground.setHeight(cx, cz, val);
}

void GLTest::paintGL(){

    camera.continueMoving();
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera

    camera.setFixArea((1 << 6) - 1);
    double cx = camera.get('x');
    double cz = camera.get('z');
    double cy =(ground.groundHeight(cx, cz, true, true) + camera.getJmpHeight() ) ;
    gluLookAt(cx,  0.5 + cy  ,cz,
        cx+ camera.getLook('x'),  0.5 + cy + camera.getLook('y')  ,cz + camera.getLook('z'),
        0, 1, 0	);
    glPushMatrix();
    sky.draw(textureMgr.getTexture("sky"));
    glPopMatrix();

    //Draw Ground
    glPushMatrix();
    ground.draw();
    glPopMatrix();

    //std::cout << "Camera: " << cx << ", "<<cy <<  ", " << cz  <<std::endl;

    //  glTranslatef(0, ground.Height(0, 0, true),-10);
    // tree.draw();
	if(dLists.size() > 0){
		glCallList(dLists[0]);
	}


    for(size_t i = 1 ; i < dLists.size() ; i++){
        glPushMatrix();
        glCallList(dLists[i]);
        glPopMatrix();
    }
    snow.draw(wind, ground);
    //QMetaObject::invokeMethod(this,"updateGL",Qt::QueuedConnection);
}


void GLTest::resizeGL(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void GLTest::keyPressEvent2(QKeyEvent *e){
    if(e->isAutoRepeat()){
        return ;
    }

    if(e->key() == Qt::Key_Escape){
        exit(0);
    }

    switch (e->key()) {
    case Qt::Key_Left :
        camera.moveSwitch(C_LEFT, C_ON);
        break;
    case Qt::Key_Right  :
        camera.moveSwitch(C_RIGHT, C_ON);
        break;
    case Qt::Key_Up :
        camera.moveSwitch(C_FRONT, C_ON);
        break;
    case Qt::Key_Down :
        camera.moveSwitch(C_BACK, C_ON);
        break;
    case Qt::Key_PageUp:
        camera.moveSwitch(C_UP, C_ON);
        break;
    case Qt::Key_PageDown:
        camera.moveSwitch(C_DOWN, C_ON);
        break;
     case Qt::Key_Space:
        camera.moveSwitch(C_JMP, C_ON);
        break;
    case Qt::Key_O:
        setGroundHeight(1);
        break;
    }

}

void GLTest::setupFlowers(int textureType, int type, int levels, int levelCnt[]){
    double cx = camera.get('x');
    double cz = camera.get('z');
    double cy =ground.groundHeight(cx, cz, true) ;

    Flower newFlower(cx, cy, cz, 3);
    newFlower.setTextureType(textureType);
    newFlower.setFlowerType(type);
    newFlower.setCenterCount(levels, levelCnt);
    newFlower.setCenterTexture(textureMgr.getTexture("center"));
    newFlower.setLeavesTexture(textureMgr.getTexture("leaves"));
    switch(textureType){
    case 0:
        newFlower.setFlowerTexture(textureMgr.getTexture("flower1"));
        break;
    case 1:
        newFlower.setFlowerTexture(textureMgr.getTexture("flower2"));
        break;
    case 2:
        newFlower.setFlowerTexture(textureMgr.getTexture("flower3"));
        break;
    default:
        newFlower.setFlowerTexture(textureMgr.getTexture("flower"));
        break;
    }


    flowers.push_back(newFlower);
    ground.setPlantArea(cx - 2, cz - 2, cx + 2, cz + 2);
    for(float x = cx - 2.0 ; x < cx + 2.0 ; x +=  (1.0 / BUFFER_PRECISION) ){
        for(float z = cz - 2.0 ; z < cz + 2.0 ; z +=  (1.0 / BUFFER_PRECISION) ){
            float currentHeight = newFlower.getHeight(x, z);
            if( currentHeight > cy){
                ground.setPlantHeight(x, z, currentHeight);
            }else{
                ground.setPlantHeight(x, z, ground.groundHeight(x, z, true));
            }
        }
    }

    GLuint tempList = glGenLists(1);

    glNewList(tempList, GL_COMPILE);
    newFlower.draw();
    glEndList();
    dLists.push_back(tempList);

}

void GLTest::setupFlowers(Flower newFlower){
    double cx = camera.get('x');
    double cz = camera.get('z');
    double cy = ground.groundHeight(cx, cz, true) + 0.1;
    ground.setPlantArea(cx - 2, cz - 2, cx + 2, cz + 2);
    if(cx < BUFFER_AREA && cx > -BUFFER_AREA && cz < BUFFER_AREA && cz > -BUFFER_AREA ){
        for(float x = cx - 2.0 ; x < cx + 2.0 ; x += (1.0 / BUFFER_PRECISION) ){
            for(float z = cz - 2.0 ; z < cz + 2.0 ; z += (1.0 / BUFFER_PRECISION)  ){
                float currentHeight = newFlower.getHeight(x, z);
                if( currentHeight > cy + 0.1){
                    ground.setPlantHeight(x, z, currentHeight);
                }else{
                    ground.setPlantHeight(x, z, ground.groundHeight(x, z, true));
                }
            }
        }
    }

    flowers.push_back(newFlower);
    GLuint tempList = glGenLists(1);
    glNewList(tempList, GL_COMPILE);
    newFlower.draw();
    glEndList();
    dLists.push_back(tempList);
}

void GLTest::setupTrees(double height, double width, int levels){
    double cx = camera.get('x');
    double cz = camera.get('z');
    double cy =ground.groundHeight(cx, cz, true) ;
    Tree newTree(height, width, levels);
    newTree.setTexture(textureMgr.getTexture("brack"), textureMgr.getTexture("top"));
	newTree.setPosition(cx, cy, cz);

    ground.setPlantArea(cx - width, cz - width, cx + width, cz + width);
    if(cx < BUFFER_AREA && cx > -BUFFER_AREA && cz < BUFFER_AREA && cz > -BUFFER_AREA ){
        for(float x = cx - width ; x < cx + width ; x += (1.0 / PLANT_PRECISION) ){
            for(float z = cz - width ; z < cz + width ; z += (1.0 / PLANT_PRECISION) ){
                float currentHeight = newTree.getHeight(x, z);
                if(currentHeight > cy + 0.1){
                    ground.setPlantHeight(x, z, currentHeight);
                }else{
                    ground.setPlantHeight(x, z, ground.groundHeight(x, z, true));
                }
            }
        }
    }

    trees.push_back(newTree);
    GLuint tempList = glGenLists(1);
    glNewList(tempList, GL_COMPILE);
    newTree.draw();
    glEndList();
    dLists.push_back(tempList);
}

void GLTest::setupTrees(Tree tree){
    trees.push_back(tree);
    double cx = camera.get('x');
    double cz = camera.get('z');
    double cy =ground.groundHeight(cx, cz, true) ;
    tree.setPosition(cx, cy, cz);

    ground.setPlantArea(cx - 3, cz - 3, cx + 3, cz + 3);
    if(cx < BUFFER_AREA && cx > -BUFFER_AREA && cz < BUFFER_AREA && cz > -BUFFER_AREA ){
        for(float x = cx - 3 ; x < cx + 3 ; x +=  (1.0 / BUFFER_PRECISION)  ){
            for(float z = cz - 3 ; z < cz + 3 ; z +=  (1.0 / BUFFER_PRECISION)  ){
                float currentHeight = tree.getHeight(x, z);
                if(currentHeight > cy + 0.1){
                    ground.setPlantHeight(x, z, currentHeight);
                }else{
                    ground.setPlantHeight(x, z, ground.groundHeight(x, z, true));
                }
            }
        }
    }

    GLuint tempList = glGenLists(1);
    glNewList(tempList, GL_COMPILE);
    tree.draw();
    glEndList();
    dLists.push_back(tempList);
}

void GLTest::stopMoving(){
    camera.stop();
}


void GLTest::stopSnow(){
    snow.stop();
}

void GLTest::startSnow(int val){
    snow.start(val);
}

void GLTest::setSnowArea(int val){
    snow.setArea(val);
}

void GLTest::setMeltSpeed(int val){
    val = val > 1000 ? 1000 : val;
    ground.setMeltingSpeed(val);
}

void GLTest::setFallSpeed(float val){
    wind.setFallSpeed(val);
}


void GLTest::setWindLevel(int direction, float value){
    direction = direction > 360 ? 360 : direction;
    direction = direction < 0 ? 0 : direction;
    value = value > 0.5 ? 0.5 : value;
    value = value < 0 ? 0 : value;
    double angle = (double)direction / 180.0 * 3.14159;
    float lz = sin(angle) * value;
    float lx = cos(angle) * value;
    float ly = wind.getLevelY();
    wind.setLevel(lx, ly, lz);
}

void GLTest::keyReleaseEvent2(QKeyEvent *e){
    if(e->isAutoRepeat()){
        return ;
    }
    repeat = 0;

    if(e->key() == Qt::Key_W){

        Tree newTree(10, 4.0, 3);
        newTree.setTexture(textureMgr.getTexture("brack"), textureMgr.getTexture("top"));
        newTree.setPosition(camera.get('x'),
                                        ground.groundHeight(camera.get('x'), camera.get('z')),
                                        camera.get('z') );
        trees.push_back(newTree);
        dLists.push_back(getTreeList());
    }


    switch (e->key()) {
    case Qt::Key_Left :
        camera.moveSwitch(C_LEFT, C_OFF);
        break;
    case Qt::Key_Right  :
        camera.moveSwitch(C_RIGHT, C_OFF);
        break;
    case Qt::Key_Up :
        camera.moveSwitch(C_FRONT, C_OFF);
        break;
    case Qt::Key_Down :
        camera.moveSwitch(C_BACK, C_OFF);
        break;
    case Qt::Key_PageUp:
        camera.moveSwitch(C_UP, C_OFF);
        break;
    case Qt::Key_PageDown:
        camera.moveSwitch(C_DOWN, C_OFF);
        break;
    }
}



void GLTest::loadFile(const char *fileName){
    ifstream ifs(fileName);
    string str;
    while(ifs >> str){
        if(str == "Flower"){
            Flower flower;
            flower.read(ifs);
            flower.setCenterTexture(textureMgr.getTexture("center"));
            flower.setLeavesTexture(textureMgr.getTexture("leaves"));
            switch(flower.getTextureType()){
            case 0:
                flower.setFlowerTexture(textureMgr.getTexture("flower1"));
                break;
            case 1:
                flower.setFlowerTexture(textureMgr.getTexture("flower2"));
                break;
            case 2:
                flower.setFlowerTexture(textureMgr.getTexture("flower3"));
                break;
            default:
                flower.setFlowerTexture(textureMgr.getTexture("flower"));
                break;
            }

            setupFlowers(flower);
        }else if(str == "Tree"){
            Tree tree;
            tree.read(ifs);
            tree.setTexture(textureMgr.getTexture("brack"), textureMgr.getTexture("top"));
            setupTrees(tree);
        }
    }
}



void GLTest::saveFile(const char *fileName){
    ofstream ofs(fileName);
    for(size_t i = 0 ; i < flowers.size() ; i++){
        flowers[i].save(ofs);
    }
    for(size_t i = 0 ; i < trees.size() ; i++){
        trees[i].save(ofs);
    }
}
