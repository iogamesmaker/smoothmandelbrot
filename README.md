stuff here: ![personal webpage](https://hetboeitmeniet.nl/smoothmandelbrot/)
# smooth mandelbrot
The Mandelbrot set using the Escape Time algorithm, and smooth coloring. 1k iterations is ~1.3 seconds on a 800x600 window on a chromebook.
I stole the smooth coloring algorithm from https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set.
uses GL/glut.h=
`g++ mandel.cpp -o mandel -lGL -lGLU -lglut -Ofast` to compile on linux. requires `freeglut3`.

multithreading for some reason only slows stuff down (using omp.h), so not doing that.

# Controls:
Drag to move.

Q/E to zoom in/out.

-/= to change the maximum amount of iterations.

1 for Mandelbrot set.

2 for Burning Ship.

3 for Tricorn/mandelbar

4 for weird line fractal with spider web julia sets

5 for Failed Möbius/Depressed mandelbrot

F goes into fullscreen

R resets.

J for julia set at the point where your cursor is.

SPACE prints position + zoom

B to toggle biomorphs

S to toggle smooth coloring

[&] to in/decrease biomorph value
o&p to in/decrease bailout
# planned stuff
general optimizations, like
boundry tracing? (any help really appreciated)
better controls
# me complaining
I am a total C++ noob, so do not expect much. I do not know anything about glut, I used tutorials.
# Screenshots
here are some epik screenshots using only this program (and the KDE screenshot thing)

![mandel](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/3a938b3b-b0f3-441e-9257-b60af0aa5bbe)
![mandel2](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/91980032-05f3-40e6-b359-6d9432411276)
![mandel3](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/bc4f7b51-6f9b-4805-aef9-6810c6a30961)
![mandel4](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/88f2a6fb-e9fc-4650-8279-64b084ea33fe)
![mandel5](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/08a411b9-04c9-49a3-b297-813710030927)
![mandel6](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/a5c6fe6d-4ee2-4c6f-9968-41e91ffbfd1f)

I find this one interesting, with a lower bailout value + smooth colors, we get this pretty cool image of a Julia set of the Mandelbrot set.
![julia](https://github.com/iogameplayer/smoothmandelbrot/assets/130794776/4de4b40d-8f75-4262-8971-6aa82b44d333)

