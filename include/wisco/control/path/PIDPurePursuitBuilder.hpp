#ifndef WISCO_CONTROL_PATH_PID_PURE_PURSUIT_BUILDER_HPP
#define WISCO_CONTROL_PATH_PID_PURE_PURSUIT_BUILDER_HPP

#include "PIDPurePursuit.hpp"

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
 * @brief Namespace for path components
 * @author Nathan Sandvig
 * 
 */
namespace path
{

/**
 * @brief Builder class for PID pure pursuit controllers
 * @author Nathan Sandvig
 * 
 */
class PIDPurePursuitBuilder
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
     * @brief The follow distance
     * 
     */
    double m_follow_distance{};

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
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Adds an rtos mutex to the build
     * 
     * @param mutex The rtos mutex
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Adds an rtos task to the build
     * 
     * @param task The rtos task
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Adds a linear PID controller to the build
     * 
     * @param linear_pid The linear PID controller
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withLinearPID(PID linear_pid);

    /**
     * @brief Adds a rotational PID controller to the build
     * 
     * @param rotational_pid The rotational PID controller
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withRotationalPID(PID rotational_pid);

    /**
     * @brief Adds a follow distance to the build
     * 
     * @param follow_distance The follow distance
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withFollowDistance(double follow_distance);

    /**
     * @brief Adds a target tolerance to the build
     * 
     * @param target_tolerance The motion target tolerance
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withTargetTolerance(double target_tolerance);

    /**
     * @brief Adds a target velocity to the build
     * 
     * @param target_velocity The motion target velocity
     * @return PIDPurePursuitBuilder* This object for build chaining
     */
    PIDPurePursuitBuilder* withTargetVelocity(double target_velocity);

    /**
     * @brief Builds the PID pure pursuit controller
     * 
     * @return std::unique_ptr<IPathFollower> The PID pure pursuit controller as a path follower interface object
     */
    std::unique_ptr<IPathFollower> build();
};
} // namespace boomerang
} // namespace control
} // namespace wisco

#endif