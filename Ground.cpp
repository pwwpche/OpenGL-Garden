#include "Ground.h"
#include <iostream>
#include <fstream>
using namespace std;
#define GRASS_SIZE 128
#define START_ACCUMULATE 100
#define AVALANCHE_HEIGHT 300
Ground::Ground(int x, int y, int z, int size){
    LoadRawFile("./Data/Terrain.raw", MAP_TEXTURE_SIZE * MAP_TEXTURE_SIZE);
    textureLoaded = false;
	centerX = x;
	centerY = y;
	centerZ = z;
	mapSize = size;
    startTime = std::clock();
    meltSpeed = 0;
    //Record which area has snow and height of snow
    hasSnow = new unsigned short[SNOW_LINE * SNOW_LINE];
	funcStatus = false;	
    memset(hasSnow, 0, sizeof(short) * SNOW_LINE * SNOW_LINE);
    setupBufferHeight();
	glewInit();
    setupVBO();
    cout << "glewinit" << endl;
}

Ground::~Ground(){
    delete [] hasSnow;
    delete [] bufferHeight;
    delete [] plantHeight;
    delete [] needFlake;

}

int Ground::getBufferIndex(float x, float z){
    int i = (int)floor(x * BUFFER_PRECISION + 0.5);
    int j = (int)floor(z * BUFFER_PRECISION + 0.5);
    int index = (i+ BUFFER_OFFSET) * BUFFER_LINE
            + (j + BUFFER_OFFSET);
    return index;
}



float Ground::heightBuffer(float x, float z){
    if(x <= -BUFFER_AREA ||
            x >= BUFFER_AREA ||
            z <= -BUFFER_AREA ||
            z >= BUFFER_AREA)
    {
        return groundHeight(x, z, true);
    }

    int index = getBufferIndex(x, z);
    return bufferHeight[index];
}



void Ground::setupBufferHeight(){
    //Set up ground base height buffer
    bufferHeight = new float[BUFFER_LINE * BUFFER_LINE];
    plantHeight = new float[BUFFER_LINE * BUFFER_LINE];
    needFlake = new char[BUFFER_LINE * BUFFER_LINE];
    memset(bufferHeight, 0, sizeof(float) * BUFFER_LINE * BUFFER_LINE);
    memset(needFlake, 0, sizeof(char) * BUFFER_LINE * BUFFER_LINE );
    for(int i = -BUFFER_OFFSET ; i <= BUFFER_OFFSET ; i++){
        for(int j = -BUFFER_OFFSET ; j <= BUFFER_OFFSET ; j++){
           float x = (float)i / (float)BUFFER_PRECISION;
           float z = (float)j / (float)BUFFER_PRECISION;
           int index = (i + BUFFER_OFFSET) * BUFFER_LINE + (j +BUFFER_OFFSET);
            bufferHeight[index] = groundHeight(x, z, true);
        }
    }
    memcpy(plantHeight, bufferHeight, sizeof(float)  * BUFFER_LINE * BUFFER_LINE);
}


bool Ground::checkSetup(){
    cout << "Checking setup" << endl;
    ofstream ofs("C:/1.txt", ios::app);
    for(int i =-BUFFER_OFFSET ; i < BUFFER_OFFSET ; i++){
        for(int j = -BUFFER_OFFSET ; j < BUFFER_OFFSET ; j++){
            float x = (float)i / (float)BUFFER_PRECISION;
            float z = (float)j / (float)BUFFER_PRECISION;
            float res = heightBuffer(x, z) - groundHeight(x, z, true);
            if(res < -0.05 || res > 0.05){
                ofs <<"ERR: x="<< x << " z=" << z << endl;
            }
        }
    }
    ofs.close();
    return true;
}



void Ground::LoadRawFile(LPSTR strName, int nSize)
{
	FILE *pFile = NULL;
    fopen_s(&pFile, strName, "rb" );
	if ( pFile == NULL )	
	{
		return;
	}
	fread( g_HeightMap, 1, nSize, pFile );
	fclose(pFile);
}


GLfloat Ground::groundHeight(GLfloat x, GLfloat z, bool getAccurate, bool isCamera)				// This Returns The Height From A Height Map Index
{
    if(!getAccurate){
        int ix = (int)x;
        int iz = (int)z;
        ix = ix - ix % PRINT_STEP;
        ix = x < 0 ? ix - PRINT_STEP : ix;
        iz = iz - iz % PRINT_STEP;
        iz = z < 0 ? iz - PRINT_STEP : iz;

        if(x >= (centerX + mapSize / 2.0) ||
            x <= (centerX - mapSize / 2.0) ||
            z >= (centerZ + mapSize / 2.0) ||
            z <= (centerZ - mapSize / 2.0)
            ){
                return 0;
        }

        int heightX = (ix - centerX + mapSize / 2) *MAP_TEXTURE_SIZE / mapSize;								// Error Check Our x Value
        int heightY = (iz - centerZ + mapSize / 2) * MAP_TEXTURE_SIZE / mapSize;								// Error Check Our y Value
        if(!g_HeightMap) {
            return 0;							// Make Sure Our Data Is Valid
        }

        int result = g_HeightMap[heightX + (heightY * MAP_TEXTURE_SIZE)]  / 32;
        return result;
	}else{
        double resultFloat = getVal(x, z, isCamera);
		return resultFloat;
	}
}


