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

#include <lumiererenderer\glass.h>

namespace LumiereRenderer
{
    Glass::Glass(float c1, float c2, float c3, float c4, float c5, float c6) : mC1(c1), mC2(c2), mC3(c3), mC4(c4), mC5(c5), mC6(c6)
    {
        mRayWavelength = createAttribute<float>("WoWavelength", 0);
        mIOR = createAttribute<float>("outIOR", 0);
    }

    Glass::~Glass(void)
    {
    }

    void Glass::evaluate(Attribute* attr, RenderContext& rc)
    {
        if (attr == mIOR)
        {
            float wavelength = rc.getInput( mRayWavelength ).asFloat();
            float wl = wavelength/1000.0f;
            float wl2 = wl*wl;	
            float ior = sqrt( (mC1*wl2)/(wl2-mC4) + (mC2*wl2)/(wl2-mC5) + (mC3*wl2)/(wl2-mC6) + 1);
            rc.setOutput(mIOR, ior);
        }
    }
}