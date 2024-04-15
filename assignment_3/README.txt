Derek Dorr
CPSC 566
04/18/2024

INSTRUCTIONS:
 . navigate to project directory and execute: ./assignment_3
     . additional parameters:   r - sets the step function (r = RK4, e = Euler, t = Trapazoidal)
                                0.04 - sets the time step
     . example:                 ./assignment_3 t 0.04

 . press 't' to swap between particle simulations

 . to compile, simply navigate to the project direcory and execute 'make'


REFERENCES:
    - https://paulbourke.net/miscellaneous/particle/
    - Physics for Game Developers, 2nd Edition [Book]
    - https://www.cs.cmu.edu/%7Ebaraff/pbm/particles.pdf
    - https://www.youtube.com/watch?v=Rr-5HiXquhw [ Coding Challenge #160: Spring Forces - The Coding Train]


PROBLEMS:
1) i don't know if it is just my environment or something wrong with my code, 
    but  I get a malloc tcache error and the executable fails to run about 50% of the time.
    usually I can just keep trying to run it and it will eventually work.... So if you get that error,
    just know that the code works sometimes, try running it again.

2) cloth simulation. Could not figure out how to do it because I was unable to display multiple particles.

3) I tried implementing a new spring / particle class but could not get that code to work with the starter code

4) I believe I implemented the particle chain in a way that should work but i keep getting an error from glut
    free(): invalid next size (fast)
    Aborted

    I have not been able to figure out why this wont work, even with extensive debugging.

5) Sometimes the first pendulum simulation just wont work. I cannot figure out why but the ball just goes off to infinity for no reason.
    when print line debugging, i got x or y values of infinity or nan


SUGGESTIONS:
1) I don't think there's enough information in the homework handout and in the slides to successfully solve this assignment. 
    I used 2 text books and many online references to see how particles are implemented with ODE's, integrators, and time steppers.
    I still couldn't figure out how to successfully use the evalF function, as when I implemented my custom particle & spring solution inside evalF,
    evalF would just fail.