float Ground::getPlantHeight(float x, float z){
    if(x <= -BUFFER_AREA ||
            x >= BUFFER_AREA ||
            z <= -BUFFER_AREA ||
            z >= BUFFER_AREA)
    {
        return groundHeight(x, z, true);
    }
    if(PLANT_PRECISION <= 10){
        int index = getBufferIndex(x, z);
        return plantHeight[index];
    }else{
        x = floor(x * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
        z = floor(z * PLANT_PRECISION + 0.5) / PLANT_PRECISION;

        size_t size = plantAreas.size();
        float result = heightBuffer(x, z);
        for(size_t i = 0 ; i < size ; i++){
            if(x > plantAreas[i][0] && x <  plantAreas[i][2] &&
                z > plantAreas[i][1] && z <  plantAreas[i][3]    )
            {
                int colCnt = plantAreaSize[i][0];
                int index = ((z - plantAreas[i][1]) * PLANT_PRECISION * colCnt) + (x - plantAreas[i][0]) * PLANT_PRECISION;
                if(plantHeightMap[i][index] > result){
                    result = plantHeightMap[i][index] + (float)needFlakeMap[i][index] / 40.0 - 0.1 ;
                }

            }
        }
        return result;
    }
}

void Ground::setPlantArea(float startX, float startZ, float endX, float endZ){
    if(PLANT_PRECISION <= 10){
        return ;
    }

    startX = floor(startX * PLANT_PRECISION + 0.5);
    startZ = floor(startZ * PLANT_PRECISION + 0.5);
    endX = floor(endX * PLANT_PRECISION + 0.5);
    endZ = floor(endZ * PLANT_PRECISION + 0.5);

    plantAreas.push_back(glm::vec4(startX / PLANT_PRECISION, startZ  / PLANT_PRECISION,
                                                    endX  / PLANT_PRECISION, endZ  / PLANT_PRECISION));


    int colCnt = (endX - startX) + 1;
    int rowCnt = (endZ - startZ) + 1;

    plantAreaSize.push_back(glm::vec2(colCnt, rowCnt));

    int areaCount = rowCnt * colCnt;
    float* currentArea = new float[areaCount];
    char* needFlakeArea = new char[areaCount];
    memset(needFlakeArea, 0, sizeof(char) * areaCount);
    plantHeightMap.push_back(currentArea);
    needFlakeMap.push_back(needFlakeArea);

    currentMap = plantHeightMap.size() - 1;
    return;
}

void Ground::setPlantHeight(float x, float z, float height){

    //cout << "Setting plant height x=" << x << " z=" << z << " height=" << height << endl;
    if(x <= -BUFFER_AREA ||
            x >= BUFFER_AREA ||
            z <= -BUFFER_AREA ||
            z >= BUFFER_AREA)
    {
        return ;
    }

    if(PLANT_PRECISION > 10){
        x = floor(x * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
        z = floor(z * PLANT_PRECISION + 0.5) / PLANT_PRECISION;

        int colCnt = plantAreaSize[currentMap][0];

        int index = ((z - plantAreas[currentMap][1]) * PLANT_PRECISION * colCnt) + (x - plantAreas[currentMap][0]) * PLANT_PRECISION;
        int areaCount = plantAreaSize[currentMap][0] * plantAreaSize[currentMap][1];
        if(index >= areaCount){
            return ;
        }
        plantHeightMap[currentMap][index] = height;
        if(height > groundHeight(x, z, true)){
            needFlakeMap[currentMap][index] = true;
        }
    }else{
        int index = getBufferIndex(x, z);
        if(height > plantHeight[index]){
            plantHeight[index] = height;
            needFlake[index] = 1;
        }
    }
    return ;
}

bool Ground::plantIndexToPos(int plantIndex, int posIndex, float &x, float &z){
    if(PLANT_PRECISION <= 10){      //No need to use this function
        return false;
    }

    if(plantIndex > plantAreas.size()){     //This plant does not exist
        return false;
    }
    int colCount = plantAreaSize[plantIndex][0];
    int rowCount = plantAreaSize[plantIndex][1];
    if(posIndex > rowCount * colCount){     //Position index is outside plant area
        return false;
    }

    float startX = plantAreas[plantIndex][0];
    float startZ = plantAreas[plantIndex][1];

    z = (float)posIndex / (float)colCount / (float)PLANT_PRECISION + startZ;
    x = (float)(posIndex % colCount) / (float)PLANT_PRECISION + startX;
    return true;
}

int Ground::plantFlake(float x, float z, int incr, int plantIndex){
    if(PLANT_PRECISION > 10){

        //Get which plant the flake falls onto
        x = floor(x * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
        z = floor(z * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
        size_t size = plantAreas.size();
        float maxHeight = heightBuffer(x, z);
        int rectIndex = -1, plantPosIndex = -1, colCnt = -1;
        if(plantIndex != -1 && plantIndex < size){
            if(x > plantAreas[plantIndex][0] && x <  plantAreas[plantIndex][2] &&     //Make sure current (x, z) falls into the area of this plant
                z > plantAreas[plantIndex][1] && z <  plantAreas[plantIndex][3]    ){
                rectIndex = plantIndex;
                colCnt = plantAreaSize[rectIndex][0];       //convert (x, z) into position index
                plantPosIndex = ((z - plantAreas[rectIndex][1]) * PLANT_PRECISION * colCnt) +
                        (x - plantAreas[rectIndex][0]) * PLANT_PRECISION;
            }
        }else{
            //Search the vector storing height map of plants
            for(size_t i = 0 ; i < size ; i++){
                if(x > plantAreas[i][0] && x <  plantAreas[i][2] &&     //current (x, z) falls into the area of current plant
                    z > plantAreas[i][1] && z <  plantAreas[i][3]    )
                {
                    int colCnt = plantAreaSize[i][0];       //convert (x, z) into position index
                    plantPosIndex = ((z - plantAreas[i][1]) * PLANT_PRECISION * colCnt) +
                                                (x - plantAreas[i][0]) * PLANT_PRECISION;
                    //Is this the highest point?
                    if(plantHeightMap[i][plantPosIndex]  > maxHeight){
                        rectIndex = i;
                        maxHeight = plantHeightMap[i][plantPosIndex];
                    }
                }
            }
        }
        //Plant not found
        if(rectIndex == -1){
            return -1;
        }else{
			 if(incr == 0){      //Just get the flake number, don't increase snow onto it.
				return needFlakeMap[rectIndex][plantPosIndex];
			}
            //Plant found, draw flakes on it and increase flake height
            int currentFlake = 0;
            if( needFlakeMap[rectIndex][plantPosIndex] > 0){
                needFlakeMap[rectIndex][plantPosIndex]+= incr;
                currentFlake = needFlakeMap[rectIndex][plantPosIndex];
                if(snowPosition.size() < rectIndex + 1){
                    snowPosition.resize(rectIndex + 1);
                    snowPosition[rectIndex].insert( pair< int , float > (plantPosIndex, getPlantHeight(x, z)));
                    cout << plantPosIndex << endl;
                }else{
                    cout << plantPosIndex << endl;
                    snowPosition[rectIndex][plantPosIndex] = getPlantHeight(x, z);
                }
            }

            //Avalanching
            float posInterval = (1.0 / PLANT_PRECISION);
            int dist = 5;
            int neighborFlake = 0;
            //Left neighbor
            neighborFlake = plantFlake(x - posInterval, z, 0, rectIndex);
            currentFlake = needFlakeMap[rectIndex][plantPosIndex];
            if(neighborFlake >= 0){    //This position has flake on it
                if(currentFlake - neighborFlake > dist){
                    cout << "avalanching index=" << plantPosIndex << endl;
                    int minus =  (currentFlake - neighborFlake - dist) / 2;
                    needFlakeMap[rectIndex][plantPosIndex] -= minus;
                    plantFlake(x - posInterval, z, minus, rectIndex);
                }
            }

            //Right neighbor
            neighborFlake = plantFlake(x + posInterval, z, 0, rectIndex);
            currentFlake = needFlakeMap[rectIndex][plantPosIndex];
            if(neighborFlake >= 0){    //This position has flake on it
                if(currentFlake - neighborFlake > dist){
                    cout << "avalanching index=" << plantPosIndex << endl;
                    int minus =  (currentFlake - neighborFlake - dist) / 2;
                    needFlakeMap[rectIndex][plantPosIndex] -= minus;
                    plantFlake(x + posInterval, z, minus, rectIndex);
                }
            }

            //Up neighbor
            neighborFlake = plantFlake(x, z - posInterval, 0, rectIndex);
            currentFlake = needFlakeMap[rectIndex][plantPosIndex];
            if(neighborFlake >= 0){    //This position has flake on it
                if(currentFlake - neighborFlake > dist){
                    cout << "avalanching index=" << plantPosIndex << endl;
                    int minus =  (currentFlake - neighborFlake - dist) / 2;
                    needFlakeMap[rectIndex][plantPosIndex] -= minus;
                    plantFlake(x, z- posInterval, minus, rectIndex);
                }
            }
            //Down neighbor
            neighborFlake = plantFlake(x , z + posInterval, 0, rectIndex);
            currentFlake = needFlakeMap[rectIndex][plantPosIndex];
            if(neighborFlake >= 0){    //This position has flake on it
                if(currentFlake - neighborFlake > dist){
                    cout << "avalanching index=" << plantPosIndex << endl;
                    int minus =  (currentFlake - neighborFlake - dist) / 2;
                    needFlakeMap[rectIndex][plantPosIndex] -= minus;
                    plantFlake(x, z + posInterval, minus, rectIndex);
                }
            }
            return needFlakeMap[rectIndex][plantPosIndex];
        }
    }else{
        int plantIndex = getBufferIndex(x, z);
        if(needFlake[plantIndex] > 0 && needFlake[plantIndex] < 100) {
            needFlake[plantIndex]+= incr;
        }
        return needFlake[plantIndex];
    }
}




void Ground::setHeight(GLdouble x,GLdouble z, int addVal){
    int ix = (int)x;
    int iz = (int)z;
    ix = ix - ix % PRINT_STEP;
    ix = x < 0 ? ix - PRINT_STEP : ix;
    iz = iz - iz % PRINT_STEP;
    iz = z < 0 ? iz - PRINT_STEP : iz;

    if(x >= (centerX + mapSize / 2.0) ||
        x <= (centerX - mapSize / 2.0) ||
        z >= (centerZ + mapSize / 2.0) ||
        z <= (centerZ - mapSize / 2.0)
        ){
            return ;
    }

    int heightX = (ix - centerX + mapSize / 2) *MAP_TEXTURE_SIZE / mapSize;								// Error Check Our x Value
    int heightY = (iz - centerZ + mapSize / 2) * MAP_TEXTURE_SIZE / mapSize;								// Error Check Our y Value


    if(!g_HeightMap) return ;							// Make Sure Our Data Is Valid
    int result = g_HeightMap[heightX + (heightY * MAP_TEXTURE_SIZE)];

    result = result + addVal > 255 ? 255 : result + addVal;
    result = result + addVal < 0 ? 0 : result + addVal;

    g_HeightMap[heightX + (heightY * MAP_TEXTURE_SIZE)] = result;
    return ;
}

void Ground::setupFunctions(){

    glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2f");
    glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC ) wglGetProcAddress("glActiveTextureARB");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC ) wglGetProcAddress("glActiveTexture");
    glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC ) wglGetProcAddress("glClientActiveTextureARB");
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC )wglGetProcAddress("glBufferDataARB");
    glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");
    funcStatus = true;
}

