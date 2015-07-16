/**
 SwarmGL
 =======
 QuadrantCoordinates.h
 
 This is a convenient class for coordinates for 
 quadrants.
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 */

#pragma once
class QuadrantCoordinates
{
 // Variables
private:
	float x;
	float y;
	float z;
 // Methods
public:
    /**
     Constructor, using x = 0; y = 0; z = 0;
     */
	QuadrantCoordinates();
    
    /**
     Constructor
     @param x - setting the x coordinate.
     @param y - setting the y coordinate.
     @param z - setting the z coordinate.
     */
	QuadrantCoordinates(float x, float y, float z);
    
    /**
     Setter for x
     @param x
     */
	void setX(float x);
	
    /**
     Setter for y
     @param y
     */
    void setY(float y);
    
    /**
     Setter for z
     @param z
     */
	void setZ(float z);
    
    /**
     Getter for x
     @return x
     */
	float getX();
	
    /**
     Getter for y
     @return y
     */
    float getY();
    
    /**
     Getter for z
     @return z
     */
	float getZ();
    
    /**
     Returns the biggest absolute coordinate.
     @return the biggest absolute coordinate
     */
	float getBiggestAbsolute();
	~QuadrantCoordinates(void);
};

