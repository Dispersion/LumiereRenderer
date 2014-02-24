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
#include <lumiererenderer\point3.h>
#include <lumiererenderer\vector3.h>
#include <lumiererenderer\ray.h>

namespace LumiereRenderer
{	
    ////////////////////////////////////////////////////////////////////////////////////
    ///
    ///	@class Matrix
    /// 
    /// [m00, m01, m02, m03]
    /// [m10, m11, m12, m13]
    /// [m20, m21, m22, m23]
    /// [m30, m31, m32, m33] 
    ///
    /// @brief A 4x4 Matrix
    ////////////////////////////////////////////////////////////////////////////////////

    class Matrix
    {
    public:
        Matrix();
        Matrix( float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33 );
        ~Matrix();
        float* operator[](int i);
        const float* operator[](int i) const;
        
        /// Creates an identity matrix. An identity matrix has all zeros except on the diagonal going from left to right, which contains ones.
        /// @return A new matrix.
        static Matrix IDENTITY();
        
        /// Creates a matrix with all zeroes.
        /// @return A new matrix.
        static Matrix ZEROS();
        
        /// Creates a matrix with all ones.
        /// @return A new matrix.
        static Matrix ONES();
        
        /// Mulitplies the matrix A with the matrix B.
        /// @param[in] b Matrix.
        /// @return A new matrix containing the result.
        Matrix operator *( const Matrix& b ) const;

        /// Mulitplies the matrix A with the matrix B.
        /// @param[in] b Matrix.
        /// @return This matrix.
        Matrix& operator *=( const Matrix& b );
        
        // TODO: these functions should be in the transform class
        Point3 operator *( const Point3& b ) const;
        Vector3 operator *( const Vector3& b ) const;
        Ray operator *( const Ray& b ) const;

        /// Add a scalar s to each element of matrix A.
        /// @param[in] s Scalar
        /// @return This matrix.
        Matrix& operator +=( float s );
        
        /// Subtract a scalar s from each element of matrix A.
        /// @param[in] s Scalar
        /// @return This matrix.
        Matrix& operator -=( float s );
        
        /// Mulitply a scalar s with each element of matrix A.
        /// @param[in] s Scalar
        /// @return This matrix.
        Matrix& operator *=( float s );
        
        /// Divide element of matrix A with a scalar s.
        /// @param[in] s Scalar
        /// @return This matrix.
        Matrix& operator /=( float s );
        
        /// Element-wise compare of two matrices A and B. This will return true if A is equal to B.
        /// @param b Matrix.
        /// @return True if A is equal to B.
        bool operator ==( const Matrix& b );
        
        /// Element-wise compare of two matrices A and B. This will return true if A is not equal to B.
        /// @param b Matrix.
        /// @return True if A is not equal to B.
        bool operator !=( const Matrix& b );

    private:
        float m[4][4];
    };	

    Matrix				operator+( float s, Matrix a );
    Matrix				operator-( float s, Matrix a );
    Matrix				operator*( float s, Matrix a );
    Matrix				operator/( float s, Matrix a );

    std::ostream& operator<<( std::ostream& os, const Matrix& m );
}