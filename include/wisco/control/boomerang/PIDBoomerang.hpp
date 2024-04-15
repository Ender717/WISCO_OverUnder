#ifndef WISCO_CONTROL_BOOMERANG_PID_BOOMERANG_HPP
#define WISCO_CONTROL_BOOMERANG_PID_BOOMERANG_HPP

#include <cmath>
#include <memory>

#include "wisco/utils/UtilityFunctions.hpp"

#include "wisco/robot/Robot.hpp"
#include "wisco/robot/subsystems/drive/Velocity.hpp"
#include "wisco/robot/subsystems/position/Position.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

#include "wisco/control/path/Point.hpp"
#include "wisco/control/PID.hpp"

#include "IBoomerang.hpp"

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
 * @brief Boomerang controller for the robot drivetrain
 * @author Nathan Sandvig
 * 
 */
class PIDBoomerang : public IBoomerang
{
private:
    /**
     * @brief The loop delay on the task
     * 
     */
    static constexpr uint8_t TASK_DELAY{10};

    /**
     * @brief The name of the drive subsystem
     * 
     */
    static constexpr char DRIVE_SUBSYSTEM_NAME[]{"DIFFERENTIAL DRIVE"};

    /**
     * @brief The name of the odometry subsystem
     * 
     */
    static constexpr char ODOMETRY_SUBSYSTEM_NAME[]{"POSITION TRACKER"};

    /**
     * @brief The name of the drive set velocity command
     * 
     */
    static constexpr char DRIVE_SET_VELOCITY_COMMAND_NAME[]{"SET VELOCITY"};

    /**
     * @brief The name of the odometry get position command
     * 
     */
    static constexpr char ODOMETRY_GET_POSITION_STATE_NAME[]{"GET POSITION"};

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
     * @brief The lead ratio for the carrot point
     * 
     */
    double m_lead{};

    /**
     * @brief The acceptable tolerance to reach the target
     * 
     */
    double m_target_tolerance{};

    /**
     * @brief The robot being controlled
     * 
     */
    std::shared_ptr<robot::Robot> control_robot{};

    /**
     * @brief The motion velocity in inches per second
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
     * @brief The target angle
     * 
     */
    double target_theta{};

    /**
     * @brief Whether or not the motion has been paused
     * 
     */
    bool paused{};

    /**
     * @brief Whether or not the target point has been reached
     * 
     */
    bool target_reached{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Set the velocity for the drive
     * 
     * @param velocity The velocity for the drive
     */
    void setDriveVelocity(robot::subsystems::drive::Velocity velocity);

    /**
     * @brief Get the position from the odometry
     * 
     * @return robot::subsystems::position::Position The position from the odometry
     */
    robot::subsystems::position::Position getOdometryPosition();

    /**
     * @brief Calculates the distance to the target position
     * 
     * @param position The current position
     * @return double The distance to the target position
     */
    double calculateDistanceToTarget(wisco::robot::subsystems::position::Position position);

    /**
     * @brief Calculates the carrot point
     * 
     * @param distance The distance to the target point
     * @return path::Point The carrot point
     */
    path::Point calculateCarrotPoint(double distance);

    /**
     * @brief Updates the drive velocity
     * 
     * @param position The current position
     * @param carrot_point The carrot point
     */
    void updateVelocity(robot::subsystems::position::Position position, path::Point carrot_point);

public: 
    /**
     * @brief Initializes the boomerang controller
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the boomerang controller
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
     * @param theta The target angle
     */
    void goToPosition(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, double theta) override;

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
     * @brief Sets the lead ratio
     * 
     * @param lead The lead ratio
     */
    void setLead(double lead);

    /**
     * @brief Sets the target tolerance
     * 
     * @param target_tolerance The motion target tolerance
     */
    void setTargetTolerance(double target_tolerance);
};
} // namespace boomerang
} // namespace control
} // namespace wisco

#endif