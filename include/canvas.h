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

namespace LumiereRenderer
{
	////////////////////////////////////////////////////////////////////////////////////
	///
	/// @enum SensorFormat
	/// @brief The sensor format tells the image sensor how it should output data to the canvas.	
	///
	////////////////////////////////////////////////////////////////////////////////////
    enum SensorFormat
	{
		SENSOR_FORMAT_BAYER32,
		SENSOR_FORMAT_BAYER8,		
		SENSOR_FORMAT_R32G32B32A32,		
		SENSOR_FORMAT_R32G32B32,
		SENSOR_FORMAT_R32G3,
		SENSOR_FORMAT_R32,
		SENSOR_FORMAT_R8G8B8A8,
		SENSOR_FORMAT_R8G8B8,
		SENSOR_FORMAT_R8G8,
		SENSOR_FORMAT_R8
	};

	////////////////////////////////////////////////////////////////////////////////////
	///
	/// @class Canvas
	/// The canvas is responsible for storing the data gathered by the image sensor
	/// and output it either to a screen or a file.
	/// @brief A base class for a canvas.	
	///
	////////////////////////////////////////////////////////////////////////////////////

	class Canvas
	{
	public:		
		Canvas(void);
		virtual ~Canvas();		
		/// The imagesensor calls Done when the frame is done.
		virtual void Done() = 0;
		/// An implementation of the the canvas needs to define how the data should be stored.
		/// The format should be set accordingly.
		/// @return A pointer to the image data.
		void* GetData();
		/// The Canvas defines the format of the image data.
		/// @return the format of the data.
		SensorFormat GetFormat();
	protected:
		void* mData;
		SensorFormat mFormat;
	};
}
