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
#include <ctime>
#include <map>
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

#define MAX_SNOW_PER_PLANT 10000

const float SNOW_PRECISION = 0.5;
const int MAX_SNOW_AREA = 100;
const int SNOW_OFFSET = (int)(SNOW_PRECISION * MAX_SNOW_AREA);
const int SNOW_LINE = (int)(2.0 * MAX_SNOW_AREA * SNOW_PRECISION + 1);

#define PLANT_PRECISION 30

class Ground{
public:
    //Ground(){};
    ~Ground();
    Ground(int x = 0, int y = 0, int z = 0, int size = 1 << 8);
	void LoadRawFile(LPSTR strName, int nSize);
    inline GLfloat groundHeight(GLfloat x, GLfloat y, bool getAccurate = false, bool isCamera = false);

    float getPlantHeight(float x, float z);
    void setPlantArea(float startX, float startZ, float endX, float endZ);
    void setPlantHeight(float x, float z, float height);
    bool plantIndexToPos(int plantIndex, int posIndex, float &x, float &z);
    int plantFlake(float x, float z, int incr = 0, int plantIndex = -1);
    const vector<int* >& getSnowPosition(){return snowPosition;}
    const vector<int >& getSnowPositionCnt(){return snowPositionCnt;}

	void draw();
    void setMeltingSpeed(int val);
    void setTexture(GLuint texture, GLuint _snowTexture);
    void setHeight(GLdouble x,GLdouble z, int addVal);
    void accumulate(GLfloat x, GLfloat z);

private:
    //Set up GLEW functions
    bool funcStatus;
    void setupFunctions();
    PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2f;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
    PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
    PFNGLGENBUFFERSARBPROC glGenBuffersARB;
    PFNGLBINDBUFFERARBPROC glBindBufferARB;
    PFNGLBUFFERDATAARBPROC glBufferDataARB;
    PFNGLBINDBUFFERPROC glBindBuffer;

    //This part is for VBO
    void generateVertexBuffers();
    void setupVBO();
    void drawGroundVBO();
    GLfloat getVBOHeight(GLfloat x, GLfloat z);
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

	//Height Mat params
    BYTE g_HeightMap[MAP_TEXTURE_SIZE*MAP_TEXTURE_SIZE];

    //Textures used to render ground
    GLuint snowTexture, groundTexture;
    bool textureLoaded;


    //Plant Height
    float* plantHeight;
    char *needFlake;
    vector< int*> snowPosition;
    vector<int> snowPositionCnt;
    inline int posToPlantIndex(int plant, float x, float z);
    vector<glm::vec4> plantAreas;
    vector<glm::vec2> plantAreaSize;
    vector<float*> plantHeightMap;
    vector<char*> needFlakeMap;
    int currentMap;

    //Record where the snow falls
    inline int positionToIndex(float x, float z);
    unsigned short* hasSnow;


    //Get accurate height value
    GLfloat getVal(GLdouble x, GLdouble z, bool isVBO = false);

    //Avalanche
    void avalanche(int index, int size = 1);
    int downNeighbor(int index);
    int upNeighbor(int index);
    int leftNeighbor(int index);
    int rightNeighbor(int index);

    //Melting
    void melt();
    clock_t startTime;
    int meltSpeed;

    //Different draw methods
    void drawGround();
    GLuint getRatioColor(int ratio);
    void drawGroundMulti();
    void drawSnow();

    int centerX, centerY, centerZ, mapSize;
};


#endif
