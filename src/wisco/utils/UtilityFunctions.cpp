#include "wisco/utils/UtilityFunctions.hpp"

double bindRadians(double radians)
{
    while (radians > M_PI)
        radians -= 2 * M_PI;
    while (radians < -M_PI)
        radians += 2 * M_PI;
    return radians;
}