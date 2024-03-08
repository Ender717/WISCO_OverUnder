#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_HPP

#include <cmath>
#include <memory>

#include "wisco/hal/MotorGroup.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

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
 * @brief A kinematic drive controller with independent left and right wheelsets
 * @author Nathan Sandvig
 * 
 */
class KinematicDifferentialDrive : public IDifferentialDrive
{
private:
    /**
     * @brief The loop delay on the task
     * 
     */
    static constexpr uint8_t TASK_DELAY{10};

    /**
     * @brief The task loop function for background updates
     * 
     * @param params 
     */
    static void taskLoop(void* params);

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

    /**
     * @brief The first kinematic constant
     * 
     */
    double c1{};

    /**
     * @brief The second kinematic constant
     * 
     */
    double c2{};

    /**
     * @brief The third kinematic constant
     * 
     */
    double c3{};

    /**
     * @brief The fourth kinematic constant
     * 
     */
    double c4{};

    /**
     * @brief The fifth kinematic constant
     * 
     */
    double c5{};

    /**
     * @brief The sixth kinematic constant
     * 
     */
    double c6{};

    /**
     * @brief The target acceleration for the left drive
     * 
     */
    double m_left_acceleration{};
    
    /**
     * @brief The target acceleration for the right drive
     * 
     */
    double m_right_acceleration{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Updates the motor values using the target acceleration values
     * 
     */
    void updateAcceleration();
    
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

    /**
     * @brief Set the rtos delayer
     * 
     * @param delayer The rtos delayer
     */
    void setDelayer(std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Set the os mutex
     * 
     * @param mutex The os mutex
     */
    void setMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Set the rtos task handler
     * 
     * @param task The rtos task handler
     */
    void setTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Set the left drive motors
     * 
     * @param left_motors The motors on the left side of the drive
     */
    void setLeftMotors(hal::MotorGroup left_motors);

    /**
     * @brief Set the right drive motors
     * 
     * @param right_motors The motors on the right side of the drive
     */
    void setRightMotors(hal::MotorGroup right_motors);

    /**
     * @brief Set the mass
     * 
     * @param mass The mass of the drive
     */
    void setMass(double mass);

    /**
     * @brief Set the radius
     * 
     * @param radius The radius of the drive
     */
    void setRadius(double radius);

    /**
     * @brief Set the moment of inertia
     * 
     * @param moment_of_inertia The moment of inertia of the drive
     */
    void setMomentOfInertia(double moment_of_inertia);

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