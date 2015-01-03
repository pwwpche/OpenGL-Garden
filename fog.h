#ifndef FOG_H
#define FOG_H

#include <GL/glut.h>
class Fog
{
public:
    Fog();
    void setup();
private:
    GLuint filter;                      // Which Filter To Use
    GLuint fogMode[3];   // Storage For Three Types Of Fog
    GLuint fogfilter;                    // Which Fog To Use
    GLfloat fogColor[4];      // Fog Color
};

#endif // FOG_H
