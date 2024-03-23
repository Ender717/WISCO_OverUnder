#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIRECT_DIFFERENTIAL_DRIVE_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIRECT_DIFFERENTIAL_DRIVE_BUILDER_HPP

#include <memory>

#include "DirectDifferentialDrive.hpp"

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
 * @brief Builder class for the direct differential drive class
 * @author Nathan Sandvig
 * 
 */
class DirectDifferentialDriveBuilder
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
     * @brief The conversion constant from velocity to voltage
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
     * @brief Add a left drive motor to the build
     * 
     * @param left_motor The motor on the left side of the drive
     * @return DirectDifferentialDriveBuilder* This object for build chaining
     */
    DirectDifferentialDriveBuilder* withLeftMotor(std::unique_ptr<io::IMotor>& left_motor);

    /**
     * @brief Add a right drive motor to the build
     * 
     * @param right_motor The motor on the right side of the drive
     * @return DirectDifferentialDriveBuilder* This object for build chaining
     */
    DirectDifferentialDriveBuilder* withRightMotor(std::unique_ptr<io::IMotor>& right_motor);

    /**
     * @brief Add the velocity to voltage conversion constant to the build
     * 
     * @param mass The velocity to voltage conversion constant of the drive
     * @return DirectDifferentialDriveBuilder* This object for build chaining
     */
    DirectDifferentialDriveBuilder* withVelocityToVoltage(double velocity_to_voltage);

    /**
     * @brief Add the gear ratio to the build
     * 
     * @param gear_ratio The gear ratio of the drive
     * @return KinematicDifferentialDriveBuilder* This object for build chaining
     */
    DirectDifferentialDriveBuilder* withGearRatio(double gear_ratio);

    /**
     * @brief Add the wheel radius to the build
     * 
     * @param wheel_radius The wheel radius of the drive
     * @return KinematicDifferentialDriveBuilder* This object for build chaining
     */
    DirectDifferentialDriveBuilder* withWheelRadius(double wheel_radius);

    /**
     * @brief Builds the differential drive system
     * 
     * @return std::unique_ptr<IDifferentialDrive> The differential drive system as a differential drive interface
     */
    std::unique_ptr<IDifferentialDrive> build();
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif