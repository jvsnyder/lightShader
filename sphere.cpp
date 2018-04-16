#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "sphere.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <cmath>
#include "frustum.h"
#include "Camera.h"
#include <math.h>
using namespace std;

static Sphere sun;

static Sphere earth;

static Sphere moon;


double *matrix;
Matrix4 a;
Matrix4 f;
Matrix4 arbit;
 Frustum frust;
 Camera cam;
 Matrix4 inverse;
 double dotVec;
 Vector3 trackBallMap(int x, int y, int windowWidth, int windowHeight);
 Vector3 currentPos;
 Vector3 lastPos;
 double dx;
 double dy;
 double dz;
 Vector3 axis;
 Matrix4 lastModMat;

 Matrix4 modelMatX;
 Matrix4 modelMatY;
 Matrix4 mapTrack;

 
 int moves;
 int heldDown;
 Vector3 pixPoint;
 Matrix4 modelMat;
 double angleX;
 double angleY;
 double angleArbit;
 Vector3 V1;
 Vector3 V2;
 Vector3 V3;
 double magV1;
 double magV2;



 void mousePoint(int, int);
 void mouseState(int, int, int, int);
 GLdouble matrixd[16];

const static double PI = 3.1415926;

double rootMesh;

int indexLen;//for figuring how point placement


int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

double globalIndex = 0;

Vector3 *houseVerts;

Vector3 *colorHouse;


void Sphere::allocateOrbit(double orbAngle)
{
	orbCount = 0;
	double increment = orbAngle;

	
	for(double x = 0; x<2*PI; x = x+increment)
		orbCount++;

	//allocate space for orbitList
	orbitList = new Vector3[orbCount];
}





//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	//matrixPlay();
  //sun.spin(.0001);       // rotate sphere by 1 degree
	//Matrix4 tempMatrix = sun.getMatrix();		//scale other matrices by 1 degree
	//tempMatrix.scale(1, 1, 1);
	//sun.matrix = tempMatrix;
  displayCallback();    // call display routine to redraw sphere
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
	//glTranslatef(0, 0, -20);
	 // glMatrixMode(GL_MODELVIEW);
	//  glLoadMatrixd(cam.getMatrix().getPointer());
	 // gluLookAt(0.0, 10, 10,
		//  0.0,0.0,0.0,
		 // 0.0, 1.0,0.0);
//  glLoadMatrixd(frust.matrix);
  //glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
//  glTranslatef(inverse.get(0,3), inverse.get(1,3), inverse.get(2,3));
  //glMatrixMode(GL_MODELVIEW);
}


//----------------------------------------------------------------------------
// playing around the matricies so displayCallback doesnt get all ugly
void matrixPlay(){
	
	
}


/* This is the arbitrary matrix implementation of the trackball.
// A bug(possibly or a restraint of the arbitrary matrix implementation),
// something I don't like is that
// the trackball ball moves with respect to the face of the starting face of the image.
//  imagine there is a trackball bubble on the front of the image and it will move
//  only with respect to that side (when you spin 180* the controls are reversed -____- )
//  **To make it work you would somehow have to find a way to update the
//  camera matrix(not sure though)
//  **I would like to do this again but I would like to use quternation next time**
*/
void mousePoint(int px, int py)
{
	
	double degree = .05;
	if(!heldDown)
		return;
	//cout<<"Px: "<<px<<endl;
	//cout<<"Py: "<<py<<endl;
	
	
	moves++;
	//cout<<"moves: "<<moves<<endl;

	lastPos = currentPos;
	currentPos = trackBallMap(px, py, Window::width, Window::height);
	if(moves ==1)
	{	
		return;
	}

	Vector3 arbitAx;
	arbitAx.cross(lastPos, currentPos);
	//this is to prevent getting not a number from dragging the cursor into
	//the corners of the viewing window or anywhere outside the trackball 
	if(arbitAx[0] != arbitAx[0] || arbitAx[1] != arbitAx[1]|| arbitAx[2] != arbitAx[2])
		return;
	

	double dotA = lastPos.dot(currentPos);
	double productA =  lastPos.magnitude()*currentPos.magnitude();
	
	double angleA = acos(dotA/productA);

	//this is to prevent getting not a number for dragging the cursor off of the viewing window
	if(angleA != angleA || abs(angleA) <.0001)
		return;

	
	arbitAx.normalize();
	


	//for some reason, I had to make angleA negative to get the movement correct
	modelMat.arbitrary(arbitAx, -angleA);
	

	//accumulate object matrix
	modelMat.mult(lastModMat);
	lastModMat = modelMat;
	
	
	modelMat.mult(cam.getOtherMatrix());
	/*
	//so this is the same as the above line
	modelMat.mult(cam.getMatrix());
	modelMat.set(3,0,cam.getOtherMatrix().get(3,0));
	modelMat.set(3,1,cam.getOtherMatrix().get(3,1));
	modelMat.set(3,2,cam.getOtherMatrix().get(3,2));
	*/
	//cout<<"Model Matrix: "<<endl;
	//modelMat.printMatrix();
}






