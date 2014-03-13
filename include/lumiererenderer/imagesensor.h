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
#include <lumiererenderer\point3.h>
#include <lumiererenderer\node.h>

namespace LumiereRenderer
{
	/// @class ImageSensor
	/// The image sensor is responsible for measuring the light at each pixel. This could
	/// be a CCD, CMOS, or a piece of film. 
	/// @brief A base class for an image sensor.	

	class ImageSensor : public Node
	{
	public:

		struct Pixel
		{
			float red;
			float green;
			float blue;
			float alpha;
		};

		/// @struct Sample
		/// @brief A sample from the the image sensor.
		struct Sample
		{	
			Point3 position; ///@var The position of the pixel in world coordinates. */
			float wavelength; /**< enum value 1 */
		};

	public:
		/// Constructor for an image sensor.
		/// @param width The width of the pixel area of the image sensor in meters.
		/// @param height The height of the pixel area of the image sensor in meters.
		/// @param resolutionWidth The number of pixel on the width of the sensor.
		/// @param resolutionHeight The number of pixel on the height of the sensor.
		ImageSensor(float width, float height, int resolutionWidth, int resolutionHeight);
		virtual ~ImageSensor();		

		/// Sample a point on the surface of the sensor. The sample contains both a [x,y] pixel coordinate
		/// of the sensor and the position of the sample in world coordinates.
		/// @return The sample function will return an ImageSensorSample.
		virtual ImageSensor::Sample sample(unsigned int i, unsigned int j) = 0;

		/// After we have traced a light ray through the scene, we save the resulting irradiance at a 
		/// pixel on the sensor. The position of the pixel is given in the ImageSensorSample.
		/// @param i
		/// @param j
		/// @param exposure Exposure is irradiance multiplied by shutterspeed in seconds.
		/// @param alpha Transparency of the first hit point.
		/// @param wavelength The wavelength of the ray of light.
		virtual void SetExposure(unsigned int i, unsigned int j, float exposure, float alpha, RenderContext* rc) = 0;

		/// Set the number of pixels on the width of the sensor.
		/// @param resolutionWidth The number of pixels.
		void SetResolutionWidth(int resolutionWidth);

		/// Get the number of pixels on the width of the sensor.
		/// @return The number of pixels.
		int GetResolutionWidth();

		/// Set the number of pixels on the height of the sensor.
		/// @param resolutionHeight The number of pixels.
		void SetResolutionHeight(int resolutionHeight);

		/// Get the number of pixels on the height of the sensor.
		/// @return The number of pixels.
		int GetResolutionHeight();

     	virtual void Evaluate( Attribute* attr, RenderContext* rc ) = 0;

		virtual ImageSensor::Pixel* Data() = 0;

	protected:        	
		int mResolutionWidth, mResolutionHeight;
		float mWidth, mHeight;	
		float mPixelWidth, mPixelHeight;
	};
}