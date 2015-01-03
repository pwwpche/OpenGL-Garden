#include "fog.h"

Fog::Fog()
{
    fogfilter = 1;
    fogMode[0] = GL_EXP;
    fogMode[1] = GL_EXP2;
    fogMode[2] = GL_LINEAR;
    fogColor[0] = 0.5f;
    fogColor[1] = 0.5f;
    fogColor[2] = 0.5f;
    fogColor[3] = 0.2f;
}

void Fog::setup(){
    glClearColor(0.5f,0.5f,0.5f,0.2f);          // We'll Clear To The Color Of The Fog ( Modified )
    glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.03f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 25.0f);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
    glFogi (GL_FOG_MODE, fogMode[fogfilter]);   // Fog Mode
}
