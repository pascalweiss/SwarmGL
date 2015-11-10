SwarmGL
=======
This peace of software was made for simulating swarm behaviour. It was developed during a course on computer graphics at HTW-Berln. As inspiration, we took starling swarms, such as the one shown in this video https://www.youtube.com/watch?v=DmO4Ellgmd0. Although we couldn't reproduce the same behaviour, there are still tendencies. Watch a preview video here: 
[![IMAGE ALT TEXT HERE](https://github.com/pascalweiss/pics/blob/master/swarmGL_youtube.png?raw=true)](https://www.youtube.com/watch?v=biAm4FSOD14)

# Dependencies 
- GLFW
- GLFW
- glm
Check the folder `external`..

# Handling
In `GLOBALS.json`(which should be in the same directory as the executable), there are some values, you can modify. By doing so, you can alter the behaviour of the Swarm.<br>

**MODE** <br>
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
**VELOCITY**<br>
The speed of the particle. Can be changed on runtime.<br>
**PANIC_VELOCITY**<br>
The speed of the particle, when it is in panic mode. Can be changed on runtime.<br>
**OPENNESS**<br>
Low value makes the particles attract more to each other, so they come closer to each other. A big value makes them spread wider over the space. Can be changed on runtime.<br>
**PANIC_DAMPING**<br>
With a low value, it is very likely, that they panic, when the THREASHOLD is reached. With a high value, they might not panic, even though the THREASHOLD is reached. Can be changed on runtime.<br>

<br>
#SwarmGL Concept
#Ambition
We created this project to simulate a swarm intelligence. We worked with the imagination of a fish swarm swimming in the sea. 

#Measures
**Environment**<br>
To provide a nice observability we put our focus first on how to design the environment of the swarm in a way that the actions takes place in the visible area most of the time. 
Therefore we subdivided the space in a cuboid built out of cubes(henceforth referred to as quadrant) with a length of 1 each wielding influence on the particles in itself.

**Particles**<br>
Conveniently we display the particles as polygons. Agents in a swarm wield mutual influence. To economize the used computation power we didn't realize the mutual perception in the particle itself but as a geometric mean between the movement vectors of the particles in a quadrant and it's own direction vector.

# Implementation

# Particle
To afford the particles to move freely in the three dimensional space we realized them through three vectors. A position vector describes the middle of the polygon's basis.
A direction vector describes in which direction the polygon's peak points to and where it will move next.
To display the basis uniformly we defined a normal vector to the direction vector with a x-coordinate that equals 0.

Example: direction vector d: (dx, dy, dz) → normal vector n: (0, -dz, dy)

Each particle has a velocity which describes by which amount the position vector is moved in direction of the direction vector per iteration.
Due to these calculations the particles are regenerated and stored in the vertexbuffer in each iteration.

# Grid
The grid is a cuboid composed of cubes(quadrants) of size 1. To simplify the calculation of influence vectors the amount of quadrants per dimension must be an uneven number.
This class initiates the quadrants and their influence vectores and manages objects of the classes particle and quadrant.
The grid can move, draw and register particles in new quadrants which is necessary to calculate the new influence vectors in the next iteration.


The quadrants are stored in a three-dimensional std::vector. We choosed the frontal lower left corner as a reference point for each quadrant. The particle's positions only need to be decremented to the next whole number (1.2 turns to 1 or -1.09 turns to -2) and can be registered to the quadrant at this position (substracted by half of the dimension length of the grid). Before they are registered all particles are removed from the quadrants and reregistered after they have taken on their new positions.


# Quadrant
The quadrant's influence only applies to the direction of the particles. It is designed by each quadrant having it's own direction vector pointing to the middle of the grid. The bigger the distance to it the heavier does the vector apply force to the particle. This intensity has a range from 0 to 1.
The effective vector is calculated in the class influence vector which is instanced independently in every quadrant.
The quadrant also stores pointers to the particles which are positioned in it's space which is necessary for it to calculate the effective vector.


# Influencevector
The influence vector calculates the new direction vector that all particle in a quadrant will adopt. If the quadrant is at the edge of the grid it is only calculated by the quadrant's vector itself ignoring the particles directions to make sure they do not leave the window.

Quadrant's dircetion vector: `Qd`
Intensity: `I`
Particle's direction vector: `Pd1, Pd2, …, Pdn; n = number of particles`

`Qd * I + Pd1 * (1 – I) / n + Pd2 * (1 – I) / n + … + Pdn * (1 – I) / n`

# SwarmGLFacade
This class encapsulates instances of particle, quadrant, influencevector and grid. It initiates OpenGL and creates all objects regarding passed parameters and starts the simulation of the swarm intelligence.

# Conclusion
We renounced to work as close to reality as possible to gain a better performance and therefore simulate more particles. We also wanted to achieve a better observability by not allowing the particles to leave the space. 
It would be more natural if every particle would sense the environment autonomously and adjusts it's behavior.
Nevertheless we think that we've created an astonishing result with a discernible intelligent behavior of the swarm which is significantly modifiable by using different parameters.

 
 

