#include <math.h>


#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 
Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

void Matrix4::set(int row, int col, double value)
{
	m[row][col] = value;
}

double Matrix4::get(int row, int col)
{
	return m[row][col];
}


//mult was screwed up thanks jorgen...
void Matrix4::mult(Matrix4 a)
{

	Matrix4 temp;
	for(int row = 0; row<4; row++)
	{
		for(int col = 0; col<4; col++)
		{
			temp.set(row, col, m[row][col]);
		}
	}

	Vector4 row0(temp.m[0][0], temp.m[0][1],temp.m[0][2], temp.m[0][3]);
	Vector4 row1(temp.m[1][0], temp.m[1][1],temp.m[1][2], temp.m[1][3]);
	Vector4 row2(temp.m[2][0], temp.m[2][1],temp.m[2][2], temp.m[2][3]);
	Vector4 row3(temp.m[3][0], temp.m[3][1],temp.m[3][2], temp.m[3][3]);

	Vector4 col0(a.m[0][0], a.m[1][0],a.m[2][0],a.m[3][0]);
	Vector4 col1(a.m[0][1], a.m[1][1],a.m[2][1],a.m[3][1]);
	Vector4 col2(a.m[0][2], a.m[1][2],a.m[2][2],a.m[3][2]);
	Vector4 col3(a.m[0][3], a.m[1][3],a.m[2][3],a.m[3][3]);
	


	m[0][0] = row0.rowCol(col0);
	m[0][1] = row0.rowCol(col1);
	m[0][2] = row0.rowCol(col2);
	m[0][3] = row0.rowCol(col3);

	m[1][0] = row1.rowCol(col0);
	m[1][1] = row1.rowCol(col1);
	m[1][2] = row1.rowCol(col2);
	m[1][3] = row1.rowCol(col3);

	m[2][0] = row2.rowCol(col0);
	m[2][1] = row2.rowCol(col1);
	m[2][2] = row2.rowCol(col2);
	m[2][3] = row2.rowCol(col3);

	m[3][0] = row3.rowCol(col0);
	m[3][1] = row3.rowCol(col1);
	m[3][2] = row3.rowCol(col2);
	m[3][3] = row3.rowCol(col3);



	


	
}

//TODO mult matrix * vec4 and vec3
void Matrix4::rotateXY(double angleX, double angleY)
{
					 m[0][0] = cos(angleY);
	m[0][1] = 0;				 
					 m[0][2] = sin(angleY);
	m[0][3] = 0;				 
	m[1][0] = 0;				 
	m[1][1] = cos(angleX);		 
	m[1][2] = -sin(angleX);		 
	m[1][3] = 0;				 
					 m[2][0] = -sin(angleY);
	m[2][1] = sin(angleX);		 
	m[2][2] = cos(angleX);		 
	m[2][3] = 0;				 
	m[3][0] = 0;				 
	m[3][1] = 0;				 
	m[3][2] = 0;				 
	m[3][3] = 1;				 
}





