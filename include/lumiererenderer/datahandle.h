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
#include <lumiererenderer\vector3.h>
#include <lumiererenderer\vector4.h>
#include <lumiererenderer\point3.h>
#include <lumiererenderer\matrix.h>

namespace LumiereRenderer
{    
    class RenderContext;
    class Shader;
    class Shape;

    class DataHandle
    {
    public:
        DataHandle(RenderContext* rc, int index);
        ~DataHandle(void);

        void Set(int value);
        void Set(float value);
        void Set(double value);
        void Set(char value);
        void Set(bool value);
        void Set(Vector3 value);
        void Set(Vector4 value);
        void Set(Point3 value);
        void Set(Matrix value);
        //void Set(void* value);
        void Set(Shader* value);
        void Set(Shape* value);
        
        int AsInt();
        float AsFloat();
        double AsDouble();
        char AsChar();
        bool AsBool();
        Vector3 AsVector3();
        Vector4 AsVector4();
        Point3 AsPoint3();
        Matrix AsMatrix();
        //void* AsPointer();       
        Shader* AsShader();
        Shape* AsShape();

    private:
        RenderContext* mRenderContext;
        int mIndex;
    };
}
