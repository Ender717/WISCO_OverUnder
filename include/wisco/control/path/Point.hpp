#ifndef WISCO_CONTROL_PATH_POINT_HPP
#define WISCO_CONTROL_PATH_POINT_HPP

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
 * @brief Class for a point with an x and y coordinate
 * @author Nathan Sandvig
 * 
 */
class Point
{
private:
    /**
     * @brief The x-coordinate of the point
     * 
     */
    double m_x{};

    /**
     * @brief The y-coordinate of the point
     * 
     */
    double m_y{};

public:
    /**
     * @brief Construct a new Point object
     * 
     */
    Point() = default;

    /**
     * @brief Construct a new Point object
     * 
     * @param copy The point object being copied
     */
    Point(const Point& copy) = default;

    /**
     * @brief Construct a new Point object
     * 
     * @param move The point object being moved
     */
    Point(Point&& move) = default;

    /**
     * @brief Construct a new Point object
     * 
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     */
    Point(double x, double y);

    /**
     * @brief Destroy the Point object
     * 
     */
    ~Point() = default;

    /**
     * @brief Sets the x-coordinate of the point
     * 
     * @param x The x-coordinate of the point
     */
    void setX(double x);

    /**
     * @brief Sets the y-coordinate of the point
     * 
     * @param y The y-coordinate of the point
     */
    void setY(double y);

    /**
     * @brief Gets the x-coordinate of the point
     * 
     * @return double The x-coordinate of the point
     */
    double getX() const;

    /**
     * @brief Gets the y-coordinate of the point
     * 
     * @return double The y-coordinate of the point
     */
    double getY() const;

    /**
     * @brief Addition operator overload for point
     * 
     * @param rhs The point on the right hand side of the operator
     * @return Point A new point with the sum of the coordinates of both points
     */
    Point operator+(const Point& rhs);

    /**
     * @brief Subtraction operator overload for point
     * 
     * @param rhs The point on the right hand side of the operator
     * @return Point A new point with the difference of the coordinates of both points
     */
    Point operator-(const Point& rhs);

    /**
     * @brief Multiplication operator overload for point
     * 
     * @param rhs The multiplier on the right hand side of the operator
     * @return Point A new point with the coordinates of this point multiplied by the multiplier
     */
    Point operator*(double rhs);

    /**
     * @brief Division operator overload for point
     * 
     * @param rhs The divisor on the right hand side of the operator
     * @return Point A new point with the coordinates of this point divided by the divisor
     */
    Point operator/(double rhs);

    /**
     * @brief Addition assignment operator overload for point
     * 
     * @param rhs The point on the right hand side of the operator
     * @return Point& This point with the sum of the coordinates of both points
     */
    Point& operator+=(const Point& rhs);

    /**
     * @brief Subtraction assignment operator overload for point
     * 
     * @param rhs The point on the right hand side of the operator
     * @return Point& This point with the difference of the coordinates of both points
     */
    Point& operator-=(const Point& rhs);

    /**
     * @brief Multiplication assignment operator overload for point
     * 
     * @param rhs The multiplier on the right hand side of the operator
     * @return Point& This point with the coordinates of this point multiplied by the multiplier
     */
    Point& operator*=(double rhs);

    /**
     * @brief Division assignment operator overload for point
     * 
     * @param rhs The divisor on the right hand side of the operator
     * @return Point& This point with the coordinates of this point divided by the divisor
     */
    Point& operator/=(double rhs);

    /**
     * @brief Copy assignment operator for point
     * 
     * @param copy The point on the right hand side of the operator
     * @return Point& This point with the coordinates of the other point
     */
    Point& operator=(const Point& copy) = default;

    /**
     * @brief Move assignment operator for point
     * 
     * @param move The point value on the right hand side of the operator
     * @return Point& This point with the coordinates of the point value
     */
    Point& operator=(Point&& move) = default;
};

/**
 * @brief Multiplication operator overload for doubles with points
 * 
 * @param lhs The multiplier on the left hand side of the operator
 * @param rhs The point on the right hand side of the operator
 * @return Point A new point with the point coordinates multiplied by the multiplier
 */
Point operator*(double lhs, const Point& rhs);
} // namespace path
} // namespace control
} // namespace wisco

#endif