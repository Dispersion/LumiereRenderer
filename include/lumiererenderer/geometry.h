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

namespace LumiereRenderer
{
    /// Linear interpolation between two floats.
    /// @param a float.
    /// @param b float.
    /// @param w Weight.
    /// @return lerp returns a when w is zero and b when w is one.
    float Lerp(float a, float b, float w);
    
    /// Linear interpolation between two points.
    /// @param a Point.
    /// @param b Point.
    /// @param w Weight.
    /// @return lerp returns a when w is zero and b when w is one.
    Point3 Lerp(const Point3& a, const Point3& b, float w);
    
    /// Linear interpolation between two vectors.
    /// @param a Vector.
    /// @param b Vector.
    /// @param w Weight.
    /// @return lerp returns a when w is zero and b when w is one.
    Vector3 Lerp(const Vector3& a, const Vector3& b, float w);

    ///The length of the vector.
    /// @param a Vector.
    /// @return The length of the vector.
    float Length(const Vector3& a);

    ///If you only want to find out if a vector is longer than another vector,
    ///it is cheaper to use the square of the length.
    /// @param a Vector.
    /// @return The squared length of the vector.
    float LengthSqr(const Vector3& a);
       
    /// Normalize will set the length to 1, while keeping the direction.
    /// @param v Vector.
    /// @return The normalized vector.
    Vector3 Normalize(const Vector3& a);

    /// The distance from a point A to a point B.
    /// @param a Point.
    /// @param b Point.
    /// @return The distance.
    float Dist(Point3 a, Point3 b);

    /// The square of the distance from a point A to a point B.
    /// @param a Point.
    /// @param b Point.
    /// @return The square of the distance.
    float DistSqr(Point3 a, Point3 b);

    /// @param[in] A vector
    /// @param[out] The pdf of the reflected direction 
    /// @return The reflected ray
    Vector3 Reflect( const Vector3& wo, float& pdf );
    
    bool Refract( float n1, float n2, const Vector3& wo, Vector3& wi, float& pdf );
}
