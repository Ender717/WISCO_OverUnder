#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_CURVE_VELOCITY_PROFILE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_CURVE_VELOCITY_PROFILE_HPP

#include <cmath>
#include <memory>

#include "wisco/rtos/IClock.hpp"

#include "wisco/robot/subsystems/drive/IVelocityProfile.hpp"

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
 * @brief An s-curve velocity profile for the drive
 * @author Nathan Sandvig
 * 
 */
class CurveVelocityProfile : public IVelocityProfile
{
private:
    /**
     * @brief The system clock
     * 
     */
    std::unique_ptr<rtos::IClock> m_clock{};

    /**
     * @brief The jerk rate of the velocity profile
     * 
     */
    double m_jerk_rate{};

    /**
     * @brief The maximum acceleration output of the velocity profile
     * 
     */
    double m_max_acceleration{};

    /**
     * @brief The current acceleration rate of the profile
     * 
     */
    double m_current_acceleration{};

    /**
     * @brief The last timestamp during execution
     * 
     */
    double last_time;

public:
    /**
     * @brief Construct a new Curve Velocity Profile object
     * 
     * @param clock The system clock
     * @param jerk_rate The jerk rate for the velocity profile
     * @param max_acceleration The maximum acceleration value
     */
    CurveVelocityProfile(std::unique_ptr<rtos::IClock>& clock, double jerk_rate, double max_acceleration);

    /**
     * @brief Get the target acceleration from the profile
     * 
     * @param target_velocity The target velocity of the drive side
     * @return double The acceleration in m/s^2
     */
    double getAcceleration(double target_velocity) override;

    /**
     * @brief Set the current acceleration
     * 
     * @param acceleration The current acceleration
     */
    void setAcceleration(double acceleration) override;
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif