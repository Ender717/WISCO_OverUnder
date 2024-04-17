#ifndef WISCO_CONTROL_PATH_PID_PURE_PURSUIT_HPP
#define WISCO_CONTROL_PATH_PID_PURE_PURSUIT_HPP

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

#include "IPathFollower.hpp"

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
 * @brief Pure pursuit algorithm utilizing PID controllers that implements the IPathFollower interface
 * @author Nathan Sandvig
 * 
 */
class PIDPurePursuit : public IPathFollower
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

    /**
     * @brief The robot being controlled
     * 
     */
    std::shared_ptr<robot::Robot> control_robot{};

    /**
     * @brief The path being followed
     * 
     */
    std::vector<Point> control_path{};

    /**
     * @brief The index of the furthest found point
     * 
     */
    uint32_t found_index{};

    /**
     * @brief The motion velocity in inches per second
     * 
     */
    double motion_velocity{};

    /**
     * @brief Whether or not the motion has been paused
     * 
     */
    bool paused{};

    /**
     * @brief Whether or not the target point has been reached
     * 
     */
    bool target_reached{true};

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
     * @brief Calculates the distance to the end of the path
     * 
     * @param position The current robot position
     * @return double The distance to the end of the path
     */
    double calculateDistanceToTarget(robot::subsystems::position::Position position);

    /**
     * @brief Calculates the follow point
     * 
     * @param position The current robot position
     * @return Point The point to follow
     */
    Point calculateFollowPoint(robot::subsystems::position::Position position);

    /**
     * @brief Updates the drive velocity
     * 
     * @param position The current position
     * @param follow_point The follow point
     */
    void updateVelocity(robot::subsystems::position::Position position, Point follow_point);

public:
    /**
     * @brief Initializes the path follower
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the path follower
     * 
     */
    void run() override;

    /**
     * @brief Pauses the path follower
     * 
     */
    void pause() override;

    /**
     * @brief Resumes the path follower
     * 
     */
    void resume() override;

    /**
     * @brief Follows an input path
     * 
     * @param robot The robot being controller
     * @param path The path to follow
     * @param velocity The velocity to move along the path
     */
    void followPath(const std::shared_ptr<robot::Robot>& robot, const std::vector<Point>& path, double velocity) override;

    /**
     * @brief Sets the path following velocity
     * 
     * @param velocity The velocity to follow the path
     */
    void setVelocity(double velocity) override;

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
     * @brief Sets the follow distance
     * 
     * @param follow_distance The follow distance
     */
    void setFollowDistance(double follow_distance);

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
} // namespace path
} // namespace control
} // namespace wisco

#endif