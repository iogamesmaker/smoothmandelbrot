#include <GL/glut.h>
#include <iostream>
#include <cmath>
float lerp(float a,float b,float t){return a+t*(b-a);}
int WIDTH =800;
int HEIGHT=600;
int mouseX,mouseY;
bool biomorph=false;
bool julia=false;
bool smooth=false;
bool render=true;
bool cbdetect=true;
long double xPos=-3.2;
long double yPos=-2.0;
long double zoom=150;
long double xJul,yJul;
int fractal=1;
long double startX,startY,start_X,start_Y;
int maxIter =1000;
int maxIter2=1000;
long double zoomFactor=1.0;
float period=0,iterations=0,iter=0,log_zn,nu,r1,r2,g1,g2,b1,b2,deltaX,deltaY,t;
void reset(){
	xPos=-3.2;yPos=-2.0;zoom=150;render=true;glutPostRedisplay();
}
bool inCardioidOrBulb(double x, double y) {
    double y2 = y * y;
    double q = (x - 0.25) * (x - 0.25) + y2;
    return (q * (q + (x - 0.25)) < y2 / 4.0 || (x + 1.0) * (x + 1.0) + y2 < 0.0625);
}

void key(unsigned char key, int x, int y) {
	switch (key){
		case 'q': {
			zoom *= 1.1;
			maxIter = maxIter2;
			render = true;
			glutPostRedisplay();
			break;
		}

		case 'e': {
			zoom *= 0.9;
			maxIter = maxIter2;
			render = true;
			glutPostRedisplay();
			break;
		}
        case '+': {maxIter *= 1.1;maxIter2 = maxIter;std::cout << "Maximum iterations: " << maxIter << "\n";render = true;glutPostRedisplay();break;}
        case '=': {maxIter *= 1.1;maxIter2 = maxIter;std::cout << "Maximum iterations: " << maxIter << "\n";render = true;glutPostRedisplay();break;}
        case '-': {maxIter /= 1.1;maxIter2 = maxIter;if(maxIter<10){maxIter=10;}std::cout << "Maximum iterations: " << maxIter << "\n";render = true;glutPostRedisplay();break;}
		case 'b': {biomorph=!biomorph;glutPostRedisplay();break;}
		case 's': {smooth  =!smooth;  glutPostRedisplay();break;}
		case 'c': {cbdetect=!cbdetect;glutPostRedisplay();break;}
		case '2': {fractal=2;std::cout << "-Burning Ship-\n"; break;}
		case '1': {fractal=1;std::cout << "Mandelbrot Set\n"; break;}
        case 'r': {reset();break;}
        case 'j': {
			if(julia){
				julia=false;
				reset();
				std::cout << "-Fractal Mode-\n";
			}
			else{
				julia=true;
				xJul=mouseX/zoom+xPos;
				yJul=mouseY/zoom+yPos;
				reset();
				std::cout << "--Julia Mode--\nReal:" << xJul << "\nImag:" << yJul << "\n--------------\n";
			}
			break;
		}
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
	if(fractal==1&&cbdetect){if(inCardioidOrBulb(real,imag)){return maxIter;}}
	while(iter<maxIter&&real*real+imag*imag<=16){
		tempreal=real*real-imag*imag+r0;
		if(fractal==2){
		imag=-2*abs(real*imag)+i0;}
		else if(fractal==1){
		imag=2*real*imag+i0;}
		real=tempreal;
		iter++;
		if(real==ro&&imag==io){
			iter=maxIter;
			break;
		}
		//interesting effect
		if(biomorph){
			if(abs(real)>4&&abs(imag)>4){
				iter=real+imag;
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
		if(render){
			for(int y=HEIGHT;y>0;y--){
				glBegin(GL_POINTS);
				for(int x=0;x<WIDTH;x++){
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
						/*Sunburst:*//*
						float r1=floor(iterations)/32;
						float r2=floor(iterations+1)/32;
						float g1=floor(iterations)/64;
						float g2=floor(iterations+1)/64;
						float b1=floor(iterations)/128;
						float b2=floor(iterations+1)/128;
						/*test*//*
						float r1=floor(iterations)/32;
						float r2=floor(iterations+1)/32;
						float g1=floor(iterations)/64;
						float g2=floor(iterations+1)/64;
						float b1=floor(iterations)/128;
						float b2=floor(iterations+1)/128;*/

						t=fmod(iterations,1);
						if(smooth){
							if(x==1&&y==1){std::cout << "a";}
							glColor3f(lerp(r1,r2,t),lerp(g1,g2,t),lerp(b1,b2,t));}
						else{
							glColor3f(r1,g1,b1);
							}
				}
			}
	glEnd();
	glFlush();}
	}
	//maxIter*=1.2;
}
void reshape(int w,int h){glutReshapeWindow(w,h);HEIGHT=h;WIDTH=w;}
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
int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("mandel badandel");

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glClearColor(0.0,0.0,0.0,1.0);
	std::cout << "Maximum iterations: " << maxIter << "\n";
	glutPassiveMotionFunc(onMouseMove);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutKeyboardFunc(key);

	glutMainLoop();
	return 0;
}
