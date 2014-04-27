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
#include <lumiererenderer\shape.h>
#include <lumiererenderer\AABB.h>

namespace LumiereRenderer
{
    struct Vertex
    {
        Point3 position;
        Vector3 normal;
        Vector3 texcoord;
    };

    struct TriWald
    {
        // first 16 byte half cache line
        // plane
        float nu;
        float nv;
        float nd;
        int k;

        //second 16 byte half cache line
        //line equation for line ac
        float bnu;
        float bnv;
        float bd;
        int pad; // pad to next cache line

        //third 16 byte cache line
        //line equation for line ab
        float cnu;
        float cnv;
        float cd;
        int pad2; // pad to 48 bytes for cache alignment purposes
    };

    class Triangle : public Shape
    {
    public:
        Triangle(Vertex v0, Vertex v1, Vertex v2);
        ~Triangle(void);
        bool intersect(Ray& Ray);
        virtual Shape* getBounding();
        virtual Point3 getMin();
        virtual Point3 getMax();
        void evaluate( Attribute* attr, RenderContext& rc );
        void sample(RenderContext& rc);

        Vertex v0, v1, v2;

    private:		
        TriWald mWaldTriangle;
        AABB* mAABB;
    };
}