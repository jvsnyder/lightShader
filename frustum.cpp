#include "frustum.h"
#include <cmath>



//frust.genMatrix(1, 100, 1, fov);
const static double PI = 3.1415926;
void Frustum::genMatrix(double near, double far, double aspect, double fov)
{
	pPerp.set(0,0,(1.0/(aspect*tan(fov/2))));
	pPerp.set(1,1,(1.0/tan(fov/2)));
	pPerp.set(2, 2, (near + far)/(near-far));
	pPerp.set(2, 3, (2*near*far)/(near- far));
	pPerp.set(3, 2, -1);


	pPerp.set(1,0, 0);
	pPerp.set(2,0, 0);
	pPerp.set(3,0, 0);

	pPerp.set(0, 1, 0);
	pPerp.set(2, 1, 0);
	pPerp.set(3, 1, 0);

	pPerp.set(0,2, 0);
	pPerp.set(1,2, 0);

	pPerp.set(0,3, 0);
	pPerp.set(1,3, 0);
	pPerp.set(3,3, 0);
}

void Frustum::setGL_PROJ()
{
	glMatrixMode(GL_PROJECTION);

	GLdouble *projectionTranspose = new GLdouble[16];

	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++)
		{
			projectionTranspose[4*i+j] = pPerp.get(j, i);
		}
	}
	 
	glLoadMatrixd(projectionTranspose);
}


Matrix4 Frustum::getMatrix() {
		return pPerp;
	}


void Frustum::perSpec(double fovyInDegrees, double aspectRatio,
                      double znear, double zfar)
{
    double ymax, xmax, ymin,xmin; 
    double temp, temp2, temp3, temp4;
    ymax = znear * tan(fovyInDegrees * PI / 360.0);
    ymin = -ymax;
    xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    frustumGl(-xmax, xmax, -ymax, ymax, znear, zfar);
}

void Frustum::frustumGl(double left, double right, double bottom, double top,
                  double znear, double zfar)
{

	matrix = new double[16];
    double temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}
void Frustum::makeFrustum(double fovY, double aspectRatio, double front, double back)
{
    const double DEG2RAD = 3.14159265 / 180;

    double tangent = tan(fovY/2 * DEG2RAD);   // tangent of half fovY
    double height = front * tangent;          // half height of near plane
    double width = height * aspectRatio;      // half width of near plane

	//cout<<"width: "<<width<<" height: "<<height<<" front: "<<front<<" back: "<<back<<endl;
    // params: left, right, bottom, top, near, far
    glFrustum(-width, width, -height, height, front, back);
}