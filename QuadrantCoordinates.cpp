#include "QuadrantCoordinates.h"


QuadrantCoordinates::QuadrantCoordinates() {
}

QuadrantCoordinates::QuadrantCoordinates(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void QuadrantCoordinates::setX(int x)
{
	this->x = x;
}

void QuadrantCoordinates::setY(int y)
{
	this->y = y;
}

void QuadrantCoordinates::setZ(int z)
{
	this->z = z;
}

int QuadrantCoordinates::getX()
{
	return this->x;
}

int QuadrantCoordinates::getY()
{
	return this->y;
}

int QuadrantCoordinates::getZ()
{
	return this->z;
}

QuadrantCoordinates::~QuadrantCoordinates(void)
{
}
