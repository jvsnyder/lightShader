#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4.h"
#include <iostream>
using namespace std;

class Camera
{
protected:
	Vector3 e;	//center of projection
	Vector3 d;	//look at point
	Vector3 up; //up vector
	Matrix4 interCam;
	Matrix4 otherCam;

public:
	Camera();
	void setE(Vector3);
	void setD(Vector3);
	void setUp(Vector3);

	void setMatrix();

	Vector3 getE();
	Vector3 getD();
	Vector3 getUp();
	Matrix4& getMatrix();
	Matrix4& getOtherMatrix();
	Matrix4 getInverse();


};
#endif