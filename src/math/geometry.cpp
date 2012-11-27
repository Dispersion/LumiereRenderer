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

#include "geometry.h"
#include <ostream>

namespace LumiereRenderer
{

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Point3
/// @brief A point in 3D coordinates.
///	
////////////////////////////////////////////////////////////////////////////////////

	/// Default constructor.
	/// @return [0, 0, 0].
	Point3::Point3() : x(0), y(0), z(0)
	{
	}

	/// This will initialize a point to (x,x,x);
	/// @param x Scalar.
	/// @return [x, x, x].
	Point3::Point3(float x) : x(x), y(x), z(x)
	{
	}

	/// This will initialize a point to (x,y,z);
	/// @param x Scalar.
	/// @param y Scalar.
	/// @param z Scalar.
	/// @return [x, y, z].
	Point3::Point3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	/// Get the i'th element of a point.
	/// @param i Index.
	/// @return The i'th element of a point.
	float& Point3::operator []( const unsigned int i )
	{
		return *(&x + i);
	}

	/// Get the i'th element of a const point.
	/// @param i Index.
	/// @return The i'th element of a const point.
	const float& Point3::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}

	/// Add a vector B to a point A.  
	/// @param b Vector.
	/// @return [A.x + B.x, A.y + B.y, A.z + B.z].
	Point3 Point3::operator+(const Vector3& b) const
	{
		return Point3(x + b.x, y + b.y, z + b.z);
	}
		
	/// Subtract a vector B from a point A.  
	/// @param b Vector.
	/// @return [A.x - B.x, A.y - B.y, A.z - B.z].
	Point3 Point3::operator-(const Vector3& b) const
	{
		return Point3(x - b.x, y - b.y, z - b.z);
	}

	/// Subtract a point B from a point A, to get the vector from A to B.
	/// @param b Point.
	/// @return [A.x - B.x, A.y - B.y, A.z - B.z].
	Vector3 Point3::operator-(const Point3& b) const
	{
		return Vector3(x - b.x, y - b.y, z - b.z);
	}

	/// Add a vector B to a point A and save the result in A.
	/// @param b Vector.
	/// @return [A.x + B.x, A.y + B.y, A.x + B.y]. 
	Point3& Point3::operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	/// Subtract a vector B from a point A and save the result in A.
	/// @param b Vector.
	/// @return [A.x + B.x, A.y + B.y, A.x + B.y]. 
	Point3& Point3::operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
		
	/// Add a scalar s to a point A.  
	/// @param s Scalar.
	/// @return [A.x + s, A.y + s, A.z + s].
	Point3 Point3::operator+(float s) const
	{
		return Point3(x + s, y + s, z + s);
	}
		
	/// Substract a scalar s from a point A.
	/// @param s Scalar.
	/// @return [A.x - s, A.y - s, A.z - s].
	Point3 Point3::operator-(float s) const
	{
		return Point3(x - s, y - s, z - s);
	}

	/// Multiply a scalar s to a point A.
	/// @param s Scalar.
	/// @return [A.x * s, A.y * s, A.z * s].
	Point3 Point3::operator*(float s) const
	{
		return Point3(x * s, y * s, z * s);
	}
		
	/// Divide a point A with a scalar s.
	/// @param s Scalar.
	/// @return [A.x / s, A.y / s, A.z / s].
	Point3 Point3::operator/(float s) const
	{
		return Point3(x / s, y / s, z / s);
	}

	/// Add a scalar s to a point A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x + s, A.y + s, A.z + s]. 
	Point3& Point3::operator+=(float s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	/// Subtract a scalar s from a point A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x - s, A.y - s, A.z - s].
	Point3& Point3::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	/// Multiply a scalar s to a point A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x * s, A.y * s, A.z * s]. 
	Point3& Point3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/// Divide a vector A with a point s and save the result in A.
	/// @param s Scalar.
	/// @return [A.x / s, A.y / s, A.z / s].
	Point3& Point3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	/// Negate a point A.
	/// @return [-A.x, -A.y, -A.z].
	Point3 Point3::operator -()
	{
		return Point3(-x, -y, -z);
	}

	/// Element-wise compare of two points A and B. This will return true if A is equal to B.
	/// @param b Vector.
	/// @return True if (A.x == B.x, A.y == B.y, A.z == B.z).
	bool Point3::operator ==( const Point3& b )
	{
		return (x == b.x && y == b.y && z == b.z);
	}

	/// Element-wise compare of two points A and B. 
	/// @param b Vector.
	/// @return False if (A.x == B.x, A.y == B.y, A.z == B.z)
	bool Point3::operator !=( const Point3& b )
	{
		return (x != b.x || y != b.y || z != b.z);
	}

	/// The distance from a point A to a point B.
	/// @param a Point.
	/// @param b Point.
	/// @return The distance.
	float dist(Point3 a, Point3 b)
	{
		return length(b-a);
	}

	/// The square of the distance from a point A to a point B.
	/// @param a Point.
	/// @param b Point.
	/// @return The square of the distance.
	float distSqr(Point3 a, Point3 b)
	{
		return lengthSqr(b-a);
	}

	/// Linear interpolation between two points.
	/// @param a Point.
	/// @param b Point.
	/// @param w Weight.
	/// @return lerp returns a when w is zero and b when w is one.
	Vector3 lerp(const Vector3& a, const Vector3& b, float w)
	{
		return a + (b - a) * w;
	}
	
	/// Add a scalar s to a point A.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s + A.x, s + A.y, s + A.z].
	Point3 operator+(float s, Point3 a)
	{
		return Point3(s+a.x, s+a.y, s+a.z);
	}
	
	/// Substract a point A from a scalar s.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s - A.x, s - A.y, s - A.z].
	Point3 operator-(float s, Point3 a)
	{
		return Point3(s-a.x, s-a.y, s-a.z);
	}

	/// Multiply a point A to a scalar s.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s * A.x, s * A.y, s * A.z].
	Point3 operator*(float s, Point3 a)
	{
		return Point3(s*a.x, s*a.y, s*a.z);
	}

	/// Divide a scala s with a point A.
	/// @param s Scalar.
	/// @param a Point.
	/// @return [s / A.x, s / A.y, s / A.z].
	Point3 operator/(float s, Point3 a)
	{
		return Point3(s/a.x, s/a.y, s/a.z);
	}

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Vector3
/// @brief A vector in three dimensional space.
///	
////////////////////////////////////////////////////////////////////////////////////


	/// Default constructor.
	/// @return [0, 0, 0].
	Vector3::Vector3() : x(0), y(0), z(0) 
	{
	}

	/// This will initialize a vector to (x, x, x).
	/// @param x Scalar.
	/// @return [x, x, x].
	Vector3::Vector3(float x) : x(x), y(x), z(x) 
	{
	}

	/// This will initialize a vector to (x, y, z).
	/// @param x Scalar.
	/// @param y Scalar.
	/// @param z Scalar.
	/// @return [x, y, z].
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	/// Get an element from a vector.
	/// @param i Index.
	/// @return The i'th element of a vector.
	float& Vector3::operator []( const unsigned int i )
	{
		return *(&x + i);
	}

	/// Get an element from a const vector.
	/// @param i Index.
	/// @return The i'th element of a const vector.
	const float& Vector3::operator []( const unsigned int i ) const
	{
		return *(&x + i);
	}

	/// Add two vectors A and B. 
	/// @param b Vector.
	/// @return [A.x + B.x, A.y + B.y, A.z + B.z].
	Vector3 Vector3::operator+(const Vector3& b) const
	{
		return Vector3(x + b.x, y + b.y, z + b.z);
	}

	/// Add a vector A to a point B. 
	/// @param b Point.
	/// @return [A.x + B.x, A.y + B.y, A.z + B.z].
	Point3 Vector3::operator+(const Point3& b) const
	{
		return Point3(x + b.x, y + b.y, z + b.z);
	}

	/// Subtract two vectors A and B. 
	/// @param b Vector.
	/// @return [A.x - B.x, A.y - B.y, A.z - B.z].
	Vector3 Vector3::operator-(const Vector3& b) const
	{
		return Vector3(x - b.x, y - b.y, z - b.z);
	}

	/// Add two vectors A and B and save the result in A.
	/// @param b Vector.
	/// @return [A.x + B.x, A.y + B.y, A.z + B.z]. 
	Vector3& Vector3::operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	/// Subtract two vectors A and B and save the result in A.
	/// @param b Vector.
	/// @return [A.x - B.x, A.y - B.y, A.z - B.z]. 
	Vector3& Vector3::operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	/// Add a scalar s to a vector A.  
	/// @param s Scalar.
	/// @return [A.x + s, A.y + s, A.z + s].
	Vector3 Vector3::operator+(float s) const
	{
		return Vector3(x + s, y + s, z + s);
	}

	/// Substract a scalar s from a vector A.
	/// @param s Scalar.
	/// @return [A.x - s, A.y - s, A.z - s].
	Vector3 Vector3::operator-(float s) const
	{
		return Vector3(x - s, y - s, z - s);
	}

	/// Multiply a scalar s to a vector A.
	/// @param s Scalar.
	/// @return [A.x * s, A.y * s, A.z * s].
	Vector3 Vector3::operator*(float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	/// Divide a vector A with a scalar s.
	/// @param s Scalar.
	/// @return [A.x / s, A.y / s, A.z / s].
	Vector3 Vector3::operator/(float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	/// Add a scalar s to a vector A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x + s, A.y + s, A.z + s]. 
	Vector3& Vector3::operator+=(float s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	/// Subtract a scalar s from a vector A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x - s, A.y - s, A.z - s].
	Vector3& Vector3::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	/// Multiply a scalar s to a vector A and save the result in A.
	/// @param s Scalar.
	/// @return [A.x * s, A.y * s, A.z * s]. 
	Vector3& Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/// Divide a vector A with a scalar s and save the result in A.
	/// @param s Scalar.
	/// @return [A.x / s, A.y / s, A.z / s].
	Vector3& Vector3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	/// Negate a vector A.
	/// @return [-A.x, -A.y, -A.z].
	Vector3 Vector3::operator -()
	{
		return Vector3(-x, -y, -z);
	}

	/// Element-wise compare of two vectors A and B. 
	/// @param b Vector.
	/// @return True if (A.x == B.x, A.y == B.y, A.z == B.z).
	bool Vector3::operator ==( const Vector3& b )
	{
		return (x == b.x && y == b.y && z == b.z);
	}

	/// Element-wise compare of two vectors A and B. 
	/// @param b Vector.
	/// @return False if (A.x == B.x, A.y == B.y, A.z == B.z)
	bool Vector3::operator !=( const Vector3& b )
	{
		return (x != b.x || y != b.y || z != b.z);
	}

	/// The dot product takes two normalized vectors A and B, and returns cosinus to the angle
	/// between A and B.
	/// @param a Vector.
	/// @param b Vector.
	/// @return Cosinus to the angle between A and B.
	float dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// The cross product takes two vectors A and B, where A != B. It returns a vector C,
	/// which is orthogonal to the plane spanned by A and B.
	/// @param a Vector.
	/// @param b Vector.
	/// @return A vector orthogonal to a and b.
	Vector3	cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);			
	}

	///The length of the vector.
	/// @param a Vector.
	/// @return The length of the vector.
	float length(const Vector3& a)
	{
		return std::sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}

	///If you only want to find out if a vector is longer than another vector,
	///it is cheaper to use the square of the length.
	/// @param a Vector.
	/// @return The squared length of the vector.
	float lengthSqr(const Vector3& a)
	{
		return a.x*a.x+a.y*a.y+a.z*a.z;
	}

	/// Normalize will set the length to 1, while keeping the direction.
	/// @param v Vector.
	/// @return The normalized vector.
	Vector3 normalize(const Vector3& a)
	{
		float length = std::sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
		return Vector3( a.x/length, a.y/length, a.z/length);
	}

	/// Linear interpolation between two vectors.
	/// @param a Vector.
	/// @param b Vector.
	/// @param w Weight.
	/// @return lerp returns a when w is zero and b when w is one.
	Vector3 lerp(const Vector3& a, const Vector3& b, float w) 
	{
		return a + (b - a) * w;
	}

	/// Add a scalar s to a vector A.
	/// @param s Scalar.
	/// @param a Vector.
	/// @return [s + A.x, s + A.y, s + A.z].
	Vector3 operator+(float s, Vector3 a)
	{
		return Vector3(s+a.x, s+a.y, s+a.z);
	}
	
	/// Substract a vector A from a scalar s.
	/// @param s Scalar.
	/// @param a Vector.
	/// @return [s - A.x, s - A.y, s - A.z].
	Vector3 operator-(float s, Vector3 a)
	{
		return Vector3(s-a.x, s-a.y, s-a.z);
	}

	/// Multiply a vector A to a scalar s.
	/// @param s Scalar.
	/// @param a Vector.
	/// @return [s * A.x, s * A.y, s * A.z].
	Vector3 operator*(float s, Vector3 a)
	{
		return Vector3(s*a.x, s*a.y, s*a.z);
	}

	/// Divide a vector s with a point A.
	/// @param s Scalar.
	/// @param a Vector.
	/// @return [s / A.x, s / A.y, s / A.z].
	Vector3 operator/(float s, Vector3 a)
	{
		return Vector3(s/a.x, s/a.y, s/a.z);
	}

////////////////////////////////////////////////////////////////////////////////////
///
///	@class Ray
/// @brief A ray is a line that goes to infinity starting at the point origin and 
///	going in a certain direction.
///	
////////////////////////////////////////////////////////////////////////////////////

	/// Default constructor for a ray.
	/// The ray will be set to origin: [0, 0, 0] direction: [0, 0, 1].
	Ray::Ray() : origin(0), direction(0,0,1)
	{
	}

	/// Constructor for a Ray.
	/// @param origin The starting point for the ray.
	/// @param direction The direction of the ray.
	Ray::Ray(Point3 origin, Vector3 direction) : origin(origin), direction(direction)
	{
	}
}
