#include "Snow.h"
#define FLAKE_ON_TREE 50000
Snow::Snow(){
    snowCount = 0;
    areaSize = 0;
    maxHeight = 0;
    flakeCount = 0;
    glPointParameterfARB  = NULL;
    glPointParameterfvARB = NULL;
	srand(time(NULL));
}

Snow::Snow(int _areaSize, int _maxHeight, int _flakeCount){
    snowCount = 0;
    areaSize = _areaSize;
    maxHeight = _maxHeight;
    flakeCount = _flakeCount;
    srand(time(NULL));
    generateFlakes();
}

Snow::~Snow(){
}



void Snow::setup(int _areaSize, int _maxHeight, int _flakeCount){
    plantFlakeCnt = 0;
    plantFlake = new Flake[FLAKE_ON_TREE];
    snowCount = 0;
    areaSize = _areaSize;
    maxHeight = _maxHeight;
    flakeCount = _flakeCount;
    srand(time(NULL));
    glPointParameterfARB  = NULL;
    glPointParameterfvARB = NULL;
    generateFlakes();
}


void Snow::init(GLuint _flakeTexture){
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
}




void Snow::generateFlakes(){
    //Generate position of snow
    GLfloat x = 0, y = 0, z = 0;
    for(int i = snowCount ; i < flakeCount ; i++){
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
	rand();
    float xRatio = rand() % 512;
    float yRatio = rand() % 512;
    float zRatio = rand() % 512;

    xRatio = xRatio / 512;
    yRatio = yRatio / 512;
    zRatio = zRatio / 512;

    x = xRatio * areaSize * 2 - areaSize;
	y = yRatio * maxHeight / 2.0  + maxHeight / 2.0;
    z = zRatio * areaSize * 2 - areaSize;
}

void Snow::stop(){
    flakeCount = 0;
}



void Snow::draw(Wind &wind,Ground& ground){
    glPushMatrix();
    glEnable( GL_BLEND );
    float quadratic[] =  { -0.0f, 0.0f, -0.01f };
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
    glPointSize( 7.0f );
    glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 0.1f );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 10.0f );

    // Specify point sprite texture coordinate replacement mode for each
    // texture unit
    glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE);
    glEnable( GL_POINT_SPRITE_ARB );
    glBindTexture( GL_TEXTURE_2D, flakeTexture );
    list<Flake>::iterator it;
    unsigned int count = 0;
    glBegin(GL_POINTS);

    for(it = snow.begin() ; it != snow.end() ; it++){

        Flake& currentFlake = *it;
        count++;
        if(currentFlake.x > areaSize ||         //Flake is outside this area
            currentFlake.x < -areaSize ||
            currentFlake.z > areaSize ||
            currentFlake.z < -areaSize )
        {
            if(count < flakeCount){
                GLfloat x, y, z;
                generateSnowPos(x, y, z);           //Regenerate this flake
                currentFlake.setPosition(x, y, z);
            }else{
                continue;
            }
        }

        //Draw current flake
        glVertex3f(currentFlake.x, currentFlake.y, currentFlake.z);
        //Flake is falling
        currentFlake.fall(wind);

        bool fallen = (currentFlake.y < ground.getPlantHeight(currentFlake.x, currentFlake.z));
        if(fallen){			//Detect if snow has fallen to the ground
			bool validFall = true;
            if(count < flakeCount ){
                float groundPlantHeight = ground.getPlantHeight(currentFlake.x, currentFlake.z);
                float groundBaseHeight = ground.groundHeight(currentFlake.x, currentFlake.z, true);
                if(currentFlake.y >  groundBaseHeight &&
                    currentFlake.y < groundPlantHeight - 0.5){      //This flake falls onto some weird place...
                        validFall = false;      //Don't draw it...
                }

                int flakeCnt = ground.plantFlake(currentFlake.x, currentFlake.z);       //Get the number of flakes at this position (somewhere on a plant)
                if( flakeCnt > 0 && validFall){
                    currentFlake.y  = groundPlantHeight;        //Draw this flake()
                    if(plantFlakeCnt < FLAKE_ON_TREE){
                        plantFlake[plantFlakeCnt++] = currentFlake;
                    }
                }
                //Tell gound to accumulate snow
                ground.accumulate(currentFlake.x, currentFlake.z);

                //Respawn a flake by putting it in the sky again
                GLfloat x, y, z;
                generateSnowPos(x, y, z);
                currentFlake.setPosition(x, y, z);
            }else{
                //Just leave the flake information in the memory, and don't draw it...
                currentFlake.setPosition(areaSize + 100, areaSize + 100, areaSize + 100);
            }
		}        
    }

    vector<map<int, float>* > snowPos = ground.getSnowPosition();
    size_t posSize = snowPos.size();
    for(size_t i = 0 ; i < posSize ; i++){
        map<int, float>::iterator it;

        for(it = (*snowPos[i]).begin() ; it != (*snowPos[i]).end() ; it++){
            float x = -1, z = -1;
            int plantPosIdx = it->first;
            float plantHeight = it->second;
            bool valid = ground.plantIndexToPos(i, plantPosIdx, x, z);
            if(valid){
                glVertex3f(x, plantHeight , z);
            }
        }
    }


/*
    bool show = false;
    for(float x = -3 ; x < 3 ; x += 0.03){
        for(float z = -3 ; z < 3 ; z += 0.03){
            if(x > 0 && z > 0 && !show) {
                cout << "00000" << endl;
                show = true;
            }
            float height = ground.getPlantHeight(x, z) ;
            if(height > ground.groundHeight(x, z, true) + 0.5){
                glVertex3f(x, height , z);
            }
        }
    }
    */
/*
    for(int i = 0 ; i < plantFlakeCnt ; i++){
        Flake& currentFlake = plantFlake[i];
        if(currentFlake.y > ground.groundHeight(currentFlake.x, currentFlake.z, true) &&
                currentFlake.y < ground.getPlantHeight(currentFlake.x, currentFlake.z) - 0.5){
            //cout << "Flake Error: x=" << currentFlake.x <<  " z=" << currentFlake.z << endl;
        }
        glVertex3f(currentFlake.x, currentFlake.y, currentFlake.z);
    }
*/
    glEnd();
    glDisable(GL_BLEND);
    glDisable( GL_POINT_SPRITE_ARB );
    glBindTexture( GL_TEXTURE_2D, 0 );


    glPopMatrix();
}

void Snow::setArea(int _areaSize){
    _areaSize = _areaSize > 100.0 ? 100 : _areaSize;
    areaSize = _areaSize;
}



void Snow::start(int _flakeCount){
    if(flakeCount < _flakeCount){
        for(int i = flakeCount ; i < _flakeCount ; i++){
            GLfloat x, y, z;
            generateSnowPos(x, y, z);
            snow.push_back(Flake(x, y, z));
            snowCount++;
        }
    }
    flakeCount = _flakeCount;
}


