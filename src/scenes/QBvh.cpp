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

#include "lumiererenderer\qbvh.h"
#include "lumiererenderer\constants.h"
#include <lumiererenderer\Geometry.h>
#include <stack>
#include <iostream>
#include <math.h>

using namespace std;

namespace LumiereRenderer
{
	QBVH::QBVH()
	{
	}


	QBVH::~QBVH()
    {
        std::vector<Node4*>::iterator node;
        for ( node = mNodes.begin(); node != mNodes.end();)
        {
            delete *node;  
            node = mNodes.erase(node);
        }

        std::vector<Shape*>::iterator shape;
        for ( shape = mBVH.begin(); shape != mBVH.end();)
        {
            delete *shape;  
            shape = mBVH.erase(shape);
        }
	}

	void QBVH::FrameBegin()
	{
		mRoot = BuildHierarchy4( mShapes );
	}

	void QBVH::FrameEnd()
	{
	}

    Intersector* QBVH::getIntersector()
	{		
		return new QBVHTracer(this);
	}

	int QBVH::BuildHierarchy4( const vector<Shape*>& shapes )
	{
		if ( shapes.size() == 0 )
		{
			return 1;
		}

		Node4* node = new Node4();        
        mNodes.push_back( node );        
        int index = mNodes.size();

		node->child[0] = 0;
		node->child[1] = 0;
		node->child[2] = 0;
		node->child[3] = 0;
		
		if ( shapes.size() <= 4 )
		{
			for(unsigned int n = 0; n < shapes.size(); n++)
			{				
				mBVH.push_back( shapes[n] );
				node->child[n] = -static_cast<int>(mBVH.size());
			}	

			return index;
		}

		vector<Shape*> child0;
		vector<Shape*> child1;
		vector<Shape*> child2;
		vector<Shape*> child3;

		if ( shapes.size() > 16)
		{
			vector<Shape*> left;
			vector<Shape*> right;
			node->axis[0] = SplitScene( shapes, left, right );

			node->axis[1] = SplitScene( left, child0, child1 );
			node->axis[2] = SplitScene( right, child2, child3 );
		}
		else
		{
			SplitRemaining( shapes, child0, child1, child2, child3 );
		}

		node->child[0] = BuildHierarchy4( child0 );
		node->child[1] = BuildHierarchy4( child1 );
		node->child[2] = BuildHierarchy4( child2 );
		node->child[3] = BuildHierarchy4( child3 );

		AABB box0 = AABB(child0);
		AABB box1 = AABB(child1);
		AABB box2 = AABB(child2);
		AABB box3 = AABB(child3);

        node->min[0][0] = box3.getMin()[0];
		node->min[0][1] = box2.getMin()[0];
		node->min[0][2] = box1.getMin()[0];
		node->min[0][3] = box0.getMin()[0];
		node->min[1][0] = box3.getMin()[1];
		node->min[1][1] = box2.getMin()[1];
		node->min[1][2] = box1.getMin()[1];
		node->min[1][3] = box0.getMin()[1];
		node->min[2][0] = box3.getMin()[2];
		node->min[2][1] = box2.getMin()[2];
		node->min[2][2] = box1.getMin()[2];
		node->min[2][3] = box0.getMin()[2];

		node->max[0][0] = box3.getMax()[0];
		node->max[0][1] = box2.getMax()[0];
		node->max[0][2] = box1.getMax()[0];
		node->max[0][3] = box0.getMax()[0];
		node->max[1][0] = box3.getMax()[1];
		node->max[1][1] = box2.getMax()[1];
		node->max[1][2] = box1.getMax()[1];
		node->max[1][3] = box0.getMax()[1];
		node->max[2][0] = box3.getMax()[2];
		node->max[2][1] = box2.getMax()[2];
		node->max[2][2] = box1.getMax()[2];
		node->max[2][3] = box0.getMax()[2];
		
		return index;
	}

