////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012, LumiereRenderer
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

#include "lumiererenderer\aabb.h"

using namespace std;

namespace LumiereRenderer
{
	AABB::AABB(Point3 min, Point3 max) : mMin(min), mMax(max)
	{
	}

	AABB::AABB(const std::vector<Shape*>& primitives)
	{
		if (!primitives.empty())
		{
			Shape* bv = (*primitives.begin())->getBounding();
			mMin = bv->getMin();
			mMax = bv->getMax();
		}

		vector<Shape*>::const_iterator primitive;
		for(primitive = primitives.begin(); primitive != primitives.end(); primitive++)
		{
			Shape* bv = (*primitive)->getBounding();
			for (int axis = 0; axis < 3; axis++)
			{
				if(bv->getMax()[axis] > mMax[axis]) 
					mMax[axis] = bv->getMax()[axis];
				if(bv->getMin()[axis] < mMin[axis]) 
					mMin[axis] = bv->getMin()[axis];
			}
		}
	}

	AABB::~AABB(void)
	{
    }

    bool AABB::intersect( Ray& /*ray*/ )
    {
        // Todo
        return false;
    }

    Shape* AABB::getBounding()
    {
        return this;
    }

    Point3 AABB::getMin()
    {
        return mMin;
    }

    Point3 AABB::getMax()
    {
        return mMax;
    }

    void AABB::evaluate( Attribute* /*attr*/, RenderContext& /*rc*/ )
    {
        // Todo
    }

    void AABB::sample( RenderContext& /*rc*/ )
    {
        // Todo
    }
}
