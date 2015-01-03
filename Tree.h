
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
using namespace std;
class Tree{
public:
    Tree(double height = 10.0 , double width = 4.0, int levels = 3);
	void setTexture(GLuint brack, GLuint top);
    double getHeight(GLfloat x, GLfloat z);
	void draw();
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void save(ofstream &ofs);
    void read(ifstream &ifs);
private:
	GLuint brackTexture, topTexture;
	GLfloat rootX, rootY, rootZ;
	GLfloat height, width, levels;
};
