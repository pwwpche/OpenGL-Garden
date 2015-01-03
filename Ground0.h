#ifndef CG_GROUND
#define CG_GROUND
#include <gl/glew.h>
#include <gl/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <gl/GLAUX.H>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
//Height map predefs

#define		MAP_TEXTURE_SIZE	  1024							// Size Of Our .RAW Height Map (NEW)
#define		STEP_SIZE	  4							// Width And Height Of Each Quad (NEW)
#define		HEIGHT_RATIO  1							// Ratio That The Y Is Scaled According To The X And Z (NEW)
#define PRINT_STEP 4

#define BUFFER_AREA 100
#define BUFFER_PRECISION 10
#define BUFFER_OFFSET BUFFER_AREA * BUFFER_PRECISION
#define BUFFER_LINE (BUFFER_AREA * 2 * BUFFER_PRECISION + 1)

#define SNOW_PRECISION 2
#define MAX_SNOW_AREA 100
#define SNOW_LINE  2 * MAX_SNOW_AREA * SNOW_PRECISION

#define PLANT_PRECISION 10

class Ground{
public:
    //Ground(){};
    ~Ground();
    Ground(int x = 0, int y = 0, int z = 0, int size = 1 << 8);
	void LoadRawFile(LPSTR strName, int nSize);
    inline GLfloat groundHeight(GLfloat x, GLfloat y, bool isCamera = false);
	void draw();
    float getPlantHeight(float x, float z);
    void setPlantArea(float startX, float startZ, float endX, float endZ);
    void setPlantHeight(float x, float z, float height);
    int plantFlake(float x, float z, int incr = 0);
    void setTexture(GLuint texture, GLuint _snowTexture);
    void setSnowTexture(int i, GLuint texture);
    void setHeight(GLdouble x,GLdouble z, int addVal);
    void accumulate(GLfloat x, GLfloat z);

private:
    //Set up GLEW functions
    bool funcStatus;
    void setupFunctions();
    void generateVertexBuffers();
	PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2f;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
	PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
    PFNGLGENBUFFERSARBPROC glGenBuffersARB;
    PFNGLBINDBUFFERARBPROC glBindBufferARB;
    PFNGLBUFFERDATAARBPROC glBufferDataARB;
    PFNGLBINDBUFFERPROC glBindBuffer;

    //This part is for VBO
    typedef std::vector<glm::vec3>  PositionBuffer;
    typedef std::vector<glm::vec4>  ColorBuffer;
    typedef std::vector<glm::vec3>  NormalBuffer;
    typedef std::vector<glm::vec2>  TexCoordBuffer;
    typedef std::vector<GLuint>     IndexBuffer;
    PositionBuffer  m_PositionBuffer;
    ColorBuffer     m_ColorBuffer;
    NormalBuffer    m_NormalBuffer;
    TexCoordBuffer  m_TexCoordBuffer;
    IndexBuffer     m_IndexBuffer;
    void setupVBO();
    static const unsigned int m_uiNumTextures = 3;
    GLuint  m_GLTextures[m_uiNumTextures];
    glm::mat4x4 m_LocalToWorldMatrix;
    glm::mat4x4 m_InverseLocalToWorldMatrix;

    // The dimensions of the heightmap texture
    glm::uvec2 m_HeightmapDimensions;

    // ID's for the VBO's
    GLuint  m_GLVertexBuffer;
    GLuint  m_GLNormalBuffer;
    GLuint  m_GLColorBuffer;
    GLuint  m_GLTex0Buffer;
    GLuint  m_GLTex1Buffer;
    GLuint  m_GLTex2Buffer;
    GLuint  m_GLIndexBuffer;

    //Buffered height data, precision is BUFFER_PRECISION
    void setupBufferHeight();
    bool checkSetup();
    inline float heightBuffer(float x, float z);
    inline int getBufferIndex(float x, float z);
    float* bufferHeight;

    //Plant Height
    float* plantHeight;
    char* needFlake;
    vector<glm::vec4> plantAreas;
    vector<glm::vec2> plantAreaSize;
    vector<float*> plantHeightMap;
    vector<char*> needFlakeMap;
    int currentMap;
	//Height Mat params
    BYTE g_HeightMap[MAP_TEXTURE_SIZE*MAP_TEXTURE_SIZE];

    //Textures used to render ground
    GLuint snowTexture, groundTexture;
    GLuint snowGrounds[20];
    bool textureLoaded;

    //Different ground render methods
    void drawGround();
    void drawGroundMulti();
    void drawGroundVBO();
    void drawSnow();

    //Initialize functions
    void setupBaseHeight();
    inline int positionToIndex(float x, float z);
    unsigned short* hasSnow;
    float* baseHeight;


    //Get accurate height value
    GLfloat getVal(GLdouble x, GLdouble z);

    //Avalanche
    void avalanche(int index, int size = 1);
    int downNeighbor(int index);
    int upNeighbor(int index);
    int leftNeighbor(int index);
    int rightNeighbor(int index);

    //Melting
    void melt();
    time_t startTime;



    int centerX, centerY, centerZ, mapSize;
};


#endif
