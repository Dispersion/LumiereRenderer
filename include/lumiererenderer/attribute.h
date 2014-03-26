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

#include <string>

namespace LumiereRenderer
{
    // Forward declarations
    class Node; 
	class RenderContext;

    /*!
        @class Attribute
        @brief Attributes are used to connect nodes.

               Each node have a list of attributes. The attributes connect
               the nodes together by
    */

    class Attribute
    {
        friend Node;
        friend RenderContext;

    public:
        /// Default constructor
        Attribute();    

        /// Default destructor
        virtual ~Attribute(void);

        ///        
        Attribute& operator=(Attribute& attribute);
        
        /// Get the attribute that this attribute is connected to.
        /// @return The connected attribute.
        Attribute* getConnection() const;
        
        /// Get the name of the attribute.
        /// @return The name of the attribute.
        std::string getName() const;
        
        /// If the attribute is not connected to any other attribute it will use the 
        /// default value.
        /// @return The default value.
        void* getDefaultValue() const;
        
        ///
        /// @param readable
        void setReadable(bool readable);
        
        /// @param writeable
        void setWriteable(bool writeable);
        
        /// @return Returns true if this attribute is allowed to connect to other attributes.
        bool isReadable();
        bool isWriteable();

    protected:
        virtual size_t getSize() const = 0;

        Node*                       mOwner; 
        Attribute*                  mConnection;
        std::string                 mName;
        void*                       mDefaultValue;
        bool                        mReadable;
        bool                        mWriteable;

    private:
        void connect(Attribute* attribute); //deprecated?
        void setOwner(Node* node);
        Node* getOwner() const;
    };
}
