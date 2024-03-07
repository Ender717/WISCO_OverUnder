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
    
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif