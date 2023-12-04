#include <GL/glut.h>
#include <iostream>
#include <cmath>

long double samples=1,downscale=1;
static bool fullscreen = false;
bool color=true;
long double lerp(long double a,long double b,long double t){return a+t*(b-a);}
long double WIDTH =800,biomorphVal=4,bailout=16;;
long double oWIDTH,oHEIGHT;int col,col2;
using namespace std;
long double HEIGHT=600;
int mouseX,mouseY;
bool biomorph=false;
bool julia=false;
bool smooth=false;
bool render=true;
long double xPos=-3.2;
long double yPos=-2;
long double zoom=150;
int frame=0;int oFrame=1486618625;
long double xJul,yJul;
int fractal=1;
long double startX,startY,start_X,start_Y;
int maxIter =250;
int maxIter2=250;
int rot=0;
long double dist=0;
long double zoomFactor=1.0;
long double period=0,iterations=0,iter=0,log_zn,nu;long double r1,g1,b1,r2,g2,b2,r,g,b;long double deltaX,deltaY,t;
void reset(){
	xPos=-3.2;yPos=-2.0;zoom=150;render=true;glutPostRedisplay();
}
bool inCardioidOrBulb(long double x, long double y) {
    long double y2 = y * y;
    long double q = (x - 0.25) * (x - 0.25) + y2;
    return (q * (q + (x - 0.25)) < y2 / 4.0 || (x + 1.0) * (x + 1.0) + y2 < 0.0625);
}

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
		case 'a': {samples+=1;std::cout << "samples: " << samples << "\n";glutPostRedisplay();break;}
		case 'z': {samples-=1;if(samples==0){samples=1;}std::cout << "samples: " << samples << "\n";glutPostRedisplay();break;}
		case 'b': {biomorph=!biomorph;glutPostRedisplay();break;}
		case '[': {if(biomorph){biomorphVal-=0.1;}render=true;glutPostRedisplay();break;}
		case ']': {if(biomorph){biomorphVal+=0.1;}render=true;glutPostRedisplay();break;}
		case 'o': {bailout/=1.1;render=true;glutPostRedisplay();break;}
		case 'p': {bailout*=1.1;render=true;glutPostRedisplay();break;}
		case 's': {smooth  =!smooth;render=true;glutPostRedisplay();break;}
		case '6': {fractal=6;std::cout << "--Experiment--\n";bailout=16;glutPostRedisplay();break;}
		case '5': {fractal=5;std::cout << "--Depressed?--\n";bailout=16;  glutPostRedisplay();break;}
		case '4': {fractal=4;std::cout << "-New Fractal?-\n";bailout=2048;glutPostRedisplay();break;}
		case '3': {fractal=3;std::cout << "---Tri-corn---\n";bailout=16;  glutPostRedisplay();break;}
		case '2': {fractal=2;std::cout << "-Burning Ship-\n";bailout=16;  glutPostRedisplay();break;}
		case '1': {fractal=1;std::cout << "Mandelbrot Set\n";bailout=16;  glutPostRedisplay();break;}
        case 'r': {reset();break;}
		case 'f': {fullscreen=!fullscreen;if(fullscreen){oWIDTH=WIDTH;oHEIGHT=HEIGHT;glutFullScreen();}else{glutReshapeWindow(oWIDTH,oHEIGHT);}break;}
		case 'j': {if(julia&&frame>oFrame+8){julia=false;}else{julia=true;xJul=xPos+mouseX/zoom;
				   yJul=yPos+(HEIGHT-mouseY)/zoom;}oFrame=frame;glutPostRedisplay();break;}
		case 'u' :{downscale/=2;if(downscale<1){downscale=1;}render=true;glutPostRedisplay();break;}
		case 'i' :{downscale*=2;if(downscale>128){downscale=128;}render=true;glutPostRedisplay();break;}
		case 'c' :{color=!color;render=true;glutPostRedisplay();break;}

	}
}
long double r0,i0,real,imag,tempreal,io,ro;

long double escapesmooth(long double real, long double imag){
	r0=real;
	i0=imag;
	if(julia){
		r0=xJul;i0=yJul;
	}
	iter=0.0;
	if(fractal==1&&!julia&&bailout>2&&biomorphVal>1){if(inCardioidOrBulb(real,imag)){return maxIter;}}
	while(iter<maxIter&&real*real+imag*imag<=bailout){
		if(fractal==4){
			tempreal=real*imag+r0;
			imag=2*real-imag+i0;
			real=tempreal;
		}else if (fractal == 5) { //failed möbius fractal - still looks interesting, like an depressed version of the Mandelbrot set.
                long double rx = cosf(M_PI / 360);
                long double ry = sinf(M_PI / 360);

				long double cx2 = rx * rx * real + ry * ry * imag +r0;
				long double cy2 = rx * rx * imag - ry * ry * real +i0;

                real = rx * (real * real - imag * imag) - ry * (2 * real * imag) + cx2;
                imag = rx * (2 * real * imag)+ry*(real*real-imag*imag) + cy2;
		}else if(fractal==6){
			tempreal=real+real*real-imag*imag;
			imag=2*real*imag+i0;
			real=tempreal;
		}
		else{
			tempreal=real*real-imag*imag+r0;
			if(fractal==2){
				imag=-2*fabs(real*imag)+i0;}
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
			if(fabs(real)>biomorphVal&&fabs(imag)>biomorphVal){
				iter=maxIter-fabs(real*imag)+0.1;
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
	glPointSize(downscale);
	glBegin(GL_POINTS);
	for(int y=HEIGHT;y>-0;y-=downscale){
			for(int x=-2;x<WIDTH-1;x+=downscale){
				iterations=0;
				r=0;
				g=0;
				b=0;
				for(int z=0;z<samples;z++){
					iterations=escapesmooth((x+(z/samples))/zoom+xPos,(y+(z/samples))/zoom+yPos);
					if(!(iterations==maxIter)){
						if(color){
							r1=sinf(floorf(iterations)/10);
							g1=tanf(floorf(iterations)/10);
							b1=cosf(floorf(iterations)/10);
							t=fmod(iterations,1);
							if(smooth){
								r2=sinf(floorf((iterations+1))/10);
								g2=tanf(floorf((iterations+1))/10);
								b2=cosf(floorf((iterations+1))/10);
								}
							if(smooth){
								r+=lerp(r1,r2,t);
								g+=lerp(g1,g2,t);
								b+=lerp(b1,b2,t);
							}else{
								r+=r1;g+=g1;b+=b1;
							}
						}else{r+=1;r1+=1;}
					}
				}
				glColor3f(r/samples,g/samples,b/samples);
				glVertex2i(x,y);
			}
		}
	glEnd();
	glFlush();
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
		case GLUT_KEY_F11: {fullscreen=!fullscreen;if(fullscreen){oWIDTH=WIDTH;oHEIGHT=HEIGHT;glutFullScreen();}else{glutReshapeWindow(oWIDTH,oHEIGHT);}break;}
	}
}
int main(int argc, char** argv){
	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("mandel badandel");

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
