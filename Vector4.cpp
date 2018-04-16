#include "Vector4.h"

Vector4::Vector4() {x=0.0; y=0.0; z=0.0; j=0.0;};

Vector4::Vector4(double x0,double y0,double z0, double j0) {x=x0; y=y0; z=z0; j=j0;}

void Vector4::set(double x0,double y0,double z0, double j0) {x=x0; y=y0; z=z0; j=j0;}

double Vector4::getX(){return x;}
double Vector4::getY(){return y;}
double Vector4::getZ(){return z;}
double Vector4::getJ(){return j;}

double Vector4::operator[](int index)
{
	double notFound = 0;
	switch(index)
	{
	case(0):
		return x;
		break;
	case(1):
		return y;
		break;
	case(2):
		return z;
		break;
	case(3):
		return j;
		break;
	default:
		return notFound;
		break;
	
	}
}	


void Vector4::add(Vector4 &a) {x+=a.x; y+=a.y; z+=a.z; j+=a.j;}

void Vector4::add(Vector4 &a,Vector4 &b) {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z; j = a.j+b.j;}

void Vector4::operator+(Vector4 &a){x+=a.x; y+=a.y; z+=a.z; j+=a.j;}

void Vector4::subtract(Vector4 &a) {x-=a.x; y-=a.y; z-=a.z; j-=a.j;}

void Vector4::subtract(Vector4 &a,Vector4 &b) {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z; j= a.j-b.j;}

void Vector4::operator-(Vector4 &a){x-=a.x; y-=a.y; z-=a.z; j-=a.j;}

void Vector4::dehomogenize(){j = 1;}

double Vector4::rowCol(Vector4 &a)
{double ans = x*a.x+y*a.y+z*a.z+j*a.j;
return ans;}