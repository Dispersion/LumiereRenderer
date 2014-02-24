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

#include <lumiererenderer\point3.h>
#include <lumiererenderer\vector3.h>
#include <lumiererenderer\matrix.h>

namespace LumiereRenderer
{
	/// The dot product takes two normalized vectors A and B, and returns cosinus to the angle
	/// between A and B.
	/// @param[in] a Vector.
	/// @param[in] b Vector.
	/// @return Cosinus to the angle between A and B.
	float Dot(const Vector3& a, const Vector3& b);

	/// The dot product takes a point A and a vector B, and returns cosinus to the angle
	/// between A and B.
	/// @param[in] a Point.
	/// @param[in] b Vector.
	/// @return Cosinus to the angle between A and B.
	float Dot(const Point3& a, const Vector3& b);

	/// The dot product takes a vector A and a point B, and returns cosinus to the angle
	/// between A and B.
	/// @param[in] a Vector.
	/// @param[in] b Point.
	/// @return Cosinus to the angle between A and B.
	float Dot(const Vector3& a, const Point3& b);

	/// The cross product takes two points A and B, where A != B. It returns a vector C,
	/// which is orthogonal to the plane spanned by a vector to A and to B.
	/// @param[in] a Point.
	/// @param[in] b Point.
	/// @return A vector orthogonal to a and b.
	Vector3	Cross(const Point3& a, const Point3& b);

	/// The cross product takes two vectors A and B, where A != B. It returns a vector C,
	/// which is orthogonal to the plane spanned by A and B.
	/// @param[in] a Vector.
	/// @param[in] b Vector.
	/// @return A vector orthogonal to a and b.
	Vector3	Cross(const Vector3& a, const Vector3& b);

	Matrix Transpose(const Matrix& m);
	float Det( const Matrix& m );
	Matrix Invert(const Matrix& m);

	Matrix Translate(float x, float y, float z);
	Matrix Translate(Vector3 vector);
	//Matrix Rotate(float angle, Vector3 vector);
	//Matrix Rotate(float angle, float x, float y, float z);
	Matrix Scale(float x, float y, float z);
	Matrix Scale(Vector3 vector);
}

