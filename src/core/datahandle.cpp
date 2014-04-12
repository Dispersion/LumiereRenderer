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

#include <lumiererenderer\DataHandle.h>
#include <lumiererenderer\RenderContext.h>
#include <lumiererenderer\Shader.h>
#include <lumiererenderer\Shape.h>

namespace LumiereRenderer
{
    DataHandle::DataHandle(RenderContext* rc, int index) : mRenderContext(rc), mIndex(index)
    {
    }

    DataHandle::~DataHandle(void)
    {
    }

    float DataHandle::asFloat()
    {    
        return (static_cast<float*>(mRenderContext->getData(mIndex)))[0];
    }

    int DataHandle::asInt()
    {
        return (static_cast<int*>(mRenderContext->getData(mIndex)))[0];
    }

    double DataHandle::asDouble()
    {
        return (static_cast<double*>(mRenderContext->getData(mIndex)))[0];
    }

    char DataHandle::asChar()
    {
        return (static_cast<char*>(mRenderContext->getData(mIndex)))[0];
    }

    bool DataHandle::asBool()
    {
        return (static_cast<bool*>(mRenderContext->getData(mIndex)))[0];
    }

    Vector3 DataHandle::asVector3()
    {
        return (static_cast<Vector3*>(mRenderContext->getData(mIndex)))[0];
    }

    Vector4 DataHandle::asVector4()
    {
        return (static_cast<Vector4*>(mRenderContext->getData(mIndex)))[0];
    }

    Point3 DataHandle::asPoint3()
    {
        return (static_cast<Point3*>(mRenderContext->getData(mIndex)))[0];
    }

    Matrix DataHandle::asMatrix()
    {
        return (static_cast<Matrix*>(mRenderContext->getData(mIndex)))[0];
    }

    void* DataHandle::asPointer()
    {
        return (static_cast<void**>(mRenderContext->getData(mIndex)))[0];
    }
    
    Shader* DataHandle::asShader()
    {
        return (static_cast<Shader**>(mRenderContext->getData(mIndex)))[0];
    }

    Shape* DataHandle::asShape()
    {
        return (static_cast<Shape**>(mRenderContext->getData(mIndex)))[0];
    }

}