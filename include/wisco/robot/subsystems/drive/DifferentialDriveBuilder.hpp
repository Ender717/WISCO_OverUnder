#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_BUILDER_HPP

#include "DifferentialDrive.hpp"

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
 * @brief Builder class for the differential drive class
 * @author Nathan Sandvig
 * 
 */
class DifferentialDriveBuilder
{
private:
    /**
     * @brief The system delayer
     * 
     */
    std::unique_ptr<rtos::IDelayer> m_delayer{};

    /**
     * @brief The os mutex
     * 
     */
    std::unique_ptr<rtos::IMutex> m_mutex{};

    /**
     * @brief The task handler
     * 
     */
    std::unique_ptr<rtos::ITask> m_task{};

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
     * @brief Add an rtos delayer to the build
     * 
     * @param delayer The rtos delayer
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withDelayer(std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Add an os mutex to the build
     * 
     * @param mutex The os mutex
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Add an rtos task handler to the build
     * 
     * @param task The rtos task handler
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Add the left drive motors to the build
     * 
     * @param left_motors The motors on the left side of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withLeftMotors(hal::MotorGroup left_motors);

    /**
     * @brief Add the right drive motors to the build
     * 
     * @param right_motors The motors on the right side of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withRightMotors(hal::MotorGroup right_motors);

    /**
     * @brief Add the mass to the build
     * 
     * @param mass The mass of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withMass(double mass);

    /**
     * @brief Add the radius to the build
     * 
     * @param radius The radius of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withRadius(double radius);

    /**
     * @brief Add the moment of inertia to the build
     * 
     * @param moment_of_inertia The moment of inertia of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withMomentOfInertia(double moment_of_inertia);

    /**
     * @brief Add the gear ratio to the build
     * 
     * @param gear_ratio The gear ratio of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withGearRatio(double gear_ratio);

    /**
     * @brief Add the wheel radius to the build
     * 
     * @param wheel_radius The wheel radius of the drive
     * @return DifferentialDriveBuilder* This object for build chaining
     */
    DifferentialDriveBuilder* withWheelRadius(double wheel_radius);

    /**
     * @brief Builds the differential drive system
     * 
     * @return std::unique_ptr<IPositionTracker> The differential drive system as a differential drive interface
     */
    std::unique_ptr<IDifferentialDrive> build();
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif