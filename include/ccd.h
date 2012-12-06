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
#include "imagesensor.h"

namespace LumiereRenderer
{
	////////////////////////////////////////////////////////////////////////////////////
	///
	///	@class CCD
	/// @brief An implementation of a Charge-coupled device
	/// The CCD captures the incomming light from the scene and uses a canvas to save
	/// the result.
	///
	////////////////////////////////////////////////////////////////////////////////////

	class CCD : public ImageSensor
	{
	public:
		/// Constructor for a CCD.
		/// @param width The width of the pixelarea on the ccd chip.
		/// @param height The height of the pixelarea on the ccd chip.
		/// @param resolutionWidth The number of pixels on the width of the ccd.
		/// @param resolutionHeight The number of pixels on the height of the ccd.
		CCD(float width, float height, int resolutionWidth, int resolutionHeight);
		virtual ~CCD(void);
		/// Sample a point on the surface of the sensor. The sample contains both a [x,y] pixel coordinate
		/// of the sensor and the position of the sample in world coordinates.
		/// @return The sample function will return an ImageSensorSample.
		virtual ImageSensorSample Sample();
		/// After we have traced a light ray through the scene, we save the resulting irradiance at a 
		/// pixel on the sensor. The position of the pixel is given in the ImageSensorSample.
		/// @param sample The position of the pixel we want to update.
		/// @param irradiance The irradiance value.
		virtual void SetIrradiance(const ImageSensorSample& sample, float irradiance);
	private:
		float mPixelWidth, mPixelHeight;
	};
}
