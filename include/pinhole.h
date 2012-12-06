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
#include "geometry.h"
#include "camera.h"

namespace LumiereRenderer
{
	////////////////////////////////////////////////////////////////////////////////////
	///
	///	@class Pinhole
	/// @brief A pinhole camera.
	///
	////////////////////////////////////////////////////////////////////////////////////

	class Pinhole : public Camera
	{
	public:
		/// Constructor for a pinhole camera.
		/// @param focalLength The distance from the image sensor to to the pinhole, given in meters.
		Pinhole(float focalLength);
		/// Destructor for a pinhole camera.
		virtual ~Pinhole();
		/// Generate a ray that goes in the direction of the  starts at the pinhole.
		/// @param imageSensorSample A sample from the image sensor.
		/// @return A ray that starts at the pinhole, with a direction that goes through a point on the imagesensor and the pinhole.
		Ray GenerateRay(const ImageSensorSample& imageSensorSample);		
		/// Set the focal length to a new value.
		/// @param length The distance from the image sensor to the pinhole, given in meters.
		void SetFocalLength(float length);
		/// Get the focal length.
		/// @return The distance from the image sensor to the pinhole, given in meters.
		float GetFocalLength();

	private:
		float mFocalLength;
		Point3 mPinhole;
	};
}