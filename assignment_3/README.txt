Derek Dorr
CPSC 566
04/18/2024

INSTRUCTIONS:
 . navigate to project directory and execute: ./assignment_3
     . additional parameters:   r - sets the step function (r = RK4, e = Euler, t = Trapazoidal)
                                0.04 - sets the time step
     . example:                 ./assignment_3 t 0.04

 . press 't' to swap between particle simulations

 . press 'r' to reset current particle simulation

 . to compile, simply navigate to the project direcory and execute 'make'


REFERENCES:
    - https://paulbourke.net/miscellaneous/particle/
    - Physics for Game Developers, 2nd Edition [Book]
    - https://www.cs.cmu.edu/%7Ebaraff/pbm/particles.pdf
    - https://www.youtube.com/watch?v=Rr-5HiXquhw [ Coding Challenge #160: Spring Forces - The Coding Train]


PROBLEMS:

1) cloth simulation not quite right. I think its an issue with the springs not repelling eachother but I could not get it to work correctly.

2) I tried implementing a new spring / particle class but could not get it to work with the starter code


SUGGESTIONS:
1) I don't think there's enough information in the homework handout and in the slides to successfully solve this assignment. 
    I used 2 text books and many online references to see how particles are implemented with ODE's, integrators, and time steppers.
    I still couldn't figure out how to successfully use implement springs. It works well enough for the pendulum system but the cloth system sort of fell apart.
