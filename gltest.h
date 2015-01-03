#ifndef GLTEST_H
#define GLTEST_H

#define GLEW_STATIC
#include <gl/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <QGLWidget>

#include "Camera.h"
#include "SkySphere.h"
#include "Ground.h"
#include "TextureManager.h"
#include "Fence.h"
#include "Tree.h"
#include "Flower.h"
#include "fog.h"

#include "Wind.h"
#include "Snow.h"

#include <vector>
#include <QKeyEvent>
#include <QMouseEvent>
#include <fstream>
#include <string>
#include <gl/glext.h>
using namespace std;
class GLTest;
static GLTest* test;
class GLTest : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLTest(QWidget *parent = 0, const char* name = "", bool fs = false);
    void paintGL();
    void initializeGL();
    void resizeGL(int width, int height);
    void setupFlowers(int textureType, int type, int levels, int levelCnt[]);
    void setupFlowers(Flower newFlower);
    void setupTrees(double height, double width, int levels);
    void setupTrees(Tree tree);
    void stopMoving();
    void stopSnow();
    void startSnow(int val);
    void setSnowArea(int val);
    void setMeltSpeed(int val);
    void setFallSpeed(float val);
    void setWindLevel(int direction, float value);
    void keyPressEvent2( QKeyEvent *e );
    void keyReleaseEvent2(QKeyEvent *e);
    void loadFile(const char* fileName);
    void saveFile(const char *fileName);

    void setGroundHeight(int val);
private:
    void genList();
    GLuint getTreeList();
    GLuint dList;
    vector<GLuint> dLists;
    TextureManager textureMgr;
    Ground ground;
    SkySphere sky;
    Camera camera;
    Fence fence;
    Tree tree;
    Flower flower1;


    Fog fog;
    Snow snow;
    Wind wind;

    vector<Tree> trees;
    vector<Flower> flowers;
    int repeat;
signals:

public slots:

};


#endif // GLTEST_H
