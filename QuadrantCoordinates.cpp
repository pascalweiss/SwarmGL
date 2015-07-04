#include "QuadrantCoordinates.h"


QuadrantCoordinates::QuadrantCoordinates() {
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

QuadrantCoordinates::~QuadrantCoordinates(void)
{
}
