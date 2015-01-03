#include "Wind.h"
#include "Flake.h"
#include "Ground.h"

#include <gl/glew.h>
#include <gl/glut.h>
#include <gl/glext.h>


#include <iostream>
#include<list>
#include <vector>
#include <math.h>
#include <sys/utime.h>
using namespace std;
class Snow{
public:
	Snow();
	Snow(int areaSize, int maxHeight, int flakeCount);
    ~Snow();
    void setup(int areaSize, int maxHeight, int flakeCount);
    void draw(Wind &wind, Ground &ground);
    void start(int flakeCount);
    void setArea(int _areaSize);
    void stop();
    void init(GLuint _flakeTexture);


private:



    void generateFlakes();
    PFNGLPOINTPARAMETERFARBPROC  glPointParameterfARB;
    PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;
    GLuint flakeTexture;

    inline void generateSnowPos(GLfloat &x, GLfloat &y, GLfloat &z);
    list<Flake> snow;

    Flake* plantFlake;
    int plantFlakeCnt;

    int snowCount;
	int flakeCount;
	GLfloat areaSize;
	GLfloat maxHeight;
};
