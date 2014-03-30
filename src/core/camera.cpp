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

#include <lumiererenderer\Camera.h>
#include <lumiererenderer\LinearAlgebra.h>

namespace LumiereRenderer
{	
	Camera::Camera()
	{
		mImageSensor = 0;
	}

	Camera::~Camera()
	{
		if (mImageSensor)
		{
			delete mImageSensor;
		}

	}
	
	void Camera::setImageSensor(ImageSensor* sensor)
	{
		mImageSensor = sensor;
	}

	ImageSensor* Camera::getImageSensor()
	{
		return mImageSensor;
	}

	void Camera::setPosition( Point3 position )
	{		
		mTransform[0][3] = position[0];
		mTransform[1][3] = position[1];
		mTransform[2][3] = position[2];
	}

	Point3 Camera::getPosition()
	{
		return Point3(mTransform[0][3], mTransform[1][3], mTransform[2][3]);
	}

	void Camera::setViewDirection( Vector3 viewDirection )
	{
		viewDirection = Normalize(viewDirection);
		Vector3 right = Normalize( Cross( getUpDirection(), viewDirection ) );

		mTransform[0][2] = viewDirection[0];
		mTransform[1][2] = viewDirection[1];
		mTransform[2][2] = viewDirection[2];
		
		mTransform[0][0] = right[0];
		mTransform[1][0] = right[1];
		mTransform[2][0] = right[2];
	}

	Vector3 Camera::getViewDirection()
	{
		return Vector3(mTransform[0][2], mTransform[1][2], mTransform[2][2]);
	}

	void Camera::setUpDirection( Vector3 upDirection )
	{
		upDirection = Normalize(upDirection);
		Vector3 right = Cross(getViewDirection(), upDirection);

		mTransform[0][1] = upDirection[0];
		mTransform[1][1] = upDirection[1];
		mTransform[2][1] = upDirection[2];
		
		mTransform[0][0] = right[0];
		mTransform[1][0] = right[1];
		mTransform[2][0] = right[2];
	}

	Vector3 Camera::getUpDirection()
	{
		return Vector3(mTransform[0][1], mTransform[1][1], mTransform[2][1]);
	}
}