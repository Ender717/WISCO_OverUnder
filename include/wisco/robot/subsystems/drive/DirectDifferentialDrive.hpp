#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIRECT_DIFFERENTIAL_DRIVE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIRECT_DIFFERENTIAL_DRIVE_HPP

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
 * @brief A direct drive controller with independent left and right wheelsets
 * @author Nathan Sandvig
 * 
 */
class DirectDifferentialDrive : public IDifferentialDrive
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
     * @brief Converts the input velocity to a voltage to control 
     * 
     */
    double m_velocity_to_voltage{1.0};

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
     * @brief Get the velocity values of the drive
     * 
     * @return double The drive velocity
     */
    Velocity getVelocity() override;

    /**
     * @brief Set the velocity values of the drive
     * 
     * @param velocity The velocity values for the drive
     */
    void setVelocity(Velocity velocity) override;

    /**
     * @brief Set the voltages of the drive directly
     * 
     * @param left_voltage The voltage for the left side of the drive
     * @param right_voltage The voltage for the right side of the drive
     */
    void setVoltage(double left_voltage, double right_voltage) override;

    /**
     * @brief Set the left drive motors
     * 
     * @param left_motors The motors on the left side of the drive
     */
    void setLeftMotors(hal::MotorGroup& left_motors);

    /**
     * @brief Set the right drive motors
     * 
     * @param right_motors The motors on the right side of the drive
     */
    void setRightMotors(hal::MotorGroup& right_motors);

    /**
     * @brief Set the velocity to voltage conversion constant
     * 
     * @param velocity_to_voltage The velocity to voltage conversion constant
     */
    void setVelocityToVoltage(double velocity_to_voltage);

    /**
     * @brief Set the gear ratio
     * 
     * @param gear_ratio The gear ratio of the drive
     */
    void setGearRatio(double gear_ratio);

    /**
     * @brief Set the wheel radius
     * 
     * @param wheel_radius The wheel radius of the drive
     */
    void setWheelRadius(double wheel_radius);
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif