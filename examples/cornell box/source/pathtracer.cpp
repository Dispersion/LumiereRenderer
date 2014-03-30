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

#include "pathtracer.h"
#include <lumiererenderer\shader.h>
#include <lumiererenderer\radiometry.h>
#include <lumiererenderer\scene.h>
#include <lumiererenderer\scenetracer.h>

namespace LumiereRenderer
{
    PathTracer::PathTracer( int maxPathLength ) : mMaxPathLength(maxPathLength)
    {		
    }

    PathTracer::~PathTracer()
    {
    }

    float PathTracer::trace( Ray& ray, RenderContext* rc )
    {        
        int rayDepth = rc->GetInput(RenderContext::RAY_DEPTH).asInt();

        if (rayDepth == mMaxPathLength)
            return 0;

        if ( !rc->GetSceneTracer()->intersect( ray, rc ) )
        {			
            if ( rayDepth == 0 )
                ray.alpha = 0;
            return 0;
        }        
        
        if ( rayDepth == 0 )
            ray.alpha = 1;

        float radiance = 0;

        Point3 surfacePosition = rc->GetInput( Shape::POSITION ).asPoint3();
        Vector3 surfaceNormal = rc->GetInput( Shape::NORMAL ).asVector3();
       // Shader* surfaceShader = static_cast<Shader*>(rc->GetInput( RenderContext::SHADER ).AsPointer());
        Shader* surfaceShader = rc->GetInput( RenderContext::SHADER ).asShader();

        //if (Dot(Normalize(hit.normal), Normalize(-ray.direction)) > 0)
        {
            // Direct lighting
            // Sample a point on the emitter and find out if there are any obstruction between 
            // the point on the surface and the point on the emitter.
             
            rc->push();
            
            if ( rc->GetScene()->sampleEmitters( rc ) )
            {
                Point3 emitterPosition = rc->GetInput( Shape::POSITION ).asPoint3();
                
                if( !rc->GetSceneTracer()->intersect( surfacePosition, emitterPosition ) )
                {
                    Vector3 emitterNormal = rc->GetInput( Shape::NORMAL ).asVector3();
                    Shader* emitterShader = rc->GetInput( RenderContext::SHADER ).asShader();
                    float emitterPdf = rc->GetInput( RenderContext::PDF ).asFloat();          

                    Ray wi = Ray( surfacePosition, emitterPosition );   

                    DataHandle rayWavelength = rc->GetOutput(RenderContext::RAY_WAVELENGTH);
                    rayWavelength.set( ray.wavelength );
                    float emmittedRadiance = emitterShader->evaluate( rc, wi );
                    rc->pop();

                    radiance = ( surfaceShader->evaluate( rc, -wi ) * G( surfacePosition, emitterPosition, surfaceNormal, emitterNormal ) 
                        * emmittedRadiance ) / emitterPdf;
                }

                else
                {
                    rc->pop();
                }
            }
            else
            {
                rc->pop();
            }         

            // Indirect lighting
            if ( rayDepth == 0 || !surfaceShader->isEmitter() || ray.specular )
            {	
                float transmittance = 1;

                Shader* shader = rc->getCurrenShader();
                if ( shader )
                {
                    transmittance = shader->evaluate( rc, ray.origin, surfacePosition );
                }

                surfaceShader->evaluate( Shader::RADIANCE, rc );
                radiance += rc->GetOutput(Shader::RADIANCE).asFloat() * transmittance;				
            }
            else
            {
                surfaceShader->evaluate( Shader::RADIANCE, rc );
            }                       
        }

        return radiance;
    }
}