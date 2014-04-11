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

#include <lumiererenderer\RenderContext.h>
#include <lumiererenderer\Integrator.h>
#include <lumiererenderer\Scene.h>
#include <lumiererenderer\AttributeValue.h>

namespace LumiereRenderer
{
    Attribute* RenderContext::RAY_ORIGIN = new AttributeValue<Point3>("RayOrigin", 0);
    Attribute* RenderContext::RAY_DIRECTION = new AttributeValue<Vector3>("RayDirection", 0);
//    Attribute* RenderContext::RAY_WAVELENGTH = new AttributeValue<float>("RayWavelength", 0);
    Attribute* RenderContext::TRACE_DEPTH = new AttributeValue<int>("RayDepth", 0);
//    Attribute* RenderContext::RAY_IOR = new AttributeValue<float>("RayIOR", 0);
    Attribute* RenderContext::RAY_BARYCENTRIC_COORDINATES = new AttributeValue<Point3>("RayBarycentricCoordinates", 0);
    Attribute* RenderContext::RAY_LENGTH = new AttributeValue<float>("RayLength", 0);
    
    Attribute* RenderContext::WO_DIRECTION = new AttributeValue<Vector3>("WoDirection", 0);
    Attribute* RenderContext::WO_WAVELENGTH = new AttributeValue<float>("WoWavelength", 0);    
    Attribute* RenderContext::WO_IOR = new AttributeValue<float>("WoIor", 0);
    Attribute* RenderContext::WO_PDF = new AttributeValue<float>("WoPdf", 0);

    Attribute* RenderContext::WI_DIRECTION = new AttributeValue<Vector3>("WiDirection", 0);
    Attribute* RenderContext::WI_WAVELENGTH = new AttributeValue<float>("WiWavelength", 0);    
    Attribute* RenderContext::WI_IOR = new AttributeValue<float>("WiIor", 0);
    Attribute* RenderContext::WI_PDF = new AttributeValue<float>("WiPdf", 0);

    Attribute* RenderContext::SHADER = new AttributeValue<Shader*>("Shader", 0);
    Attribute* RenderContext::SHAPE = new AttributeValue<Shape*>("Shape", 0);
    Attribute* RenderContext::PDF = new AttributeValue<float>("Pdf", 0);

    RenderContext::RenderContext(Scene* scene, Camera* camera, Integrator* integrator) : mScene(scene), mCamera(camera), mIntegrator(integrator)
    {
        mBufferSize = 128;
        mHandlesSize = 128;
        mNextAvailable = 0;
        mCurrentBlock = 0;
        mNextDataAvailable = 0;
        mData = new char[mBufferSize];
        mHandles = new int[mHandlesSize];
        mSceneTracer = scene->getSceneTracer();
        push();
    }

    RenderContext::~RenderContext(void)
    {
        pop();
        delete []mData;
    }

    void RenderContext::clear()
    {
        mNextAvailable = 0;
        mCurrentBlock = 0;
        mNextDataAvailable = 0;
    }

    DataHandle RenderContext::GetInput(Attribute* attribute)
    {
        Attribute* connection = attribute->getConnection();

        // Test to see if the attribute is connected to anything
        if ( connection )
        {
            // We have a connection to something, so let us find out if
            // the result is cached.
            int index = Find(connection);
            if ( index != -1 )
            {
                return DataHandle( this, index );
            }
            else
            {   
                if (connection->getOwner())
                {
                    connection->getOwner()->evaluate( connection, this );
                    index = Find( connection );
                    if ( index != -1 )
                    {
                        return DataHandle( this, index );
                    }
                }
                else
                {
                    // We have a connection to one of the default attributes
                    // We have to send the request to the shape to get the result.

                    index = Find(SHAPE);
                    (static_cast<Shape**>(GetData(index)))[0]->evaluate( connection, this );
                    index = Find( connection );
                    if ( index != -1 )
                    {
                        return DataHandle( this, index );
                    }
                }
            }        
        }

        // The attribute did not have any connection, so we will use the default value.
        int index = Find(attribute);
        if ( index != -1 )
        {
            // The attribute value have already been calculated, we just have to return it.
            return DataHandle(this, index);
        }
        else
        {
            // We have to find out if it is a value such as position or normal, that is computed by
            // the shape.
            index = Find(SHAPE);
            (static_cast<Shape**>(GetData(index)))[0]->evaluate( attribute, this );
            index = Find( attribute );
            if ( index != -1 )
            {
                return DataHandle( this, index );
            }
            else
            {
                // Since the shape could not calculate the value of this attribute, we use
                // the default value of the attribute.
                index = Allocate(attribute);
                memcpy(mData+index, attribute->getDefaultValue(), attribute->getSize());
                return DataHandle(this, index);
            }
        }
    }

