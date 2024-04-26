#ifndef WISCO_CONTROL_MOTION_PID_GO_TO_POINT_HPP
#define WISCO_CONTROL_MOTION_PID_GO_TO_POINT_HPP

#include <cmath>
#include <memory>

#include "wisco/utils/UtilityFunctions.hpp"

#include "wisco/robot/Robot.hpp"
#include "wisco/robot/subsystems/drive/Velocity.hpp"
#include "wisco/robot/subsystems/position/Position.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"
#include "wisco/control/PID.hpp"

#include "IGoToPoint.hpp"

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
 * @brief PID-based control for going to a target point
 * @author Nathan Sandvig
 * 
 */
class PIDGoToPoint : public IGoToPoint
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
     * @param params The task parameters
     */
    static void taskLoop(void* params);

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

    /**
     * @brief The robot being controlled
     * 
     */
    std::shared_ptr<robot::Robot> control_robot{};

    /**
     * @brief The velocity for the motion
     * 
     */
    double motion_velocity{};

    /**
     * @brief The target x-coordinate
     * 
     */
    double target_x{};

    /**
     * @brief The target y-coordinate
     * 
     */
    double target_y{};

    /**
     * @brief Whether or not the target has been reached
     * 
     */
    bool target_reached{true};

    /**
     * @brief Whether or not the motion is paused
     * 
     */
    bool paused{};

    /**
     * @brief Set the velocity for the drive
     * 
     * @param velocity The velocity for the drive
     */
    void setDriveVelocity(double left, double right);

    /**
     * @brief Get the position from the odometry
     * 
     * @return robot::subsystems::position::Position The position from the odometry
     */
    robot::subsystems::position::Position getOdometryPosition();

    /**
     * @brief Get the velocity from the odometry
     * 
     * @return double The velocity from the odometry
     */
    double getOdometryVelocity();

    /**
     * @brief Updates the control velocity
     * 
     * @param forward_distance The forward distance to the target
     * @param target_angle The angle to the target
     * @param theta The current robot heading
     */
    void updateVelocity(double forward_distance, double target_angle, double theta);

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

public:
    /**
     * @brief Initializes the go to point controller
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the go to point controller
     * 
     */
    void run() override;

    /**
     * @brief Moves to the target position
     * 
     * @param robot The robot
     * @param velocity The motion velocity
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     */
    void goToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y) override;

    /**
     * @brief Sets the velocity of the current motion
     * 
     * @param velocity The new velocity
     */
    void setVelocity(double velocity) override;

    /**
     * @brief Pauses the current motion
     * 
     */
    void pause() override;

    /**
     * @brief Resumes the current motion
     * 
     */
    void resume() override;

    /**
     * @brief Checks if the target has been reached
     * 
     * @return true The target has been reached
     * @return false The target has not been reached
     */
    bool targetReached() override;

    /**
     * @brief Sets the rtos delayer
     * 
     * @param delayer The rtos delayer
     */
    void setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Sets the rtos mutex
     * 
     * @param mutex The rtos mutex
     */
    void setMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Sets the rtos task
     * 
     * @param task The rtos task
     */
    void setTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Sets the linear PID controller
     * 
     * @param linear_pid The linear PID controller
     */
    void setLinearPID(PID linear_pid);

    /**
     * @brief Sets the rotational PID controller
     * 
     * @param rotational_pid The rotational PID controller
     */
    void setRotationalPID(PID rotational_pid);

    /**
     * @brief Sets the target tolerance
     * 
     * @param target_tolerance The motion target tolerance
     */
    void setTargetTolerance(double target_tolerance);

    /**
     * @brief Sets the target velocity
     * 
     * @param target_velocity The motion target velocity
     */
    void setTargetVelocity(double target_velocity);
};
} // namespace motion
} // namespace control
} // namespace wisco

#endif