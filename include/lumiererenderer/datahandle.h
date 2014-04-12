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
#include <lumiererenderer\Vector3.h>
#include <lumiererenderer\Vector4.h>
#include <lumiererenderer\Point3.h>
#include <lumiererenderer\Matrix.h>

namespace LumiereRenderer
{    
    // Forward declarations
    class RenderContext;  
    class Shader;         
    class Shape;          

    /*!
        @class DataHandle
        @brief A handle to the value of an attribute.

               To access the data of an attribute it must go through the RenderContext. 
               The RenderContext will return a handle to the data of the attribute. Use 
               the 'As' functions to get the value required type. Make sure you use the 
               correct type of the attribute otherwise it would create undefined results.

               If the attribute is an output attribute, you will still get an handle to 
               the data. Use the 'Set' functions to set the output value.
    */

    class DataHandle
    {
    public:
        DataHandle(RenderContext* rc, int index);
        ~DataHandle(void);

        int asInt();
        float asFloat();
        double asDouble();
        char asChar();
        bool asBool();
        Vector3 asVector3();
        Vector4 asVector4();
        Point3 asPoint3();
        Matrix asMatrix();
        void* asPointer();       
        Shader* asShader();
        Shape* asShape();

    private:
        RenderContext*              mRenderContext;
        int                         mIndex;
    };
}
