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

#include <lumiererenderer\Attribute.h>
#include <lumiererenderer\RenderContext.h>
#include <map>
#include <string>


namespace LumiereRenderer
{
    /*!
        @class Node
        @brief 

               This is the base node of a node. The nodes are part of a DAG 
               each node contains a number of attributes. The nodes can be 
               connected to each other, by connecting them though their 
               attributes. 
               
               The output of one node will become the input of one or more 
               other nodes. The connections form a DAG. Data flows through 
               the nodes by using the attributes. Data comes through 
               the attributes and the node perform operation of the data. 
               
               A node should not require any data than what is through the 
               attributes. They are connected by a network of nodes. 
    */

    class Node
    {
    public:
            Node(void);
            virtual ~Node(void);
        
		    /** The evaluate function evaluates the value of an attribute in a certain render context.
		      * 
              * @param[in] attribute   The attribute that should be evaluated.
              * @param[in] rc   Used to get and set values of attributes and to trace new rays.
	          */
            virtual void evaluate( Attribute* attribute, RenderContext& rc ) = 0;
              
		    /** 
		      * Get a reference to an attribute by using its name. Use it to either get the attribute
		      * or to set its value. You can create a connection between two attributes in by using this
		      * syntax:
		      *
		      *		node1["diffuse"] = node0["outColor"];
		      *
		      * This will connect in a way that, when node1 needs to use the "diffuse" attribute, it will
		      * use whatever value is returned by the "outColor" attribute in node0. 
		      *
		      *
              * @param[in] name   The name of the attribute.
              * @return A reference to the attribute.
	          */	
		    Attribute* operator[](const char* name);        

		    template<class T>
		    Attribute* createAttribute(const char* name, T value)
		    {
			    Attribute* attribute = new Attribute(name, value);
			    addAttribute(attribute);
			    return attribute;
		    }

    protected:
            std::map<std::string, Attribute*> mAttributes;
	
    private:
		    void                        addAttribute( Attribute* attribute );
    };    
}