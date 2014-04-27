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
#include <lumiererenderer\Ray.h>
#include <lumiererenderer\RenderContext.h>
#include <lumiererenderer\Node.h>

namespace LumiereRenderer
{
	// Forward declerations
    class BoundingVolume; 
    class Shader;
    class Hitpoint;

    /*!
        @class Shape
        @brief Objects in the scene that will reflect light.

               The is the base node of a shape. The shapes are use to define
               geometry in the scene. 
    */
	
    class Shape : public Node
    {
    public:
		    /// Default constructor
            Shape();

            /// Default destructor
            virtual ~Shape();

		    /// Intersect a ray with the shape. This funtion only determines if the ray intersects
		    /// with the shape and not where it intersects. 
            /// @param[in] ray  The ray used to test for intersection.
            /// @return It will return true if the ray intersects with the shape, otherwise it will return false.
		    virtual bool intersect( Ray& ray ) = 0;
  	    
		    /// Each shape have a pointer to the shader used to shade the shape. This means that, however, we store
		    /// the shapes in the scene, we can find out which shader we should use to shade the shape.
            /// @return The shader used to shade this shape.
		    Shader* getShader();
        	
		    /// Each shape have a pointer to the shader used to shade the shape. This means that, however, we store
		    /// the shapes in the scene, we can find out which shader we should use to shade the shape.
            /// @param[in] shader  The shader used to shade this shape.          
		    void setShader( Shader* shader );

            virtual Shape* getBounding() = 0;
            virtual Point3 getMin() = 0;
            virtual Point3 getMax() = 0;

		    /// The node system will call the evaluate function, when a connected node wants to find the value
		    /// of one of this shapes attributes. Any shape must implement this function to evaluate the 
		    /// default shape attributes:
		    ///
		    ///      RenderContext::POSITION            The intersection point between the ray and the shape.
		    ///      RenderContext::NORMAL              The normal on the shape at the intersection point.
		    ///      RenderContext::TANGENT             The tangent on the shape at the intersection point.
		    ///      RenderContext::BINORMAL            The binormal is orthogonal to the tangent and normal.
		    ///      RenderContext::TEXCOORD            The texture coordinates at the intersection point.
		    ///      RenderContext::SHADER_TO_WORLD     The matrix that transform a ray from normal space to world space.
		    ///      RenderContext::WORLD_TO_SHADER     The matrix that transform a ray from world space to normal space.
		    ///
            /// @param[in] attr  The attribute we want to find the value of.
		    /// @param[in] rc    The RenderContext is used to get values from incomming attributes.
            virtual void evaluate( Attribute* attr, RenderContext& rc ) = 0;

		    ///
            /// @param[in] rc    The RenderContext is used to get values from incomming attributes.
		    virtual void                sample( RenderContext& rc ) = 0;
	
	protected:
            Shader*                     mShader;
    };
}