void Ground::generateVertexBuffers(){
    cout << "Generate vertex buffer" << endl;
    //Generate Vertex Buffer
    // First generate the buffer object ID's
    cout << glGenBuffersARB << endl;
    glGenBuffersARB(1, &m_GLVertexBuffer);
    glGenBuffersARB(1, &m_GLNormalBuffer);
    glGenBuffersARB(1, &m_GLColorBuffer);
    glGenBuffersARB(1, &m_GLTex0Buffer);
    glGenBuffersARB(1, &m_GLTex1Buffer);
    glGenBuffersARB(1, &m_GLTex2Buffer);
    glGenBuffersARB(1, &m_GLIndexBuffer);
    cout << "Copy host data" << endl;
    // Copy the host data into the vertex buffer objects
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLVertexBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec3) * m_PositionBuffer.size(), &(m_PositionBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLColorBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec4) * m_ColorBuffer.size(), &(m_ColorBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLNormalBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec3) * m_NormalBuffer.size(), &(m_NormalBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex0Buffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec2) * m_TexCoordBuffer.size(), &(m_TexCoordBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex1Buffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec2) * m_TexCoordBuffer.size(), &(m_TexCoordBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex2Buffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec2) * m_TexCoordBuffer.size(), &(m_TexCoordBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_GLIndexBuffer );
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLuint) * m_IndexBuffer.size(), &(m_IndexBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBuffer( GL_ARRAY_BUFFER_ARB, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
}

void Ground::setupVBO(){

    int halfSize = mapSize / 2;
    unsigned int lineCount = mapSize / PRINT_STEP;
    unsigned int numVerts = lineCount * lineCount;

    m_PositionBuffer.resize( numVerts);
    m_ColorBuffer.resize( numVerts);
    m_NormalBuffer.resize( numVerts);
    m_TexCoordBuffer.resize( numVerts);

    m_HeightmapDimensions = glm::uvec2(lineCount, lineCount);
    float x0, y0, z0;
    int x, z;
    unsigned int index = 0;
    cout << "Setup vertex array object" << endl;

    for(z = centerX - halfSize ; z < centerX + halfSize ; z += PRINT_STEP)
    {
        for(x = centerZ - halfSize ; x < centerZ + halfSize ; x += PRINT_STEP)
        {
            // Get The (X, Y, Z) Value For The Bottom Left Vertex
            index = (z + halfSize) / PRINT_STEP * lineCount + (x + halfSize) / PRINT_STEP;
            x0 = x;
            z0 = z;
            y0 = groundHeight(x0, z0, true );
            float tex0Contribution = 0.0;
            float tex2Contribution = 1.0 - tex0Contribution;
            m_NormalBuffer[index] = glm::vec3(0);
            m_PositionBuffer[index] = glm::vec3( x0, y0, z0 );
            m_ColorBuffer[index] = glm::vec4( tex0Contribution, tex0Contribution, tex0Contribution, tex2Contribution );
            index++;
        }
        cout <<"VBO: x=" << x << " z=" << z << " index=" << index << endl;
    }

    cout << "Generate index buffer" << endl;
    //Generate index buffer
    const unsigned int numTriangles = ( lineCount - 1 ) * ( lineCount - 1 ) * 2;

    m_IndexBuffer.resize( numTriangles * 3 );
    m_TexCoordBuffer.resize( numTriangles * 3 );
    int i, j, vertexIndex, px, pz, ix, iz;
    index = 0;
    for (i = -halfSize; i < halfSize  - PRINT_STEP; i+=PRINT_STEP )
    {
        for (j = -halfSize; j < halfSize  - PRINT_STEP; j+=PRINT_STEP )
        {
            iz = (i + halfSize ) / PRINT_STEP;
            ix = (j + halfSize ) / PRINT_STEP;
            vertexIndex = ( iz * lineCount ) + ix;
            pz = vertexIndex / lineCount * PRINT_STEP - halfSize;
            px = (vertexIndex % lineCount) * PRINT_STEP - halfSize;
            // Top triangle (T0)

            //Height Wrong
            m_TexCoordBuffer[index] = glm::vec2(1,0);
            m_IndexBuffer[index++] = vertexIndex;                           // V0
            m_TexCoordBuffer[index] = glm::vec2(1,1);
            m_IndexBuffer[index++] = vertexIndex + lineCount + 1;        // V3
            m_TexCoordBuffer[index] = glm::vec2(0,1);
            m_IndexBuffer[index++] = vertexIndex + 1;                       // V1


            m_TexCoordBuffer[index] = glm::vec2(1,0);
            m_IndexBuffer[index++] = vertexIndex;                           // V0
            m_TexCoordBuffer[index] = glm::vec2(0,0);
            m_IndexBuffer[index++] = vertexIndex + lineCount;            // V2
            m_TexCoordBuffer[index] = glm::vec2(0,1);
            m_IndexBuffer[index++] = vertexIndex + lineCount + 1;        // V3


            //One vertex wrong
            /*
            m_TexCoordBuffer[index] = glm::vec2(1,0);
            m_IndexBuffer[index++] = vertexIndex + lineCount;            // V2
            m_TexCoordBuffer[index] = glm::vec2(0,0);
            m_IndexBuffer[index++] = vertexIndex + 1;                       // V1
            m_TexCoordBuffer[index] = glm::vec2(0,1); //R
            m_IndexBuffer[index++] = vertexIndex;                           // V0

            m_TexCoordBuffer[index] = glm::vec2(0,1);
            m_IndexBuffer[index++] = vertexIndex + lineCount;            // V2
            m_TexCoordBuffer[index] = glm::vec2(1,1); //
            m_IndexBuffer[index++] = vertexIndex + lineCount + 1;        // V3
            m_TexCoordBuffer[index] = glm::vec2(1,0);
            m_IndexBuffer[index++] = vertexIndex + 1;                       // V1
    */
        }
    }
    cout << "Generate Normals" << endl;
    //Generate Normals
    unsigned int indexBufSize = m_IndexBuffer.size();
    for ( unsigned int i = 0; i < indexBufSize; i += 3 )
    {
        glm::vec3 v0 = m_PositionBuffer[ m_IndexBuffer[i + 0] ];
        glm::vec3 v1 = m_PositionBuffer[ m_IndexBuffer[i + 2] ];
        glm::vec3 v2 = m_PositionBuffer[ m_IndexBuffer[i + 1] ];

        glm::vec3 normal = glm::normalize( glm::cross( v1 - v0, v2 - v0 ) );

        m_NormalBuffer[ m_IndexBuffer[i + 0] ] += normal;
        m_NormalBuffer[ m_IndexBuffer[i + 1] ] += normal;
        m_NormalBuffer[ m_IndexBuffer[i + 2] ] += normal;
    }
    const glm::vec3 UP( 0.0f, 1.0f, 0.0f );
    for ( unsigned int i = 0; i < m_NormalBuffer.size(); ++i )
    {
        m_NormalBuffer[i] = glm::normalize( m_NormalBuffer[i] );
        float fTexture0Contribution = m_NormalBuffer[i][1] - 0.1f;
        m_ColorBuffer[i] = glm::vec4( fTexture0Contribution, fTexture0Contribution, fTexture0Contribution, m_ColorBuffer[i].w );
    }

}

void Ground::drawGroundVBO(){
    glPushMatrix();

    //cout << "drawing" << endl;

    glActiveTextureARB( GL_TEXTURE0_ARB );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, groundTexture );
    glClientActiveTextureARB(GL_TEXTURE0_ARB);
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex0Buffer );
    glTexCoordPointer( 2, GL_FLOAT, 0, 0 );

    //cout << "stage 1" << endl;
    glActiveTextureARB(GL_TEXTURE1_ARB );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, groundTexture );

    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_COLOR );

    glClientActiveTextureARB(GL_TEXTURE1_ARB);
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex1Buffer );
    glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
   // cout << "stage 2" << endl;
    //
    // Texture Stage 2
    //
    // Perform a linear interpolation between the output of stage 1
    // (i.e texture0 mixed with texture1) and texture2 and use the ALPHA
    // portion of the vertex's color to mix the two.
    //
    glActiveTextureARB( GL_TEXTURE2_ARB );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, snowTexture );

    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR );

    glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB );
    glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_ALPHA );

    glClientActiveTextureARB(GL_TEXTURE2_ARB);
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLTex2Buffer );
    glTexCoordPointer( 2, GL_FLOAT, 0, 0 );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    //cout << "stage 3" << endl;
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLVertexBuffer );
    glVertexPointer( 3, GL_FLOAT, 0, 0 );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLColorBuffer );
    glColorPointer( 4, GL_FLOAT, 0, 0 );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLNormalBuffer );
    glNormalPointer( GL_FLOAT, 0, 0 );

    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_GLIndexBuffer );
    glDrawElements( GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, 0 );
    //cout << "leaving" << endl;
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    glActiveTextureARB(GL_TEXTURE2_ARB);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
    glClientActiveTextureARB(GL_TEXTURE2_ARB);
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

    glActiveTextureARB(GL_TEXTURE1_ARB);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
    glClientActiveTextureARB(GL_TEXTURE1_ARB);
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

    glActiveTextureARB(GL_TEXTURE0_ARB);
    glBindTexture(GL_TEXTURE_2D, 0);
    glClientActiveTextureARB(GL_TEXTURE0_ARB);
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

