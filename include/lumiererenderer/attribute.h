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
#include <lumiererenderer\Point3.h>

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

        struct AbstractAttribute
        {
            virtual ~AbstractAttribute() {}
            virtual void* getValue() const = 0;
            virtual size_t getSize() const = 0;
        };

        template <class T>
        struct ConcreteAttribute : public AbstractAttribute
        {
        public:
            ConcreteAttribute(T value) : mValue(value) {}
            virtual ~ConcreteAttribute() {}
            virtual void setValue(T value) 
            { 
                mValue = value; 
            }

        private:            
            virtual void* getValue() const { return (void*)&mValue; }
            size_t getSize() const {return sizeof(T);}

            T mValue;
        };

    public:
        /// Default destructor
        virtual ~Attribute(void);

        ///        
        Attribute& operator=(Attribute* attribute);
        
        /// Get the attribute that this attribute is connected to.
        /// @return The connected attribute.
        Attribute* getConnection() const;
        
        /// Get the name of the attribute.
        /// @return The name of the attribute.
        std::string getName() const;
        
        ///
        /// @param readable
        void setReadable(bool readable);
        
        ///
        /// @param writeable
        void setWriteable(bool writeable);
                
        template <class T>
        void setDefaultValue(T value)
        {
            ConcreteAttribute<T>* a = (ConcreteAttribute<T>*)(mAttribute);//->setValue(value);
            a->setValue(value);
        }

        //
        /// @return Returns true if this attribute is allowed to connect to other attributes.
        bool isReadable();
        bool isWriteable();
         void* getDefaultValue() const;
    protected:

         /// Default constructor
        template<class T>
        Attribute(std::string name, T value)  
        {
            mConnection = NULL;
            mOwner = NULL;
            mReadable = true;
            mWriteable = true;
            mName = name;
            mAttribute = new ConcreteAttribute<T>(value);
        }

        /// If the attribute is not connected to any other attribute it will use the 
        /// default value.
        /// @return The default value.
       

        size_t getSize() const;

        Node*             mOwner; 
        Attribute*        mConnection;
        std::string       mName;
        bool              mReadable;
        bool              mWriteable;
        AbstractAttribute* mAttribute;

    private:
        void connect(Attribute* attribute);
        void setOwner(Node* node);
        Node* getOwner() const;
    };
}
