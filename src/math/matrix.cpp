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

#include <lumiererenderer\matrix.h>

namespace LumiereRenderer
{	

	Matrix::Matrix(void)
	{
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
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
   
	Matrix::Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
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

	Matrix::~Matrix()
	{
	}

	float* Matrix::operator[](int i)
	{
	return m[i]; 
	}

	const float* Matrix::operator[](int i) const
	{
	return m[i]; 
	}

	Matrix Matrix::IDENTITY()
	{			
		return Matrix(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	}

	Matrix Matrix::ZEROS()
	{			
		return Matrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	}

	Matrix Matrix::ONES()
	{			
		return Matrix(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	}

	Matrix Matrix::operator *( const Matrix& b ) const
	{
		Matrix res = Matrix();
		for( unsigned int i = 0; i < 4; ++i ){
			for( unsigned int j = 0; j < 4; ++j ){
				for( unsigned int k = 0; k < 4; ++k ){
					res[i][j] += (*this)[i][k] * b[k][j];
				}
			}
		}
		return res;
	}

	Matrix& Matrix::operator *=( const Matrix& b )
	{
		for( unsigned int i = 0; i < 4; ++i ){
			for( unsigned int j = 0; j < 4; ++j ){
				for( unsigned int k = 0; k < 4; ++k ){
					m[i][j] += (*this)[i][k] * b[k][j];
				}
			}
		}

		return *this;
	}

	Point3 Matrix::operator *( const Point3& b ) const
	{
		Point3 c;

		c[0] = m[0][0] * b[0] + m[0][1] * b[1] + m[0][2] * b[2] + m[0][3];
		c[1] = m[1][0] * b[0] + m[1][1] * b[1] + m[1][2] * b[2] + m[1][3];
		c[2] = m[2][0] * b[0] + m[2][1] * b[1] + m[2][2] * b[2] + m[2][3];
		
		return c;
	}

	Vector3 Matrix::operator *( const Vector3& b ) const
	{
		Vector3 c;
		
		c[0] = m[0][0] * b[0] + m[0][1] * b[1] + m[0][2] * b[2];
		c[1] = m[1][0] * b[0] + m[1][1] * b[1] + m[1][2] * b[2];
		c[2] = m[2][0] * b[0] + m[2][1] * b[1] + m[2][2] * b[2];
		
		return c;
	}

	Ray Matrix::operator *( const Ray& b ) const
	{
		Ray c = b;
		
		c.origin[0] = m[0][0] * b.origin[0] + m[0][1] * b.origin[1] + m[0][2] * b.origin[2] + m[0][3];
		c.origin[1] = m[1][0] * b.origin[0] + m[1][1] * b.origin[1] + m[1][2] * b.origin[2] + m[1][3];
		c.origin[2] = m[2][0] * b.origin[0] + m[2][1] * b.origin[1] + m[2][2] * b.origin[2] + m[2][3];

		c.direction[0] = m[0][0] * b.direction[0] + m[0][1] * b.direction[1] + m[0][2] * b.direction[2];
		c.direction[1] = m[1][0] * b.direction[0] + m[1][1] * b.direction[1] + m[1][2] * b.direction[2];
		c.direction[2] = m[2][0] * b.direction[0] + m[2][1] * b.direction[1] + m[2][2] * b.direction[2];
		
		return c;
	}


/*	const Matrix& Matrix::operator *=( const Matrix& rhs ) const
	{
		//*this = *this * rhs;
		return *this;
	}*/

	Matrix& Matrix::operator +=( float s )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				(*this)[i][j] += s;
		return *this;
	}

	Matrix& Matrix::operator -=( float s )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				(*this)[i][j] -= s;
		return *this;
	}

	Matrix& Matrix::operator *=( float s )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				(*this)[i][j] *= s;
		return *this;
	}

	Matrix& Matrix::operator /=( float s )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				(*this)[i][j] /= s;
		return *this;
	}

	bool Matrix::operator ==( const Matrix& rhs )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				if ((*this)[i][j] != rhs[i][j]) return false; 
		return true;
	}

	bool Matrix::operator !=( const Matrix& rhs )
	{
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				if ((*this)[i][j] != rhs[i][j]) return true; 
		return false;
	}

	Matrix operator+( float s, Matrix a )
	{
				Matrix m;
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				m[i][j] = s + a[i][j];
		return m;
	}

	Matrix operator-( float s, Matrix a )
	{
				Matrix m;
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				m[i][j] = s - a[i][j];
		return m;
	}

	Matrix operator*( float s, Matrix a )
	{
				Matrix m;
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				m[i][j] = s * a[i][j];
		return m;
	}

	Matrix operator/( float s, Matrix a )
	{
		Matrix m;
		for( unsigned int i = 0; i < 4; ++i )
			for( unsigned int j = 0; j < 4; ++j )
				m[i][j] = s / a[i][j];
		return m;
	}

	std::ostream& operator<<( std::ostream& os, const Matrix& m )
	{
		return os 
			<< "[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]" << std::endl
			<< "[" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]" << std::endl
			<< "[" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]" << std::endl
			<< "[" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]" << std::endl;
	}
}
