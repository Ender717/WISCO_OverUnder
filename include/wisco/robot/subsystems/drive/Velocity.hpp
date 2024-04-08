#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_VELOCITY_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_VELOCITY_HPP

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
 * @brief Namespace for drive classes
 * @author Nathan Sandvig
 * 
 */
namespace drive
{

/**
 * @brief Holds the velocity values for the drive
 * @author Nathan Sandvig
 * 
 */
struct Velocity
{
    /**
     * @brief The velocity for the left side of the drive
     * 
     */
    double left_velocity{};

    /**
     * @brief The velocity for the right side of the drive
     * 
     */
    double right_velocity{};
};

} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif