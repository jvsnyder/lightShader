#include "Camera.h"


Camera::Camera()
{
}

void Camera::setD(Vector3 lookVec)//eye location
{
	d = lookVec;
}


void Camera::setE(Vector3 cenVec)//center or point you're looking at as the origin
{
	e = cenVec;
}

void Camera::setUp(Vector3 upVec)//up
{
	up = upVec;
}




void Camera::setMatrix()
{
	Vector3 tempVec;
	Matrix4 tempCam;
	tempCam.identity();

	//z-axis

	//F

	tempVec.set(d[0], d[1], d[2]);
	
	tempVec-e; 
	

	
	
	double magF = tempVec.magnitude();
	

	
	Vector3 forward(tempVec.getX()/magF, tempVec.getY()/magF, tempVec.getZ()/magF);
	

	double magUp = up.magnitude();
	Vector3 upPrime(up.getX()/magUp, up.getY()/magUp, up.getZ()/magUp);
	
	tempVec.cross(forward, upPrime);

	Vector3 s(tempVec.getX(), tempVec.getY(), tempVec.getZ());
	
	tempVec.cross(s, forward);
	Vector3 u(tempVec.getX(), tempVec.getY(), tempVec.getZ());
	




	 /*this is the matrix set up from http://www.manpagez.com/man/3/gluLookAt/*/
	interCam.set(0,0,  s.getX());
	interCam.set(1,0,  s.getY());
	interCam.set(2,0,  s.getZ());
	interCam.set(3,0,  0);

	interCam.set(0,1, u.getX());
	interCam.set(1,1, u.getY());
	interCam.set(2,1, u.getZ());
	interCam.set(3,1,  0);

	interCam.set(0,2, forward.getX()*-1);
	interCam.set(1,2, forward.getY()*-1);
	interCam.set(2,2, forward.getZ()*-1);
	interCam.set(3,2, 0);

	
	interCam.set(0,3, 0);
	interCam.set(1,3, 0);
	interCam.set(2,3, 0);
	interCam.set(3,3, 1);
	 
	
	/*
	otherCam.identity();
	otherCam.set(0,3,e.getX()*-1);
	otherCam.set(1,3,e.getY()*-1);
	otherCam.set(2,3,e.getZ()*-1);
	*/

	otherCam.identity();
	otherCam.set(3,0,e.getX()*-1);
	otherCam.set(3,1,e.getY()*-1);
	otherCam.set(3,2,e.getZ()*-1);
	
}



Vector3 Camera::getD()
{
	return d;
}

Vector3 Camera::getE()
{
	return e;
}

Vector3 Camera::getUp()
{
	return up;
}

Matrix4& Camera::getMatrix()
{
	return interCam;
}

Matrix4& Camera::getOtherMatrix()
{
	return otherCam;
}

Matrix4 Camera::getInverse()
{
		return interCam.calcInverse();
}

