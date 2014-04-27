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

#include <lumiererenderer\Geometry.h>
#include <lumiererenderer\LinearAlgebra.h>

namespace LumiereRenderer
{

    float Lerp(float a, float b, float w)
    {
        return a + (b - a) * w;
    }

    Point3 Lerp(const Point3& a, const Point3& b, float w)
    {
        return a + (b - a) * w;
    }

    Vector3 Lerp(const Vector3& a, const Vector3& b, float w) 
    {
        return a + (b - a) * w;
    }

    float Length(const Vector3& a)
    {
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    }

    float LengthSqr(const Vector3& a)
    {
        return a.x*a.x+a.y*a.y+a.z*a.z;
    }

    Vector3 Normalize(const Vector3& a)
    {
        float length = sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
        return Vector3( a.x/length, a.y/length, a.z/length);
    }

    float Dist(Point3 a, Point3 b)
    {
        return Length(b-a);
    }

    float DistSqr(Point3 a, Point3 b)
    {
        return LengthSqr(b-a);
    }

    Vector3 Reflect(const Vector3& wo, float& pdf)
    {
        pdf = 1.0;      
        return Vector3(-wo.x, -wo.y, wo.z);
    }

    bool Refract( float n1, float n2, const Vector3& wo, Vector3& wi, float& pdf)
    {
       /* pdf = 1.0;
        float eta = n1/n2;

        float c1 = wo.z;
        float c2 = 1 - eta*eta *( 1-c1*c1);

        if ( c2 < 0 ) return false;

        wi = Normalize(-eta*Vector3(wo.x, wo.y, wo.z-c1) - Vector3( 0, 0, sqrt(c2)));

        return true;*/

        pdf = 1.0;
        Vector3 normal = Vector3(0,0,1);

        float eta = n1/n2;
        if (Dot( normal, wo ) < 0)
        {
            normal = -normal;
        }

        float c1 = Dot( normal, wo );
        float c2 = 1 - eta*eta *( 1-c1*c1);

        if ( c2 < 0 ) return false;

        wi = Normalize(-eta*(wo - c1*normal) - sqrt(c2) * normal);

        return true;
    }
}
