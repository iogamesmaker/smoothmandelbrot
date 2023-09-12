# smooth mandelbrot
The Mandelbrot set using the Escape Time algorithm, and smooth coloring. 1k iterations is ~1.3 seconds on a 800x600 window on a chromebook.
I stole the smooth coloring algorithm from https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set.
uses GL/glut.h=
`g++ mandel.cpp -o mandel -lGL -lGLU -lglut` to compile on linux. requires `freeglut3`.

multithreading for some reason only slows stuff down (using omp.h), so not doing that.

# planned stuff
general optimizations, like
boundry tracing? (any help really appreciated)
better controls
# me complaining
I am a total C++ noob, so do not expect much. I do not know anything about glut, I used tutorials.
