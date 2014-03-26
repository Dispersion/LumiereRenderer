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
#include <lumiererenderer\Point3.h>
#include <lumiererenderer\Node.h>

namespace LumiereRenderer
{
    /*!
    @class ImageSensor
    @brief Converts incident light to an image.

    The heart of a camera is the image sensor. In an analog camera 
    the image sensor is typical some sort of photographic film. In 
    a digital camera there are mainly two types of image sensors; 
    the Charge-Coupled Device (CCD) and the Complementary Metal-Oxide 
    Semiconductor (CMOS). Both work in similar ways by converting the 
    incident light to a digital signal that can be saved in the memory 
    of the camera.

    Photographic film contains silver-halide cystals, which undergoes 
    an chemical reaction when exposed to light. On a CCD chip, a large 
    array of metal oxide semiconductors (photo-diodes) called photosites 
    convert the incident photons to an electric charge. After the 
    analog signal is created it is transferred to the analog-to-digital 
    converter (ADC). The output from the ADC, will be the brightness 
    value of a pixel in the final image.

    The spectral responsitivity of the system, is the relation between 
    the response of the image sensor and the incident light. In an CCD 
    chip, the spectral responsitivity is the factor between the incomming 
    photons and the electric current. if every photon generate an 
    electron, the 1 photon flux (photons per second) would generate 
    1 electron flux (electrons per second). However, when light 
    strikes the front of the image sensor, some of the photons will 
    be reflected of the surface. This means that not all the incident 
    light will be affect the image sensor. The percentage of photons 
    that will produce an electron, can be measure as the quantum efficiency. 
    Since the energy of a photon depend on its wavelength, the quantum 
    efficiency is measured over different wavelengths. 
    */

    class ImageSensor : public Node
    {
    public:

        /// @struct Pixel
        /// @brief The type of a pixel in an image.
        struct Pixel
        {
            float red;       ///< The red component of the pixel
            float green;     ///< The green component of the pixel
            float blue;      ///< The blue component of the pixel
            float alpha;     ///< The transparency of the pixel
        };

        /// @struct Sample
        /// @brief A sample from the the image sensor.
        struct Sample
        {	
            Point3 position;  ///< The position of the pixel in world coordinates.
            float wavelength; ///< Wavelength of the light given in nm.
        };

        /// Constructor for an image sensor.
        /// @param width The width of the pixel area of the image sensor in meters.
        /// @param height The height of the pixel area of the image sensor in meters.
        /// @param resolutionWidth The number of pixel on the width of the sensor.
        /// @param resolutionHeight The number of pixel on the height of the sensor.
        ImageSensor(float width, float height, int resolutionWidth, int resolutionHeight);

        /// Default destructor
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

        virtual void evaluate( Attribute* attr, RenderContext* rc ) = 0;

        virtual ImageSensor::Pixel* Data() = 0;

    protected:        	
        /// The number of pixels on the ???
        int                             mResolutionWidth;
        
        /// The number of pixels on the ???
        int                             mResolutionHeight;
        
        /// The width of the image sensor in meters.
        float                           mWidth;
        
        /// The height of the image sensor in meters.
        float                           mHeight;	
        
        // The width of a single pixel.
        float                           mPixelWidth;
        
        // The height of a single pixel.
        float                           mPixelHeight;
    };
}