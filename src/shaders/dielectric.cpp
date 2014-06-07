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

#include <lumiererenderer\Dielectric.h>
#include <lumiererenderer\Geometry.h>
#include <lumiererenderer\Constants.h>
#include <lumiererenderer\LinearAlgebra.h>
#include <lumiererenderer\Sampler.h>

namespace LumiereRenderer 
{ 
    Dielectric::Dielectric()
    {
        mPosition = createAttribute<Point3>("Position", 0);
        mNormal = createAttribute<Vector3>("Normal", 0);
        mWoIor = createAttribute<float>("WoIor", 0);
        mWiIor = createAttribute<float>("WiIor", 0);
        mRayDirection = createAttribute<Vector3>("WoDirection", 0);
        mShaderToWorld = createAttribute<Matrix>("ShaderToWorld", Matrix());
        mWorldToShader = createAttribute<Matrix>("WorldToShader", Matrix());
        mWavelength = createAttribute<float>("WoWavelength", 0);
        mReflectance = createAttribute<float>("Reflectance", 1);
        mInteriorIor = createAttribute<float>("InteriorIor", 1.5);
        mExteriorIor = createAttribute<float>("ExteriorIor", 1);                    
    }

    Dielectric::~Dielectric(void)
    {
        delete mPosition;
        delete mNormal;
        delete mWoIor;
        delete mWiIor;
        delete mRayDirection;
        delete mShaderToWorld;
        delete mWorldToShader;
        delete mWavelength;
        delete mReflectance;
        delete mInteriorIor;
        delete mExteriorIor;
    }

    float Dielectric::evaluateDir( RenderContext& /*rc*/ )
    {
        return 0;
    }

    float Dielectric::evaluateSample( RenderContext& rc )
    {
        float pdf;
        Point3 position = rc.getInput( mPosition ).asPoint3();
        Vector3 normal = rc.getInput( mNormal ).asVector3();
        float woIor = rc.getInput( mExteriorIor ).asFloat();
        float wiIor = rc.getInput( mInteriorIor ).asFloat();
        Vector3 rayDirection = rc.getInput( mRayDirection ).asVector3();
        Matrix shaderToWorld = rc.getInput( mShaderToWorld ).asMatrix();
        Matrix worldToShader = rc.getInput( mWorldToShader ).asMatrix();
        float wavelength = rc.getInput( mWavelength ).asFloat();
        //float reflectance = rc.getInput( mReflectance ).asFloat(); 

        Vector3 wo = worldToShader * -rayDirection;
        Vector3 wi;

       // normal = Normalize(normal);

        float Fr = 1;
        float refraction = 0;
        float reflection = 0;

        if ( Dot( normal, -rayDirection ) > 0)
        {
            // We enter the material                        
            if (Refract( woIor, wiIor, wo, wi, pdf))
            {
                Fr = FresnelDielectric(wo.z, -wi.z, woIor, wiIor);
                wi = shaderToWorld*wi;
                Ray ray = Ray(position, wi, wavelength);					                
                ray.origin = ray.origin + ray.direction * EPSILON*10;
                ray.specular = true;
                ray.transmission = true;
                refraction = rc.trace(ray)/* * reflectance*/;
            }
        }
        else
        {
            // We exit the material.
            if( Refract( wiIor, woIor, wo, wi, pdf) )
            {
                Fr = FresnelDielectric(-wo.z, wi.z, wiIor, woIor);
                wi = shaderToWorld*wi;
                Ray ray = Ray(position, wi, wavelength);					                
                ray.origin = ray.origin + ray.direction * EPSILON*10;
                ray.specular = true;
                ray.transmission = true;
                refraction =  rc.trace(ray)/* * reflectance*/;
            }
        }
            
        wi = shaderToWorld*Reflect(wo, pdf);
        Ray ray = Ray(position, wi, wavelength);					                
        ray.origin = ray.origin + ray.direction * EPSILON*10;        
        ray.transmission = false;
        ray.specular = true;
        reflection = rc.trace(ray);

        return ((1.0f-Fr)*refraction) + Fr*reflection;
    }
}
