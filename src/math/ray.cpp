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

#include <lumiererenderer\ray.h>
#include <lumiererenderer\constants.h>
#include <lumiererenderer\geometry.h>

namespace LumiereRenderer
{	
    Ray::Ray() : origin( 0 ), direction( 0, 0, 1 )
    {
        t = INFINITY;
        specular = false;
        transmission = false;
        entered = false;
        exited = false;
    }

    Ray::Ray( Point3 origin, Vector3 direction ) : origin(origin)
    {		
        this->direction = Normalize(direction);
        t = INFINITY;
        specular = false;
        transmission = false;
        entered = false;
        exited = false;
    }

    Ray::Ray( Point3 a, Point3 b )
    {
        origin = a;
        direction = Normalize(b-a);
        t = INFINITY;
        specular = false;
        transmission = false;
        entered = false;
        exited = false;
    }

    Ray::~Ray()
    {
    }

    Ray Ray::operator-()
    {
        return Ray(origin, -direction);
        
    }
}
