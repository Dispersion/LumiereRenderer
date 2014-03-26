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

#include <lumiererenderer\Point3.h>
#include <lumiererenderer\Vector3.h>

namespace LumiereRenderer
{
	Point3::Point3() : x(0), y(0), z(0)
	{
	}

	Point3::Point3(float x) : x(x), y(x), z(x)
	{
	}

	Point3::Point3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Point3::~Point3(void)
	{
	}

	float& Point3::operator []( const unsigned int i )
	{
		return *(&x + i);
	}

	const float& Point3::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}

	Point3 Point3::operator+(const Vector3& b) const
	{
		return Point3(x + b.x, y + b.y, z + b.z);
	}

	Point3 Point3::operator-(const Vector3& b) const
	{
		return Point3(x - b.x, y - b.y, z - b.z);
	}

	Vector3 Point3::operator+(const Point3& b) const
	{
		return Vector3(x + b.x, y + b.y, z + b.z);
	}

	Vector3 Point3::operator-(const Point3& b) const
	{
		return Vector3(x - b.x, y - b.y, z - b.z);
	}

	Point3& Point3::operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	Point3& Point3::operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
		
	Point3 Point3::operator+(float s) const
	{
		return Point3(x + s, y + s, z + s);
	}

	Point3 Point3::operator-(float s) const
	{
		return Point3(x - s, y - s, z - s);
	}

	Point3 Point3::operator*(float s) const
	{
		return Point3(x * s, y * s, z * s);
	}

	Point3 Point3::operator/(float s) const
	{
		return Point3(x / s, y / s, z / s);
	}

	Point3& Point3::operator+=(float s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	Point3& Point3::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	Point3& Point3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Point3& Point3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	Point3 Point3::operator -()
	{
		return Point3(-x, -y, -z);
	}

	Point3 Point3::operator -() const
	{
		return Point3(-x, -y, -z);
	}

	bool Point3::operator ==( const Point3& b )
	{
		return (x == b.x && y == b.y && z == b.z);
	}

	bool Point3::operator !=( const Point3& b )
	{
		return (x != b.x || y != b.y || z != b.z);
	}

	Point3 operator+(float s, Point3 a)
	{
		return Point3(s+a.x, s+a.y, s+a.z);
	}

	Point3 operator-(float s, Point3 a)
	{
		return Point3(s-a.x, s-a.y, s-a.z);
	}

	Point3 operator*(float s, Point3 a)
	{
		return Point3(s*a.x, s*a.y, s*a.z);
	}

	Point3 operator/(float s, Point3 a)
	{
		return Point3(s/a.x, s/a.y, s/a.z);
	}

	std::ostream& operator<<( std::ostream& os, const Point3& p )
	{
		return os 
			<< "[" << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
	}
}