// angle in radians
void Matrix4::rotateX(double angle)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateY(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateZ(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

//arbitrary unit axis

void Matrix4::arbitrary(Vector3 axis, double th)
{
	
	/*
	m[0][0] = uniVec.getX()*uniVec.getX()*(1-cos(angle))+cos(angle);
	m[0][1] = uniVec[0]*uniVec[1]*(1-cos(angle)) - uniVec[2]*sin(angle);
	m[0][2] = uniVec[0]*uniVec[2]*(1-cos(angle)) + uniVec[1]*sin(angle);
	m[0][3] = 0;
	m[1][0] = uniVec[0]*uniVec[1]*(1-cos(angle)) + uniVec[2]*sin(angle);
	m[1][1] = uniVec[1]*uniVec[1]*(1-cos(angle)) + cos(angle);
	m[1][2] = uniVec[1]*uniVec[2]*(1-cos(angle)) - uniVec[0]*sin(angle);
	m[1][3] = 0;
	m[2][0] = uniVec[0]*uniVec[2]*(1-cos(angle)) - uniVec[1]*sin(angle);
	m[2][1] = uniVec[1]*uniVec[2]*(1-cos(angle)) + uniVec[0]*sin(angle);
	m[2][2] = uniVec[2]*uniVec[2]*(1-cos(angle)) + cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	*/
	axis.normalize();
		
		double X=axis[0];
		double Y=axis[1];
		double Z=axis[2];
		
		double COS = cos(th);
		double SIN = sin(th);
		
		// First row
		m[0][0] = 1+(1-COS)*(X*X-1);
		m[0][1] = -Z*SIN+(1-COS)*X*Y;
		m[0][2] = Y*SIN+(1-COS)*X*Z;
		m[0][3] = 0;
		
		//nd row
		m[1][0] = Z*SIN+(1-COS)*Y*X;
		m[1][1] = 1+(1-COS)*(Y*Y-1);
		m[1][2] = -X*SIN+(1-COS)*Y*Z;
		m[1][3] = 0;
		//d row
		m[2][0] = -Y*SIN+(1-COS)*Z*X;
		m[2][1] = X*SIN+(1-COS)*Z*Y;
		m[2][2] = 1+(1-COS)*(Z-1);
		m[2][3] = 0;

		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;
		



}

//non-uniform scaling matrix
void Matrix4::scale(double x, double y, double z)
{
	m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

}


Matrix4 Matrix4::calcInverse(){

double inv[16], mat[16], det;
		
		for (int i=0; i<4; i++) {
			mat[i] = m[i][0];
		}
		for (int i=0; i<4; i++) {
			mat[i+4] = m[i][1];
		}
		for (int i=0; i<4; i++) {
			mat[i+8] = m[i][2];
		}
		for (int i=0; i<4; i++) {
			mat[i+12] = m[i][3];
		}
		/*
		cout << "MAT IS NOW" << endl;
		for (int i=0; i<16; i++) {
			cout << mat[i] << " ";
		}
		cout << endl;
		*/

                inv[0] =   mat[5]*mat[10]*mat[15] - mat[5]*mat[11]*mat[14] - mat[9]*mat[6]*mat[15]
                        + mat[9]*mat[7]*mat[14] + mat[13]*mat[6]*mat[11] - mat[13]*mat[7]*mat[10];
                inv[4] =  -mat[4]*mat[10]*mat[15] + mat[4]*mat[11]*mat[14] + mat[8]*mat[6]*mat[15]
                        - mat[8]*mat[7]*mat[14] - mat[12]*mat[6]*mat[11] + mat[12]*mat[7]*mat[10];
                inv[8] =   mat[4]*mat[9]*mat[15] - mat[4]*mat[11]*mat[13] - mat[8]*mat[5]*mat[15]
                        + mat[8]*mat[7]*mat[13] + mat[12]*mat[5]*mat[11] - mat[12]*mat[7]*mat[9];
                inv[12] = -mat[4]*mat[9]*mat[14] + mat[4]*mat[10]*mat[13] + mat[8]*mat[5]*mat[14]
                        - mat[8]*mat[6]*mat[13] - mat[12]*mat[5]*mat[10] + mat[12]*mat[6]*mat[9];
                inv[1] =  -mat[1]*mat[10]*mat[15] + mat[1]*mat[11]*mat[14] + mat[9]*mat[2]*mat[15]
                        - mat[9]*mat[3]*mat[14] - mat[13]*mat[2]*mat[11] + mat[13]*mat[3]*mat[10];
                inv[5] =   mat[0]*mat[10]*mat[15] - mat[0]*mat[11]*mat[14] - mat[8]*mat[2]*mat[15]
                        + mat[8]*mat[3]*mat[14] + mat[12]*mat[2]*mat[11] - mat[12]*mat[3]*mat[10];
                inv[9] =  -mat[0]*mat[9]*mat[15] + mat[0]*mat[11]*mat[13] + mat[8]*mat[1]*mat[15]
                        - mat[8]*mat[3]*mat[13] - mat[12]*mat[1]*mat[11] + mat[12]*mat[3]*mat[9];
                inv[13] =  mat[0]*mat[9]*mat[14] - mat[0]*mat[10]*mat[13] - mat[8]*mat[1]*mat[14]
                        + mat[8]*mat[2]*mat[13] + mat[12]*mat[1]*mat[10] - mat[12]*mat[2]*mat[9];
                inv[2] =   mat[1]*mat[6]*mat[15] - mat[1]*mat[7]*mat[14] - mat[5]*mat[2]*mat[15]
                        + mat[5]*mat[3]*mat[14] + mat[13]*mat[2]*mat[7] - mat[13]*mat[3]*mat[6];
                inv[6] =  -mat[0]*mat[6]*mat[15] + mat[0]*mat[7]*mat[14] + mat[4]*mat[2]*mat[15]
                        - mat[4]*mat[3]*mat[14] - mat[12]*mat[2]*mat[7] + mat[12]*mat[3]*mat[6];
                inv[10] =  mat[0]*mat[5]*mat[15] - mat[0]*mat[7]*mat[13] - mat[4]*mat[1]*mat[15]
                        + mat[4]*mat[3]*mat[13] + mat[12]*mat[1]*mat[7] - mat[12]*mat[3]*mat[5];
                inv[14] = -mat[0]*mat[5]*mat[14] + mat[0]*mat[6]*mat[13] + mat[4]*mat[1]*mat[14]
                        - mat[4]*mat[2]*mat[13] - mat[12]*mat[1]*mat[6] + mat[12]*mat[2]*mat[5];
                inv[3] =  -mat[1]*mat[6]*mat[11] + mat[1]*mat[7]*mat[10] + mat[5]*mat[2]*mat[11]
                        - mat[5]*mat[3]*mat[10] - mat[9]*mat[2]*mat[7] + mat[9]*mat[3]*mat[6];
                inv[7] =   mat[0]*mat[6]*mat[11] - mat[0]*mat[7]*mat[10] - mat[4]*mat[2]*mat[11]
                        + mat[4]*mat[3]*mat[10] + mat[8]*mat[2]*mat[7] - mat[8]*mat[3]*mat[6];
                inv[11] = -mat[0]*mat[5]*mat[11] + mat[0]*mat[7]*mat[9] + mat[4]*mat[1]*mat[11]
                        - mat[4]*mat[3]*mat[9] - mat[8]*mat[1]*mat[7] + mat[8]*mat[3]*mat[5];
                inv[15] =  mat[0]*mat[5]*mat[10] - mat[0]*mat[6]*mat[9] - mat[4]*mat[1]*mat[10]
                        + mat[4]*mat[2]*mat[9] + mat[8]*mat[1]*mat[6] - mat[8]*mat[2]*mat[5];



				Matrix4 result; 
				result.identity();

                det = mat[0]*inv[0] + mat[1]*inv[4] + mat[2]*inv[8] + mat[3]*inv[12];
                if (det == 0)
                        return result;

                det = 1.0 / det;
		/*	cout << "INV IS NOW" << endl;
		for (int i=0; i<16; i++) {
			cout << inv[i] << " ";
		}
		cout << endl;
		*/

                
		for (int i=0; i<4; i++) {
			result.m[i][0] = inv[i];
                }

                for (int i=0; i<4; i++) {
			result.m[i][1] = inv[i+4];
                }

                for (int i=0; i<4; i++) {
			result.m[i][2] = inv[i+8];
		}

		for (int i=0; i<4; i++) {
			result.m[i][3] = inv[i+12];
                }

		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				result.m[i][j] *= det;
			}
		}
		return result;
        }


void Matrix4::printMatrix()
{
	for(int x = 0; x<4; x++)
	{
		for(int y = 0; y<4; y++)
		{
			cout<<m[x][y]<<" ";
			if(y == 3)
				cout<<endl;
		}
	}
}

