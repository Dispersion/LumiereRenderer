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

#include <lumiererenderer\Shape.h>
#include <lumiererenderer\Shader.h>
#include <lumiererenderer\AttributeValue.h>

namespace LumiereRenderer
{
	Attribute* Shape::POSITION = new AttributeValue<Point3>("Position", 0);
    Attribute* Shape::NORMAL = new AttributeValue<Vector3>("Normal", 0);
    Attribute* Shape::BINORMAL = new AttributeValue<Vector3>("Binormal", 0);
    Attribute* Shape::TANGENT = new AttributeValue<Vector3>("Tangent", 0);
    Attribute* Shape::TEXCOORD = new AttributeValue<Vector3>("Texcoord", 0);
	Attribute* Shape::WORLD_TO_SHADER = new AttributeValue<Matrix>("WorldToShader", Matrix());
    Attribute* Shape::SHADER_TO_WORLD = new AttributeValue<Matrix>("ShaderToWorld", Matrix());

	Shape::Shape(void)
	{
		mShader = 0;
	}

	Shape::~Shape(void)
	{
	}

	Shader* Shape::GetShader()
	{
		return mShader;
	}

	void Shape::SetShader(Shader* shader)
	{
		mShader = shader;
	}
}