GLfloat Ground::getVBOHeight(GLfloat x, GLfloat z){
    int ix = (int) (x + mapSize / 2);
    int iz = (int) (z + mapSize / 2);
    //Get which rectangle (x,z) belongs to

    ix = ix - ix % PRINT_STEP;
    iz = iz - iz % PRINT_STEP;

    //Get index in VBO
    int lineCount = mapSize / PRINT_STEP;
    int indexVBO = iz / PRINT_STEP * lineCount + ix / PRINT_STEP ;
    return m_PositionBuffer[indexVBO][1];
}

GLfloat Ground::getVal(GLdouble x, GLdouble z, bool isVBO)		//Bottom-Left, Bottom-Right, Up-Left, Up-Right
{
        int ix = (int)x;
        int iz = (int)z;
        ix = ix - ix % PRINT_STEP;
        ix = x < 0 ? ix - PRINT_STEP : ix;
        iz = iz - iz % PRINT_STEP;
        iz = z < 0 ? iz - PRINT_STEP : iz;

        double y1, y2, y3, c1, c2;
        if(!isVBO){
            y2 = groundHeight(ix, iz + PRINT_STEP);
            y3 = groundHeight(ix + PRINT_STEP, iz);
        }else{
            y2 = getVBOHeight(ix, iz + PRINT_STEP);
            y3 = getVBOHeight(ix + PRINT_STEP, iz);
        }
        double a = (double)(x - ix);
        double b = (double)(z - iz);
        if(b < PRINT_STEP - a){
            y1 = isVBO ? getVBOHeight(ix, iz) : groundHeight(ix, iz);
            c1 = b / (double)PRINT_STEP;
            c2 = a / (double)PRINT_STEP;
        }else{
            y1 = isVBO ? getVBOHeight(ix + PRINT_STEP, iz + PRINT_STEP) : groundHeight(ix + PRINT_STEP, iz + PRINT_STEP);
            c1 = -a / (double)PRINT_STEP + 1;
            c2 = -b / (double)PRINT_STEP + 1;
        }
        double result = y1 + c1 * (y2 - y1) + c2 * (y3 - y1);
        return result;
}

