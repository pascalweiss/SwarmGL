#pragma once
class QuadrantCoordinates
{
private:
	int x;
	int y;
	int z;
public:
	QuadrantCoordinates(void);
	void setX();
	void setY();
	void setZ();
	int getX();
	int getY();
	int getZ();
	~QuadrantCoordinates(void);
};

