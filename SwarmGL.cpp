/**
  @author Tom Bisson, Pascal Weiß
  @date   16.07.2015
*/

#include "SwarmGLFacade.h"
#include <time.h>
#include <iostream>

/**
 The initial parameters for the swarm. 
 Some of them can be changed on runtime in 
 'Globals.json'
 */

/**
    TODO
 */
int MODE = 0;
 /**
  Initial value for the number of particles. 
  Can't be changed on runtime
 */
int NUMBER_OF_PARTICLES = 1000;

 /**
  Initial value for the number of quadrants 
  in one dimension. E.g. for
  DIMENSION_LENGTH = 41 you get 41 * 41 * 41 
  quandrants. This is the space in which the 
  particles are allowed to move. Can't be 
  changed on runtime
  */
int DIMENSION_LENGTH = 17;

 /**
  The length of the particles. Can be changed
  on runtime.
 */
float PARTICLE_LENGTH = 0.15f;

/**
  Gives some debugging information on runtime.
  Can be changed on runtime.
 */
bool DEBUG_FLAG = false;

/**
  When too many particles are very close to each 
  other (in the same quadrant), then they go in 
  'panic mode', which means, that the direction of 
  their movement becomes random. The number of 
  particles, that is required to enable the panic 
  mode is 'PANIC_THRESHOLD'.
  Can be changed on runtime.
 */
int PANIC_THRESHOLD = 35;

/**
 The speed of the particle.
 Can be changed on runtime.
 */
float VELOCITY = 0.2;

/**
 The speed of the particle, when it is in panic 
 mode. Can be changed on runtime.
 */
float PANIC_VELOCITY = 0.3;

/**
 Low value makes the particles attract more to each
 other, so they come closer to each other. A big value 
 makes them spread wider over the space.
 Can be changed on runtime.
 */
float OPENNESS = 10;

/**
 With a low value, it is very likely, that they panic, 
 when the THREASHOLD is reached. With a high value, 
 they might not panic, even though the THREASHOLD is 
 reached. 
 Can be changed on runtime.
 */
int PANIC_DAMPING = 10;


int main(void) {
	SwarmGLFacade *swarm = new SwarmGLFacade();
	delete swarm;
}