void Ground::accumulate(GLfloat x, GLfloat z){
    if (x < MAX_SNOW_AREA && x > -MAX_SNOW_AREA && 
		z < MAX_SNOW_AREA && z > -MAX_SNOW_AREA){        //Max area size should be < 100
        int index = positionToIndex(x, z);
        plantFlake(x, z, 1);
        avalanche(index, 1);
    }
}

void Ground::avalanche(int index, int size){
    if(size == 0){
        return;
    }

    hasSnow[index]+= size;

    int neighbor = upNeighbor(index);
    if(hasSnow[index] - hasSnow[neighbor] > AVALANCHE_HEIGHT ){
        int minus =  (hasSnow[index] - hasSnow[neighbor]- AVALANCHE_HEIGHT) / 2;
        hasSnow[index] -= (minus);
        avalanche(neighbor, minus);
    }

    neighbor = downNeighbor(index);
    if(hasSnow[index] - hasSnow[neighbor] > AVALANCHE_HEIGHT ){
        int minus =  (hasSnow[index] - hasSnow[neighbor]- AVALANCHE_HEIGHT) / 2;
        hasSnow[index] -= (minus);
        avalanche(neighbor, minus);
    }

    neighbor = leftNeighbor(index);
    if(hasSnow[index] - hasSnow[neighbor] > AVALANCHE_HEIGHT ){
        int minus =  (hasSnow[index] - hasSnow[neighbor]- AVALANCHE_HEIGHT) / 2;
        hasSnow[index] -= (minus);
        avalanche(neighbor, minus);
    }

    neighbor = rightNeighbor(index);
    if(hasSnow[index] - hasSnow[neighbor] > AVALANCHE_HEIGHT ){
        int minus =  (hasSnow[index] - hasSnow[neighbor]- AVALANCHE_HEIGHT) / 2;
        hasSnow[index] -= (minus);
        avalanche(neighbor, minus);
    }

}

