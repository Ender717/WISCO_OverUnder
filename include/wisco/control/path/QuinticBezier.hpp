#ifndef WISCO_CONTROL_PATH_QUINTIC_BEZIER_HPP
#define WISCO_CONTROL_PATH_QUINTIC_BEZIER_HPP

#include <cmath>

#include "Point.hpp"

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
 * @brief A quintic bezier with a point function
 * @author Nathan Sandvig
 * 
 */
class QuinticBezier
{
public:
    /**
     * @brief The first control point
     * 
     */
    Point k0{};

    /**
     * @brief The second control point
     * 
     */
    Point c0{};

    /**
     * @brief The third control point
     * 
     */
    Point c1{};

    /**
     * @brief The fourth control point
     * 
     */
    Point c2{};

    /**
     * @brief The fifth control point
     * 
     */
    Point c3{};

    /**
     * @brief The sixth control point
     * 
     */
    Point k1{};

    /**
     * @brief Construct a new Quintic Bezier object
     * 
     */
    QuinticBezier() = default;

    /**
     * @brief Construct a new Quintic Bezier object
     * 
     * @param copy The QuinticBezier object being copied
     */
    QuinticBezier(const QuinticBezier& copy) = default;

    /**
     * @brief Construct a new Quintic Bezier object
     * 
     * @param move The QuinticBezier object being moved
     */
    QuinticBezier(QuinticBezier&& move) = default;

    /**
     * @brief Construct a new Quintic Bezier object
     * 
     * @param c1 The first control point
     * @param c2 The second control point
     * @param c3 The third control point
     * @param c4 The fourth control point
     * @param c5 The fifth control point
     * @param c6 The sixth control point
     */
    QuinticBezier(Point c1, Point c2, Point c3, Point c4, Point c5, Point c6);

    /**
     * @brief Gets the point at f(t)
     * 
     * @param t The input value
     * @return Point The point at that input value
     */
    Point calculatePoint(double t);

    /**
     * @brief Copy assignment operator for QuinticBezier
     * 
     * @param copy The QuinticBezier on the right hand side of the operator
     * @return QuinticBezier& This QuinticBezier with the control points of the other QuinticBezier
     */
    QuinticBezier& operator=(const QuinticBezier& rhs) = default;

    /**
     * @brief Move assignment operator for QuinticBezier
     * 
     * @param rhs The QuinticBezier value on the right hand side of the operator
     * @return QuinticBezier& This QuinticBezier with the control points of the QuinticBezier value
     */
    QuinticBezier& operator=(QuinticBezier&& rhs) = default;
};
} // namespace path
} // namespace control
} // namespace wisco

#endif