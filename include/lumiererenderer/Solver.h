#pragma once

namespace LumiereRenderer
{    
    extern int solveLinear(float a, float b, float& x);
    extern int solveQuadratic(float a, float b, float c, float& x0, float& x1);

    /// Solves an equation of the form
    ///   ax^3 + bx^2 + cx + d = 0

    /// @param[in] a   The 'a' coefficient.
    /// @param[in] b   The 'b' coefficient.
    /// @param[in] c   The 'c' coefficient.
    /// @param[in] d   The 'c' coefficient.
    /// @param[in] x0  The first root.
    /// @param[in] x1  The second root.
    /// @param[in] x2  The third root.
    /// @return        The number of real roots found.
    extern int solveCubic(float a, float b, float c, float d, float& x0, float& x1, float& x2);
}
