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

#include <lumiererenderer\list.h>
#include <lumiererenderer\constants.h>
#include <lumiererenderer\geometry.h>

namespace LumiereRenderer
{
    List::List(void)
    {
    }

    List::~List(void)
    {
    }

    Intersector* List::getIntersector()
    {
        return new ListTracer(this);
    }

    std::vector<Shape*>& List::getShapes()
    {
        return mShapes;
    }

    List::ListTracer::ListTracer(List* list) : mList(list)
    {
    }

    List::ListTracer::~ListTracer(void)
    {
    }

    bool List::ListTracer::intersect(const Point3 from, const Point3 to)
    {
        Ray ray;		
        ray.t = Length(to - from)-(EPSILON*20);
        ray.direction = Normalize(to - from);
        ray.origin = from + ray.direction * EPSILON*10;

        std::vector<Shape*>::const_iterator shape;
        for (shape = mList->getShapes().begin(); shape != mList->getShapes().end(); shape++)
        {
            if ((*shape)->intersect(ray) /*&& shape != to->shape*/)
            {
                return true;
            }
        }

        return false;
    }

    bool List::ListTracer::intersect(Ray& ray, RenderContext& rc)// const 
    {
        Shape* hitShape = NULL;

        std::vector<Shape*>::const_iterator shape;
        for (shape = mList->getShapes().begin(); shape != mList->getShapes().end(); shape++)
        {
            if ((*shape)->intersect(ray))
            {
                hitShape = *shape;
            }
        }		

        if (hitShape)
        {
            rc.setOutput(RenderContext::SHAPE, hitShape);
            rc.setOutput(RenderContext::SHADER, hitShape->getShader());
            rc.setOutput(RenderContext::RAY_BARYCENTRIC_COORDINATES, Vector3(ray.u, ray.v, (1-ray.u-ray.v)));
            rc.setOutput(RenderContext::RAY_LENGTH, ray.t);
            rc.setOutput(RenderContext::RAY_ORIGIN, ray.origin);
            rc.setOutput(RenderContext::RAY_DIRECTION, ray.direction);
            return true;
        }

        return false;
    }
}