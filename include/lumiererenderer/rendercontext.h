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

#include <lumiererenderer\DataHandle.h>
#include <stack>

namespace LumiereRenderer
{    
    // Forward declarations
    class Camera;
    class Integrator;
    class Scene;
    class SceneTracer;
    class Attribute;

    /*!
        @class RenderContext
        @brief Storage for data being transfered between nodes.

               The render context contains everything you need when rendering.
    */

    class RenderContext
    {
		    friend DataHandle;

    public:
            RenderContext(Scene* scene, Camera* camera, Integrator* integrator);
            ~RenderContext();

            void clear();
            DataHandle GetInput(Attribute* attribute);
            DataHandle GetOutput(Attribute* attribute);
  
            float Trace( Ray& ray );            
            Shader* getCurrenShader();

            Camera* GetCamera();
            Scene* GetScene();
            SceneTracer* GetSceneTracer();
            Integrator* GetIntegrator();

            /// The orgin of the current ray.
            static Attribute*           RAY_ORIGIN;
            
            /// The direction of the current ray.
            static Attribute*           RAY_DIRECTION;
            
            /// The wavelength of the current ray in nm.
            static Attribute*           RAY_WAVELENGTH;

            /// The number of bounces the ray has gone through.
            static Attribute*           RAY_DEPTH;

            /// The index of refraction of the material were moving through.   //TODO: verify this wild claim
            static Attribute*           RAY_IOR;

            /// The barycentric coordinates of the intersection between the ray and the shape it hit.
            static Attribute*           RAY_BARYCENTRIC_COORDINATES;

            /// The length of the ray.
            static Attribute*           RAY_LENGTH;
            
            /// ???
            static Attribute*           OUTER_IOR;
            
            /// The shader of the shape the ray intersected with.
            static Attribute*           SHADER;

            /// The shape the ray intersected with.
            static Attribute*           SHAPE;

            /// ???
            static Attribute*           PDF;
                        void push();
            void pop();
    private:
		    void* GetData(int index);
		    void SetData(int index, void* data, size_t size);
            void ResizeBuffer(size_t size);
            void ResizeHandles(size_t size);
            int  Find( Attribute* attribute );
            int  Allocate( Attribute* attribute );



            char*                       mData;
            int*                        mHandles;
            size_t                      mBufferSize;
            size_t                      mHandlesSize;
            int                         mNextDataAvailable;
            int                         mNextAvailable;
            int                         mCurrentBlock;

            Scene*                      mScene;
            SceneTracer*                mSceneTracer;
            Integrator*                 mIntegrator;
            Camera*                     mCamera;        
            std::stack<Shader*>         mShaderStack;    
    };
}
