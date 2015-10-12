SwarmGL
=======
This peace of software was made for simulating swarm behaviour. It was developed during a course on computer graphics at HTW-Berln. As inspiration, we took starling swarms, such as the one shown in this video https://www.youtube.com/watch?v=DmO4Ellgmd0. Although we couldn't reproduce the same behaviour, there are still tendencies. Watch a preview video here 

# Dependencies 
- GLFW
- GLFW
- glm
Check the folder `external`..

# Handling
In `GLOBALS.json`(which should be in the same directory as the executable), there are some values, you can modify. By doing so, you can alter the behaviour of the Swarm.<br>

**Mode** <br>
`0` - allows the particles to leave the space<br>
`1` - permits the particles to leave the space<br>
**NUMBER_OF_PARTICLES** <br>
Initial value for the number of particles. Can't be changed on runtime<br>
**DIMENSION_LENGTH** <br>
Initial value for the number of quadrants in one dimension. E.g. for DIMENSION_LENGTH = 41 you get 41 * 41 * 41 quandrants. This is the space in which the particles are allowed to move. Can't be changed on runtime <br>
**PARTICLE_LENGTH**<br>
The length of the particles. Can be changed on runtime.<br>
**DEBUG_FLAG**<br>
Gives some debugging information on runtime. Can be changed on runtime.<br>
**PANIC_THRESHOLD**<br>
When too many particles are very close to each other (in the same quadrant), then they go in 'panic mode', which means, that the direction of their movement becomes random. The number of particles, that is required to enable the panic mode is 'PANIC_THRESHOLD'. Can be changed on runtime.<br>
**VELOCITY **<br>
The speed of the particle. Can be changed on runtime.<br>
**PANIC_VELOCITY**<br>
The speed of the particle, when it is in panic mode. Can be changed on runtime.<br>
**OPENNESS**<br>
Low value makes the particles attract more to each other, so they come closer to each other. A big value makes them spread wider over the space. Can be changed on runtime.<br>
**PANIC_DAMPING**<br>
With a low value, it is very likely, that they panic, when the THREASHOLD is reached. With a high value, they might not panic, even though the THREASHOLD is reached. Can be changed on runtime.<br>

 

