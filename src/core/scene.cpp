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

#include <lumiererenderer\Scene.h>
#include <lumiererenderer\Shader.h>
#include <lumiererenderer\Random.h>

namespace LumiereRenderer
{
    Scene::Scene(void)
    {
    }

    Scene::~Scene(void)
    {
    }

    void Scene::addShape(Shape* shape)
    {
        if (shape->GetShader()->isEmitter())
        {
            mEmitters.push_back(shape);
        }

        mShapes.push_back(shape);
    }

    bool Scene::sampleEmitters(RenderContext& rc) const
    {
        if (mEmitters.empty())
            return false;

        int i = static_cast<int>(floor(Random() * (mEmitters.size()-1)+0.5));
        
        mEmitters[i]->Sample( rc );       
        DataHandle pdf = rc.getInput( RenderContext::PDF );
        //pdf.set( pdf.asFloat() / mEmitters.size() );

        rc.setOutput(RenderContext::PDF, pdf.asFloat() / mEmitters.size());

        return true;
    }
}