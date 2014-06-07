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

#include <lumiererenderer\Node.h>
#include <lumiererenderer\Shape.h>

namespace LumiereRenderer
{
    Node::Node(void)
    {
    }

    Node::~Node(void)
    {
    }

	void Node::addAttribute( Attribute* attribute )
    {
        //mAttributes[attribute->GetName()] = attribute;

		std::string name = attribute->getName();

        if (name.compare("Position") == 0 )
        {
            attribute->connect( RenderContext::POSITION );
        } 
        else if (name.compare("Normal") == 0 )
        {
            attribute->connect( RenderContext::NORMAL );
        }
        else if (name.compare("Binormal") == 0 )
        {
            attribute->connect( RenderContext::BINORMAL );
        }
        else if (name.compare("Tangent") == 0 )
        {
            attribute->connect( RenderContext::TANGENT );
        }
        else if (name.compare("Texcoord") == 0 )
        {
            attribute->connect( RenderContext::TEXCOORD );
        }
        else if (name.compare("WiDirection") == 0 )
        {
            attribute->connect( RenderContext::WI_DIRECTION );
        }
        else if (name.compare("WiWavelength") == 0 )
        {
            attribute->connect( RenderContext::WI_WAVELENGTH );
        }		
        else if (name.compare("WiIor") == 0 )
        {
            attribute->connect( RenderContext::WI_IOR );
        }	
        else if (name.compare("WiPdf") == 0 )
        {
            attribute->connect( RenderContext::WI_PDF );
        }	
        else if (name.compare("WoDirection") == 0 )
        {
            attribute->connect( RenderContext::WO_DIRECTION );
        }
        else if (name.compare("WoWavelength") == 0 )
        {
            attribute->connect( RenderContext::WO_WAVELENGTH );
        }		
        else if (name.compare("WoIor") == 0 )
        {
            attribute->connect( RenderContext::WO_IOR );
        }
        else if (name.compare("WoPdf") == 0 )
        {
            attribute->connect( RenderContext::WO_PDF );
        }
        else if (name.compare("TraceDepth") == 0 )
        {
            attribute->connect( RenderContext::TRACE_DEPTH );
        }	
        else if (name.compare("RayBarycentricCoordinates") == 0 )
        {
            attribute->connect( RenderContext::RAY_BARYCENTRIC_COORDINATES );
        }
        else if (name.compare("RayLength") == 0 )
        {
            attribute->connect( RenderContext::RAY_LENGTH );
        }
        /*else if ( name.compare("OuterIOR") == 0 )
        {
            attribute->connect( RenderContext::OUTER_IOR );
        }*/
        else if ( name.compare("WorldToShader") == 0 )
        {
            attribute->connect( RenderContext::WORLD_TO_SHADER );
        }
        else if ( name.compare("ShaderToWorld") == 0 )
        {
            attribute->connect( RenderContext::SHADER_TO_WORLD );
        }

        mAttributes[attribute->getName()] = attribute;
        attribute->setOwner(this);
    }

    Attribute* Node::operator[](const char* name)
    {
        return mAttributes[name];
    }
}