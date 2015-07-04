#pragma once
class QuadrantCoordinates
{
private:
	int x;
	int y;
	int z;
public:
	QuadrantCoordinates();
	QuadrantCoordinates(int x, int y, int z);
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	int getX();
	int getY();
	int getZ();
	~QuadrantCoordinates(void);
};

