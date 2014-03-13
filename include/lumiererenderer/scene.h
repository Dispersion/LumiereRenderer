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
#include <vector>
#include <lumiererenderer\shape.h>

namespace LumiereRenderer
{
    class SceneTracer;

    ////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @class Scene
    /// The scene is a datastructure for all the objects that can be rendered. The scene
    /// can use an optimized structure such as a BVH, KD-tree or a use simple list, to
    /// store a reference to all the objects in the scene.
    /// The scene is shared among threads and can not be changed during rendering. This
    /// means that the scene can not hold temporary data during rendering such as which
    /// object was hit in the last intersection test. Instead each scene, must implement 
    /// a SceneTracer, which can hold the temporary data. Each thread during rendering will
    /// have it's own SceneTracer.
    /// @brief A data structure for storing objects.
    ///
    ////////////////////////////////////////////////////////////////////////////////////

    class Scene
    {
    public:
        Scene(void);
        virtual ~Scene(void);
        virtual void AddShape(Shape* shape);
        virtual bool SampleEmitters(RenderContext* rc) const;
        virtual SceneTracer* GetSceneTracer() = 0;		

    protected:
        std::vector<Shape*> mShapes; 
        std::vector<Shape*> mEmitters;
    };
}