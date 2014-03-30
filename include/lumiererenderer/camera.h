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
#include <lumiererenderer\Geometry.h>
#include "Imagesensor.h"
#include <lumiererenderer\Matrix.h>
#include <lumiererenderer\Rendercontext.h>

namespace LumiereRenderer
{
	// Forwad declerations
	class Integrator;

    /*!
        @class Camera
        @brief A base class for a camera.

               The camera is responsible for generating rays. The camera 
               allows you to set your own imagesensor.
    */

	class Camera : public Node
    {
    public:
            /// Default constructor.
            Camera();
            
            /// Default destructor.
            virtual ~Camera();
        
		    /// Trace the scene from the camera.
            /// @param[in] x   The pixel position on the X axis of the image sensor.
            /// @param[in] y   The pixel position on the Y axis of the image sensor.
		    /// @param[in] rc
            virtual void trace( unsigned int x, unsigned int y, RenderContext* rc ) = 0;

            /// Set the image sensor.
		    /// @param[in] sensor
            void setImageSensor( ImageSensor* sensor );
        
            /// Get the current image sensor.
            ImageSensor* getImageSensor();
        
            /// The postion of the camera defines the center of the imagesensor.
            /// @param[in] position The postion of the camera.
            void setPosition( Point3 position );
        
            /// @return The postion of the camera.
            Point3 getPosition();
        
            /// The view direction is the optical axis of the camera. It is a straight line passing through the geometrical centre of the lens.
            /// @param[in] viewDirection The view direction.
            void setViewDirection( Vector3 viewDirection );
        
            /// The view direction is the optical axis of the camera. It is a straight line passing through the geometrical centre of the lens.
            /// @return The view direction.		
            Vector3 getViewDirection();
        
            /// The up direction is the Y axis on the imagesensor in world space.
            /// @param[in] upDirection The up direction.
            void setUpDirection( Vector3 upDirection );
        
            /// The up direction is the Y axis on the imagesensor in world space.
            /// @return The up direction.
            Vector3 getUpDirection();

            ///
            /// @param attribute    
            /// @param rc          
            virtual void evaluate( Attribute* attr, RenderContext* rc ) = 0;

    protected:
            ImageSensor*                mImageSensor;
            Matrix                      mTransform;
    };

}