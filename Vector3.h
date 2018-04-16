#ifndef Vector3_H
#define Vector3_H
#include <math.h>
#include <iostream>
using namespace std;
class Vector3
{
public:

double x,y,z;

Vector3();

Vector3(double, double,double);


void set(double, double, double);

void setX(double);
void setY(double);
void setZ(double);

double getX();
double getY();
double getZ();

double operator[](int);



void add(Vector3 &);

void add(Vector3 &,Vector3 &);

void operator+(Vector3 &);

void subtract(Vector3 &);

void subtract(Vector3 &,Vector3 &);

void operator-(Vector3 &);

void negate();

void negate(Vector3 &);

void scale(double);

void scale(double,Vector3 &);

double dot(Vector3 &);

void cross(Vector3 &,Vector3 &);

void printVec3();
double magnitude();

void normalize();



};
#endif