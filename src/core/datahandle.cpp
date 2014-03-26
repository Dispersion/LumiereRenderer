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

    void DataHandle::Set(int value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(int));
    }

    void DataHandle::Set(float value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(float));
    }

    void DataHandle::Set(double value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(double));
    }

    void DataHandle::Set(char value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(char));
    }

    void DataHandle::Set(bool value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(bool));
    }

    void DataHandle::Set(Vector3 value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Vector3));
    }

    void DataHandle::Set(Vector4 value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Vector4));
    }

    void DataHandle::Set(Point3 value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Point3));
    }

    void DataHandle::Set(Matrix value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Matrix));
    }

  /*  void DataHandle::Set(void* value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(void*));
    }*/

    void DataHandle::Set(Shader* value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Shader*));
    }

    void DataHandle::Set(Shape* value)
    {
        mRenderContext->SetData(mIndex, &value, sizeof(Shape*));
    }

    float DataHandle::AsFloat()
    {    
        return (static_cast<float*>(mRenderContext->GetData(mIndex)))[0];
    }

    int DataHandle::AsInt()
    {
        return (static_cast<int*>(mRenderContext->GetData(mIndex)))[0];
    }

    double DataHandle::AsDouble()
    {
        return (static_cast<double*>(mRenderContext->GetData(mIndex)))[0];
    }

    char DataHandle::AsChar()
    {
        return (static_cast<char*>(mRenderContext->GetData(mIndex)))[0];
    }

    bool DataHandle::AsBool()
    {
        return (static_cast<bool*>(mRenderContext->GetData(mIndex)))[0];
    }

    Vector3 DataHandle::AsVector3()
    {
        return (static_cast<Vector3*>(mRenderContext->GetData(mIndex)))[0];
    }

    Vector4 DataHandle::AsVector4()
    {
        return (static_cast<Vector4*>(mRenderContext->GetData(mIndex)))[0];
    }

    Point3 DataHandle::AsPoint3()
    {
        return (static_cast<Point3*>(mRenderContext->GetData(mIndex)))[0];
    }

    Matrix DataHandle::AsMatrix()
    {
        return (static_cast<Matrix*>(mRenderContext->GetData(mIndex)))[0];
    }

   /* void* DataHandle::AsPointer()
    {
        return mRenderContext->GetData(mIndex);
    }*/
    
    Shader* DataHandle::AsShader()
    {
        return (static_cast<Shader**>(mRenderContext->GetData(mIndex)))[0];
    }

    Shape* DataHandle::AsShape()
    {
        return (static_cast<Shape**>(mRenderContext->GetData(mIndex)))[0];
    }

}