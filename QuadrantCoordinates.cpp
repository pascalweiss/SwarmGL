#include "QuadrantCoordinates.h"
#include <cmath>

QuadrantCoordinates::QuadrantCoordinates() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

QuadrantCoordinates::QuadrantCoordinates(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void QuadrantCoordinates::setX(float x)
{
	this->x = x;
}

void QuadrantCoordinates::setY(float y)
{
	this->y = y;
}

void QuadrantCoordinates::setZ(float z)
{
	this->z = z;
}

float QuadrantCoordinates::getX()
{
	return this->x;
}

float QuadrantCoordinates::getY()
{
	return this->y;
}

float QuadrantCoordinates::getZ()
{
	return this->z;
}

float QuadrantCoordinates::getBiggestAbsolute() {
#ifdef __APPLE__ || __MACH__
	float biggest = fabs(this->x);
	float absY = fabs(this->y);
	float absZ = fabs(this->z);
#else
    float biggest = abs(this->x);
    float absY = abs(this->y);
    float absZ = abs(this->z);

#endif
	if (absY > biggest) {
		biggest = absY;
	}
	if (absZ > biggest) {
		biggest = absZ;
	}
	return biggest;
}
 
QuadrantCoordinates::~QuadrantCoordinates(void)
{
}
