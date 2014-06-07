#include <lumiererenderer\Solver.h>
#include <math.h>

namespace LumiereRenderer
{
    // Solves the equation ax+b = 0
    int solveLinear(float a, float b, float& x)
    {
        x = -b/a;
        return 1;
    }
    
    // find the roots of a Quadratic equation.
    // ax^2 + bx + c = 0
    int solveQuadratic(float a, float b, float c, float& x0, float& x1)
    {
        if( a == 0 )
        {
            return solveLinear(b, c, x0);
        }

        float d = b*b - 4*a*c;

        if( d < 0 )
        {
            return 0;
        }

        if( d == 0 )
        {
            x0 = -b / (2*a);
            return 1;
        }

        float sd = sqrt(d);
        x0 = (-b + sd) / (2*a);
        x1 = (-b - sd) / (2*a);

        return 2;
    }

    int solveCubic(float a, float b, float c, float d, float& x0, float& x1, float& x2)
    {
        // We wish to solve the cubic equation of  
        // ax^3 + bx^2 + cx + d = 0
        // if a is 0, we can interpret it as a quadratic equation
        if( a == 0 )
        {
            return solveQuadratic(b, c, d, x0, x1);
        }

        if( d == 0 )
        {
            x1 = 0;
            int roots = solveQuadratic(a, b, c, x0, x2);
            return roots + 1;
        }


        // Our solution assumes that 'a' is 1, so we divide all the cofficients by 'a'
        // this gives us the slightly simpler equation:
        // x^3 + bx^2 + cx + d = 0        
        b /= a;
        c /= a;
        d /= a;

        // We eleminate the square term by using the substitution x = t - a/3 
        // this give us t^3 + p*t + q = 0
        // where p and q are defined as:
        float p = c - ((b*b)/(3.0f));                    
        float q = d + (2.0f*b*b*b - 9*b*c) / 27.0f;  

        // By letting t = u + v, we can rewrite the equation as
        // u^3 + v^3 + (u + v)(3*u*v + p) + q = 0

        float disc = q*q/4 + p*p*p/27.0f;          

        if( disc > 0 )
        {
            float u = -q/2.0f + sqrt(disc);
            float v = q/2.0f + sqrt(disc);
            
            float k = u < 0 ? -1.0f : 1.0f;
            u = k*pow(k*u, 1.0f/3.0f);
            
            k = u < 0 ? -1.0f : 1.0f;
            v = k*pow(k*v, 1.0f/3.0f);

            x0 = (u - v) - b/3.0f;
            return 1;
        }
        else
        {
            float r = sqrt(q*q/4 - disc);
            float theta = acos(-q/(2.0f*r));

            float k = r < 0 ? -1.0f : 1.0f;
            r = k*pow(k*r, 1.0f/3.0f);

            float m = cos(theta/3.0f);
            float n = sqrt(3.0f)*(sin(theta/3.0f));
            float p = b/3.0f;

            x0 = 2.0f*r*cos(theta/3.0f) - p;
            x1 = -r*(m + n) - p;
            x2 = -r*(m - n) - p;

            return 3;
        }
    }
}