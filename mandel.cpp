#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include <cmath>
using namespace std::chrono;
float lerp(float a,float b,float t){return a+t*(b-a);}
const int WIDTH =800;
const int HEIGHT=600;
double xPos=-2.0;
double yPos=-1.0;
double zoom=300;
int maxIter=1000;
float escapesmooth(double real, double imag){ // Optimized Escape Time Algorithm
	double r0=real;
	double i0=imag;
	float iter=0.0;
	double tempreal;
	while(iter<	maxIter&&real*real+imag*imag<=4){
		tempreal=real*real-imag*imag+r0;
		imag=2*real*imag+i0;
		real=tempreal;
		iter++;
	}
	if(iter<maxIter){
		float log_zn=log((real*real)+(imag*imag))/2;
		float nu=log(log_zn/log(2))/log(2);
		iter=iter+1.0-nu;}
	return iter;
}
int escape(double real, double imag){ // Escape time algorithm 
	double r0=real;
	double ig0=imag;
	int iter=0;
	double tempreal=0;
	while(iter<	maxIter&&real*real+imag*imag<=4){
		tempreal=real*real-imag*imag+r0;
		imag=2*real*imag+ig0;
		real=tempreal;
		iter++;
	}
	return iter;
}

void display(){
    auto start = high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT);
	for(int x=0;x<WIDTH;x++){
		glBegin(GL_POINTS);
		for(int y=0;y<HEIGHT;y++){
			float iterations=escapesmooth(x/zoom+xPos,y/zoom+yPos);
			glVertex2i(x,y);
			if(iterations==maxIter){
				glColor3f(0,0,0);
			}
			else{/*
				float r1=0.5+sin(floor(iterations)/10)/2;
				float r2=0.5+sin((floor(iterations)+1)/10)/2;
				float g1=floor(iterations)/maxIter;
				float g2=(floor(iterations)+1)/maxIter;
				float b1=1-floor(iterations)/maxIter;
				float b2=1-(floor(iterations)+1)/maxIter;*/
				
				float r1=floor(iterations)/32;
				float r2=floor(iterations+1)/32;
				float g1=floor(iterations)/64;
				float g2=floor(iterations+1)/64;
				float b1=floor(iterations)/128;
				float b2=floor(iterations+1)/128;
				
				float t=fmod(iterations,1);
                glColor3f(lerp(r1,r2,t),lerp(g1,g2,t),lerp(b1,b2,t));
                //glColor3f(r1,g1,b1);
				}
		}
		glEnd();
		//glFlush();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count() << "\n";
	glFlush();
	glutSwapBuffers();
}
void reshape(int w,int h){glutReshapeWindow(WIDTH,HEIGHT);}

int main(int argc, char** argv){
	glutInit(&argc,argv); // Initialize Glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("mandel badandel");
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glClearColor(0.0,0.0,0.0,1.0);
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	return 0;
}
