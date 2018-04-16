#ifndef _sphere_H_
#define _sphere_H_

#include "Matrix4.h"

class Sphere			
{
  protected:
                     // model matrix
    double angle;                   // rotation angle [degrees]

  public:
	  Matrix4 matrix;
	Sphere();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin sphere [degrees]

	int coor;
	Vector3 *pointList;
	void createSphere(int, Vector3, double);
	
	void allocateSphere(int);

	void allocateOrbit(double);
	int orbCount;
	int orbIndex;
	Vector3 *orbitList;
	void orbit(double, Vector3, double);

};

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

