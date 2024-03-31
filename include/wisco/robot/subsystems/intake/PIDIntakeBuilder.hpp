#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_PID_INTAKE_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_PID_INTAKE_BUILDER_HPP

#include "PIDIntake.hpp"

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
 * @brief Namespace for intake classes
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

/**
 * @brief A builder class for a PID-based intake subsystem
 * @author Nathan Sandvig
 * 
 */
class PIDIntakeBuilder
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
     * @brief The velocity PID controller
     * 
     */
    control::PID m_pid{};

    /**
     * @brief The motors on the intake
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The radius of the intake roller
     * 
     */
    double m_roller_radius{};

public:
    /**
     * @brief Add an rtos clock to the build
     * 
     * @param clock The rtos clock
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withClock(const std::unique_ptr<rtos::IClock>& clock);

    /**
     * @brief Add an rtos delayer to the build
     * 
     * @param delayer The rtos delayer
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Add a thread mutex to the build
     * 
     * @param mutex The thread mutex
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Add a task handler to the build
     * 
     * @param task The task handler
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Add a PID controller to the build
     * 
     * @param pid The PID controller
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withPID(control::PID pid);

    /**
     * @brief Add a motor to the build
     * 
     * @param motor The motor
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withMotor(std::unique_ptr<io::IMotor>& motor);

    /**
     * @brief Add a roller radius to the build
     * 
     * @param roller_radius The radius of the roller
     * @return PIDIntakeBuilder* This object for build chaining
     */
    PIDIntakeBuilder* withRollerRadius(double roller_radius);

    /**
     * @brief Builds the intake
     * 
     * @return std::unique_ptr<IIntake> The PIDIntake object built with the stored data
     */
    std::unique_ptr<IIntake> build();
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif