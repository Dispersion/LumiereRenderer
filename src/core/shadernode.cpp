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


#include <lumiererenderer\shadernode.h>
#include <lumiererenderer\rendercontext.h>

namespace LumiereRenderer
{
    ShaderNode::ShaderNode(void)
    {
    }

    ShaderNode::~ShaderNode(void)
    {
    }

    void ShaderNode::AddAttribute( Attribute* attribute )
    {
        std::string name = attribute->GetName();

        if (name.compare("Position") == 0 )
        {
            attribute->Connect( RenderContext::POSITION );
        } 
        else if (name.compare("Normal") == 0 )
        {
            attribute->Connect( RenderContext::NORMAL );
        }
        else if (name.compare("Binormal") == 0 )
        {
            attribute->Connect( RenderContext::BINORMAL );
        }
        else if (name.compare("Tangent") == 0 )
        {
            attribute->Connect( RenderContext::TANGENT );
        }
        else if (name.compare("Texcoord") == 0 )
        {
            attribute->Connect( RenderContext::TEXCOORD );
        }
        else if (name.compare("RayOrigin") == 0 )
        {
            attribute->Connect( RenderContext::RAY_ORIGIN );
        }
        else if (name.compare("RayDirection") == 0 )
        {
            attribute->Connect( RenderContext::RAY_DIRECTION );
        }
        else if (name.compare("RayWavelength") == 0 )
        {
            attribute->Connect( RenderContext::RAY_WAVELENGTH );
        }		
        else if (name.compare("RayDepth") == 0 )
        {
            attribute->Connect( RenderContext::RAY_DEPTH );
        }	
        else if (name.compare("RayIOR") == 0 )
        {
            attribute->Connect( RenderContext::RAY_IOR );
        }	
        else if (name.compare("RayBarycentricCoordinates") == 0 )
        {
            attribute->Connect( RenderContext::RAY_BARYCENTRIC_COORDINATES );
        }
        else if (name.compare("RayLength") == 0 )
        {
            attribute->Connect( RenderContext::RAY_LENGTH );
        }
        else if ( name.compare("OuterIOR") == 0 )
        {
            attribute->Connect( RenderContext::OUTER_IOR );
        }
        else if ( name.compare("WorldToShader") == 0 )
        {
            attribute->Connect( RenderContext::WORLD_TO_SHADER );
        }
        else if ( name.compare("ShaderToWorld") == 0 )
        {
            attribute->Connect( RenderContext::SHADER_TO_WORLD );
        }

        mAttributes[attribute->GetName()] = attribute;
        attribute->SetOwner(this);
    }
}