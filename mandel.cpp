#include <GL/glut.h>
#include <iostream>
#include <cmath>
static bool fullscreen = false;
float lerp(float a,float b,float t){return a+t*(b-a);}
float WIDTH =800;
float oWIDTH,oHEIGHT;
using namespace std;
float HEIGHT=600;
int mouseX,mouseY;
bool biomorph=false;
bool julia=false;
bool smooth=false;
bool render=true;
long double xPos=-3.2;
long double yPos=-2.0;
long double zoom=150;
int frame=0;int oFrame=1486618625;
long double xJul,yJul;
int fractal=1;
long double startX,startY,start_X,start_Y;
int maxIter =250;
int maxIter2=250;
int rot=0;
float dist=0;
long double zoomFactor=1.0;
float period=0,iterations=0,iter=0,log_zn,nu,r1,r2,g1,g2,b1,b2,deltaX,deltaY,t;
void reset(){
	xPos=-3.2;yPos=-2.0;zoom=150;render=true;glutPostRedisplay();
}
//bool inCardioidOrBulb(long double x, long double y) {
//    long double y2 = y * y;
//    long double q = (x - 0.25) * (x - 0.25) + y2;
//    return (q * (q + (x - 0.25)) < y2 / 4.0 || (x + 1.0) * (x + 1.0) + y2 < 0.0625);
//}

void key(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == 32){
		if(julia){
			std::cout << "---Position---\n"<< "x: " << xPos <<"\ny: " << yPos << "\nZoom: " << zoom << "\nJulia x: " << xJul << "\nJulia y: " << yJul << "\n--------------\n";glutPostRedisplay();

		}else{
		std::cout << "---Position---\n"<< "x: " << xPos <<"\ny: " << yPos << "\nZoom:" << zoom << "\n--------------\n";glutPostRedisplay();}
	}

	switch (key){
		case 'q': {zoom *= 1.1;maxIter = maxIter2;render = true;xPos+=WIDTH/20/zoom;yPos+=HEIGHT/20/zoom;glutPostRedisplay();break;}
		case 'e': {zoom *= 0.9;maxIter = maxIter2;render = true;xPos-=WIDTH/20/zoom;yPos-=HEIGHT/20/zoom;glutPostRedisplay();break;}

        case '+': {maxIter *= 1.1;if(maxIter>1000000){maxIter=1000000;}if(maxIter<11){maxIter+=1;}
        maxIter2 = maxIter;std::cout << "Maximum iterations: " << maxIter << "\n";render = true;glutPostRedisplay();break;}
        case '=': {maxIter *= 1.1;if(maxIter>1000000){maxIter=1000000;}if(maxIter<11){maxIter+=1;}
        maxIter2 = maxIter;std::cout << "Maximum iterations: " << maxIter << "\n";render = true;glutPostRedisplay();break;}
        case '-': {if(maxIter<11){maxIter-=1;if(maxIter==-1){maxIter=0;}}else{maxIter /= 1.1;}
        maxIter2 = maxIter;std::cout << "Maximum iterations: " << maxIter << "\n";render = true;
		if(maxIter>1000000){maxIter=1000000;}glutPostRedisplay();break;}

		case 'b': {biomorph=!biomorph;glutPostRedisplay();break;}
		case 's': {smooth  =!smooth;  glutPostRedisplay();break;}
		case '4': {fractal=4;std::cout << "-New Fractal?-\n";glutPostRedisplay();break;}
		case '5': {fractal=5;std::cout << "----thing?----\n";glutPostRedisplay();break;}
		case '3': {fractal=3;std::cout << "---Tri-corn---\n";glutPostRedisplay();break;}
		case '2': {fractal=2;std::cout << "-Burning Ship-\n";glutPostRedisplay();break;}
		case '1': {fractal=1;std::cout << "Mandelbrot Set\n";glutPostRedisplay();break;}
        case 'r': {reset();break;}
		case 'f': {fullscreen=!fullscreen;if(fullscreen){oWIDTH=WIDTH;oHEIGHT=HEIGHT;glutFullScreen();}else{glutReshapeWindow(oWIDTH,oHEIGHT);}break;}
		case 'j': {if(julia&&frame>oFrame+8){julia=false;reset();}else{julia=true;xJul=xPos+mouseX/zoom;
				   yJul=yPos+(HEIGHT-mouseY)/zoom;}oFrame=frame;glutPostRedisplay();break;}
	}
}
long double r0,i0,real,imag,tempreal,io,ro;

