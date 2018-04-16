#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "project4.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <cmath>
#include "frustum.h"
#include "Camera.h"
#include <math.h>
using namespace std;
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

double globalIndex = 0;

Vector3 *houseVerts;

Vector3 *colorHouse;
void mousePoint(int, int);
void mouseState(int, int, int, int);


void mousePoint(int, int);
void mouseState(int, int, int, int);
GLdouble matrixd[16];
int Window::width = 512;   // set window width in pixels here
int Window::height = 512;
const static double PI = 3.1415926;

void mousePoint(int px, int py)
{

	double degree = .05;
	if (!heldDown)
		return;
	//cout<<"Px: "<<px<<endl;
	//cout<<"Py: "<<py<<endl;


	moves++;
	//cout<<"moves: "<<moves<<endl;

	lastPos = currentPos;
	currentPos = trackBallMap(px, py, Window::width, Window::height);
	if (moves == 1)
	{
		return;
	}

	Vector3 arbitAx;
	arbitAx.cross(lastPos, currentPos);
	//this is to prevent getting not a number from dragging the cursor into
	//the corners of the viewing window or anywhere outside the trackball 
	if (arbitAx[0] != arbitAx[0] || arbitAx[1] != arbitAx[1] || arbitAx[2] != arbitAx[2])
		return;


	double dotA = lastPos.dot(currentPos);
	double productA = lastPos.magnitude()*currentPos.magnitude();

	double angleA = acos(dotA / productA);

	//this is to prevent getting not a number for dragging the cursor off of the viewing window
	if (angleA != angleA || abs(angleA) <.0001)
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

/*Gets the state of the mouse buttons
// function created with specific params cuz of
// gl's glutmousefunc requires it to be so
//
*/
void mouseState(int button, int state, int x, int y) {

	int leftTouchOff = 0;
	int flagLeft = 0;
	int flagRight = 0;

	if (button == GLUT_RIGHT_BUTTON) {
		flagRight = 1;
	}

	if (button == GLUT_LEFT_BUTTON) {
		flagLeft = 1;
	}

	if (state == GLUT_DOWN)
	{
		heldDown = 1;
	}
	else
	{
		heldDown = 0;
		moves = 0;
		mapTrack = modelMat;

	}


	if (flagLeft == 1 && heldDown == 0)
	{
		//cout<<"left button clicked!"<<endl;
		flagLeft = 0;
		leftTouchOff = 0;
	}

	if (flagRight == 1)
	{
		//cout<<"right button clicked!"<<endl;
		flagRight = 0;
	}

}

Vector3 trackBallMap(int x, int y, int windowWidth, int windowHeight)
{
	//const double TRACKBALL_SIZE = 1.3;
	Vector3 v;
	double d;



	//set X row to X axis
	if (abs(mapTrack.get(0, 0)) >= abs(mapTrack.get(1, 0)) && abs(mapTrack.get(0, 0)) >= abs(mapTrack.get(2, 0)))
	{

		if (mapTrack.get(0, 0) < 0)
			v.setX(-1 * (2.0*x - windowWidth) / windowWidth);
		else
		{
			v.setX((2.0*x - windowWidth) / windowWidth);
		}

		//set Y row to Y axis XYZ
		if (abs(mapTrack.get(1, 1)) >= abs(mapTrack.get(2, 1)))
		{
			if (mapTrack.get(1, 1) < 0)
				v.setY(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setY((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setZ(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setZ((d < 1.0) ? d : 1.0);
			if (mapTrack.get(2, 2) < 0)
				v.setZ(-1 * sqrt(1.001 - d*d));
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
			if (mapTrack.get(2, 1) < 0)
				v.setZ(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setZ((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setY(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setY((d < 1.0) ? d : 1.0);
			if (mapTrack.get(1, 2) < 0)
				v.setY(-1 * sqrt(1.001 - d*d));
			else
				v.setY(sqrt(1.001 - d*d));
			//v.setZ(expf(-TRACKBALL_SIZE * d *d));

			//cout<<"coordinates: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
			v.normalize();
			//cout<<"coordinates after normalizing: "<<v.getX()<<" "<<v.getY()<<" "<<v.getZ()<<endl;
		}



	}

	//set Y column to X axis
	else if (abs(mapTrack.get(1, 0)) >= abs(mapTrack.get(0, 0)) && abs(mapTrack.get(1, 0)) >= abs(mapTrack.get(2, 0)))
	{

		if (mapTrack.get(0, 0) < 0)
			v.setY(-1 * (2.0*x - windowWidth) / windowWidth);
		else
		{
			v.setY((2.0*x - windowWidth) / windowWidth);
		}

		//set X row to Y axis XYZ
		if (abs(mapTrack.get(0, 1)) >= abs(mapTrack.get(2, 1)))
		{
			if (mapTrack.get(0, 1) < 0)
				v.setX(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setX((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setZ(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setZ((d < 1.0) ? d : 1.0);
			if (mapTrack.get(2, 2) < 0)
				v.setZ(-1 * sqrt(1.001 - d*d));
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
			if (mapTrack.get(2, 1) < 0)
				v.setZ(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setZ((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setY(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setX((d < 1.0) ? d : 1.0);
			if (mapTrack.get(0, 2) < 0)
				v.setX(-1 * sqrt(1.001 - d*d));
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
		if (mapTrack.get(2, 0) < 0)
			v.setZ(-1 * (2.0*x - windowWidth) / windowWidth);
		else
		{
			v.setZ((2.0*x - windowWidth) / windowWidth);
		}

		//set Y row to Y axis ZYX
		if (abs(mapTrack.get(1, 1)) >= abs(mapTrack.get(0, 1)))
		{
			if (mapTrack.get(1, 1) < 0)
				v.setY(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setY((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setX(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setX((d < 1.0) ? d : 1.0);
			if (mapTrack.get(0, 2) < 0)
				v.setX(-1 * sqrt(1.001 - d*d));
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
			if (mapTrack.get(0, 1) < 0)
				v.setX(-1 * (windowHeight - 2.0 * y) / windowHeight);
			else
			{
				v.setX((windowHeight - 2.0 * y) / windowHeight);
			}
			v.setY(0.0);

			d = sqrt(v[0] * v[0] + v[1] * v[1]);



			v.setY((d < 1.0) ? d : 1.0);
			if (mapTrack.get(1, 2) < 0)
				v.setY(-1 * sqrt(1.001 - d*d));
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


//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, float(w)/float(h), 1.0, 100.0);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  GLfloat specular[]  = {1.0, 1.0, 1.0, 1.0};
  GLfloat shininess[] = {50.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Generate specular material properties:
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  
  // Draw the first sphere:
  glTranslatef(-1.5, 0, -8);
  glutSolidSphere(1.0, 12, 12); 
  
  // Done with that, clear the modelview matrix
  glLoadIdentity();

  // Draw the second sphere:
  glTranslatef(1.5, 0, -8);
  glutSolidSphere(1.0, 12, 12); 
  
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  GLfloat light0_position[] = {5.0, 5.0, 3.0, 0.0};
  GLfloat ambient[]         = {0.2, 0.2, 0.2, 1.0};  // default ambient color for all light sources
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(512, 512);         // set initial window size
  glutCreateWindow("Two Spheres");      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable z-buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_LIGHTING);                              // enables lighting; this changes the behavior of glColor
  glEnable(GL_LIGHT0);                                // enable a light source; otherwise you will only see ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);  // set the default ambient color
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  // allow glColor to set ambient and diffuse colors of geometry
  



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
	  4,4,-4, -4,4,-4, 0,8,-4 };                   // rear attic wall



												   // These are the RGB colors corresponding to the vertices, in the same order


  int index = 0;
  //read in houseVerts to array
  for (int x = 0; x<42; x++)
  {
	  houseVerts[x].set(vertices[index], vertices[index + 1], vertices[index + 2]);
	  index = index + 3;
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
	  0,0,1, 0,0,1, 0,0,1, };              // rear attic wall is red



  index = 0;



  colorHouse = new Vector3[42];
  for (int x = 0; x<42; x++)
  {
	  colorHouse[x].set(colors[index], colors[index + 1], colors[index + 2]);
	  index = index + 3;
  }




  double fov = 60.0 *PI / 360;
  //genMatrix(double near, double far, double aspect, double fov)
  frust.genMatrix(1, 100, 1, fov);

  frust.perSpec(fov, 1, 1, 100);


  cout << "Frustum Matrix: " << endl;
  frust.getMatrix().printMatrix();
  cout << endl;


  //image 1
  Vector3 cenVec(0, 0, 40);//center of projection(e)
  Vector3 lookVec(0, 0, 0);//look at(d)
  Vector3 upVec(0, 1, 0);//up vector (up)


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





  cout << "cam Matrix: " << endl;
  cam.getMatrix().printMatrix();

  frust.perSpec(60, 1, 1, 100);


  
  modelMat.identity();
  modelMatX.identity();
  modelMatY.identity();
  lastModMat.identity();

  mapTrack.identity();

  V1.set(1, 0, 0);
  V2.set(0, 1, 0);
  angleX = 0;
  angleY = 0;

  cam.getOtherMatrix().mult(cam.getMatrix());

  modelMat.mult(cam.getOtherMatrix());

  cout << "Cam's otherMatrix: " << endl;
  cam.getOtherMatrix().printMatrix();

  cout << "Pix point: " << pixPoint.getX() << " " << pixPoint.getY() << " " << pixPoint.getZ() << endl;

  // Install callback functions:


  lastPos.set(0, 0, 0);

  arbit.identity();

  //glutMouseFunc(mouseState);
  glutMotionFunc(mousePoint);

  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
    
  glutMainLoop();
  return 0;
}

