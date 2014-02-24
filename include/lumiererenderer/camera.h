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
#include <lumiererenderer\geometry.h>
#include <lumiererenderer\imagesensor.h>
#include <lumiererenderer\matrix.h>
#include <lumiererenderer\rendercontext.h>

namespace LumiereRenderer
{
    
    class Integrator;

    ////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @class Camera
    /// The camera is responsible for generating rays. The camera allows you to set your
    /// own imagesensor. 
    /// @brief A base class for a camera.	
    ///
    ////////////////////////////////////////////////////////////////////////////////////

    class Camera : public Node
    {
    public:
        /// Default constructor.
        Camera();
        /// Default destructor.
        virtual ~Camera();
        
        virtual RGBA Trace( unsigned int i, unsigned int j, RenderContext* rc ) = 0;

        /// Trace the scene from the camera.
        /// @param[in] integrator The integrator the camera should use to trace the scene.
        /// @param[in] i The pixel position on the X axis of the image sensor.
        /// @param[in] j The pixel position on the Y axis of the image sensor.
        //virtual float Trace( Integrator* integrator, unsigned int i, unsigned int j ) = 0;
        
        /// Set the image sensor.
        void SetImageSensor( ImageSensor* sensor );
        
        /// Get the current image sensor.
        ImageSensor* GetImageSensor();
        
        /// The postion of the camera defines the center of the imagesensor.
        /// @param[in] position The postion of the camera.
        void SetPosition( Point3 position );
        
        /// @return The postion of the camera.
        Point3 GetPosition();
        
        /// The view direction is the optical axis of the camera. It is a straight line passing through the geometrical centre of the lens.
        /// @param[in] viewDirection The view direction.
        void SetViewDirection( Vector3 viewDirection );
        
        /// The view direction is the optical axis of the camera. It is a straight line passing through the geometrical centre of the lens.
        /// @return The view direction.		
        Vector3 GetViewDirection();
        
        /// The up direction is the Y axis on the imagesensor in world space.
        /// @param[in] upDirection The up direction.
        void SetUpDirection( Vector3 upDirection );
        
        /// The up direction is the Y axis on the imagesensor in world space.
        /// @return The up direction.
        Vector3 GetUpDirection();


        virtual void Evaluate( Attribute* attr, RenderContext* rc ) = 0;

    protected:
        ImageSensor* mImageSensor;
        Matrix mTransform;
    };

}