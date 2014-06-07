#pragma once
#include <vector>
#include "lumiererenderer\Vector3.h"
#include "lumiererenderer\Vector4.h"

namespace LumiereRenderer
{ 


class Curve
{
private:
    struct Key
    {
        float time;
        float value;
        float inX;
        float inY;
        float outX;
        float outY;
    };

public:
    Curve(void);
    ~Curve(void);

    void add(float time, float value, float inX, float inY, float outX, float outY);
    float operator[](float time);


private:
    std::vector<Key> mKeys;
};

}