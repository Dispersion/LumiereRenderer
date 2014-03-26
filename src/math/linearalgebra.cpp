////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014, LumiereRenderer
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of LumiererRenderer nor the
//      names of its contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
////////////////////////////////////////////////////////////////////////////////////

#include <lumiererenderer\LinearAlgebra.h>

namespace LumiereRenderer
{

	float Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}


	float Dot(const Point3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}


	float Dot(const Vector3& a, const Point3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}


	Vector3	Cross(const Point3& a, const Point3& b)
	{
		return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);			
	}


	Vector3	Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);			
	}


	Matrix Transpose(const Matrix& m)
	{
		Matrix t;
		for( unsigned int i = 0; i < 4; ++i ) 
		{
			for( unsigned int j = 0; j < 4; ++j) 
			{
				t[j][i] = m[i][j];
			}
		}
		return t;
	}

	float Det( const Matrix& m )
	{
		return 
			m[0][0]*(m[1][1]*(m[2][2]*m[3][3] - m[2][3]*m[3][2]) + m[1][2]*(m[2][3]*m[3][1] - m[2][1]*m[3][3]) + m[1][3]*(m[2][1]*m[3][2] - m[2][2]*m[3][1])) +
			m[0][1]*(m[1][0]*(m[2][3]*m[3][2] - m[2][2]*m[3][3]) + m[1][2]*(m[2][0]*m[3][3] - m[2][3]*m[3][0]) + m[1][3]*(m[2][2]*m[3][0] - m[2][0]*m[3][2])) +
			m[0][2]*(m[1][0]*(m[2][1]*m[3][3] - m[2][3]*m[3][1]) + m[1][1]*(m[2][3]*m[3][0] - m[2][0]*m[3][3]) + m[1][3]*(m[2][0]*m[3][1] - m[2][1]*m[3][0])) + 
			m[0][3]*(m[1][0]*(m[2][2]*m[3][1] - m[2][1]*m[3][2]) + m[1][1]*(m[2][0]*m[3][2] - m[2][2]*m[3][0]) + m[1][2]*(m[2][1]*m[3][0] - m[2][0]*m[3][1]));
	}

	Matrix Invert(const Matrix& m)
	{
		float determinant = Det(m);
		if (determinant == 0)
			throw std::exception("Singular matrix");

		float a = m[2][2]*m[3][3];
		float b = m[2][3]*m[3][2];
		float c = m[2][3]*m[3][1];
		float d = m[2][1]*m[3][3];
		float e = m[2][1]*m[3][2];
		float f = m[2][2]*m[3][1];

		return (1.0f/determinant) * Matrix(	
			m[1][1]*(a - b) + m[1][2]*(c - d) + m[1][3]*(e - f),
			m[0][1]*(b - a) + m[0][2]*(d - c) + m[0][3]*(f - e),
			m[0][1]*(m[1][2]*m[3][3] - m[1][3]*m[3][2]) + m[0][2]*(m[1][3]*m[3][1] - m[1][1]*m[3][3]) + m[0][3]*(m[1][1]*m[3][2] - m[1][2]*m[3][1]),
			m[0][1]*(m[1][3]*m[2][2] - m[1][2]*m[2][3]) + m[0][2]*(m[1][1]*m[2][3] - m[1][3]*m[2][1]) + m[0][3]*(m[1][2]*m[2][1] - m[1][1]*m[2][2]),
			m[1][0]*(b - a) + m[1][2]*(m[2][0]*m[3][3] - m[2][3]*m[3][0]) + m[1][3]*(m[2][2]*m[3][0] - m[2][0]*m[3][2]),
			m[0][0]*(a - b) + m[0][2]*(m[2][3]*m[3][0] - m[2][0]*m[3][3]) + m[0][3]*(m[2][0]*m[3][2] - m[2][2]*m[3][0]),
			m[0][0]*(m[1][3]*m[3][2] - m[1][2]*m[3][3]) + m[0][2]*(m[1][0]*m[3][3] - m[1][3]*m[3][0]) + m[0][3]*(m[1][2]*m[3][0] - m[1][0]*m[3][2]),
			m[0][0]*(m[1][2]*m[2][3] - m[1][3]*m[2][2]) + m[0][2]*(m[1][3]*m[2][0] - m[1][0]*m[2][3]) + m[0][3]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]),
			m[1][0]*(d - c) + m[1][1]*(m[2][3]*m[3][0] - m[2][0]*m[3][3]) + m[1][3]*(m[2][0]*m[3][1] - m[2][1]*m[3][0]),
			m[0][0]*(c - d) + m[0][1]*(m[2][0]*m[3][3] - m[2][3]*m[3][0]) + m[0][3]*(m[2][1]*m[3][0] - m[2][0]*m[3][1]),
			m[0][0]*(m[1][1]*m[3][3] - m[1][3]*m[3][1]) + m[0][1]*(m[1][3]*m[3][0] - m[1][0]*m[3][3]) + m[0][3]*(m[1][0]*m[3][1] - m[1][1]*m[3][0]),
			m[0][0]*(m[1][3]*m[2][1] - m[1][1]*m[2][3]) + m[0][1]*(m[1][0]*m[2][3] - m[1][3]*m[2][0]) + m[0][3]*(m[1][1]*m[2][0] - m[1][0]*m[2][1]),
			m[1][0]*(f - e) + m[1][1]*(m[2][0]*m[3][2] - m[2][2]*m[3][0]) + m[1][2]*(m[2][1]*m[3][0] - m[2][0]*m[3][1]),
			m[0][0]*(e - f) + m[0][1]*(m[2][2]*m[3][0] - m[2][0]*m[3][2]) + m[0][2]*(m[2][0]*m[3][1] - m[2][1]*m[3][0]),
			m[0][0]*(m[1][2]*m[3][1] - m[1][1]*m[3][2]) + m[0][1]*(m[1][0]*m[3][2] - m[1][2]*m[3][0]) + m[0][2]*(m[1][1]*m[3][0] - m[1][0]*m[3][1]),
			m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) + m[0][1]*(m[1][2]*m[2][0] - m[1][0]*m[2][2]) + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]));	
	}

	Matrix Translate(float x, float y, float z)
	{
		Matrix m = Matrix::IDENTITY();
		m[0][3] = x;
		m[1][3] = y;
		m[2][3] = z;
		return m;
	}

	Matrix Translate(Vector3 vector)
	{
		Matrix m = Matrix::IDENTITY();
		m[0][3] = vector.x;
		m[1][3] = vector.y;
		m[2][3] = vector.z;
		return m;
	}

	/*Matrix Rotate(float angle, Vector3 vector)
	{
	}

	Matrix Rotate(float angle, float x, float y, float z)
	{
	}*/

	Matrix Scale(float x, float y, float z)
	{
		Matrix m = Matrix::IDENTITY();
		m[0][0] = x;
		m[1][1] = y;
		m[2][2] = z;
		return m;
	}

	Matrix Scale(Vector3 vector)
	{
		Matrix m = Matrix::IDENTITY();
		m[0][0] = vector.x;
		m[1][1] = vector.y;
		m[2][2] = vector.z;
		return m;
	}
}
