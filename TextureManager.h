#include <gl/GLAUX.H>
#include <gl/glut.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <soil\SOIL.h>
#include <map>
#include <string>
#pragma comment(lib,"glaux.lib")

const int MAX_TEXTURESIZE = 100;
const int TEXTUREMGR_NOT_FOUND = (1 << 28) - 123456789;

class TextureManager{
public:
	TextureManager();
	AUX_RGBImageRec *loadBMP(char *Filename);				// Loads A Bitmap Image
	int loadTextures(char* fileName, GLint method, char* textureName );
	GLuint getTexture(char* textureName);
	
private:
	std::map<char*, int> textureIndex;
	int textureCnt;
	GLuint texture[MAX_TEXTURESIZE];
};
