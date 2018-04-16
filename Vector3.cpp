#include "Vector3.h"


Vector3::Vector3() {x=0.0; y=0.0; z=0.0;};

Vector3::Vector3(double x0,double y0,double z0) {x=x0; y=y0; z=z0;}

void Vector3::set(double x0,double y0,double z0) {x=x0; y=y0; z=z0;}

double Vector3::getX(){return x;}
double Vector3::getY(){return y;}
double Vector3::getZ(){return z;}

void Vector3::setX(double xer){x = xer;}
void Vector3::setY(double yer){y = yer;}
void Vector3::setZ(double zer){z = zer;}


double Vector3::operator[](int index)
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
	default:
		return notFound;
		break;
	}
}	


void Vector3::add(Vector3 &a) {x+=a.x; y+=a.y; z+=a.z;}

void Vector3::add(Vector3 &a,Vector3 &b) {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}

void Vector3::operator+(Vector3 &a){x+=a.x; y+=a.y; z+=a.z;}

void Vector3::subtract(Vector3 &a) {x-=a.x; y-=a.y; z-=a.z;}

void Vector3::subtract(Vector3 &a,Vector3 &b) {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}

void Vector3::operator-(Vector3 &a){x-=a.x; y-=a.y; z-=a.z;}

void Vector3::negate() {x=-x; y=-y; z=-z;}

void Vector3::negate(Vector3 &a) {x=-a.x; y=-a.y; z=-a.z;}

void Vector3::scale(double s) {x*=s; y*=s; z*=s;}

void Vector3::scale(double s,Vector3 &a) {x=s*a.x; y=s*a.y; z=s*a.z;}

double Vector3::dot(Vector3 &a) {return x*a.x+y*a.y+z*a.z;}
void Vector3::printVec3(){cout<<"X: "<<x<<" Y: "<<y<<" Z: "<<z<<endl;}


void Vector3::cross(Vector3 &a,Vector3 &b)
{x=a.y*b.z-a.z*b.y; y=a.z*b.x-a.x*b.z; z=a.x*b.y-a.y*b.x;}

double Vector3::magnitude() {return sqrt(x*x+y*y+z*z);}

void Vector3::normalize() {scale(1.0/magnitude());}