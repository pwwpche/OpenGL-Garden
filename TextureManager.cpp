#include "TextureManager.h"
#include <QImage>
#include <QGLWidget>
#include <Qt>
#include <iostream>
#pragma comment(lib, "advapi32.lib")

TextureManager::TextureManager(){
	textureCnt = 0;

}

AUX_RGBImageRec* TextureManager::loadBMP(char *Filename)	{
	FILE *File=NULL;									// File Handle
	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}
    fopen_s(&File, Filename,"r");							// Check To See If The File Exists
	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoadA(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;										// If Load Failed Return NULL
}

int TextureManager::loadTextures(char* fileName, GLint method, char* textureName )									// Load Bitmaps And Convert To Textures
{
    int Status=false;									// Status Indicator

    QImage tex, buf;
    if ( !buf.load( fileName ) )
	{
		
        Status=FALSE;
		std::cerr << fileName << std::endl;
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, QImage::Format_RGB32 );
        dummy.fill( 1 << 10 );
        buf = dummy;

    }else{
        qWarning("Loaded");
        Status=TRUE;									// Set The Status To TRUE
    }

    tex = QGLWidget::convertToGLFormat( buf );
        glGenTextures(1, &texture[textureCnt]);					// Create The Texture
        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, texture[textureCnt]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,method);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,method);
        textureIndex.insert(std::pair<char*, int>(textureName, textureCnt));
        textureCnt++;

	return Status;										// Return The Status
}

GLuint TextureManager::getTexture(char* textureName){
	if(textureIndex.find(textureName) == textureIndex.end()){
		return TEXTUREMGR_NOT_FOUND;
	}else{
		int index = textureIndex[textureName];
		return texture[index];
	}
}
