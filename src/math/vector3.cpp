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

#include <lumiererenderer\vector3.h>
#include <lumiererenderer\point3.h>

namespace LumiereRenderer
{
	Vector3::Vector3() : x(0), y(0), z(0) 
	{
	}
	
	Vector3::Vector3(float x) : x(x), y(x), z(x) 
	{
	}

	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Vector3::~Vector3()
	{
	}
	
	float& Vector3::operator []( const unsigned int i )
	{
		return *(&x + i);
	}
	
	const float& Vector3::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}
	
	Vector3 Vector3::operator+(const Vector3& b) const
	{
		return Vector3(x + b.x, y + b.y, z + b.z);
	}
	
	Point3 Vector3::operator+(const Point3& b) const
	{
		return Point3(x + b.x, y + b.y, z + b.z);
	}

	Vector3 Vector3::operator-(const Vector3& b) const
	{
		return Vector3(x - b.x, y - b.y, z - b.z);
	}

	Vector3	Vector3::operator*( const Vector3& b ) const
	{
		return Vector3(x * b.x, y * b.y, z * b.z);
	}

	Vector3& Vector3::operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	Vector3& Vector3::operator *=( const Vector3& b )
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	}

	Vector3 Vector3::operator+(float s) const
	{
		return Vector3(x + s, y + s, z + s);
	}

	Vector3 Vector3::operator-(float s) const
	{
		return Vector3(x - s, y - s, z - s);
	}

	Vector3 Vector3::operator*(float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	Vector3 Vector3::operator/(float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	Vector3& Vector3::operator+=(float s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	Vector3& Vector3::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	Vector3& Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& Vector3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	Vector3 Vector3::operator -()
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 Vector3::operator -() const
	{
		return Vector3(-x, -y, -z);
	}

	bool Vector3::operator ==( const Vector3& b )
	{
		return (x == b.x && y == b.y && z == b.z);
	}
	
	bool Vector3::operator !=( const Vector3& b )
	{
		return (x != b.x || y != b.y || z != b.z);
	}

	Vector3 operator+(float s, Vector3 a)
	{
		return Vector3(s+a.x, s+a.y, s+a.z);
	}
		
	Vector3 operator-(float s, Vector3 a)
	{
		return Vector3(s-a.x, s-a.y, s-a.z);
	}

	Vector3 operator*(float s, Vector3 a)
	{
		return Vector3(s*a.x, s*a.y, s*a.z);
	}
	
	Vector3 operator/(float s, Vector3 a)
	{
		return Vector3(s/a.x, s/a.y, s/a.z);
	}

	std::ostream& operator<<( std::ostream& os, const Vector3& a )
	{
		return os 
			<< "[" << a[0] << ", " << a[1] << ", " << a[2] << "]" << std::endl;
	}
}