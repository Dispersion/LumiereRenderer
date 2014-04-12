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

#include <lumiererenderer\Attribute.h>
#include <lumiererenderer\Node.h>

namespace LumiereRenderer
{
    

    Attribute::~Attribute(void)
    {
    }

    Attribute& Attribute::operator=(Attribute& attribute)
    {
        if( mWriteable && attribute.isReadable() )
        {
            mConnection = &attribute;
        }
        return *this;
    }

    Attribute* Attribute::getConnection() const
    {
        return mConnection;
    }

    std::string Attribute::getName() const
    {
        return mName;
    }

    /** Attribute::getDefaultValue() const
    {
        return mDefaultValue;
    }*/


    void* Attribute::getDefaultValue() const
    {
        return mAttribute->getValue();
    }

    size_t Attribute::getSize() const    
    {
        return mAttribute->getSize();
    }

    void Attribute::connect(Attribute* attribute)
    {
        mConnection = attribute;
    }

    void Attribute::setOwner(Node* node)
    {
        mOwner = node;
    }

    Node* Attribute::getOwner() const
    {
        return mOwner;
    }

    void Attribute::setReadable(bool readable)
    {
        mReadable = readable;
    }

    void Attribute::setWriteable(bool writeable)
    {
        mWriteable = writeable;
    }

    bool Attribute::isReadable()
    {
        return mReadable;
    }

    bool Attribute::isWriteable()
    {
        return mWriteable;
    }
}