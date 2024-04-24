#ifndef WISCO_CONTROL_BOOMERANG_PID_BOOMERANG_BUILDER_HPP
#define WISCO_CONTROL_BOOMERANG_PID_BOOMERANG_BUILDER_HPP

#include "PIDBoomerang.hpp"

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
 * @brief Namespace for boomerang controller components
 * @author Nathan Sandvig
 * 
 */
namespace boomerang
{

/**
 * @brief Builder class for PID boomerang controllers
 * @author Nathan Sandvig
 * 
 */
class PIDBoomerangBuilder
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
     * @brief The lead ratio for the carrot point
     * 
     */
    double m_lead{};

    /**
     * @brief The distance to aim at the target
     * 
     */
    double m_aim_distance{};    

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
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Adds an rtos mutex to the build
     * 
     * @param mutex The rtos mutex
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Adds an rtos task to the build
     * 
     * @param task The rtos task
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Adds a linear PID controller to the build
     * 
     * @param linear_pid The linear PID controller
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withLinearPID(PID linear_pid);

    /**
     * @brief Adds a rotational PID controller to the build
     * 
     * @param rotational_pid The rotational PID controller
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withRotationalPID(PID rotational_pid);

    /**
     * @brief Adds a lead ratio to the build
     * 
     * @param lead The lead ratio
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withLead(double lead);

    /**
     * @brief Adds an aim distance to the build
     * 
     * @param aim_distance The distance to aim at the point
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withAimDistance(double aim_distance);

    /**
     * @brief Adds a target tolerance to the build
     * 
     * @param target_tolerance The motion target tolerance
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withTargetTolerance(double target_tolerance);

    /**
     * @brief Adds a target velocity to the build
     * 
     * @param target_velocity The motion target velocity
     * @return PIDBoomerangBuilder* This object for build chaining
     */
    PIDBoomerangBuilder* withTargetVelocity(double target_velocity);

    /**
     * @brief Builds the PID boomerang controller
     * 
     * @return std::unique_ptr<IBoomerang> The PID boomerang controller as a boomerang interface object
     */
    std::unique_ptr<IBoomerang> build();
};
} // namespace boomerang
} // namespace control
} // namespace wisco

#endif