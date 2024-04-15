Problems:
1) i don't know if it is just my environment or something wrong with my code, 
    but  I get a malloc tcache error and the executable fails to run about 50% of the time.
    usually I can just keep trying to run it and it will eventually work.... So if you get that error,
    just know that the code works sometimes.

2) cloth simulation. Could not figure out how to do it.

3) I tried implementing a new spring / particle class but could not get that code to work with the starter code

4) I believe I implemented the particle chain in a way that should work but i keep getting an error from glut
    free(): invalid next size (fast)
    Aborted

    I have not been able to figure out why this wont work, even with extensive debugging.


suggestions:
1) I don't think there's enough information in the homework handout and in the slides to successfully solve this assignment. 
    I used 2 text books and many online references to see how particles are implemented with ODE's, integrators, and time steppers.
    I still couldn't figure out how to successfully use the evalF function, as when I implemented my custom particle & spring solution inside evalF,
    evalF would just fail.