    DataHandle RenderContext::GetOutput(Attribute* attribute)
    {
        int index = Find(attribute);

        if( index == -1 )
        {
            index = Allocate(attribute);
        }

        return DataHandle(this, index);   
    }
	
    void* RenderContext::GetData(int index)
    {
        return &mData[index];
    }

    void RenderContext::SetData(int index, void* data, size_t size)
    {
        memcpy(mData+index, data, size);
    }

    void RenderContext::ResizeBuffer( size_t size )
    {
        if( size > mBufferSize )
        {            
            while( mBufferSize < size )
            {
                mBufferSize *= 2;
            }

            char* data = new char[mBufferSize];
            memcpy( data, mData, mNextDataAvailable );
            delete[] mData;
            mData = data;
        }
    }

    void RenderContext::ResizeHandles( size_t size )
    {
        if( size > mHandlesSize )
        {            
            while( mHandlesSize < size )
            {
                mHandlesSize *= 2;
            }

            int* data = new int[mHandlesSize];
            memcpy( data, mHandles, mNextAvailable*4 );
            delete[] mHandles;
            mHandles = data;
        }
    }

    int RenderContext::Find( Attribute* attribute)
    {
        for(int n = mCurrentBlock; n < mNextAvailable; n += 2)
        {
            if ( attribute == reinterpret_cast<Attribute*>(mHandles[n]) )
            {
                return mHandles[n+1];
            }        
        }

        return -1;
    }

    int RenderContext::Allocate( Attribute* attribute )
    {
        ResizeHandles( mNextAvailable + 2 );

        int index = mNextDataAvailable;
        mHandles[mNextAvailable++] = reinterpret_cast<int>(attribute);
        mHandles[mNextAvailable++] = index;

        mNextDataAvailable += attribute->getSize();

        // If we are going to use more memory than allocated for the
        // data buffer, we have to resize it.
        ResizeBuffer( mNextDataAvailable );
        return index;
    }

    void RenderContext::push()
    {
        ResizeHandles( mNextAvailable + 1 );
        mHandles[mNextAvailable] = mCurrentBlock;
        mCurrentBlock = ++mNextAvailable;
    }

    void RenderContext::pop()
    {
        if( mCurrentBlock != mNextAvailable )
        {
            mNextDataAvailable = mHandles[mCurrentBlock+1];
        }
        mNextAvailable = mCurrentBlock-1;
        mCurrentBlock = mHandles[mCurrentBlock-1];
    }

    float RenderContext::Trace( Ray& ray )
    {        
        // When the trace function is called, we send the request to the integrator,
        // but first we have to push the current shader onto the shader stack. The
        // reason is that if we move through a glass object, and we exit on the other 
        // side, we can find the shader that was used before we entered glass object,
        // by looking in the shader stack.

       
        Shader* top = NULL;

        // If the ray enters an object, like a glass sphere, we push the glass shader
        // onto the shader stack. If the ray exits the glass sphere, we pop the glass
        // shader from the stack. 

        if (ray.entered)		
        {
           // mShaderStack->push( mHitPoint->shader );
           //Shader* shader = static_cast<Shader*>(GetInput( RenderContext::SHADER ).AsPointer());
            Shader* shader = GetInput( RenderContext::SHADER ).asShader();
            mShaderStack.push( shader );
        }

        if (ray.exited)
        {
            if ( !mShaderStack.empty() )
            {
                top = mShaderStack.top();
                mShaderStack.pop();
            }
        }


        int rayDepth = GetInput(TRACE_DEPTH).asInt();
        // Use the assigned integrator, to trace the ray.
        this->push();

        GetOutput(TRACE_DEPTH).set(rayDepth+1);

        float radiance = mIntegrator->trace( ray, this );
        this->pop();

        // Some shaders can shoot out more than one ray, e.g. a glass shader could shoot 
        // out a ray in the reflected and the refracted direction. Since we only have one
        // shaderstack for each integrator, the two rays uses the same one. We have to make
        // sure, that the first ray does not change the shader stack before we shoot out
        // next one. We do that by always reversing the last action to the stack, after we 
        // are done tracing that ray.

        if (ray.entered)		
        {
            mShaderStack.pop();
        }

        if (ray.exited && top)
        {
            mShaderStack.push( top );
        }

        return radiance;  
    }

    /*std::stack<Shader*>* RenderContext::GetShaderStack()
    {
        return &mShaderStack;
    }*/

    Shader* RenderContext::getCurrenShader()
    {
        if( mShaderStack.empty() )
        {
            return NULL;
        }
        
        return mShaderStack.top();
    }

    Camera* RenderContext::GetCamera()
    {
        return mCamera;
    }

    Scene* RenderContext::GetScene()
    {
        return mScene;
    }

    SceneTracer* RenderContext::GetSceneTracer()
    {
        return mSceneTracer;
    }

    Integrator* RenderContext::GetIntegrator()
    {
        return mIntegrator;
    }
}