Vector3 trackBallMap(int x, int y, int windowWidth, int windowHeight)
{
	//const double TRACKBALL_SIZE = 1.3;
	Vector3 v;
	double d;
	


	//set X row to X axis
	if(abs(mapTrack.get(0,0)) >= abs(mapTrack.get(1,0)) && abs(mapTrack.get(0,0)) >= abs(mapTrack.get(2,0)))
	{
		
		if(mapTrack.get(0,0) < 0)
			v.setX(-1*(2.0*x - windowWidth)/windowWidth);
		else
		{
			v.setX((2.0*x - windowWidth)/windowWidth);
		}

		//set Y row to Y axis XYZ
		if(abs(mapTrack.get(1,1))>= abs(mapTrack.get(2,1)))
		{
			if(mapTrack.get(1,1) < 0)
				v.setY(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setY((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setZ(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setZ ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(2,2) < 0)
				v.setZ(-1*sqrt(1.001 - d*d));
			else
			v.setZ(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		
		}
		//set Z row to Y axis XZY
		else
		{
			if(mapTrack.get(2,1) < 0)
				v.setZ(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setZ((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setY(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setY ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(1,2) < 0)
				v.setY(-1*sqrt(1.001 - d*d));
			else
			v.setY(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		}

		

	}

	//set Y column to X axis
	else if(abs(mapTrack.get(1,0)) >= abs(mapTrack.get(0,0)) && abs(mapTrack.get(1,0)) >= abs(mapTrack.get(2,0)))
		{

			if(mapTrack.get(0,0) < 0)
			v.setY(-1*(2.0*x - windowWidth)/windowWidth);
		else
		{
			v.setY((2.0*x - windowWidth)/windowWidth);
		}

		//set X row to Y axis XYZ
		if(abs(mapTrack.get(0,1))>= abs(mapTrack.get(2,1)))
		{
			if(mapTrack.get(0,1) < 0)
				v.setX(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setX((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setZ(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setZ ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(2,2) < 0)
				v.setZ(-1*sqrt(1.001 - d*d));
			else
			v.setZ(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		
		}
		//set Z row to Y axis XZY
		else
		{
			if(mapTrack.get(2,1) < 0)
				v.setZ(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setZ((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setY(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setX ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(0,2) < 0)
				v.setX(-1*sqrt(1.001 - d*d));
			else
			v.setX(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		}




		}

	//set Z column to X axis
	else
		{
			if(mapTrack.get(2,0) < 0)
			v.setZ(-1*(2.0*x - windowWidth)/windowWidth);
		else
		{
			v.setZ((2.0*x - windowWidth)/windowWidth);
		}

		//set Y row to Y axis ZYX
		if(abs(mapTrack.get(1,1))>= abs(mapTrack.get(0,1)))
		{
			if(mapTrack.get(1,1) < 0)
				v.setY(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setY((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setX(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setX ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(0,2) < 0)
				v.setX(-1*sqrt(1.001 - d*d));
			else
			v.setX(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		
		}
		//set X row to Y axis ZXY
		else
		{
			if(mapTrack.get(0,1) < 0)
				v.setX(-1*(windowHeight - 2.0 * y)/windowHeight);
			else
			{
				v.setX((windowHeight - 2.0 * y)/windowHeight);
			}
			v.setY(0.0);
			
			d = sqrt(v[0] *v[0] + v[1] * v[1]);



			v.setY ( (d < 1.0) ? d : 1.0);
			if(mapTrack.get(1,2) < 0)
				v.setY(-1*sqrt(1.001 - d*d));
			else
			v.setY(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		}
		}




	/*
	v.setX((2.0*x - windowWidth)/windowWidth);
	v.setY((windowHeight - 2.0 * y)/windowHeight);
	v.setZ(0.0);
	


	//clamping to -1, 1
	/*
	v.setX ( max(-1.0, v[0]));
	v.setX ( min(1.0, v[0]));

	v.setY ( max(-1.0, v[1]));
	v.setY ( min(1.0, v[1]));
	

	
	d = sqrt(v[0] *v[0] + v[1] * v[1]);



	v.setZ ( (d < 1.0) ? d : 1.0);
	v.setZ(sqrt(1.001 - d*d));
	//v.setZ(expf(-TRACKBALL_SIZE * d *d));

	//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
	v.normalize();
	//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;

	*/
	return v;
}

/*Gets the state of the mouse buttons
// function created with specific params cuz of
// gl's glutmousefunc requires it to be so
//
*/
void mouseState(int button, int state, int x, int y){

	int leftTouchOff = 0;
	int flagLeft = 0;
	int flagRight = 0;
	
	if(button == GLUT_RIGHT_BUTTON){
		flagRight = 1;
	}
	
	if(button == GLUT_LEFT_BUTTON){
		flagLeft = 1;
	}
	
	if(state==GLUT_DOWN)
	{
		heldDown =1;
	}
	else
	{
		heldDown = 0;
		moves = 0;
		mapTrack = modelMat;

	}


	if(flagLeft ==1 && heldDown == 0)
	{
		//cout<<"left button clicked!"<<endl;
		flagLeft = 0;
		leftTouchOff = 0;
	}

	if(flagRight ==1 )
	{
		//cout<<"right button clicked!"<<endl;
		flagRight = 0;
	}

}






//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	
	glMatrixMode(GL_PROJECTION);
	

	//view frustrum
	glLoadIdentity();
	glLoadMatrixd(frust.getMatrix().getPointer());
	//GLdouble projMatrix[16];
	//glGetDoublev(GL_PROJECTION, projMatrix);

	/*(
	int y = 0;
	cout<<"projMatrix: "<<endl;
	for( int x = 0; x<16; x++)
	{
		cout<<projMatrix[x]<<" ";
		y++;
		if(y == 4)
			cout<<endl;
	}
	*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	//model matrix * view frustrum = modelviewMat
	//modelMat.mult(cam.getMatrix());
	glLoadMatrixd(modelMat.getPointer());
	


	
   // Draw sides of sphere in object coordinate system:
	glBegin(GL_TRIANGLES);
    
	int nVerts = 42;    // your vertex array needs to have this many entries


		




			 // The index data stores the connectivity of the triangles; 
  // index 0 refers to the first triangle defined above
  int indices[] = {
            0,2,3,    0,1,2,      // front face
            4,6,7,    4,5,6,      // left face
            8,10,11,  8,9,10,     // back face
            12,14,15, 12,13,14,   // right face
            16,18,19, 16,17,18,   // top face
            20,22,23, 20,21,22,   // bottom face
                   
            24,26,27, 24,25,26,   // grass
            28,29,30,             // front attic wall
            31,33,34, 31,32,33,   // left slope
            35,37,38, 35,36,37,   // right slope
            39,40,41};            // rear attic wall

			for(int x = 0; x<60; x= x+3)
			{
				

				glColor3f(colorHouse[indices[x]].getX(),colorHouse[indices[x]].getY() ,colorHouse[indices[x]].getZ());

				glVertex3f(houseVerts[indices[x]].getX(), houseVerts[indices[x]].getY(), houseVerts[indices[x]].getZ());
				glVertex3f(houseVerts[indices[x+1]].getX(), houseVerts[indices[x+1]].getY(), houseVerts[indices[x+1]].getZ());
				glVertex3f(houseVerts[indices[x+2]].getX(), houseVerts[indices[x+2]].getY(), houseVerts[indices[x+2]].getZ());
			}


	

  glEnd();
  
  glFlush();  
  glutSwapBuffers();
}

Sphere::Sphere()
{
  angle = 0.0;
  orbIndex = 0;
}


void Sphere::allocateSphere(int mesh)
{
	

	
	rootMesh = sqrt((double)mesh);

	int tempCircum = (int)rootMesh;

	coor = 4.0 * tempCircum*tempCircum;

	pointList = new Vector3[coor];
	

}

//TODO: make sure adjacent colors aren't the same
//		the mesh always will go to a perfect square above or below thanks to truncating
void Sphere::createSphere(int mesh, Vector3 translation, double radius)
{

	
	//change this to an int then back to float to get floor value of circum
	double circum;
	

	
	rootMesh = sqrt((double)mesh);

	int tempCircum = (int)rootMesh;


	circum = (double)tempCircum;
	
	indexLen = tempCircum +1;

	//cout<<"circum: "<<circum<<endl;
	double length = (2.0*PI)/circum;// XY-coor space
	double height = (PI)/circum;// XZ-coor space
	
	//float radius = 5;

	int index = 0;
	Vector3 marker;//starting at bottom

	double xCor;
	double yCor;
	double zCor;

	double tempRad;


	index = 0;

	for(int x = 0; x<indexLen; x++)
	{
		
		for(int y = 0; y<indexLen; y++)
		{
			
		

			yCor = radius * cos(height*(x));//we would add in an angle constant "w" e.g. yCor = radius * cos(height*(x) + w));
			tempRad = radius * sin(height*(x));
			
			

			xCor = tempRad*cos(length*(y));
			zCor =	tempRad*sin(length*(y));
			

			marker.set(xCor, yCor, zCor);
			

			marker.add(translation);

			
			pointList[index] = marker;
			index++;

		}//inner for

		

	}//outer for

}


Matrix4& Sphere::getMatrix()
{
  return matrix;
}

void Sphere::spin(double deg)
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  matrix.rotateY(angle);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title
  if (glutGet(GLUT_WINDOW_COLORMAP_SIZE) != 0) 
  {
    cerr << "Fatal Error: bad RGBA colormap size\n" << endl;
    exit(1);
  }
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glDisable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  


	




	houseVerts = new Vector3[42];

		 float vertices[] = {  
            -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
            -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
            4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
            4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
            4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
            -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

            -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
            -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
            4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
            -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
            4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall



						  // These are the RGB colors corresponding to the vertices, in the same order
 

			int index = 0;
	//read in houseVerts to array
	for(int x = 0; x<42;x++)
	{
			houseVerts[x].set(vertices[index], vertices[index+1],vertices[index+2]);
			index = index+3;
	}





	 float colors[] = { 
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
  
            0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
            0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
            1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
            0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
            0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red



	index = 0;
	


	colorHouse = new Vector3[42];
	for(int x = 0;x<42;x++)
	{
		colorHouse[x].set(colors[index], colors[index+1], colors[index+2]);
		index = index+3;
	}




	double fov = 60.0 *PI/360;
	//genMatrix(double near, double far, double aspect, double fov)
	frust.genMatrix(1, 100, 1, fov);

	 frust.perSpec(fov,1,1,100);


	cout<<"Frustum Matrix: "<<endl;
	frust.getMatrix().printMatrix();
	cout<<endl;

	
	//image 1
	Vector3 cenVec(0,0,40);//center of projection(e)
	Vector3 lookVec(0,0,0);//look at(d)
	Vector3 upVec(0,1,0);//up vector (up)
	
	
	/*
	//image 2
	Vector3 cenVec(-10,40,40);
	Vector3 lookVec(-5,0,0);
	Vector3 upVec(0,1,0);
	*/
	
	 /*
	Vector3 cenVec(-15,5,10);
	Vector3 lookVec(-5,0,0);
	Vector3 upVec(0,1,.5);
	*/
	
	cam.setE(cenVec);
	cam.setD(lookVec);
	cam.setUp(upVec);

	cam.setMatrix();


	
	

	cout<<"cam Matrix: "<<endl;
	cam.getMatrix().printMatrix();

	frust.perSpec(60, 1, 1, 100);


	matrixPlay();
	modelMat.identity();
	modelMatX.identity();
	modelMatY.identity();
	lastModMat.identity();

	mapTrack.identity();

	V1.set(1,0,0);
	V2.set(0,1,0);
	angleX = 0;
	angleY = 0;
	
	cam.getOtherMatrix().mult(cam.getMatrix());

	modelMat.mult(cam.getOtherMatrix());

	cout<<"Cam's otherMatrix: "<<endl;
	cam.getOtherMatrix().printMatrix();

	cout<<"Pix point: "<<pixPoint.getX()<<" "<<pixPoint.getY()<<" "<<pixPoint.getZ()<<endl;

  // Install callback functions:
	
	
	lastPos.set(0,0,0);

	arbit.identity();
	
	glutMouseFunc(mouseState);
	glutMotionFunc(mousePoint);
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  
  
  
  
  glutMainLoop();
  return 0;
}

