#ifndef WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_PID_ELEVATOR_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_PID_ELEVATOR_BUILDER_HPP

#include <memory>

#include "PIDElevator.hpp"

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
 * @brief Namespace for elevator classes
 * @author Nathan Sandvig
 * 
 */
namespace elevator
{

/**
 * @brief Builder class for a pid-based elevator system
 * @author Nathan Sandvig
 * 
 */
class PIDElevatorBuilder
{
private:
    /**
     * @brief The rtos clock
     * 
     */
    std::unique_ptr<rtos::IClock> m_clock{};

    /**
     * @brief The rtos delayer
     * 
     */
    std::unique_ptr<rtos::IDelayer> m_delayer{};

    /**
     * @brief The mutex for thread safety
     * 
     */
    std::unique_ptr<rtos::IMutex> m_mutex{};

    /**
     * @brief The background task handler
     * 
     */
    std::unique_ptr<rtos::ITask> m_task{};

    /**
     * @brief The position PID controller
     * 
     */
    control::PID m_pid{};

    /**
     * @brief The motors on the elevator
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The rotation sensor on the elevator
     * 
     */
    std::unique_ptr<io::IRotationSensor> m_rotation_sensor{};

    /**
     * @brief The number of movement inches per radian
     * 
     */
    double m_inches_per_radian{};

public:
    /**
     * @brief Add an rtos clock to the build
     * 
     * @param clock The rtos clock
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withClock(const std::unique_ptr<rtos::IClock>& clock);

    /**
     * @brief Add an rtos delayer to the build
     * 
     * @param delayer The rtos delayer
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Add a thread mutex to the build
     * 
     * @param mutex The thread mutex
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Add a task handler to the build
     * 
     * @param task The task handler
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Add a PID controller to the build
     * 
     * @param pid The PID controller
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withPID(control::PID pid);

    /**
     * @brief Add a motor to the build
     * 
     * @param motor The motor
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withMotor(std::unique_ptr<io::IMotor>& motor);

    /**
     * @brief Add a rotation sensor to the build
     * 
     * @param rotation_sensor The rotation sensor
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withRotationSensor(std::unique_ptr<io::IRotationSensor>& rotation_sensor);

    /**
     * @brief Add an inches per radian constant to the build
     * 
     * @param inches_per_radian The inches per radian of the elevator
     * @return PIDElevatorBuilder* This object for build chaining
     */
    PIDElevatorBuilder* withInchesPerRadian(double inches_per_radian);

    /**
     * @brief Builds the elevator
     * 
     * @return std::unique_ptr<IElevator> The PIDElevator object built with the stored data
     */
    std::unique_ptr<IElevator> build();
};
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif