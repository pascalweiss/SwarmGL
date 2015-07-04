#pragma once
class QuadrantCoordinates
{
private:
	float x;
	float y;
	float z;
public:
	QuadrantCoordinates();
	QuadrantCoordinates(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float getX();
	float getY();
	float getZ();
	~QuadrantCoordinates(void);
};

