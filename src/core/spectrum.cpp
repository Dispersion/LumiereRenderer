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

#include <lumiererenderer\Spectrum.h>
#include <lumiererenderer\Geometry.h>
#include <lumiererenderer\AttributeValue.h>

namespace LumiereRenderer
{
    Spectrum::Spectrum()
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] = 0;
        }        

        mRayWavelength = createAttribute<float>("RayWavelength", 0);
        aOutColor = createAttribute<float>("outColor", 0);		

        //AddAttribute( mRayWavelength );
        //AddAttribute( aOutColor );
    }

    Spectrum::Spectrum(float* wavelength, float* intensity, unsigned int size)
    {	
        float w1 = wavelength[0];
        float i1 = intensity[0];
        unsigned int i = 0;
        
        for (int n = 0; n < 37; n++)
        {
            float w = (n*10.0f+390.0f);

            if (w < w1)
            {
                mIntensity[n] = 0;
                continue;
            }
            
            while(i < size)
            {
                if (w <= wavelength[i])
                {
                    float w2 = wavelength[i];
                    float i2 = intensity[i];

                    if (w == w1)
                    {
                        mIntensity[n] = i1;
                        break;
                    }

                    if (w == w2)
                    {
                        mIntensity[n] = i2;
                        break;
                    }

                    float weight = (w-w1)/(w2 - w1);
                    mIntensity[n] = Lerp(i1, i2, weight);
                    break;
                }
                w1 = wavelength[i];
                i1 = intensity[i];
                i++;
            }

            if (i+1 > size)
            {
                mIntensity[n] = 0;
                continue;
            }
        }

        mRayWavelength = createAttribute<float>("RayWavelength", 0);
        aOutColor = createAttribute<float>("outColor", 0);		

        //AddAttribute( mRayWavelength );
        //AddAttribute( aOutColor );
    }

    Spectrum::~Spectrum()
    {
    }

    void Spectrum::evaluate( Attribute* attr, RenderContext* rc )
    {	
        if (attr == aOutColor)
        {
            float wavelength = rc->GetInput( mRayWavelength ).AsFloat();

            DataHandle outColor = rc->GetOutput(aOutColor);
            outColor.Set( GetIntensity(wavelength) );
        }
    }


    /*float& Spectrum::operator[]( const unsigned int i )
    {
        return mIntensity[i];
    }

    const float& Spectrum::operator[]( const unsigned int i ) const
    {
        return mIntensity[i];
    }*/



    float Spectrum::GetIntensity( float wavelength )
    {
        float i = (wavelength - 390.0f) / 10;

            int a = (int)floor(i);
            int b = (int)ceil(i);
            float w = i - a;

            return mIntensity[a] + (mIntensity[b] - mIntensity[a]) * w;
    }

    /*void Spectrum::operator*(float scalar)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] *= scalar;
        }
    }*/
    
  /*  Spectrum Spectrum::operator+(const Spectrum& b) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] + b[n];
        }
        return ret;
    }

    Spectrum Spectrum::operator-(const Spectrum& b) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] - b[n];
        }
        return ret;
    }

    Spectrum Spectrum::operator*(const Spectrum& b) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] * b[n];
        }
        return ret;
    }

    Spectrum Spectrum::operator/(const Spectrum& b) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] / b[n];
        }
        return ret;
    }

    Spectrum& Spectrum::operator+=(const Spectrum& b)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] += b[n];
        }
        return *this;
    }

    Spectrum& Spectrum::operator-=(const Spectrum& b)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] -= b[n];
        }
        return *this;
    }

    Spectrum& Spectrum::operator*=(const Spectrum& b)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] *= b[n];
        }
        return *this;
    }

    Spectrum& Spectrum::operator/=(const Spectrum& b)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] /= b[n];
        }
        return *this;
    }

    Spectrum Spectrum::operator+(float s) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] + s;
        }
        return ret;
    }

    Spectrum Spectrum::operator-(float s) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] - s;
        }
        return ret;
    }

    Spectrum Spectrum::operator*(float s) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] * s;
        }
        return ret;
    }

    Spectrum Spectrum::operator/(float s) const
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = mIntensity[n] / s;
        }
        return ret;
    }

    Spectrum& Spectrum::operator+=(float s)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] += s;
        }
        return *this;
    }

    Spectrum& Spectrum::operator-=(float s)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] -= s;
        }
        return *this;
    }

    Spectrum& Spectrum::operator*=(float s)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] *= s;
        }
        return *this;
    }

    Spectrum& Spectrum::operator/=(float s)
    {
        for (int n = 0; n < 37; n++)
        {
            mIntensity[n] /= s;
        }
        return *this;
    }

    Spectrum operator+(float s, Spectrum spectrum)
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = s + spectrum[n];
        }
        return ret;
    }

    Spectrum operator-(float s, Spectrum spectrum)
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = s - spectrum[n];
        }
        return ret;
    }

    Spectrum operator*(float s, Spectrum spectrum)
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = s * spectrum[n];
        }
        return ret;
    }

    Spectrum operator/(float s, Spectrum spectrum)
    {
        Spectrum ret;
        for (int n = 0; n < 37; n++)
        {
            ret[n] = s / spectrum[n];
        }
        return ret;
    }*/

    Spectrum* RGBToSpectrum(float /*r*/, float /*g*/, float /*b*/)
    {
        float wavelength[] = {380, 418, 456, 494, 532, 570, 608, 646, 684, 720};

        float white[] = {1.0000f, 1.0000f, 0.9999f, 0.9993f, 0.9992f, 0.9998f, 1.0000f, 1.0000f, 1.0000f, 1.0000f};
        float cyan[] = {0.9710f, 0.9426f, 1.0007f, 1.0007f, 1.0007f, 1.0007f, 0.1564f, 0.0000f, 0.0000f, 0.0000f};
        float magenta[] = {1.0000f, 1.0000f, 0.9685f, 0.2229f, 0.0000f, 0.0458f, 0.8369f, 1.0000f, 1.0000f, 0.9959f};
        float yellow[] = {0.0001f, 0.0000f, 0.1088f, 0.6651f, 1.0000f, 1.0000f, 0.9996f, 0.9586f, 0.9685f, 0.9840f};
        float red[] = {0.1012f, 0.0515f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.8325f, 1.0149f, 1.0149f, 1.0149f};
        float green[] = {0.0000f, 0.0000f, 0.0273f, 0.7937f, 1.0000f, 0.9418f, 0.1719f, 0.0000f, 0.0000f, 0.0025f};
        float blue[] = {1.0000f, 1.0000f, 0.8916f, 0.3323f, 0.0000f, 0.0000f, 0.0003f, 0.0369f, 0.0483f, 0.0496f};

        Spectrum whiteSpectrum   = Spectrum(wavelength, white, 10);
        Spectrum cyanSpectrum    = Spectrum(wavelength, cyan, 10);
        Spectrum magentaSpectrum = Spectrum(wavelength, magenta, 10);
        Spectrum yellowSpectrum  = Spectrum(wavelength, yellow, 10);
        Spectrum redSpectrum     = Spectrum(wavelength, red, 10);
        Spectrum greenSpectrum   = Spectrum(wavelength, green, 10);
        Spectrum blueSpectrum    = Spectrum(wavelength, blue, 10);
        
        Spectrum* ret = new Spectrum();
      //  *ret = redSpectrum * r + greenSpectrum * g + blueSpectrum * b;

        return ret;


        //Spectrum ret;
        /*if (r <= g && r <= b)
        {
            ret += r* whiteSpectrum;

            if(green <= blue)
            {
                ret += (green - red) * cyanSpectrum;
                ret += (blue - green) * blueSpectrum;
            }
            else
            {
                ret += (blue - red) * cyanSpectrum;
                ret += (green - blue) * greenSpectrum;
            }
        }
*/

        //return ret;
    }

}