int Ground::downNeighbor(int index){
    if(index > SNOW_LINE * (SNOW_LINE - 1)){
        return index;
    }else{
        return index + SNOW_LINE;
    }
}

int Ground::upNeighbor(int index){
    if(index < SNOW_LINE){
        return index;
    }else{
        return index + SNOW_LINE;
    }
}

int Ground::leftNeighbor(int index){
    if(index % SNOW_LINE == 0){
        return index;
    }else{
        return index - 1;
    }
}

int Ground::rightNeighbor(int index){
    if((index + 1) % SNOW_LINE == 0){
        return index;
    }else{
        return index + 1;
    }
}

int Ground::positionToIndex(float x, float z){
	x = floor(x * SNOW_PRECISION + 0.5) ;
	z = floor(z * SNOW_PRECISION + 0.5) ;
	int result = (z + SNOW_OFFSET) * SNOW_LINE + (x + SNOW_OFFSET);
    return result;
}

int Ground::posToPlantIndex(int plant, float x, float z){
    x = floor(x * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
    z = floor(z * PLANT_PRECISION + 0.5) / PLANT_PRECISION;
    int colCnt = plantAreaSize[plant][0];
    int index = ((z - plantAreas[plant][1]) * PLANT_PRECISION * colCnt) + (x - plantAreas[plant][0]) * PLANT_PRECISION;
    return index;
}

GLuint Ground::getRatioColor(int ratio){
    unsigned int textureId = 0;
    //生成纹理名字
    glGenTextures(1, &textureId);
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //存储纹理数据到硬件内存中
    int blendRatio = ratio;
    int blendAlpha = 20;
    char snow_data[2][2][4] = {blendRatio, blendRatio, blendRatio, blendAlpha,
                               blendRatio, blendRatio, blendRatio, blendAlpha,
                               blendRatio, blendRatio, blendRatio, blendAlpha,
                               blendRatio, blendRatio, blendRatio, blendAlpha
                              };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, snow_data);
    //设置纹理放大、缩小时的过滤方法
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return textureId;
}

