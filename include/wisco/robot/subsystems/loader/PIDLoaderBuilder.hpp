#ifndef WISCO_ROBOT_SUBSYSTEMS_LOADER_PID_LOADER_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_LOADER_PID_LOADER_BUILDER_HPP

#include "PIDLoader.hpp"

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
 * @brief Namespace for loader classes
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief Builder class for a pid-based loader system
 * @author Nathan Sandvig
 * 
 */
class PIDLoaderBuilder
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
     * @brief The motors on the loader
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The position for match loads
     * 
     */
    double m_match_load_position{};

    /**
     * @brief The position for ready
     * 
     */
    double m_ready_position{};

    /**
     * @brief The allowed tolerance around the target positions
     * 
     */
    double m_position_tolerance{};

public:
    /**
     * @brief Add a rtos clock to the build
     * 
     * @param clock The rtos clock
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withClock(const std::unique_ptr<rtos::IClock>& clock);

    /**
     * @brief Add a rtos delayer to the build
     * 
     * @param delayer The rtos delayer
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Add a thread mutex to the build
     * 
     * @param mutex The thread mutex
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Add a task handler to the build
     * 
     * @param task The task handler
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Add a PID controller to the build
     * 
     * @param pid The PID controller
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withPID(control::PID pid);

    /**
     * @brief Add a motor to the build
     * 
     * @param motor The motor
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withMotor(std::unique_ptr<io::IMotor>& motor);

    /**
     * @brief Add a position for match loads to the build
     * 
     * @param match_load_position The position for match loads
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withMatchLoadPosition(double match_load_position);

    /**
     * @brief Add a position for ready to the build
     * 
     * @param ready_position The position for ready
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withReadyPosition(double ready_position);

    /**
     * @brief Add an allowed tolerance around the target positions to the build
     * 
     * @param position_tolerance The allowed tolerance around the target positions
     * @return This object for build chaining
     */
    PIDLoaderBuilder* withPositionTolerance(double position_tolerance);

    /**
     * @brief Builds the pid loader
     * 
     * @return std::unique_ptr<ILoader> The pid loader as a loader interface
     */
    std::unique_ptr<ILoader> build();
};
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif