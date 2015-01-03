
#include <gl/glut.h>
#include <vector>
using namespace std;

class Fence{
public:
    Fence(GLfloat cx = 0, GLfloat cy = 0, GLfloat cz = 0, GLfloat height = 4, GLfloat w = 1 << 7);
	void setTexture(GLuint t);
	void draw();
	void setHeight(vector<double> h1, vector<double> h2, vector<double> h3, vector<double> h4 );
	int getLength();
	int getSize();
private:
	void drawSideFrontBack();
	void drawSideLeftRight();
	int fenceLength;
	GLfloat centerX;
	GLfloat centerY;
	GLfloat centerZ;
	GLfloat height;
	GLfloat width;
	GLuint texture;
	bool textureLoaded;
	vector<double> frontHeight;
	vector<double> backHeight;
	vector<double> leftHeight;
	vector<double> rightHeight;
};
