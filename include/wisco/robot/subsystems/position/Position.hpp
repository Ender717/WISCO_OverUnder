#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief Namespace for all robot subsystems
 * @author Nathan Sandvig
 * 
 */
namespace subsystems
{

/**
 * @brief Namespace for all position subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace position
{

/**
 * @brief Holds a robot position
 * @author Nathan Sandvig
 * 
 */
struct Position
{
    double x{};
    double y{};
    double theta{};
    double xV{};
    double yV{};
    double thetaV{};
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif