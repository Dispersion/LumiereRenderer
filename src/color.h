#pragma once
#include <lumiererenderer\shadernode.h>

namespace LumiereRenderer
{
    class Color : public ShaderNode
    {
    public:
        Color(void);
        ~Color(void);

        void Evaluate(Attribute* attr, RenderContext* rc);

    private:
        Attribute* mRayWavelength;
        Attribute* aOutColor;
    };

}