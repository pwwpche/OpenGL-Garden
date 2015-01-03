#include "Snow.h"

Snow::Snow(){
    groundSnowCnt = 0;
    snowCount = 0;
    areaSize = 0;
    maxHeight = 0;
    flakeCount = 0;
    glPointParameterfARB  = NULL;
    glPointParameterfvARB = NULL;
	srand(time(NULL));
}

Snow::~Snow(){
    delete [] groundSnow;
}

float Snow::getGroundHeight(float i, float j){
    i = i < MAX_HEIGHT_BUFFER_AREA ? i : MAX_HEIGHT_BUFFER_AREA;
    i = i > -MAX_HEIGHT_BUFFER_AREA ? i : -MAX_HEIGHT_BUFFER_AREA;
    j = j < MAX_HEIGHT_BUFFER_AREA ? j : MAX_HEIGHT_BUFFER_AREA;
    j = j > -MAX_HEIGHT_BUFFER_AREA ? j : -MAX_HEIGHT_BUFFER_AREA;
    int index = (i + MAX_HEIGHT_BUFFER_AREA) * MAP_PRECISION * MAX_HEIGHT_BUFFER_AREA +(j + MAX_HEIGHT_BUFFER_AREA) * MAP_PRECISION;
    return groundBaseHeight[index];
}

void Snow::setup(int _areaSize, int _maxHeight, int _flakeCount){
    groundSnowCnt = 0;
    snowCount = 0;
    areaSize = _areaSize;
    maxHeight = _maxHeight;
    flakeCount = _flakeCount;
    srand(time(NULL));
    glPointParameterfARB  = NULL;
    glPointParameterfvARB = NULL;
    //Record where the snow falls onto
    groundSnow = new float[MAX_GROUND_SNOW * 3];

    //Record which area has snow and height of snow
    hasSnow = new unsigned short[3010 * 3010];

    //Set up ground base height buffer
    groundBaseHeight = new float[3010 * 3010];
    for(float i = -100 ; i < 100 ; i += 0.1){
        for(float j = -100 ; j < 100 ; j += 0.1){
            int index = (i + 100) * 10000 +(j + 100) * 10;
            float height = ground.Height(i, j, true) + hasSnow[index] * 0.02 + 0.1;
        }
    }

    memset(hasSnow, 0, sizeof(hasSnow));
    generateFlakes();
}

void Snow::init(GLuint _flakeTexture, GLuint _groundTexture){
    //Make sure we can use point sprite on out machine
    char *ext = (char*)glGetString( GL_EXTENSIONS );
    if( strstr( ext, "GL_ARB_point_parameters" ) == NULL )
    {
        return;
    }
    else
    {
        glPointParameterfARB  = (PFNGLPOINTPARAMETERFARBPROC)wglGetProcAddress("glPointParameterfARB");
        glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)wglGetProcAddress("glPointParameterfvARB");

        if( !glPointParameterfARB || !glPointParameterfvARB )
        {
            return;
        }
    }


    flakeTexture = _flakeTexture;
    groundTexture = _groundTexture;

    //Generate Shape of snow
    for(int i = 0 ; i < MAX_SNOW_VEX ; i++){
        snowBuf[i] = glGenLists(1);
        glNewList(snowBuf[i], GL_COMPILE);
        glutSolidSphere(0.03, i, i);
        glEndList();
    }
}



Snow::Snow(int _areaSize, int _maxHeight, int _flakeCount){
    groundSnowCnt = 0;
    snowCount = 0;
	areaSize = _areaSize;
	maxHeight = _maxHeight;
	flakeCount = _flakeCount;
    srand(time(NULL));
	generateFlakes();
}

void Snow::generateFlakes(){
    //Generate position of snow
	GLfloat x, y, z;
	for(int i = 0 ; i < flakeCount ; i++){
		generateSnowPos(x, y, z);
		snow.push_back(Flake(x, y, z));
        snowCount++;
	}
}

void Snow::generateSnowPos(GLfloat &x, GLfloat &y, GLfloat &z){    
	if(flakeCount == 0){
		x = 0;
		y = 0;
		z = 0;
		return ;
	}
	float xRatio = (float)(rand() % flakeCount) / (float)flakeCount;
	float yRatio = (float)(rand() % flakeCount) / (float)flakeCount;
	float zRatio = (float)(rand() % flakeCount) / (float)flakeCount;

	x = xRatio * areaSize * (rand() % 2 == 0 ? 1.0 : -1.0);
	y = yRatio * maxHeight / 2.0  + maxHeight / 2.0;
	z = zRatio * areaSize * (rand() % 2 == 0 ? 1.0 : -1.0);
}


