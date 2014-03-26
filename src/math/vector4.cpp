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

#include <lumiererenderer\Vector4.h>

namespace LumiereRenderer
{
	Vector4::Vector4(void) : x(0), y(0), z(0), w(0)
	{
	}

	Vector4::Vector4(float x) : x(x), y(x), z(x), w(0)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{
	}

	Vector4::~Vector4(void)
	{
	}


	float& Vector4::operator []( const unsigned int i )
	{
		return *(&x + i);
	}

	const float& Vector4::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}

	Vector4 Vector4::operator+(const Vector4& b) const
	{
		return Vector4(x + b.x, y + b.y, z + b.z, w + b.w);
	}

	/*Point4 Vector4::operator+(const Point4& b) const
	{
		return Point4(x + b.x, y + b.y, z + b.z, w + b.w);
	}*/

	Vector4 Vector4::operator-(const Vector4& b) const
	{
		return Vector4(x - b.x, y - b.y, z - b.z, w - b.w);
	}

	Vector4& Vector4::operator+=(const Vector4& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return *this;
	}

	Vector4 Vector4::operator+(float s) const
	{
		return Vector4(x + s, y + s, z + s, w + s);
	}

	Vector4 Vector4::operator-(float s) const
	{
		return Vector4(x - s, y - s, z - s, w - s);
	}

	Vector4 Vector4::operator*(float s) const
	{
		return Vector4(x * s, y * s, z * s, w * s);
	}

	Vector4 Vector4::operator/(float s) const
	{
		return Vector4(x / s, y / s, z / s, w/ s);
	}
 
	Vector4& Vector4::operator+=(float s)
	{
		x += s;
		y += s;
		z += s;
		w += s;
		return *this;
	}

	Vector4& Vector4::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		return *this;
	}

	Vector4& Vector4::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	Vector4& Vector4::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	Vector4 Vector4::operator -()
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 Vector4::operator -() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	bool Vector4::operator ==( const Vector4& b )
	{
		return (x == b.x && y == b.y && z == b.z && w == b.w);
	}

	bool Vector4::operator !=( const Vector4& b )
	{
		return (x != b.x || y != b.y || z != b.z || w != b.w);
	}

	Vector4 operator+(float s, Vector4 a)
	{
		return Vector4(s+a.x, s+a.y, s+a.z, s+a.w);
	}
	
	Vector4 operator-(float s, Vector4 a)
	{
		return Vector4(s-a.x, s-a.y, s-a.z, s-a.w);
	}

	Vector4 operator*(float s, Vector4 a)
	{
		return Vector4(s*a.x, s*a.y, s*a.z, s*a.w);
	}

	Vector4 operator/(float s, Vector4 a)
	{
		return Vector4(s/a.x, s/a.y, s/a.z, s/a.w);
	}

	std::ostream& operator<<( std::ostream& os, const Vector4& a )
	{
		return os 
			<< "[" << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << "]" << std::endl;
	}
}