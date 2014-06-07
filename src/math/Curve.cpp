#include "lumiererenderer\Curve.h"

#include "lumiererenderer\Vector4.h"
#include "lumiererenderer\Solver.h"

namespace LumiereRenderer
{ 
    Curve::Curve(void)
    {
    }


    Curve::~Curve(void)
    {
    }

    void Curve::add(float time, float value, float inX, float inY, float outX, float outY)
    {
        Key key;
        key.time = time;
        key.value = value;
        key.inX = inX;
        key.inY = inY;
        key.outX = outX;
        key.outY = outY;
        mKeys.push_back(key);
    }

    float Curve::operator[](float time)
    {        
        if( mKeys.size() < 2 )
        {
            return 0;
        }

        Key k0 = mKeys[0];
        Key k1 = mKeys[0];
        
        if (time < k1.time)
        {
            return mKeys[0].value;
        }

        for( int n = 1; n < mKeys.size(); ++n )
        {            
            k0 = k1;
            k1 = mKeys[n];

            if (time <= k1.time)
            {
                float a = 2.0f*k0.time + k0.outX + k1.inX - 2.0f*k1.time;
                float b = -3.0f*k0.time + 3.0f*k1.time - 2.0f*k0.outX - k1.inX;
                float c = k0.outX;
                float d = k0.time - time;
                
                float x0, x1, x2;
                int roots = solveCubic(a, b, c, d, x0, x1, x2);                

                float t = x0;             
                if( x1 >= 0 && x1 <= 1 && roots > 1 ) t = x1;
                if( x2 >= 0 && x2 <= 1 && roots > 2 ) t = x2;
                float t2 = t*t;
                float t3 = t2*t;

                Vector4 h;
                h[0] =  2*t3 - 3*t2 + 1;
                h[1] = -2*t3 + 3*t2;
                h[2] =    t3 - 2*t2 + t;
                h[3] =    t3 -   t2;

                float w0 = a*t3+b*t2+c*t+d;
                float w1 = h[0]*k0.time + h[1]*k1.time + h[2]*k0.outX + h[3]*k1.inX;
                return h[0]*k0.value + h[1]*k1.value + h[2]*k0.outY + h[3]*k1.inY;
            }

        }

        return mKeys[mKeys.size()-1].value;
    }


    
}