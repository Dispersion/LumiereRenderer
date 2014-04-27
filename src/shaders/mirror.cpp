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

#include <lumiererenderer\mirror.h>
#include <lumiererenderer\sampler.h>
#include <lumiererenderer\geometry.h>
#include <lumiererenderer\integrator.h>
#include <lumiererenderer\constants.h>

namespace LumiereRenderer
{

	Mirror::Mirror()
	{
		mPosition = createAttribute<Point3>("Position", 0);
		mNormal = createAttribute<Vector3>("Normal", 0);
		mRayDirection = createAttribute<Vector3>("WoDirection", 0);
		mWoWavelength = createAttribute<float>("WoWavelength", 0);
        mShaderToWorld = createAttribute<Matrix>("ShaderToWorld", Matrix());
        mWorldToShader = createAttribute<Matrix>("WorldToShader", Matrix());
        mReflectance = createAttribute<float>("Reflectance", 1);
		//mRayDepth = CreateInput("TraceDepth");
		//mOutColor = CreateOutput("outColor");
	}

	Mirror::~Mirror(void)
	{
	}

    float Mirror::evaluateDir( RenderContext& /*rc*/ )
    {
        return 0;
    }

	float Mirror::evaluateSample( RenderContext& rc )
    {
        Point3 position = rc.getInput( mPosition ).asPoint3();
        Vector3 normal = rc.getInput( mNormal ).asVector3();
        Vector3 rayDirection = rc.getInput( mRayDirection ).asVector3();
        float rayWavelength = rc.getInput( mWoWavelength ).asFloat();
        //int rayDepth = rc.getInput( mRayDepth ).asInt();
        Matrix shaderToWorld = rc.getInput( mShaderToWorld ).asMatrix();
        Matrix worldToShader = rc.getInput( mWorldToShader ).asMatrix();
        float reflectance = rc.getInput( mReflectance ).asFloat(); 
        float pdf;
        Vector3 wo = worldToShader * -rayDirection;
        Vector3 wi = shaderToWorld*Reflect(wo, pdf);

        Ray ray = Ray(position, wi, rayWavelength);					
        //Ray wi = Ray(position, Reflect(rayDirection, normal, pdf), rayWavelength);					
        ray.specular = true;
        ray.origin = ray.origin + ray.direction * EPSILON*10;
        //wi.depth = rayDepth;

        return rc.trace(ray) * reflectance;
	}
}