	int QBVH::SplitScene( const vector<Shape*>& primitives, vector<Shape*>& left, vector<Shape*>& right )
	{
		if ( primitives.size() == 0 )
		{
			return 0;
		}

		AABB box = AABB(primitives);

		int splitAxis = 0;
		float split = BuildMinMax( primitives, splitAxis, box );		

		vector<Shape*> middle;
		vector<Shape*>::const_iterator primitive;
		for(primitive = primitives.begin(); primitive != primitives.end(); primitive++)
		{
            Shape* primitiveAABB = (*primitive)->getBounding();
            float min = primitiveAABB->getMin()[splitAxis];
            float max = primitiveAABB->getMax()[splitAxis];

			if ( max <= split ) 
			{
				left.push_back(*primitive);
			} 
			else if ( min >= split ) 
			{
				right.push_back(*primitive);
			}
			else
			{
				middle.push_back(*primitive);
			}
		}

		if ( middle.size() == 1 )
		{
			if ( left.size() > right.size() )
			{
				right.push_back( middle[0] );
			}
			else
			{
				left.push_back( middle[0] );
			}
		} 
		else 
		{
			unsigned int n;
			for( n = 0; n < middle.size()/2; n++)
			{
				left.push_back( middle[n] );
			}
			for( ; n < middle.size(); n++)
			{
				right.push_back( middle[n] );
			}
		}

		return splitAxis;
	}

	int QBVH::SplitRemaining( const std::vector<Shape*>& primitives, std::vector<Shape*>&child0, std::vector<Shape*>&child1, std::vector<Shape*>&child2, std::vector<Shape*>&child3 )
	{		
		for (unsigned int n = 0; n < primitives.size(); n++)
		{
			if (n < 4)
			{
				child0.push_back(primitives[n]);
			} 
			else if (n < 8)
			{
				child1.push_back(primitives[n]);
			}
			else if (n < 12)
			{
				child2.push_back(primitives[n]);
			}
			else 
			{
				child3.push_back(primitives[n]);
			}		
		}

		return -1;
	}


	float QBVH::BuildMinMax( const std::vector<Shape*>& primitives, int& splitAxis, AABB& box)
	{		
        Vector3 size = box.getMax() - box.getMin();

		vector<int> minimum;
		vector<int> maximum;
		minimum.assign(32,0);
		maximum.assign(32,0);

		int minsplit = primitives.size();
		int splitIndex = 0;

		for (int axis = 0; axis < 3; axis++)
		{			
			if (size[axis] > EPSILON)
			{
				int step = (int)log10((float)primitives.size());

				if (step < 1) step = 1;

				for (unsigned int n = 0; n < primitives.size(); n += step)
				{
					Shape* primitiveAABB = primitives[n]->getBounding();
                    float min = primitiveAABB->getMin()[axis];
					float max = primitiveAABB->getMax()[axis];
                    minimum[static_cast<int>((min-box.getMin()[axis])/size[axis]*31)]++;					
                    maximum[static_cast<int>((max-box.getMin()[axis])/size[axis]*31)]++;
				}

				int leftPrimitives = 0;
				int rightPrimitives = 0;

				for (int n = 0; n < 32; n++)
				{
					rightPrimitives += maximum[n];
				}

				for (int n = 0; n < 31; n++)
				{
					leftPrimitives += minimum[n];
					rightPrimitives -= maximum[n];

					if ( abs(leftPrimitives-rightPrimitives) < minsplit)
					{
						minsplit = abs(leftPrimitives-rightPrimitives);
						splitIndex = n;
						splitAxis = axis;
					}
				}
			}
		}

        float split = ((splitIndex+1)/32.f) * size[splitAxis] + box.getMin()[splitAxis];
		return split;
	}

	QBVHTracer::QBVHTracer(QBVH* scene) : mScene(scene)
	{
	}

	QBVHTracer::~QBVHTracer(void)
	{
	}

