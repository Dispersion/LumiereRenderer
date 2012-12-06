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

#include "ccd.h"
#include <math.h>

namespace LumiereRenderer
{
	CCD::CCD(float width, float height, int resolutionWidth, int resolutionHeight) : ImageSensor(width, height, resolutionWidth, resolutionHeight)
	{
		mPixelWidth = width / resolutionWidth;
		mPixelHeight = height / resolutionHeight;
	}

	CCD::~CCD(void)
	{
	}

	ImageSensorSample CCD::Sample()
	{
		static int i = 0;
		static int j = 0;

		ImageSensorSample sample = ImageSensorSample();
		sample.x = i;
		sample.y = j;
		sample.position = Point3((i - mResolutionWidth * 0.5f) * mPixelWidth, (j - mResolutionHeight * 0.5f) * mPixelHeight, 0);		

		i++;
		if (i >= mResolutionWidth)
		{
			i = 0;
			j++;
			if (j >= mResolutionHeight) 
			{
				j = 0;

				mCanvas->Done();
			}
		}

		return sample;
	}
	
	void CCD::SetIrradiance(const ImageSensorSample& sample, float irradiance)
	{
		switch (mCanvas->GetFormat())
		{
		case SENSOR_FORMAT_R32G32B32A32:
			{
				float* data = (float*)(mCanvas->GetData());
				data[sample.y * (mResolutionWidth*4) + (sample.x*4) + 0] = irradiance;
				data[sample.y * (mResolutionWidth*4) + (sample.x*4) + 1] = irradiance;
				data[sample.y * (mResolutionWidth*4) + (sample.x*4) + 2] = irradiance;
				data[sample.y * (mResolutionWidth*4) + (sample.x*4) + 3] = 1;
			}
		}
	}
}
