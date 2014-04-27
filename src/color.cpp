#include "color.h"
#include <lumiererenderer\attributevalue.h>

namespace LumiereRenderer
{
    Color::Color(void)
    {
        mRayWavelength = new AttributeValue<float>("RayWavelength", 0);
        aOutColor = new AttributeValue<float>("outColor", 0);		

        AddAttribute( mRayWavelength );
        AddAttribute( aOutColor );
    }


    Color::~Color(void)
    {
    }


    void Color::Evaluate( Attribute* attr, RenderContext* rc )
    {	
        if (attr == aOutColor)
        {
            float wavelength = rc->GetInput( mRayWavelength ).AsFloat();

            DataHandle outColor = rc->GetOutput(aOutColor);
            outColor.Set( GetIntensity(wavelength) );
        }
    }
}