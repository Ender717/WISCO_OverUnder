#ifndef WISCO_CONTROL_MOTION_PID_TURN_BUILDER_HPP
#define WISCO_CONTROL_MOTION_PID_TURN_BUILDER_HPP

#include "PIDTurn.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for basic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Builder class for PID turn controllers
 * @author Nathan Sandvig
 * 
 */
class PIDTurnBuilder
{
    /**
     * @brief The rtos delayer
     * 
     */
    std::unique_ptr<rtos::IDelayer> m_delayer{};

    /**
     * @brief The rtos mutex
     * 
     */
    std::unique_ptr<rtos::IMutex> m_mutex{};

    /**
     * @brief The rtos task
     * 
     */
    std::unique_ptr<rtos::ITask> m_task{};

    /**
     * @brief The PID controller
     * 
     */
    PID m_pid{};

    /**
     * @brief The acceptable tolerance to reach the target
     * 
     */
    double m_target_tolerance{};

    /**
     * @brief The acceptable velocity to reach the target
     * 
     */
    double m_target_velocity{};

public: 
    /**
     * @brief Adds an rtos delayer to the build
     * 
     * @param delayer The rtos delayer
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Adds an rtos mutex to the build
     * 
     * @param mutex The rtos mutex
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Adds an rtos task to the build
     * 
     * @param task The rtos task
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Adds a PID controller to the build
     * 
     * @param pid The PID controller
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withPID(PID pid);

    /**
     * @brief Adds a target tolerance to the build
     * 
     * @param target_tolerance The motion target tolerance
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withTargetTolerance(double target_tolerance);

    /**
     * @brief Adds a target velocity to the build
     * 
     * @param target_velocity The motion target velocity
     * @return PIDTurnBuilder* This object for build chaining
     */
    PIDTurnBuilder* withTargetVelocity(double target_velocity);

    /**
     * @brief Builds the PID turn controller
     * 
     * @return std::unique_ptr<ITurn> The PID turn controller as a turn interface object
     */
    std::unique_ptr<ITurn> build();
};
} // namespace motion
} // namespace control
} // namespace wisco

#endif