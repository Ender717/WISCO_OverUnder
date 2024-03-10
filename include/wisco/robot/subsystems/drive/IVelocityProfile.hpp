#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_VELOCITY_PROFILE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_VELOCITY_PROFILE_HPP

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
 * @brief Interface for drive velocity profiles
 * @author Nathan Sandvig
 * 
 */
class IVelocityProfile
{
public:
    /**
     * @brief Destroy the IVelocityProfile object
     * 
     */
    virtual ~IVelocityProfile() = default;

    /**
     * @brief Get the target acceleration from the profile
     * 
     * @param current_velocity The current velocity
     * @param target_velocity The target velocity
     * @return double The acceleration in m/s^2
     */
    virtual double getAcceleration(double current_velocity, double target_velocity) = 0;

    /**
     * @brief Set the current acceleration
     * 
     * @param acceleration The current acceleration
     */
    virtual void setAcceleration(double acceleration) = 0;
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif