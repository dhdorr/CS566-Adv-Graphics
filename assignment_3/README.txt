Derek Dorr
CPSC 566
04/20/2024

INSTRUCTIONS:
 . navigate to project directory and execute: ./assignment_3
     . additional parameters:   r - sets the step function (r = RK4, e = Euler, t = Trapazoidal)
                                0.04 - sets the time step
     . example:                 ./assignment_3 t 0.04

 . press 't' to swap between particle simulations

 . press 'r' to reset current particle simulation

 . press 'h' for the help menu

 . to compile, simply navigate to the project direcory and execute 'make'


REFERENCES:
    - https://paulbourke.net/miscellaneous/particle/
    - Physics for Game Developers, 2nd Edition [Book]
    - https://www.cs.cmu.edu/%7Ebaraff/pbm/particles.pdf
    - https://www.youtube.com/watch?v=Rr-5HiXquhw [ Coding Challenge #160: Spring Forces - The Coding Train]


PROBLEMS:

1) cloth simulation not quite right. I think its an issue with the springs not repelling eachother but I could not get it to work correctly.
    I had to fake a repelling spring force by dampening the springs greatly on the x-axis

2) I tried implementing a new spring / particle class but could not get it to work with the starter code

3) On my machine, I sometimes get segmentation faults when running the cloth simulation after making a new build.
    I also sometimes see crashes when cycling too fast to the cloth simulation. I have no idea why this happens, it is inconsistent.
    But if my program crashes, please try running it again.


SUGGESTIONS:
1) I don't think there's enough information in the homework handout and in the slides to successfully solve this assignment. 
    I used 2 text books and many online references to see how particles are implemented with ODE's, integrators, and time steppers.
    I still couldn't figure out how to successfully use implement springs. It works well enough for the pendulum system but the cloth system sort of fell apart.
