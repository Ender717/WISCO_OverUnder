#ifndef WISCO_CONTROL_PATH_QUINTIC_BEZIER_SPLINE_HPP
#define WISCO_CONTROL_PATH_QUINTIC_BEZIER_SPLINE_HPP

#include <vector>

#include "QuinticBezier.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for path components
 * @author Nathan Sandvig
 * 
 */
namespace path
{

/**
 * @brief A spline of quintic beziers
 * @author Nathan Sandvig
 * 
 */
class QuinticBezierSpline
{
public:
    /**
     * @brief Calculates a smooth spline using quintic beziers
     * 
     * @param control_points The control points for the spline
     * @return std::vector<Point> The points in the spline
     */
    static std::vector<Point> calculate(std::vector<Point>& control_points);
};
} // namespace path
} // namespace control
} // namespace wisco

#endif