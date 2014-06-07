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

#include <lumiererenderer\Vector2.h>

namespace LumiereRenderer
{
	Vector2::Vector2() : x(0), y(0)
	{
	}
	
	Vector2::Vector2(float x) : x(x), y(x)
	{
	}

	Vector2::Vector2(float x, float y) : x(x), y(y)
	{
	}

	Vector2::~Vector2()
	{
	}
	
	float& Vector2::operator []( const unsigned int i )
	{
		return *(&x + i);
	}
	
	const float& Vector2::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}
	
	Vector2 Vector2::operator+(const Vector2& b) const
	{
		return Vector2(x + b.x, y + b.y);
	}
	
	Vector2 Vector2::operator-(const Vector2& b) const
	{
		return Vector2(x - b.x, y - b.y);
	}

	Vector2	Vector2::operator*( const Vector2& b ) const
	{
		return Vector2(x * b.x, y * b.y);
	}

	Vector2& Vector2::operator+=(const Vector2& b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& b)
	{
		x -= b.x;
		y -= b.y;
		return *this;
	}

	Vector2& Vector2::operator *=( const Vector2& b )
	{
		x *= b.x;
		y *= b.y;
		return *this;
	}

	Vector2 Vector2::operator+(float s) const
	{
		return Vector2(x + s, y + s);
	}

	Vector2 Vector2::operator-(float s) const
	{
		return Vector2(x - s, y - s);
	}

	Vector2 Vector2::operator*(float s) const
	{
		return Vector2(x * s, y * s);
	}

	Vector2 Vector2::operator/(float s) const
	{
		return Vector2(x / s, y / s);
	}

	Vector2& Vector2::operator+=(float s)
	{
		x += s;
		y += s;
		return *this;
	}

	Vector2& Vector2::operator-=(float s)
	{
		x -= s;
		y -= s;
		return *this;
	}

	Vector2& Vector2::operator*=(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2& Vector2::operator/=(float s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	Vector2 Vector2::operator -()
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator -() const
	{
		return Vector2(-x, -y);
	}

	bool Vector2::operator ==( const Vector2& b )
	{
		return (x == b.x && y == b.y);
	}
	
	bool Vector2::operator !=( const Vector2& b )
	{
		return (x != b.x || y != b.y);
	}

	Vector2 operator+(float s, Vector2 a)
	{
		return Vector2(s+a.x, s+a.y);
	}
		
	Vector2 operator-(float s, Vector2 a)
	{
		return Vector2(s-a.x, s-a.y);
	}

	Vector2 operator*(float s, Vector2 a)
	{
		return Vector2(s*a.x, s*a.y);
	}
	
	Vector2 operator/(float s, Vector2 a)
	{
		return Vector2(s/a.x, s/a.y);
	}
}