void Ground::drawGroundMulti()					// This Renders The Height Map As Quads
{
    cout << "miltitexture started" << endl;
    int x, z;										// Create Some Variables For Readability
    int x0, y0, z0;

    if(!g_HeightMap){
        return;								// Make Sure Our Height Data Is Valid
    }




    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    glActiveTexture(GL_TEXTURE1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getRatioColor(20));



    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
    glTexEnvf(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);
    glTexEnvf(GL_TEXTURE_ENV,GL_SRC0_RGB,GL_TEXTURE);
    glTexEnvf(GL_TEXTURE_ENV,GL_OPERAND0_RGB,GL_SRC_COLOR);
    glTexEnvf(GL_TEXTURE_ENV,GL_SRC1_RGB,GL_PREVIOUS);
    glTexEnvf(GL_TEXTURE_ENV,GL_OPERAND1_RGB,GL_SRC_COLOR);



   // glEnable (GL_BLEND);


    int halfSize = mapSize / 2;
    for(x = centerX - mapSize / 2 ; x < centerX + halfSize ; x+=PRINT_STEP){
        for(z = centerZ - mapSize / 2 ; z < centerZ + halfSize ; z+=PRINT_STEP)
        {

            glBegin( GL_QUADS );							// Render Polygons
            // Get The (X, Y, Z) Value For The Bottom Left VertexZZZ
			x0 = x;
			z0 = z;
            y0 = groundHeight(x0, z0 );
            glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
            glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
            //glTexCoord2f(0,0);
            glVertex3i(x0, y0, z0);

			// Get The (X, Y, Z) Value For The Top Left Vertex
			x0 = x;
			z0 = z + PRINT_STEP ;					
            y0 = groundHeight(x0, z0 );
            //glTexCoord2f(0,1);
            glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
            glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
            glVertex3i(x0, y0, z0);						// Send This Vertex To OpenGL To Be Rendered
            glBindTexture(GL_TEXTURE_2D, getRatioColor(100));
			// Get The (X, Y, Z) Value For The Top Right Vertex
			x0 = x + PRINT_STEP; 
			z0 = z + PRINT_STEP ;
            y0 = groundHeight(x0, z0 );
            //glTexCoord2f(1,1);
            glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
            glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
            glVertex3i(x0, y0, z0);

			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			x0 = x + PRINT_STEP; 
			z0 = z;
            y0 = groundHeight( x0, z0 );
            //glTexCoord2f(1,0);
            glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
            glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
            glVertex3i(x0, y0, z0);
            glEnd();

		}
    }


    glActiveTexture (GL_TEXTURE1);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDisable (GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glActiveTexture (GL_TEXTURE0);
    glDisable(GL_BLEND);
    cout << "miltitexture returned" << endl;
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
    return ;
}

void Ground::drawGround()					// This Renders The Height Map As Quads
{
    if(!funcStatus){
        setupFunctions();
    }
    int x,  z;										// Create Some Variables For Readability
    int x0,y0, z0;

    if(!g_HeightMap){
        return;								// Make Sure Our Height Data Is Valid
    }


    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
                                // Render Polygons
    int halfSize = mapSize / 2;
    for(x = centerX - mapSize / 2 ; x < centerX + halfSize ; x+=PRINT_STEP){
        for(z = centerZ - mapSize / 2 ; z < centerZ + halfSize ; z+=PRINT_STEP)
        {
            glEnable(GL_BLEND);
            glBindTexture(GL_TEXTURE_2D, groundTexture);
            glBegin( GL_QUADS );
            // Get The (X, Y, Z) Value For The Bottom Left VertexZZZ
            x0 = x;
            z0 = z;
            y0 = groundHeight(x0, z0 );
            glTexCoord2f(0,0);
            glVertex3i(x0, y0, z0);

            // Get The (X, Y, Z) Value For The Top Left Vertex
            x0 = x;
            z0 = z + PRINT_STEP ;
            y0 = groundHeight(x0, z0 );
            glTexCoord2f(0,1);
            glVertex3i(x0, y0, z0);						// Send This Vertex To OpenGL To Be Rendered

            // Get The (X, Y, Z) Value For The Top Right Vertex
            x0 = x + PRINT_STEP;
            z0 = z + PRINT_STEP ;
            y0 = groundHeight(x0, z0 );
            glTexCoord2f(1,1);
            glVertex3i(x0, y0, z0);

            // Get The (X, Y, Z) Value For The Bottom Right Vertex
            x0 = x + PRINT_STEP;
            z0 = z;
            y0 = groundHeight( x0, z0 );
            glTexCoord2f(1,0);
            glVertex3i(x0, y0, z0);
            glEnd();
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}


void Ground::draw()
{
    if(!funcStatus){
        setupFunctions();
        generateVertexBuffers();
    }
    drawGroundVBO();
    //drawGroundMulti();
    //drawGround();
    drawSnow();
    melt();
}

void Ground::drawSnow(){
    glBindTexture(GL_TEXTURE_2D, snowTexture);
    glBegin( GL_QUADS );
    for(float x = -80 ; x < 80 ; x += PRINT_STEP){
        for(float z = -80 ; z < 80 ; z += PRINT_STEP){
            //float height = ground.Height(i, j, true)  + hasSnow[index] * 0.01 + 0.1;
            // Get The (X, Y, Z) Value For The Bottom Left Vertex
            int snowCnt = 0;
            for(float i = 0 ; i < PRINT_STEP ; i += (1.0 / (float)SNOW_PRECISION)){
                for(float j = 0 ; j < PRINT_STEP ; j += (1.0 / (float)SNOW_PRECISION)){
					int index = positionToIndex(i + x, j + z);
					if(hasSnow[index] > 0){
						snowCnt += hasSnow[index];
					}
                }
            }
			if(snowCnt > 0){
				snowCnt = snowCnt + 1 - 1;
			}
            int ix = (int) (x + mapSize / 2);
            int iz = (int) (z + mapSize / 2);
            //Get which rectangle (x,z) belongs to
            ix = ix - ix % PRINT_STEP;
            iz = iz - iz % PRINT_STEP;

            //Get index in VBO
            int lineCount = mapSize / PRINT_STEP;
            int indexVBO = iz / PRINT_STEP * lineCount + ix / PRINT_STEP ;
            float tex0Contribution;
            if(snowCnt >=START_ACCUMULATE ){
                //cout << "ground: x=" << x << " z= " << z << " index=" << indexVBO << endl;
                tex0Contribution = 1.0;
                m_PositionBuffer[indexVBO][1] = groundHeight(x, z) + (float)snowCnt / START_ACCUMULATE / 100.0 ;
            }else{
                 tex0Contribution = (float)(snowCnt) / (float)START_ACCUMULATE;
            }
            float tex2Contribution = 1.0 - tex0Contribution;
            m_ColorBuffer[indexVBO] = glm::vec4( tex0Contribution, tex0Contribution, tex0Contribution, tex2Contribution );
        }
    }
    glEnd();

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLVertexBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec3) * m_PositionBuffer.size(), &(m_PositionBuffer[0]), GL_STATIC_DRAW_ARB );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_GLColorBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(glm::vec4) * m_ColorBuffer.size(), &(m_ColorBuffer[0]), GL_STATIC_DRAW_ARB );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}

