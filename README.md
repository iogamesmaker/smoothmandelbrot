# smooth mandelbrot
The Mandelbrot set using the Escape Time algorithm, and smooth coloring. 1k iterations is 1.51 seconds on a 800x600 window.
I stole the smooth coloring algorithm from https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set.
uses GL/glut.h
`g++ mandel.cpp -o mandel -lGL -lGLU -lglut`