     bool QBVHTracer::intersect(const Point3 from, const Point3 to)
	{
		Ray ray;		
		ray.t = Length( to - from )-( EPSILON*20 );
		ray.direction = Normalize( to - from );
		ray.origin = from + ray.direction * EPSILON*10;

		if (mScene->mNodes.empty()) return NULL;

		SimdVector3 origin( ray.origin );		
		SimdVector3 invRayDir( 1.f/ray.direction );
				
		mNodeStack.push_back( mScene->mNodes[0] );

		while( !mNodeStack.empty() )
		{
			Node4* node = mNodeStack.back();
			mNodeStack.pop_back();

			if (node->child[0]>0 && node->child[1]>0 && node->child[2]>0 && node->child[3]>0)
			{
				__m128 hits = TraceAABB4(ray.t, origin, invRayDir, node);

				for (int i = 0; i < 4; i++)
				{
					int n = node->child[i]-1;
					if ( ( !hits.m128_f32[i] ) && n )
					{						
						mNodeStack.push_back( mScene->mNodes[n] );
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{	
					int child = (-node->child[i])-1;

					if ( child != -1 )
					{																	
                        if ( mScene->mBVH[child]->intersect(ray) )
						{		
							return true;
						}
					}
				}
			}			
		}
		return false;
	}

    bool QBVHTracer::intersect(Ray& ray, RenderContext& rc)
	{			
		Shape* hitShape = NULL;

		if (mScene->mNodes.empty()) return NULL;

		SimdVector3 origin( ray.origin );		
		SimdVector3 invRayDir( 1.f/ray.direction );
		
		mNodeStack.push_back( mScene->mNodes[0] );	    
		while( !mNodeStack.empty() )
		{
			Node4* node = mNodeStack.back();
			mNodeStack.pop_back();

			if (node->child[0]>0 && node->child[1]>0 && node->child[2]>0 && node->child[3]>0)
			{				
				__m128 hits = TraceAABB4(ray.t, origin, invRayDir, node);

				for (int i = 0; i < 4; i++)
				{
					int n = node->child[i]-1;
					if ( (!hits.m128_f32[i]) && n )
					{						
						mNodeStack.push_back( mScene->mNodes[n] );
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{	
					int child = (-node->child[i])-1;

					if ( child != -1 )
					{																	
                        if ( mScene->mBVH[child]->intersect(ray) )
						{				
							hitShape = mScene->mBVH[child];
						}
					}
				}
			}			
		}

		if (hitShape)
		{
			//hitShape->GetHitpoint(ray, hit);
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

	inline __m128 QBVHTracer::TraceAABB4( float far, const SimdVector3& origin, const SimdVector3& invRayDir, Node4* node) const
	{
		__m128 t0 = _mm_setzero_ps();
		__m128 res = _mm_setzero_ps();
		__m128 t1 = _mm_set1_ps(far);

		for (int i = 0; i < 3; ++i)
		{
			__m128 min = _mm_set_ps( node->min[i][0], node->min[i][1], node->min[i][2], node->min[i][3] );
			__m128 max = _mm_set_ps( node->max[i][0], node->max[i][1], node->max[i][2], node->max[i][3] );
			
			// float tNear = (node->min[i] - ray->origin[i]) * invRayDir;
			__m128 tNear = _mm_mul_ps( _mm_sub_ps( min, origin[i] ), invRayDir[i] );			 
			
			// float tFar = (node->max[i] - ray->origin[i]) * invRayDir;
			__m128 tFar = _mm_mul_ps( _mm_sub_ps( max, origin[i] ), invRayDir[i] );

			//if ( tNear > tFar) swap(tNear, tFar);
			__m128 mask = _mm_cmpgt_ps( tNear, tFar );
            __m128 nNear = _mm_blendv_ps( tNear, tFar, mask);
            __m128 nFar = _mm_blendv_ps( tFar, tNear, mask);

			//t0 = tNear > t0 ? tNear : t0;
            t0 = _mm_blendv_ps( t0, nNear, _mm_cmpgt_ps( nNear, t0 ));

			//t1 = tFar < t1 ? tFar : t1;
            t1 = _mm_blendv_ps( t1, nFar,  _mm_cmplt_ps( nFar, t1 ));

			//if ( t0 > t1 ) return false;
			res = _mm_or_ps( res, _mm_cmpgt_ps( t0, t1 ) );
		}

		return res;
	}
}