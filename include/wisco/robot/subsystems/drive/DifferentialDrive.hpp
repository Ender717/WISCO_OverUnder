#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_HPP

#include "wisco/hal/MotorGroup.hpp"

#include "wisco/robot/subsystems/drive/IDifferentialDrive.hpp"

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
 * @brief A drive controller with independent left and right wheelsets
 * @author Nathan Sandvig
 * 
 */
class DifferentialDrive : public IDifferentialDrive
{
private:
    /**
     * @brief The left motors on the differential drive
     * 
     */
    hal::MotorGroup m_left_motors{};

    /**
     * @brief The right motors on the differential drive
     * 
     */
    hal::MotorGroup m_right_motors{};

    /**
     * @brief The mass of the robot
     * 
     */
    double m_mass{};

    /**
     * @brief The radius of the drive
     * 
     */
    double m_radius{};

    /**
     * @brief The moment of inertia of the robot
     * 
     */
    double m_moment_of_inertia{};

    /**
     * @brief The gear ratio from the motors to the drive (drive gear / motor gear)
     * 
     */
    double m_gear_ratio{};

    /**
     * @brief The radius of the drive wheels
     * 
     */
    double m_wheel_radius{};
    
public:
    /**
     * @brief Initializes the differential drive
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the differential drive
     * 
     */
    void run() override;

    /**
     * @brief Get the velocity of the left side of the drive
     * 
     * @return double The left drive velocity
     */
    double getLeftVelocity() override;

    /**
     * @brief Get the velocity of the right side of the drive
     * 
     * @return double The right drive velocity
     */
    double getRightVelocity() override;

    /**
     * @brief Set the acceleration values of the drive
     * 
     * @param left_acceleration The acceleration of the left side of the drive
     * @param right_acceleration The acceleration of the right side of the drive
     */
    void setAcceleration(double left_acceleration, double right_acceleration) override;  
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif