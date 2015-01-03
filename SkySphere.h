#include <gl/glew.h>
#include <gl/glut.h>
//#include <gl/GLAUX.H>

class SkySphere{
public:
    SkySphere(){rotation = 0;};
	void draw(GLuint texture);
private:
    GLfloat rotation;
	GLfloat angle;
};
