#ifndef Vector4_H
#define Vector4_H
#include <math.h>

class Vector4
{
public:

double x,y,z,j;

Vector4();

Vector4(double, double, double, double);

void set(double, double, double, double);

double getX();
double getY();
double getZ();
double getJ();

double Vector4::operator[](int index);

void add(Vector4 &);

void add(Vector4 &,Vector4 &);

void operator+(Vector4 &);

void subtract(Vector4 &);

void subtract(Vector4 &,Vector4 &);

void operator-(Vector4 &);

void dehomogenize();

double rowCol(Vector4 &);



};
#endif