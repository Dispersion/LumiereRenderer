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

#pragma once
#include <lumiererenderer\scene.h>
#include <lumiererenderer\Intersector.h>
#include <lumiererenderer\aabb.h>
#include <xmmintrin.h>
#include <stack>

namespace LumiereRenderer
{
	class SimdVector3
	{
	public:
		__m128 x, y, z;

		SimdVector3(Vector3 v)
		{
			x = _mm_set1_ps(v[0]);
			y = _mm_set1_ps(v[1]);
			z = _mm_set1_ps(v[2]);
		}

		SimdVector3(Point3 v)
		{
			x = _mm_set1_ps(v[0]);
			y = _mm_set1_ps(v[1]);
			z = _mm_set1_ps(v[2]);
		}

		SimdVector3(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
		{
			x = _mm_set_ps(v3[0], v2[0], v1[0], v0[0]);
			y = _mm_set_ps(v3[1], v2[1], v1[1], v0[1]);
			z = _mm_set_ps(v3[2], v2[2], v1[2], v0[2]);			
		}

		__m128& operator []( const unsigned int i )
		{
			return *(&x + i);
		}

		const __m128& operator []( const unsigned int i ) const
		{
			return *(&x + i);
		}
	};

	struct Node4
	{
		float max[3][4];
		float min[3][4];
		int child[4];
		int axis[4];
	};

	////////////////////////////////////////////////////////////////////////////////////
	///
	/// @class QBVH
	/// 
	/// 
	/// @brief Optimized scene structure.
	///
	////////////////////////////////////////////////////////////////////////////////////

	class QBVH : public Scene
	{
	public:
		QBVH(void);
		virtual ~QBVH(void);
		
		void FrameBegin();
		void FrameEnd();

		Intersector* getIntersector();

		std::vector<Node4*> mNodes;
		std::vector<Shape*> mBVH;

	private:
		int BuildHierarchy4( const std::vector<Shape*>& shapes );
		int SplitScene( const std::vector<Shape*>& primitives, std::vector<Shape*>& left, std::vector<Shape*>& right );
		int SplitRemaining( const std::vector<Shape*>& primitives, std::vector<Shape*>&child0, std::vector<Shape*>&child1, std::vector<Shape*>&child2, std::vector<Shape*>&child3 );
		float BuildMinMax( const std::vector<Shape*>& primitives, int& splitAxis, AABB& box);
		
		int mRoot;		
	};

    class QBVHTracer : public Intersector
	{
	public:
		QBVHTracer(QBVH* scene);
		virtual ~QBVHTracer(void);
        bool intersect(const Point3 from, const Point3 to);
        bool intersect(Ray& ray, RenderContext& rc);
		
	private:
		__m128 TraceAABB4( float far, const SimdVector3& origin, const SimdVector3& invRayDir, Node4* node) const;		
        std::vector<Node4*> mNodeStack;
		QBVH* mScene;
	};
}