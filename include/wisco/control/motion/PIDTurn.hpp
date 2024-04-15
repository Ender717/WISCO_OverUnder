#ifndef WISCO_CONTROL_MOTION_PID_TURN_HPP
#define WISCO_CONTROL_MOTION_PID_TURN_HPP

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

#include "ITurn.hpp"

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
 * @brief Interface for turn motion controls
 * @author Nathan Sandvig
 * 
 */
class PIDTurn : public ITurn
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
     * @brief The name of the drive get radius command
     * 
     */
    static constexpr char DRIVE_GET_RADIUS_STATE_NAME[]{"GET RADIUS"};

    /**
     * @brief The name of the odometry get position command
     * 
     */
    static constexpr char ODOMETRY_GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The distance to calculate a point at for turn to angle
     * 
     */
    static constexpr double TURN_TO_ANGLE_DISTANCE{120000};

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

    /**
     * @brief The robot being controlled
     * 
     */
    std::shared_ptr<robot::Robot> control_robot{};

    /**
     * @brief The turn direction
     * 
     */
    ETurnDirection turn_direction{};

    /**
     * @brief The turn velocity in radians per second
     * 
     */
    double turn_velocity{};

    /**
     * @brief Whether or not the turn should be reversed
     * 
     */
    bool turn_reversed{};
    
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
     * @brief Whether or not the forced direction has been reached
     * 
     */
    bool forced_direction_reached{};

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
     * @brief Get the radius of the drive
     * 
     * @return double The radius of the drive
     */
    double getDriveRadius();

    /**
     * @brief Get the position from the odometry
     * 
     * @return robot::subsystems::position::Position The position from the odometry
     */
    robot::subsystems::position::Position getOdometryPosition();

    /**
     * @brief Calculates the angle to the target position
     * 
     * @param position The current position
     * @return double The angle to the target position
     */
    double calculateAngleToTarget(wisco::robot::subsystems::position::Position position);

    /**
     * @brief Calculates the velocity of the drive
     * 
     * @param robot_angle The robot angle
     * @param target_angle The angle to the target point
     * @return robot::subsystems::drive::Velocity The drive velocity
     */
    robot::subsystems::drive::Velocity calculateDriveVelocity(double robot_angle, double target_angle);

public:
    /**
     * @brief Initializes the turn
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the turn
     * 
     */
    void run() override;

    /**
     * @brief Turns to the target angle
     * 
     * @param robot The robot
     * @param velocity The angular velocity
     * @param theta The target angle
     * @param reversed Whether or not to turn to face away from the point
     * @param direction The turn direction (default AUTO)
     */
    void turnToAngle(const std::shared_ptr<robot::Robot>& robot, double velocity, double theta, 
                     bool reversed = false, ETurnDirection direction = ETurnDirection::AUTO) override;

    /**
     * @brief Turns to the target point
     * 
     * @param robot The robot
     * @param velocity The angular velocity
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     * @param reversed Whether or not to turn to face away from the point
     * @param direction The turn direction (default AUTO)
     */
    void turnToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, 
                     bool reversed = false, ETurnDirection direction = ETurnDirection::AUTO) override;

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
     * @brief Sets the PID controller
     * 
     * @param pid The PID controller
     */
    void setPID(PID pid);

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