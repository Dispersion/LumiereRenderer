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

#include <lumiererenderer\Sampler.h>
#include <lumiererenderer\Random.h>
#include <lumiererenderer\Constants.h>
#include <lumiererenderer\Geometry.h>

namespace LumiereRenderer
{
    Vector3 SampleHemisphere( float& pdf )
    {	
        pdf = TWO_PI_INV;
        float r1 = Random();
        float r2 = Random();

        float m = 2*PI*r1;
        float n = sqrtf( std::max( 0.f, 1.f - r2*r2 ) );       

        Vector3 v = Vector3( cosf( m ) * n, sinf( m ) * n, r2 );

        return Normalize( v );        
    }

    Vector3 SampleCosineHemisphere( float& pdf )
    {		
        float u1 = Random();
        float u2 = Random();

        Point3 p = SampleDisc(u1, u2);
        Vector3 v = Vector3(p[0],p[1], sqrt( std::max(0.f, 1.f - p[0] * p[0] - p[1] * p[1]))); 
        Vector3 res = Normalize(v);

        pdf = std::max(EPSILON, res.z ) / PI;
        return res;
    }

    //bool Refract( Vector3 normal, float n1, float n2, const Vector3& wo, Vector3& wi, float& pdf)
    //{
    //    pdf = 1.0;
    //    float eta = n1/n2;
    //    /*if (Dot( normal, wo ) < 0)
    //    {
    //        //normal = -normal;
    //        //eta = n2/n1;
    //    }*/

    //    float c1 = Dot( normal, wo );
    //    float c2 = 1 - eta*eta *( 1-c1*c1);

    //    if ( c2 < 0 ) return false;

    //    wi = Normalize(-eta*(wo - c1*normal) - sqrt(c2) * normal);

    //    return true;
    //}

    Point3 SampleDisc(float u1, float u2)
    {
        float r = sqrt(u1);
        float theta = TWO_PI * u2;
        return Point3( r*cosf(theta), r*sinf(theta), 0 );
    }

    float FresnelDielectric( float cosi, float cost, float etai, float etat)
    {
        float rparl = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float rperp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (rparl*rparl + rperp*rperp) * 0.5f;
    }
}