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

#include <lumiererenderer\pinhole.h>
#include <lumiererenderer\sampler.h>
#include <lumiererenderer\constants.h>
#include <lumiererenderer\integrator.h>
#include <lumiererenderer\radiometry.h>
#include <lumiererenderer\random.h>
#include <iostream>

namespace LumiereRenderer
{
    Pinhole::Pinhole(float focalLength, float aperture, float shutterSpeed)
    {		
        mFocalLength = createAttribute<float>("focalLength", 0.06f);
        mShutterSpeed = createAttribute<float>("shutterSpeed", 0.3f);
        mAperture = createAttribute<float>("aperture", 0.00005f);
    }

    Pinhole::~Pinhole()
    {
    }

    void Pinhole::trace( unsigned int i, unsigned int j, RenderContext& rc )
    {
		float focalLength = rc.getInput( mFocalLength ).asFloat();
        float shutterSpeed = rc.getInput( mShutterSpeed ).asFloat();
        float aperture = rc.getInput( mAperture ).asFloat();

        ImageSensor::Sample imageSensorSample = mImageSensor->sample( i,j );

        Point3 pointOnAperture;
        if ( mAperture > 0 )
        {
            pointOnAperture = SampleDisc(Random(), Random()) * aperture;
        }

        imageSensorSample.position.z = focalLength;
        Ray ray = Ray( imageSensorSample.position, pointOnAperture, imageSensorSample.wavelength );
        ray.origin = pointOnAperture;

        // Transform ray with camera transformation.
        ray = mTransform * ray;
        
        ray.t = INFINITY;

        rc.setOutput(RenderContext::TRACE_DEPTH, -1);
        rc.setOutput(RenderContext::WO_WAVELENGTH, imageSensorSample.wavelength);
    
       
        float pdf = 1.0f / ( PI*aperture*aperture );
        float g = G( imageSensorSample.position, pointOnAperture, Vector3( 0, 0, -1 ), Vector3( 0, 0, 1) );
        float time = shutterSpeed;
        float exposure = ( ( time * g ) / pdf ) * rc.trace( ray );

        mImageSensor->setExposure( i, j, exposure, ray.alpha, rc );
    }

    void Pinhole::evaluate( Attribute* /*attr*/, RenderContext& /*rc*/ )
    {
        // Todo	
	}

    void Pinhole::setFocalLength(float length)
    {
        mFocalLength->setDefaultValue(length);
    }

    /*float Pinhole::getFocalLength()
    {
        return static_cast<float>(mFocalLength->getDefaultValue());
    }*/
}