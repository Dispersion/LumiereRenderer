////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012, LumiereRenderer
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

#pragma once

////////////////////////////////////////////////////////////////////////////////////
/// 
/// \mainpage LumiereRenderer
/// Lumiere Renderer is an open source rendering framework for renderers based on 
/// ray tracing.
///
////////////////////////////////////////////////////////////////////////////////////

namespace LumiereRenderer
{
	class Vector3;

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Point3
/// @brief A point in 3D coordinates.
///	
////////////////////////////////////////////////////////////////////////////////////

	class Point3
    {
	public:		
		Point3();
		Point3(float x);
		Point3(float x, float y, float z);
		float& operator []( const unsigned int i );
		const float& operator []( const unsigned int i ) const;
		Point3 operator+(const Vector3& b) const;
		Point3 operator-(const Vector3& b) const;
		Vector3 operator-(const Point3& b) const;
		Point3& operator+=(const Vector3& b);
		Point3& operator-=(const Vector3& b);
		Point3 operator+(float s) const;
		Point3 operator-(float s) const;
		Point3 operator*(float s) const;
		Point3 operator/(float s) const;
		Point3& operator+=(float s);
		Point3& operator-=(float s);
		Point3& operator*=(float s);
		Point3& operator/=(float s);
		Point3 operator -();
		bool operator ==( const Point3& b );
		bool operator !=( const Point3& b );

		float x, y, z;
	};

	float dist(Point3 a,Point3 b);
	float distSqr(Point3 a,Point3 b);
	Vector3 lerp(const Vector3& a, const Vector3& b, float w);
	Point3 operator+(float s, Point3 a);
	Point3 operator-(float s, Point3 a);
	Point3 operator*(float s, Point3 a);
	Point3 operator/(float s, Point3 a);

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Vector3
/// @brief A vector in three dimensional space.
///	
////////////////////////////////////////////////////////////////////////////////////

	class Vector3
	{
	public:
		Vector3();
		Vector3(float x);
		Vector3(float x, float y, float z);
		float& operator []( const unsigned int index );
		const float& operator []( const unsigned int index ) const;
		Vector3 operator+(const Vector3& b) const;
		Point3 operator+(const Point3& b) const;
		Vector3 operator-(const Vector3& b) const;		
		Vector3& operator+=(const Vector3& b);
		Vector3& operator-=(const Vector3& b);
		Vector3 operator+(float s) const;
		Vector3 operator-(float s) const;
		Vector3 operator*(float s) const;
		Vector3 operator/(float s) const;
		Vector3& operator+=(float s);
		Vector3& operator-=(float s);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
		Vector3 operator -();
		bool operator ==( const Vector3& b );
		bool operator !=( const Vector3& b );

		float x, y, z;
	};

	float dot(const Vector3& a, const Vector3& b);
	Vector3	cross(const Vector3& a, const Vector3& b);
	float length(const Vector3& a);
	float lengthSqr(const Vector3& a);
	Vector3 normalize(const Vector3& a);
	Vector3 lerp(const Vector3& a, const Vector3& b, float w);
	Vector3 operator+(float s, Vector3 a);
	Vector3 operator-(float s, Vector3 a);
	Vector3 operator*(float s, Vector3 a);
	Vector3 operator/(float s, Vector3 a);

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Ray
/// @brief A ray is a line that goes to infinity starting at the point origin and 
///	going in a certain direction.
///	
////////////////////////////////////////////////////////////////////////////////////

	class Ray
	{
	public:
		Ray();		
		Ray(Point3 origin, Vector3 direction);		

		Point3 origin;
		Vector3 direction;
	};
}
