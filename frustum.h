#ifndef FRUSTUM_H
#define FRUSTUM_H
#include "Matrix4.h"
#include "glut.h"
class Frustum
{
protected:
	Matrix4 pPerp;
	
public:
	double *matrix;
	void genMatrix(double, double, double, double);
	void setGL_PROJ();
	Matrix4 getMatrix();
	void frustumGl( double left, double right, double bottom, double top,
                  double znear, double zfar);

	void perSpec(double fovyInDegrees, double aspectRatio,
                      double znear, double zfar);
	void makeFrustum(double fovY, double aspectRatio, double front, double back);

};

#endif