float escapesmooth(long double real, long double imag, int x, int y){
	r0=real;
	i0=imag;
	if(julia){
		r0=xJul;i0=yJul;
	}
	iter=0.0;
	//if(fractal==1&&!julia){if(inCardioidOrBulb(real,imag)){return maxIter;}}
	while(iter<maxIter&&real*real+imag*imag<=16){
		if(fractal==4){
			tempreal=real*imag+r0;
			imag=2*real-imag+i0;
			real=tempreal;
		}else if (fractal == 5) { //failed möbius fractal - still looks interesting, like an depressed version of the Mandelbrot set.
                long double rx = cos(M_PI / 360);
                long double ry = sin(M_PI / 360);

                long double cx2 = rx * rx * real + ry * ry * imag +r0;
				long double cy2 = rx * rx * imag - ry * ry * real +i0;

                real = rx * (real * real - imag * imag) - ry * (2 * real * imag) + cx2;
                imag = rx * (2 * real * imag) + ry * (real * real - imag * imag) + cy2;
		}
		else{
			tempreal=real*real-imag*imag+r0;
			if(fractal==2){
				imag=-2*abs(real*imag)+i0;}
			else if(fractal==1){
				imag=2*real*imag+i0;}
			else if(fractal==3){
				imag=-2*real*imag+i0;}
			real=tempreal;}
		iter++;
		if(real==ro&&imag==io){
			iter=maxIter;
			break;
		}
		//interesting effect
		if(biomorph){
			if(abs(real)>4&&abs(imag)>4){
				iter=maxIter-abs(real*imag)+0.1;
				break;
			}
		}
		period++;
		if(period>20){
			period=0;
			ro=real;
			io=imag;
		}
	}
	if(smooth&&iter<maxIter){
		log_zn=log((real*real)+(imag*imag))/2;
		nu=log(log_zn/log(2))/log(2);
		iter=iter+1.0-nu;
	}
	return iter;
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(render){
		for(int y=HEIGHT;y>0;y--){
		glBegin(GL_POINTS);
			for(int x=0;x<WIDTH+1;x++){
				iterations=escapesmooth(x/zoom+xPos,y/zoom+yPos,xJul,yJul);
					glVertex2i(x,y);
				if(iterations==maxIter){
					glColor3f(0,0,0);
				}
				else{
					r1=0.5+sin(floor(iterations)/10)/2;
					g1=floor(iterations)/maxIter;
					b1=1-floor(iterations)/maxIter;
					if(smooth){
						r2=0.5+sin((floor(iterations)+1)/10)/2;
						g2=  (floor(iterations)+1)/maxIter;
						b2=1-(floor(iterations)+1)/maxIter;}
					/*Sunburst:
					float r1=floor(iterations)/32;
					float r2=floor(iterations+1)/32;
					float g1=floor(iterations)/64;
					float g2=floor(iterations+1)/64;
					float b1=floor(iterations)/128;
					float b2=floor(iterations+1)/128;
					/*test
					float r1=floor(iterations)/32;
					float r2=floor(iterations+1)/32;
					float g1=floor(iterations)/64;
					float g2=floor(iterations+1)/64;
					float b1=floor(iterations)/128;
					float b2=floor(iterations+1)/128;*/
					t=fmod(iterations,1);
					if(smooth){
						glColor3f(lerp(r1,r2,t),lerp(g1,g2,t),lerp(b1,b2,t));}
					else{
						glColor3f(r1,g1,b1);
					}
				}
			}
		}
	glEnd();
	glFlush();
	}
glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	WIDTH = w;
	HEIGHT = h;
	render=true;
	glutPostRedisplay();
}
bool isDragging = false;
int lastX,lastY;

void mouse(int button, int state, int x, int y){
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		isDragging=true;
		lastX=x;
		lastY=y;
	} else if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP){
		isDragging=false;
	}
}
void motion(int x, int y) {
	if (isDragging) {
		deltaX=(x-lastX)/zoom;
		deltaY=(y-lastY)/zoom;
		xPos-=deltaX;
		yPos+=deltaY;
		lastX=x;
		lastY=y;
		maxIter=maxIter2;
		glutPostRedisplay();
	}
}
void onMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}
void idle(){
	frame++;
}
void specialfunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:{
			yPos+=40/zoom;glutPostRedisplay();break;}
		case GLUT_KEY_DOWN:{
			yPos-=40/zoom;glutPostRedisplay();break;}
		case GLUT_KEY_RIGHT:{
			xPos+=40/zoom;glutPostRedisplay();break;}
		case GLUT_KEY_LEFT:{
			xPos-=40/zoom;glutPostRedisplay();break;}
	}
}
int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("mandel badandel");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glLoadIdentity();
	glClearColor(0.0,0.0,0.0,1.0);
	glutSetKeyRepeat(1);
	std::cout << "Maximum iterations: " << maxIter << "\n";

	glutSpecialFunc(specialfunc);
	glutPassiveMotionFunc(onMouseMove);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