void Snow::draw(Wind &wind, GLfloat cx, GLfloat cz, Ground& ground){
    glPushMatrix();
    ////Billboard effect
    /*
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);

    // Identify the 3*3 sub matrix in Top-left corner
    mat[1] = mat[2] = mat[6] = 0;
    mat[4] = mat[8] = mat[9] = 0;
    mat[0] = mat[5] = mat[10] = 1;
    glColor3f(1, 1, 1);
    glLoadMatrixf(mat);
    */

    ////Test Rectangle
    //glBegin(GL_QUADS);
    //glVertex3f(-3.0f, -3.0f,  -5.0f);  // Bottom Left Of The Texture and Quad
    //glVertex3f( 3.0f, -3.0f,  -5.0f);  // Bottom Right Of The Texture and Quad
    //glVertex3f( 3.0f,  3.0f,  -5.0f);  // Top Right Of The Texture and Quad
    //glVertex3f(-3.0f,  3.0f,  -5.0f);  // Top Left Of The Texture and Quad
    //glEnd();


    // This is how will our point sprite's size will be modified by
    // distance from the viewer
    float quadratic[] =  { -0.0f, 0.0f, -0.01f };
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );

    // Query for the max point size supported by the hardware
    float maxSize = 0.0f;
    glGetFloatv( GL_POINT_SIZE_MAX_ARB, &maxSize );

    glPointSize( 10.0f );
    // The alpha of a point is calculated to allow the fading of points
    // instead of shrinking them past a defined threshold size. The threshold
    // is defined by GL_POINT_FADE_THRESHOLD_SIZE_ARB and is not clamped to
    // the minimum and maximum point sizes.
    glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );

    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 0.1f );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 10.0f );

    // Specify point sprite texture coordinate replacement mode for each
    // texture unit
    glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );

    //
    // Set up for blending...
    //
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    //
    // Render point sprites...
    //
    glEnable( GL_POINT_SPRITE_ARB );
    glBindTexture( GL_TEXTURE_2D, flakeTexture );
    list<Flake>::iterator it;

    for(it = snow.begin() ; it != snow.end() ; it++){
        Flake& currentFlake = *it;
        //currentFlake.draw(cx, cz, false, snowBuf);
        glBegin(GL_POINTS);
        glVertex3f(currentFlake.x, currentFlake.y, currentFlake.z);
        glEnd();
        currentFlake.fall(wind);

       // if(currentFlake.y < ground.Height(currentFlake.x, currentFlake.z, true) ){
        if(currentFlake.y < getGroundHeight(currentFlake.x, currentFlake.z) ){
            //Snow on the ground
            if(groundSnowCnt < MAX_GROUND_SNOW && snowCount == flakeCount){
                if(groundSnowCnt > 0 && groundSnow[(groundSnowCnt - 1 )* 3] != currentFlake.x || groundSnowCnt == 0 ){
                   if (currentFlake.x < 100 && currentFlake.x > -100 && currentFlake.z < 100 && currentFlake.z > -100){
                       int fallX = (currentFlake.x + 100) * 10;    //Max area size should be < 100
                       int fallZ = (currentFlake.z + 100) * 10;
                       int index = fallX * 1000 + fallZ;
                       //groundSnow[groundSnowCnt*3 + 0] = currentFlake.x;
                       //groundSnow[groundSnowCnt*3 + 1] = currentFlake.y + 0.1;//+ 0.02 * hasSnow[fallX * 2000 + fallZ];
                       //groundSnow[groundSnowCnt*3 + 2] = currentFlake.z;
                       hasSnow[index]++;
                       groundSnowCnt++;
                   }
                }
            }
            //cout << currentFlake.x << " " << currentFlake.y << " " << currentFlake.z << " " << endl;


			GLfloat x, y, z;
			generateSnowPos(x, y, z);
            currentFlake.setPosition(x, y, z);
		}        
	}



    //Snow on the ground
    quadratic[2] =  -0.1f;
    glPointSize( 10.0f );
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 0.1f );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 20.0f );
    glBindTexture( GL_TEXTURE_2D, groundTexture );
    glBegin(GL_POINTS);
    /*
    for(int i = 0  ;i < groundSnowCnt ; i++){
        float currentFlakeX = groundSnow[i * 3];
        float currentFlakeY = groundSnow[i * 3 + 1];
        float currentFlakeZ = groundSnow[i * 3 + 2];
        glVertex3f(currentFlakeX, currentFlakeY, currentFlakeZ);
    }
    */

    for(float i = -100 ; i < 100 ; i += 0.1){
        for(float j = -100 ; j < 100 ; j += 0.1){
            int index = (i + 100) * 10000 +(j + 100) * 10;
            if(hasSnow[index] > 0){
//                float height = ground.Height(i, j, true) + hasSnow[index] * 0.02 + 0.1;
                //glVertex3f(i, height , j);
            }
        }
    }

    glEnd();
    glBindTexture( GL_TEXTURE_2D, 0 );


    glDisable( GL_POINT_SPRITE_ARB );
    glDisable(GL_BLEND);
    glPopMatrix();
}

