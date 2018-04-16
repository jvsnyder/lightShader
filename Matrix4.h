#ifndef _MATRIX4_H_
#define _MATRIX4_H_
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>
using namespace std;
class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements
	void set(int row, int col, double value);
	double get(int row, int col);
	void mult(Matrix4);
    void identity();  // create identity matrix
    void rotateX(double); // rotation about x axis
	void rotateY(double); // rotation about y axis
	void rotateZ(double); // rotation about z axis
	void rotateXY(double, double);
	void arbitrary(Vector3, double);
	void scale(double, double, double);
	void printMatrix();
	Matrix4 calcInverse();
};

#endif