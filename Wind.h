#ifndef CG_WIND
#define CG_WIND
class Wind{
public:
	Wind();
	Wind(float lx, float ly, float lz);
	void setLevel(float lx, float ly, float lz);
	float getLevelX();
	float getLevelY();
	float getLevelZ();
    void setFallSpeed(float speed);
public:
	float x;
	float y;
	float z;
	float gravity;
};
#endif
