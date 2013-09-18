	You have been hired as a programmer for Niagara Mohawk Power Corps Nuclear Test Division.  Your first assignment is to write a program to simulate the collisions of enriched uranium particles trying to escape from a reactor core.  The movement of the particles occurs within a 7 x 7x 7 meter space whose innermost 3 x 3 x 3 area is composed of the reactor core and whose outer areas are composed of a lead shield. 

Lead helps protect from radiation because of its high density with an atomic number of 82. Lead is effective at stopping gamma rays and x rays. However lead does not fully stop radioactive uranium enriched particles . It does however diminish their energy level as they pass through this dense material.



Particle Movement Rules:

1) All particles are placed in the shield at the same time. NO energy will 
be dissipated when a particle is placed in the shield.

2) Particles enter the shield at some random position in the core’s coordinate space. The random number generator should be called three times for each particle. The first number will be the row, while the second will be the column,  and the third will be the depth, the set together denotes the starting position of the particle in the shield.

3) Once a particle is placed in the shield it moves one meter per second in one of six directions(North, South, East, West, Up, Down)  
(enumeration type)

4) The next second direction of travel is determined by a random number from 0 to 5 (which corresponds to the abovementioned enumeration type respectively).  

For movement in the core: 
5) Each movement in the same direction of travel will dissipate one unit of energy from the particle

6) Each change in direction dissipates two units of energy from that particle.

For movement in the lead shield:
7) Each movement in the same direction of travel will dissipate four units of energy from the particle

8) Each change in direction dissipates eight units of energy from that particle.





9) Initial movements will be counted as a change of direction. 
Any time a particle enters a cell that contains 1 or more active particles,  its energy is additionally reduced by the number of active particles found within that cell.

10) At some point in time a particle will either exit the shield and       
     contaminate the surrounding atmosphere, or run out of energy.

11) For this simulation particles will move every second and always move in the same order. Refer to particles by number and move them in ascending order

12) A particle exits the shield if its position places it outside the shield coordinate space before it runs out of energy. If this occurs, the particle no longer moves as we cannot track it.  

But the particles have affinity for environmentally conscious protesters and they then attach themselves to one of 100 random protesters who then make laps around the nuclear facility carrying a banner until such time as the protester and attached particle run out of energy. (1000  laps  decrease the particle/protester by one unit of energy).

13) If a particle does not have enough energy to enter a new cell, It remains in the current cell and all energy is dissipated.

14) Particles become inactive when they have zero energy remaining.


Your program should keep track of :
1) The number of particles which remain within each square foot of the shield/core
2) The number of particles which began in each square of the core.
3) For exterior cells , the number of particles which exit the shield from that space.
4) The percentage of particles which exit the shield.
5) The percentage of particles which remain within the shield and the percentage of particles that remain within the core
6) Every cell that a particle visits more than one time.
 
The program should receive as keyboard input two values: 
1) The number of particles to be tracked for this program’s execution.
2) The energy value that every particle will have when entering the shield.
3) All other values needed will be generated using the C++ random number generator. 
4) The random number generator should be seeded with the value 987645321.

For output(file- “results.dat”) the program should generate a table looking similar to each level of the three dimensional shield and for each square meter list 3 values, began remaining  and exiting).


For example : the output for the top level of a 3x3x3 shield might appear as follows.. (the asterisks indicate that a particle could not be born in that cell.

**	**	**
R1	R2	R0
E2	E3	E1

**	**	**
R1	R2	R2
E0	E5	E1

**	**	**
R2	R2	R3
E0	E4	E2

This should be followed the other 3 statistics (% escaping, % remaining in shield, % remaining in core) nicely formatted for two decimal places. 

This should be followed by a listing for each particle which includes the number of times it visited a cell that it had been in before. Identify the particles by particle number, identify each cell by its coordinates then the number of times it visited the cell.
