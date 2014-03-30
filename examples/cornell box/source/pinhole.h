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
#include <lumiererenderer\camera.h>

namespace LumiereRenderer
{
    ////////////////////////////////////////////////////////////////////////////////////
    ///
    ///	@class Pinhole
    /// @brief A pinhole camera.
    ///
    ////////////////////////////////////////////////////////////////////////////////////

    class Pinhole : public Camera
    {
    public:
        /// Constructor for a pinhole camera.
        /// @param focalLength The distance from the image sensor to to the pinhole, given in meters.
        /// @param aperture The diameter of the aperture in meters. If you set it to 0 then it will give you an infinte small pinhole.
        Pinhole( float focalLength, float aperture = 0, float shutterSpeed = 1 );
        
        /// Destructor for a pinhole camera.
        ~Pinhole();
            
        /// Trace the scene from the camera.
        /// 
        void trace( unsigned int i, unsigned int j, RenderContext* rc );

        ///
		void evaluate( Attribute* attr, RenderContext* rc );

        /// Set the focal length to a new value.
        /// @param length The distance from the image sensor to the pinhole, given in meters.
        void setFocalLength( float length );
        
        /// Get the focal length.
        /// @return The distance from the image sensor to the pinhole, given in meters.
        float getFocalLength();

    private:
        float mFocalLength;
        Point3 mPinhole;
        float mAperture;
        float mShutterSpeed;

        //Attribute* mExposure;
		//Attribute* mAperture;

    };
}