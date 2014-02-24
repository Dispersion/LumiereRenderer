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
#include <lumiererenderer\point3.h>
#include <lumiererenderer\shadernode.h>
#include <lumiererenderer\rendercontext.h>


namespace LumiereRenderer 
{
    ////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @class Shader
    /// A surface shader will shade the surface of an object.
    /// 
    /// @brief Shade the surface of an object.
    ///
    ////////////////////////////////////////////////////////////////////////////////////

    class Shader : public ShaderNode
    {
    public:
        Shader(void);
        virtual ~Shader(void);
        
        /// Evaluate the light going through the material between two points.
        /// @param[in] sc The shadercontext is used to get values from incomming attributes.
        /// @param[in] from The starting point of the ray.
        /// @param[in] to The end point of the ray.
        /// @return Radiance.
        virtual float Evaluate( RenderContext* rc, const Point3& from, const Point3& to ) = 0;
        
        /// Evaluate the light comming from wi.
        /// @param[in] sc The shadercontext is used to get values from incomming attributes.
        /// @param[in] wi The ray in the direction of the lightsource.
        /// @return Radiance.
        virtual float Evaluate( RenderContext* rc, const Ray& wi ) = 0;
        
        /// Evaluate an outgoing attribute.
        /// @param[in] attr The outgoing attribute.
        /// @param[in] sc The shadercontext is used to get values from incomming attributes.
        virtual void Evaluate( Attribute* attr, RenderContext* rc ) = 0;

        /// Get the index of refraction of the material.
        /// @param[in] sc The shadercontext is used to get values from incomming attributes.
        /// @return The IOR.
        virtual float GetIor(RenderContext* rc);

        /// If a material is used as a light source, this function should return true.
        virtual bool DoEmit();

        static Attribute* RADIANCE;
    };
}