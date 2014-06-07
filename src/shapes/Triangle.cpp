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

#include <lumiererenderer\triangle.h>
#include <lumiererenderer\random.h>
#include <lumiererenderer\constants.h>
#include <lumiererenderer\linearalgebra.h>
#include <lumiererenderer\geometry.h>
#include <math.h>

namespace LumiereRenderer
{
    static const unsigned int modulo[5] = {0,1,2,0,1};

    Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2) : v0(v0), v1(v1), v2(v2)
    {		
        Point3 p0 = v0.position;
        Point3 p1 = v1.position;
        Point3 p2 = v2.position;

        //Precompute Wald triangle
        Vector3 b = p2 - p0;
        Vector3 c = p1 - p0;
        Vector3 n = Cross(c, b);		
        int k;

        if (abs(n[0]) > abs(n[1]))
        {
            if (abs(n[0]) > abs(n[2])) k = 0; else k = 2;
        }
        else
        {
            if (abs(n[1]) > abs(n[2])) k = 1; else k = 2;
        }
            
        int u = modulo[k+1];
        int v = modulo[k+2];

        n[u] = n[u] / n[k];
        n[v] = n[v] / n[k];
        n[k] = 1;

        mWaldTriangle.nu = n[u];
        mWaldTriangle.nv = n[v];
        mWaldTriangle.nd = Dot(p0, n);
        mWaldTriangle.k = k;
        
        float denom = (b[u]*c[v] - b[v]*c[u]); 
        mWaldTriangle.bnu = -b[v] / denom; 
        mWaldTriangle.bnv = b[u] / denom; 
        mWaldTriangle.bd = (b[v]*p0[u] - b[u]*p0[v]) / denom;

        mWaldTriangle.cnu = c[v] / denom; 
        mWaldTriangle.cnv = -c[u] / denom;
        mWaldTriangle.cd = (c[u]*p0[v] - c[v]*p0[u]) / denom;		

        Point3 minPoint = Point3( std::min(p0[0], std::min(p1[0], p2[0])), std::min(p0[1], std::min(p1[1], p2[1])), std::min(p0[2], std::min(p1[2], p2[2])));
        Point3 maxPoint = Point3( std::max(p0[0], std::max(p1[0], p2[0])), std::max(p0[1], std::max(p1[1], p2[1])), std::max(p0[2], std::max(p1[2], p2[2])));
        mAABB = new AABB(minPoint, maxPoint);
    }

    Triangle::~Triangle(void)
    {
        delete mAABB;
    }

    bool Triangle::intersect(Ray& ray)
    {
        ////Walds method
#define ku modulo[mWaldTriangle.k+1]
#define kv modulo[mWaldTriangle.k+2]

        // don’t prefetch here, assume data has already been prefetched
        // start high-latency division as early as possible
        const float nd = 1.f/(ray.direction[mWaldTriangle.k]
        + mWaldTriangle.nu * ray.direction[ku] + mWaldTriangle.nv * ray.direction[kv]);
        const float f = (mWaldTriangle.nd - ray.origin[mWaldTriangle.k]
        - mWaldTriangle.nu * ray.origin[ku] - mWaldTriangle.nv * ray.origin[kv]) * nd;

        // check for valid distance.
        if (!(ray.t > f && f > EPSILON )) 
            return false;

        // compute hitpoint positions on uv plane
        const float hu = (ray.origin[ku] + f * ray.direction[ku]);
        const float hv = (ray.origin[kv] + f * ray.direction[kv]);

        // check first barycentric coordinate
        const float lambda = (hu * mWaldTriangle.bnu + hv * mWaldTriangle.bnv + mWaldTriangle.bd);
        if (lambda < 0.0f) 
            return false;

        // check second barycentric coordinate
        const float mue = (hu * mWaldTriangle.cnu + hv * mWaldTriangle.cnv + mWaldTriangle.cd);

        if (mue < 0.0f || lambda+mue > 1.0f) 
            return false;

        ray.t = f;
        ray.u = lambda;
        ray.v = mue;

        return true;
    }

    Shape* Triangle::getBounding()
    {
        return mAABB;
    }

    Point3 Triangle::getMin()
    {
        return mAABB->getMin();
    }

    Point3 Triangle::getMax()
    {
        return mAABB->getMax();
    }

    void Triangle::evaluate( Attribute* attr, RenderContext& rc )
    { 
        if( attr == RenderContext::POSITION )
        {
            Point3 rayOrigin = rc.getInput(RenderContext::RAY_ORIGIN).asPoint3();
            Vector3 rayDirection = rc.getInput(RenderContext::RAY_DIRECTION).asVector3();
            float rayLength = rc.getInput(RenderContext::RAY_LENGTH).asFloat();
            Point3 position = rayDirection * rayLength + rayOrigin;
            rc.setOutput(RenderContext::POSITION, position);
        }
        else if( attr == RenderContext::NORMAL )
        {
            Vector3 rayBarycentric = rc.getInput(RenderContext::RAY_BARYCENTRIC_COORDINATES).asVector3();
            Vector3 normal = Normalize(rayBarycentric.z * v0.normal + rayBarycentric.x * v1.normal + rayBarycentric.y * v2.normal);
            rc.setOutput(RenderContext::NORMAL, normal); 
        }
        else if( attr == RenderContext::TEXCOORD )
        {
            Vector3 rayBarycentric = rc.getInput(RenderContext::RAY_BARYCENTRIC_COORDINATES).asVector3();
            Vector3 texcoord = rayBarycentric.z * v0.texcoord + rayBarycentric.x * v1.texcoord + rayBarycentric.y * v2.texcoord;
            rc.setOutput(RenderContext::TEXCOORD, texcoord);
        }
        else if ( attr == RenderContext::SHADER_TO_WORLD )
        {
            Vector3 rayBarycentric = rc.getInput(RenderContext::RAY_BARYCENTRIC_COORDINATES).asVector3();
            Vector3 n = Normalize(rayBarycentric.z * v0.normal + rayBarycentric.x * v1.normal + rayBarycentric.y * v2.normal);
            Vector3 t = Normalize(v1.position - v0.position);
            Vector3 b = Cross(n,t);
            t = Cross(b,n);
            
            Matrix m( t.x, b.x, n.x, 0, t.y, b.y, n.y, 0, t.z, b.z, n.z, 0, 0, 0, 0, 1 );
            rc.setOutput(RenderContext::SHADER_TO_WORLD, m);
        }
        else if ( attr == RenderContext::WORLD_TO_SHADER )
        {
            Vector3 rayBarycentric = rc.getInput(RenderContext::RAY_BARYCENTRIC_COORDINATES).asVector3();
            Vector3 n = Normalize(rayBarycentric.z * v0.normal + rayBarycentric.x * v1.normal + rayBarycentric.y * v2.normal);
            Vector3 t = Normalize(v1.position - v0.position);
            Vector3 b = Cross(n,t);
            t = Cross(b,n);

            Matrix m( t.x, t.y, t.z, 0, b.x, b.y, b.z, 0, n.x, n.y, n.z, 0, 0, 0, 0, 1 );
            rc.setOutput(RenderContext::WORLD_TO_SHADER, m);
        }
    }

    void Triangle::sample(RenderContext& rc)
    {
        float r1 = Random();
        float r2 = Random();
        float m = sqrt(r1);

        float a = 1.0f - m;
        float b = (1.0f - r2) * m;
        float c = r2 * m;

        Point3 p0 = v0.position;
        Point3 p1 = v1.position;
        Point3 p2 = v2.position;

        float area = Length(Cross(p0,p1) + Cross(p1,p2) + Cross(p2,p0)) * 0.5f;
        
        rc.setOutput(RenderContext::POSITION, a * p0 + b * p1 + c * p2);
        rc.setOutput(RenderContext::NORMAL, a * v0.normal + b * v1.normal + c * v2.normal);
        rc.setOutput(RenderContext::TEXCOORD, a * v0.texcoord + b * v1.texcoord + c * v2.texcoord);
        rc.setOutput(RenderContext::SHADER, mShader);
        rc.setOutput(RenderContext::SHAPE, this);		
        rc.setOutput(RenderContext::PDF, 1.0f/area);
    }
}