void Ground::setTexture(GLuint _groundTexture, GLuint _snowTexture){
    groundTexture = _groundTexture;
    snowTexture = _snowTexture;
    textureLoaded = true;
}


void Ground::melt(){
    clock_t currentTime = clock();
    double meltTime = (currentTime  - startTime) / (double)(CLOCKS_PER_SEC / 1000);
    if(meltTime < 50){
        return ;
    }else{
        int plantSize = needFlakeMap.size();
        for(int idx = 0 ; idx < plantSize ; idx++){
            int areaSize = plantAreaSize[idx][0] * plantAreaSize[idx][1];
            int randStart = rand() % areaSize;
            int meltCnt = 0;
            for(int i = randStart ; i < areaSize; i++){
                if(meltCnt >= meltSpeed / 10){
                    break;
                }
                if(needFlakeMap[idx][i] > 1) {
                    cout << "decreasing index " << i << endl;
                    needFlakeMap[idx][i]--;
                    if(needFlakeMap[idx][i] == 1){
                        snowPosition[idx].erase(snowPosition[idx].find(i));

                    }
                    meltCnt++;
                }
            }
        }

        for(float x = -MAX_SNOW_AREA ; x < MAX_SNOW_AREA ; x += PRINT_STEP){
            for(float z = -MAX_SNOW_AREA ; z < MAX_SNOW_AREA ; z += PRINT_STEP){
                int minCnt = 0;
                for(float i = 0 ; i < PRINT_STEP ; i += (1.0 / (float)SNOW_PRECISION)){
                    for(float j = 0 ; j < PRINT_STEP ; j += (1.0 / (float)SNOW_PRECISION)){
                        if(hasSnow[positionToIndex(i + x, j + z)] > 0){
                            hasSnow[positionToIndex(i + x, j + z)]--;
                            minCnt++;
                        }
                        if(minCnt > meltSpeed){
                            break;
                        }
                    }
                    if(minCnt > meltSpeed)
                    {
                        break;
                    }
                }
            }
        }

        startTime = currentTime;
        //cout << "total snow: " << sum << endl;
    }

}

void Ground::setMeltingSpeed(int val){
    meltSpeed = val * 10;
}

