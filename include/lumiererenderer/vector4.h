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
    ////////////////////////////////////////////////////////////////////////////////////
    ///	@class Vector4
    /// @brief A vector in four dimensional space.
    ///	
    ////////////////////////////////////////////////////////////////////////////////////

    class Vector4
    {
    public:
        
        /// Default constructor.
        /// @return [0, 0, 0, 0].
        Vector4(void);
        
        /// This will initialize a vector to (x, x, x, x).
        /// @param[in] x Scalar.
        /// @return [x, x, x, x].
        Vector4(float x);
        
        /// This will initialize a vector to (x, y, z).
        /// @param[in] x Scalar.
        /// @param[in] y Scalar.
        /// @param[in] z Scalar.
        /// @param[in] w Scalar.
        /// @return [x, y, z, w].
        Vector4(float x, float y, float z, float w);
        
        /// Default destructor.
        ~Vector4(void);
        
        /// Get an element from a vector.
        /// @param[in] index Index.
        /// @return The i'th element of a vector.
        float& operator []( const unsigned int index );
        
        /// Get an element from a const vector.
        /// @param[in] index Index.
        /// @return The i'th element of a const vector.
        const float& operator []( const unsigned int index ) const;
        
        /// Add two vectors A and B. 
        /// @param[in] b Vector.
        /// @return [A.x + B.x, A.y + B.y, A.z + B.z,  A.w + B.w].
        Vector4 operator +( const Vector4& b ) const;
        
        /// Subtract two vectors A and B. 
        /// @param[in] b Vector.
        /// @return [A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w].
        Vector4	operator -( const Vector4& b ) const;		
        
        /// Add two vectors A and B and save the result in A.
        /// @param[in] b Vector.
        /// @return [A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w].
        Vector4& operator +=( const Vector4& b );
        
        /// Subtract two vectors A and B and save the result in A.
        /// @param[in] b Vector.
        /// @return [A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w].
        Vector4& operator -=( const Vector4& b );
        
        /// Add a scalar s to a vector A.  
        /// @param[in] s Scalar.
        /// @return [A.x + s, A.y + s, A.z + s, A.w + s].
        Vector4	operator +( float s ) const;
        
        /// Substract a scalar s from a vector A.
        /// @param[in] s Scalar.
        /// @return [A.x - s, A.y - s, A.z - s, A.w - s].
        Vector4	operator -( float s ) const;
        
        /// Multiply a scalar s to a vector A.
        /// @param[in] s Scalar.
        /// @return [A.x * s, A.y * s, A.z * s, A.w * s].
        Vector4	operator *( float s ) const;
        
        /// Divide a vector A with a scalar s.
        /// @param[in] s Scalar.
        /// @return [A.x / s, A.y / s, A.z / s, A.w / s].
        Vector4	operator /( float s ) const;
        
        /// Add a scalar s to a vector A and save the result in A.
        /// @param[in] s Scalar.
        /// @return [A.x + s, A.y + s, A.z + s, A.w + s]. 
        Vector4& operator +=( float s );
        
        /// Subtract a scalar s from a vector A and save the result in A.
        /// @param[in] s Scalar.
        /// @return [A.x - s, A.y - s, A.z - s, A.w - s].
        Vector4& operator -=( float s );
        
        /// Multiply a scalar s to a vector A and save the result in A.
        /// @param[in] s Scalar.
        /// @return [A.x * s, A.y * s, A.z * s, A.w * s].
        Vector4& operator *=( float s );
        
        /// Divide a vector A with a scalar s and save the result in A.
        /// @param[in] s Scalar.
        /// @return [A.x / s, A.y / s, A.z / s, A.w / s].
        Vector4& operator /=( float s );
        
        /// Negate a vector A.
        /// @return [-A.x, -A.y, -A.z, -A.w].
        Vector4	operator -();

        /// Negate a vector A.
        /// @return [-A.x, -A.y, -A.z, -A.w].
        Vector4	operator -() const;

        /// Element-wise compare of two vectors A and B. 
        /// @param[in] b Vector.
        /// @return True if (A.x == B.x, A.y == B.y, A.z == B.z, A.w == B.w).
        bool operator ==( const Vector4& b );
        
        /// Element-wise compare of two vectors A and B. 
        /// @param[in] b Vector.
        /// @return False if (A.x == B.x, A.y == B.y, A.z == B.z, A.w == B.w)
        bool operator !=( const Vector4& b );
        
        float x, y, z, w;
    };

    /// Add a scalar s to a vector A.
    /// @param[in] s Scalar.
    /// @param[in] a Vector.
    /// @return [s + A.x, s + A.y, s + A.z, s + A.w].
    Vector4	operator+( float s, Vector4 a );
    
    /// Substract a vector A from a scalar s.
    /// @param[in] s Scalar.
    /// @param[in] a Vector.
    /// @return [s - A.x, s - A.y, s - A.z, s - A.w].
    Vector4	operator-( float s, Vector4 a );
    
    /// Multiply a vector A to a scalar s.
    /// @param[in] s Scalar.
    /// @param[in] a Vector.
    /// @return [s * A.x, s * A.y, s * A.z, s * A.w].
    Vector4	operator*( float s, Vector4 a );
    
    /// Divide a vector s with a point A.
    /// @param[in] s Scalar.
    /// @param[in] a Vector.
    /// @return [s / A.x, s / A.y, s / A.z, s / A.w].
    Vector4	operator/( float s, Vector4 a );
    
    std::ostream& operator<<( std::ostream& os, const Vector4& a );
}
