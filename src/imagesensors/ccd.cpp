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

#include <lumiererenderer\ccd.h>
#include <lumiererenderer\random.h>

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

        mRed = createAttribute<float>("Red", 0);
        mGreen = createAttribute<float>("Green", 0);
        mBlue = createAttribute<float>("Blue", 0);
        mExposure = createAttribute<float>("Exposure", 0);
        mSampleX = createAttribute<float>("SampleX", 0);
        mSampleY = createAttribute<float>("SampleY", 0);
        mPosition = createAttribute<float>("Position", 0);
        mRGBA = createAttribute<Vector4>("RGBA", 0);

        /*AddAttribute( mRed );
        AddAttribute( mGreen );
        AddAttribute( mBlue );
        AddAttribute( mExposure );
        AddAttribute( mSampleX );
        AddAttribute( mSampleY );
        AddAttribute( mPosition );
        AddAttribute( mRGBA );*/

        mSamples = new unsigned int[ resolutionWidth * resolutionHeight ];
        mImage = new Pixel[resolutionWidth * resolutionHeight];
        clear();        
    }

    CCD::~CCD(void)
    {
        delete mRed;
        delete mGreen;
        delete mBlue;
        delete mExposure;
        delete mSampleX;
        delete mSampleY;
        delete mPosition;
        delete mRGBA;

        delete[] mSamples;
        delete[] mImage;   
    }

    ImageSensor::Sample CCD::sample(unsigned int i, unsigned int j)
    {
        ImageSensor::Sample _sample = ImageSensor::Sample();
        _sample.position = Point3((((mResolutionWidth-i) - mResolutionWidth * 0.5f)+Random())  * mPixelWidth, (((mResolutionHeight-j) - mResolutionHeight * 0.5f)-Random()) * mPixelHeight, 0);
        _sample.wavelength = 390+360*Random();
        return _sample;
    }

    void CCD::setExposure(unsigned int i, unsigned int j, float exposure, float alpha, RenderContext& rc)
    {
        float red = rc.getInput( mRed ).asFloat();
        float green = rc.getInput( mGreen ).asFloat();
        float blue = rc.getInput( mBlue ).asFloat();

        Vector3 c = std::max(0.0f, exposure) * Vector3( red, green, blue ) * 255;

        //Vector3 c = exposure * Vector3( mRed->GetIntensity(wavelength), mGreen->GetIntensity(wavelength), mBlue->GetIntensity(wavelength) )*255;
        int index = j * mResolutionWidth + i;

        unsigned int samples = mSamples[j * mResolutionWidth + i];
        Pixel L = mImage[index];

        
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

        mSamples[j * mResolutionWidth + i]++;
    }

	void CCD::evaluate( Attribute* /*attr*/, RenderContext& /*rc*/ )
	{
	}

	CCD::Pixel* CCD::getData()
	{
		return &mImage[0];
	}
    
    void CCD::clear()
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
