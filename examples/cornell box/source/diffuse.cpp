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

#include "diffuse.h"
#include <lumiererenderer\sampler.h>
#include <lumiererenderer\linearalgebra.h>
#include <lumiererenderer\constants.h>
#include <lumiererenderer\attributevalue.h>

namespace LumiereRenderer
{
    Diffuse::Diffuse()
    {		
        mPosition = new AttributeValue<Point3>("Position", 0);
        mNormal = new AttributeValue<Vector3>("Normal", 0);
        mReflectance = new AttributeValue<float>("Reflectance", 0);
        mRayWavelength = new AttributeValue<float>("RayWavelength", 0);
        mShaderToWorld = new AttributeValue<Matrix>("ShaderToWorld", Matrix());

        AddAttribute( mPosition );
        AddAttribute( mNormal );
        AddAttribute( mReflectance );
        AddAttribute( mRayWavelength );
        AddAttribute( mShaderToWorld );
    }

    Diffuse::~Diffuse(void)
    {
    }

    float Diffuse::Evaluate( RenderContext* /*sc*/, const Point3& /*from*/, const Point3& /*to*/ )
    {
        return 1;
    }

    float Diffuse::Evaluate( RenderContext* sc, const Ray& /*wi*/ )
    {
        if ( mReflectance )
        {			
            return sc->GetInput( mReflectance ).AsFloat() / PI;
        }		
        return 0;
    }

     void Diffuse::Evaluate(Attribute* attr, RenderContext* rc)
    {               
        if (attr == Shader::RADIANCE || attr == NULL)
        {
            float pdf;

            Point3 P  = rc->GetInput( mPosition ).AsPoint3();
            Vector3 N = rc->GetInput( mNormal ).AsVector3();
            float rayWavelength = rc->GetInput( mRayWavelength ).AsFloat();
            float reflectance = rc->GetInput( mReflectance ).AsFloat() / PI;
            Matrix ShaderToWorld = rc->GetInput( mShaderToWorld ).AsMatrix();
            
            //Vector3 dir = ShaderToWorld * SampleHemisphere( pdf );
            Vector3 dir = ShaderToWorld * SampleCosineHemisphere( pdf );

           //Ray wi = Ray(P, SampleHemisphere( N, pdf ));
            Ray wi = Ray(P, dir);
            wi.wavelength = rayWavelength;
            wi.origin = wi.origin + wi.direction * EPSILON*10;

            DataHandle outColor = rc->GetOutput(Shader::RADIANCE);
            outColor.Set( (reflectance * rc->Trace(wi) * Dot(wi.direction, N)) / pdf );
        }
    }
}