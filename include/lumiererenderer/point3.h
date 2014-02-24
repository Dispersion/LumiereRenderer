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

#pragma once
#include <ostream>

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
		/// Default constructor.
		/// @return [0, 0, 0].
		Point3();
		
		/// This will initialize a point to (x,x,x).
		/// @param x Scalar.
		/// @return [x, x, x].
		Point3( float x );
		
		/// This will initialize a point to (x,y,z).
		/// @param x Scalar.
		/// @param y Scalar.
		/// @param z Scalar.
		/// @return [x, y, z].
		Point3( float x, float y, float z );
		
		/// Default destructor.
		~Point3(void);
		
		/// Get the i'th element of a point.
		/// @param i Index.
		/// @return The i'th element of a point.
		float& operator []( const unsigned int i );
		
		/// Get the i'th element of a const point.
		/// @param i Index.
		/// @return The i'th element of a const point.
		const float& operator []( const unsigned int i ) const;
		
		/// Add a vector B to a point A.  
		/// @param b Vector.
		/// @return [A.x + B.x, A.y + B.y, A.z + B.z].
		Point3 operator +( const Vector3& b ) const;
		
		/// Subtract a vector B from a point A.  
		/// @param b Vector.
		/// @return [A.x - B.x, A.y - B.y, A.z - B.z].
		Point3 operator -( const Vector3& b ) const;
		
		/// Add a point B to a point A, to get the vector from A to B.
		/// @param b Point.
		/// @return [A.x + B.x, A.y + B.y, A.z + B.z].
		Vector3 operator +( const Point3& b ) const;
		
		/// Subtract a point B from a point A, to get the vector from A to B.
		/// @param b Point.
		/// @return [A.x - B.x, A.y - B.y, A.z - B.z].
		Vector3	operator -( const Point3& b ) const;
		
		/// Add a vector B to a point A and save the result in A.
		/// @param b Vector.
		/// @return [A.x + B.x, A.y + B.y, A.x + B.y]. 
		Point3&	operator +=( const Vector3& b );
		
		/// Subtract a vector B from a point A and save the result in A.
		/// @param b Vector.
		/// @return [A.x + B.x, A.y + B.y, A.x + B.y]. 
		Point3&	operator -=( const Vector3& b );
		
		/// Add a scalar s to a point A.  
		/// @param s Scalar.
		/// @return [A.x + s, A.y + s, A.z + s].
		Point3 operator +( float s ) const;
		
		/// Substract a scalar s from a point A.
		/// @param s Scalar.
		/// @return [A.x - s, A.y - s, A.z - s].
		Point3 operator -( float s ) const;
		
		/// Multiply a scalar s to a point A.
		/// @param s Scalar.
		/// @return [A.x * s, A.y * s, A.z * s].
		Point3 operator *( float s ) const;
		
		/// Divide a point A with a scalar s.
		/// @param s Scalar.
		/// @return [A.x / s, A.y / s, A.z / s].
		Point3 operator /( float s ) const;
		
		/// Add a scalar s to a point A and save the result in A.
		/// @param s Scalar.
		/// @return [A.x + s, A.y + s, A.z + s]. 
		Point3& operator +=( float s );
		
		/// Subtract a scalar s from a point A and save the result in A.
		/// @param s Scalar.
		/// @return [A.x - s, A.y - s, A.z - s].
		Point3&	operator -=( float s );
		
		/// Multiply a scalar s to a point A and save the result in A.
		/// @param s Scalar.
		/// @return [A.x * s, A.y * s, A.z * s]. 
		Point3&	operator *=( float s );
		
		/// Divide a vector A with a point s and save the result in A.
		/// @param s Scalar.
		/// @return [A.x / s, A.y / s, A.z / s].
		Point3&	operator /=( float s );
		
		/// Negate a point A.
		/// @return [-A.x, -A.y, -A.z].
		Point3 operator -();

		/// Negate a point A.
		/// @return [-A.x, -A.y, -A.z].
		Point3 operator -() const;
		
		/// Element-wise compare of two points A and B. This will return true if A is equal to B.
		/// @param b Vector.
		/// @return True if (A.x == B.x, A.y == B.y, A.z == B.z).
		bool operator ==( const Point3& b );
		
		/// Element-wise compare of two points A and B. 
		/// @param b Vector.
		/// @return False if (A.x == B.x, A.y == B.y, A.z == B.z)
		bool operator !=( const Point3& b );

		float x, y, z;
	};

	/// Add a scalar s to a point A.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s + A.x, s + A.y, s + A.z].
	Point3 operator+(float s, Point3 a);
	
	/// Substract a point A from a scalar s.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s - A.x, s - A.y, s - A.z].
	Point3 operator-(float s, Point3 a);
	
	/// Multiply a point A to a scalar s.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s * A.x, s * A.y, s * A.z].
	Point3 operator*(float s, Point3 a);
	
	/// Divide a scala s with a point A.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s / A.x, s / A.y, s / A.z].
	Point3 operator/(float s, Point3 a);

	std::ostream& operator<<( std::ostream& os, const Point3& p );
}
