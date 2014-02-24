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

#include "ccd.h"
#include <lumiererenderer\random.h>
#include <lumiererenderer\attributevalue.h>

#include <iostream>

namespace LumiereRenderer
{
    CCD::CCD(float width, float height, int resolutionWidth, int resolutionHeight, float pixelAspect/*, Spectrum* red, Spectrum* green, Spectrum* blue*/) : ImageSensor(width, height, resolutionWidth, resolutionHeight)
    {
        if ( resolutionWidth > resolutionHeight )
        {
            mPixelWidth = width / resolutionWidth;
            mPixelHeight = mPixelWidth * pixelAspect;
        }
        else
        {
            mPixelHeight = height / resolutionHeight;
            mPixelWidth = mPixelHeight / pixelAspect;
        }      

        mRed = new AttributeValue<float>("Red", 0);
        mGreen = new AttributeValue<float>("Green", 0);
        mBlue = new AttributeValue<float>("Blue", 0);
        mExposure = new AttributeValue<float>("Exposure", 0);
        mSampleX = new AttributeValue<float>("SampleX", 0);
        mSampleY = new AttributeValue<float>("SampleY", 0);
        mPosition = new AttributeValue<float>("Position", 0);
        mRGBA = new AttributeValue<Vector4>("RGBA", 0);

        AddAttribute( mRed );
        AddAttribute( mGreen );
        AddAttribute( mBlue );
        AddAttribute( mExposure );
        AddAttribute( mSampleX );
        AddAttribute( mSampleY );
        AddAttribute( mPosition );
        AddAttribute( mRGBA );

        mSamples = new unsigned int[ resolutionWidth * resolutionHeight ];
        mImage = new RGBA[resolutionWidth * resolutionHeight];
        Clear();        
    }

    CCD::~CCD(void)
    {
    }

    ImageSensorSample CCD::Sample(unsigned int i, unsigned int j)
    {
        ImageSensorSample sample = ImageSensorSample();
        sample.x = i;
        sample.y = j;
        sample.position = Point3((((mResolutionWidth-i) - mResolutionWidth * 0.5f)+Random())  * mPixelWidth, (((mResolutionHeight-j) - mResolutionHeight * 0.5f)-Random()) * mPixelHeight, 0);
        sample.wavelength = 390+360*Random();
        return sample;
    }

    void CCD::SetExposure(const ImageSensorSample& sample, float exposure, float alpha, /*float wavelength,*/ RenderContext* rc)
    {
        float red = rc->GetInput( mRed ).AsFloat();
        float green = rc->GetInput( mGreen ).AsFloat();
        float blue = rc->GetInput( mBlue ).AsFloat();

        Vector3 c = std::max(0.0f, exposure) * Vector3( red, green, blue ) * 255;

        //Vector3 c = exposure * Vector3( mRed->GetIntensity(wavelength), mGreen->GetIntensity(wavelength), mBlue->GetIntensity(wavelength) )*255;
        int index = sample.y * mResolutionWidth + sample.x;

        unsigned int samples = mSamples[sample.y * mResolutionWidth + sample.x];
        RGBA L = mImage[index];

        
        if ( ( samples-1 ) != 0)
        {
            L.red *= (static_cast<float>(samples)-1.f);
            L.green *= (static_cast<float>(samples)-1.f);
            L.blue *= (static_cast<float>(samples)-1.f);
            L.alpha *= (static_cast<float>(samples)-1.f);
        }

        

        mImage[index].red = (L.red + c.x) / samples;
        mImage[index].green = (L.green + c.y) / samples;
        mImage[index].blue = (L.blue + c.z) / samples;
        mImage[index].alpha = (L.alpha + alpha*255) / samples;		

        mSamples[sample.y * mResolutionWidth + sample.x]++;
    }


    void CCD::Evaluate( Attribute* /*attr*/, RenderContext* rc )
    {                
        float red = rc->GetInput( mRed ).AsFloat();
        float green = rc->GetInput( mGreen ).AsFloat();
        float blue = rc->GetInput( mBlue ).AsFloat();
        int sampleX = rc->GetInput( mSampleX ).AsInt();
        int sampleY = rc->GetInput( mSampleY ).AsInt();
       
        rc->GetOutput(mPosition).Set( Point3((((mResolutionWidth-sampleX) - mResolutionWidth * 0.5f)+Random())  * mPixelWidth, (((mResolutionHeight-sampleY) - mResolutionHeight * 0.5f)-Random()) * mPixelHeight, 0));
        
        rc->Push();
        rc->GetOutput( RenderContext::RAY_WAVELENGTH ).Set( 390+360*Random() );        
        float exposure = rc->GetInput( mExposure ).AsFloat();
        rc->Pop();

        Vector3 c = exposure * Vector3( red, green, blue ) * 255;
        int index = sampleY * mResolutionWidth + sampleX;

        unsigned int samples = mSamples[sampleY * mResolutionWidth + sampleX];
        RGBA L = mImage[index];

        if ( ( samples-1 ) != 0)
        {
            L.red *= (static_cast<float>(samples)-1.f);
            L.green *= (static_cast<float>(samples)-1.f);
            L.blue *= (static_cast<float>(samples)-1.f);
            L.alpha *= (static_cast<float>(samples)-1.f);
        }



        mImage[index].red = (L.red + c.x) / samples;
        mImage[index].green = (L.green + c.y) / samples;
        mImage[index].blue = (L.blue + c.z) / samples;
       // mImage[index].alpha = (L.alpha + alpha*255) / samples;		

        mSamples[sampleY * mResolutionWidth + sampleX]++;

       // int index = sampleY * mResolutionWidth + sampleX;            
        //return mImage[index];

        rc->GetOutput( mRGBA ).Set( Vector4(mImage[index].red, mImage[index].green, mImage[index].blue, mImage[index].alpha) );
    }

    RGBA CCD::GetColor(unsigned int i, unsigned int j)
    {
        int index = j * mResolutionWidth + i;
        return mImage[index];
    }
    
    void CCD::Clear()
    {
        for(int i = 0; i < mResolutionWidth; i++)
        {
            for(int j = 0; j < mResolutionHeight; j++)
            {				
                mSamples[(j * mResolutionWidth + i)] = 1;
                mImage[(j * mResolutionWidth + i)].red = 0;
                mImage[(j * mResolutionWidth + i)].green = 0;
                mImage[(j * mResolutionWidth + i)].blue = 0;
                mImage[(j * mResolutionWidth + i)].alpha = 1;
            }
        }
    }
}