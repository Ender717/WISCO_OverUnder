#ifndef WISCO_CONTROL_MOTION_PID_GO_TO_POINT_BUILDER_HPP
#define WISCO_CONTROL_MOTION_PID_GO_TO_POINT_BUILDER_HPP

#include "PIDGoToPoint.hpp"

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
 * @brief Builder class for PID go to point
 * @author Nathan Sandvig
 * 
 */
class PIDGoToPointBuilder
{
private:
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
     * @brief The linear PID controller
     * 
     */
    PID m_linear_pid{};

    /**
     * @brief The rotational PID controller
     * 
     */
    PID m_rotational_pid{};

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
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Adds an rtos mutex to the build
     * 
     * @param mutex The rtos mutex
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Adds an rtos task to the build
     * 
     * @param task The rtos task
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Adds a linear PID controller to the build
     * 
     * @param linear_pid The linear PID controller
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withLinearPID(PID linear_pid);

    /**
     * @brief Adds a rotational PID controller to the build
     * 
     * @param rotational_pid The rotational PID controller
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withRotationalPID(PID rotational_pid);

    /**
     * @brief Adds a target tolerance to the build
     * 
     * @param target_tolerance The motion target tolerance
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withTargetTolerance(double target_tolerance);

    /**
     * @brief Adds a target velocity to the build
     * 
     * @param target_velocity The motion target velocity
     * @return PIDGoToPointBuilder* This object for build chaining
     */
    PIDGoToPointBuilder* withTargetVelocity(double target_velocity);

    /**
     * @brief Builds the pid go to point
     * 
     * @return std::unique_ptr<IGoToPoint> The pid go to point as a go to point interface
     */
    std::unique_ptr<IGoToPoint> build();
};
} // namespace motion
} // namespace control
} // namespace wisco

#endif