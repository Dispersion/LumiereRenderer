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

#include "blackbody.h"
#include <lumiererenderer\constants.h>
#include <lumiererenderer\attributevalue.h>

namespace LumiereRenderer
{
    BlackBody::BlackBody()
    {
        mTemperature = new AttributeValue<float>( "Temperature", 6500 ); ;
        mNormal = new AttributeValue<Vector3>( "Normal", 0 );
        mRayDirection = new AttributeValue<Vector3>( "RayDirection", 0 );
        mRayWavelength = new AttributeValue<float>( "RayWavelength", 0 );     

        AddAttribute( mTemperature );
        AddAttribute( mNormal );
        AddAttribute( mRayDirection );
        AddAttribute( mRayWavelength );
    }

    BlackBody::~BlackBody(void)
    {
    }

    float BlackBody::Evaluate(RenderContext* /*sc*/, const Point3& /*from*/, const Point3& /*to*/ )
    {
        return 1;
    }

    float BlackBody::Evaluate( RenderContext* rc, const Ray& /*wi*/ )
    {
        /*Vector3 wo = sc->Evaluate( mRayDirection ).AsVector3();
        float wavelength = sc->Evaluate( mRayWavelength ).AsFloat();

        if (Dot( from->normal, wi.direction ) < 0 )
            return 0;

        return GetRadiance(mT, wavelength);*/
        
        Vector3 normal = rc->GetInput( mNormal ).AsVector3();
        float wavelength = rc->GetInput( mRayWavelength ).AsFloat();
        float temperature = rc->GetInput( mTemperature ).AsFloat();
        
        /*if (Dot( normal, wi.direction ) < 0 )
            return 0;*/

        return GetRadiance(temperature, wavelength);
    }

    void BlackBody::Evaluate(Attribute* attr, RenderContext* rc)
    {	

        if (attr ==  Shader::RADIANCE || attr == NULL)
        {		
            /*if (Dot(hit->normal, -wo.direction) < 0 )
            {
                data.Set(0.0f);
                return data;
            }*/

            float wavelength = rc->GetInput( mRayWavelength ).AsFloat();
            float temperature = rc->GetInput( mTemperature ).AsFloat();

            DataHandle radiance = rc->GetOutput(  Shader::RADIANCE );
            radiance.Set( GetRadiance(temperature, wavelength) );
        }

    }

    float BlackBody::GetRadiance(float kelvin, float wavelength)
    {
        //Planck's constant in J*s
        float h = 6.6260696e-34f;
        //Speed of light in M/s
        float c = 299792458.f;
        //Wavelength in M
        float w = wavelength * 1e-9f;
        //Boltzmann's constant in J/K
        float k = 1.3806488e-23f;

//		float e = 2.71828182846f;

        float n0 = 8*PI*h*c;
        float n1 =  pow(w,5);
        float n2 = n0/n1;

        float m0 = exp((h*c) / (w*k*kelvin));
        float m1 = m0-1.0f;
        float m2 = 1.0f / m1;

        //Planck's law
        //float p = ((2*h*c*c) / pow(w,5)) * (1.0f / ( pow(e, (h*c) / (w*k*mT)) - 1.0f));

        return n2*m2;
    }


    bool BlackBody::DoEmit()
    {
        return true;
    }
}