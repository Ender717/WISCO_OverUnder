#ifndef WISCO_ROUTINES_SENTRY_MODE_HPP
#define WISCO_ROUTINES_SENTRY_MODE_HPP

#include <cfloat>
#include <cmath>
#include <memory>
#include <vector>

#include "wisco/IAlliance.hpp"
#include "wisco/control/ControlSystem.hpp"
#include "wisco/io/VisionObject.hpp"
#include "wisco/robot/Robot.hpp"
#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

#include "wisco/control/path/Point.hpp"
#include "wisco/control/motion/ETurnDirection.hpp"
#include "wisco/robot/subsystems/drive/Velocity.hpp"
#include "wisco/robot/subsystems/position/Position.hpp"
#include "wisco/utils/UtilityFunctions.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for complex multi-system routines
 * @author Nathan Sandvig
 * 
 */
namespace routines
{

/**
 * @brief Routine for automatically detecting and scoring triballs
 * @author Nathan Sandvig
 * 
 */
class SentryMode
{
private:
    /**
     * @brief The states for sentry mode
     * 
     */
    enum class EState
    {
        SEARCH,
        TARGET,
        GRAB,
        HOLD
    };

    /**
     * @brief The loop delay for the background task
     * 
     */
    static constexpr uint8_t TASK_DELAY{5};

    /**
     * @brief The tolerance for the aim on targetting
     * 
     */
    static constexpr double AIM_TOLERANCE{M_PI / 72};

    /**
     * @brief The velocity for boomerang motions
     * 
     */
    static constexpr double BOOMERANG_VELOCITY{36.0};

    /**
     * @brief The position of the elevator when holding a ball
     * 
     */
    static constexpr double ELEVATOR_BALL{3.25};

    /**
     * @brief The position of the elevator when the elevator is out
     * 
     */
    static constexpr double ELEVATOR_OUT{18};

    /**
     * @brief The offset from the robot position to the elevator position
     * 
     */
    static constexpr double ELEVATOR_OFFSET{6};

    /**
     * @brief The tolerance to wait for the elevator
     * 
     */
    static constexpr double ELEVATOR_TOLERANCE{1};

    /**
     * @brief The voltage for the intake
     * 
     */
    static constexpr double INTAKE_VOLTAGE{12};

    /**
     * @brief The extra distance to move towards a ball
     * 
     */
    static constexpr double MOTION_OFFSET{0};

    /**
     * @brief The minimum object size to be visually targetted
     * 
     */
    static constexpr double MINIMUM_OBJECT_SIZE{0.15};

    /**
     * @brief The distance to turn before resuming a search after skipping
     * 
     */
    static constexpr double SKIP_DISTANCE{M_PI / 18};

    /**
     * @brief The delay to wait for a distance sensor measurement
     * 
     */
    static constexpr uint32_t DISTANCE_DELAY{20};

    /**
     * @brief The velocity to turn
     * 
     */
    static constexpr double TURN_VELOCITY{2 * M_PI};

    /**
     * @brief The task loop function
     * 
     * @param params The task parameters
     */
    static void taskLoop(void* params);

    /**
     * @brief The alliance
     * 
     */
    std::shared_ptr<IAlliance> m_alliance{};

    /**
     * @brief The rtos clock
     * 
     */
    std::shared_ptr<rtos::IClock> m_clock{};

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
     * @brief The control system
     * 
     */
    std::shared_ptr<control::ControlSystem> m_control_system{};

    /**
     * @brief The robot
     * 
     */
    std::shared_ptr<robot::Robot> m_robot{};

    /**
     * @brief The state of the routine
     * 
     */
    EState state{};

    /**
     * @brief The last distance sensor reading
     * 
     */
    double last_distance{};

    /**
     * @brief The angle to stop at if no balls are detected
     * 
     */
    double m_end_angle{};

    /**
     * @brief The target angle for a search ball
     * 
     */
    double target_angle{};

    /**
     * @brief The angle to skip to
     * 
     */
    double skip_angle{};

    /**
     * @brief The time the distance measurement started
     * 
     */
    uint32_t distance_time{};

    /**
     * @brief The direction to rotate
     * 
     */
    control::motion::ETurnDirection m_direction{};

    /**
     * @brief The location of the ball
     * 
     */
    control::path::Point ball{};

    /**
     * @brief The distance setting for the elevator when grabbing
     * 
     */
    double elevator_distance{};

    /**
     * @brief Whether or not sentry mode has finished
     * 
     */
    bool finished{};

    /**
     * @brief Whether or not sentry mode is paused
     * 
     */
    bool paused{};

    /**
     * @brief Get the position of the elevator
     * 
     * @return double The position of the elevator
     */
    double getElevatorPosition();

    /**
     * @brief Get the distance to the ball
     * 
     * @return double The distance to the ball
     */
    double getBallDistance();

    /**
     * @brief Get the ball vision objects
     * 
     * @return std::vector<io::VisionObject> The ball vision objects
     */
    std::vector<io::VisionObject> getBallVisionObjects();

    /**
     * @brief Get the position from odometry
     * 
     * @return robot::subsystems::position::Position The odometry position
     */
    robot::subsystems::position::Position getOdometryPosition();

    /**
     * @brief Set the position of the elevator
     * 
     * @param position The elevator position
     */
    void setElevatorPosition(double position);

    /**
     * @brief Set the velocity for the drive
     * 
     * @param left The left drive velocity
     * @param right The right drive velocity
     */
    void setDriveVelocity(double left, double right);

    /**
     * @brief Set the voltage of the intake
     * 
     * @param voltage The intake voltage
     */
    void setIntakeVoltage(double voltage);

    /**
     * @brief Moves to a target position using boomerang
     * 
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     * @param theta The target angle
     * @param velocity The motion velocity
     */
    void boomerangGoToPoint(double x, double y, double theta, double velocity);

    /**
     * @brief Checks if the boomerang target has been reached
     * 
     * @return true The boomerang target has been reached
     * @return false The boomerang target has not been reached
     */
    bool boomerangTargetReached();

    /**
	 * @brief Drives straight with a specified angle
	 * 
	 * @param distance The distance to drive (negative = reverse)
	 * @param velocity The velocity to move
	 * @param theta The angle to keep pointed forward
	 * @param timeout The milliseconds allowed before timing out
	 */
	void driveStraight(double distance, double velocity, double theta, uint32_t timeout = UINT32_MAX);

    /**
	 * @brief Checks if the drive straight target has been reached
	 * 
	 * @return true The drive straight target has been reached
	 * @return false The drive straight target has not been reached
	 */
	bool driveStraightTargetReached();

    /**
     * @brief Turns to a target angle
     * 
     * @param theta The target angle
     * @param velocity The turn velocity
     * @param reversed Whether or not to turn to face away from the angle
     * @param direction The turn direction
     */
    void turnToAngle(double theta, double velocity, bool reversed = false, control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

    /**
     * @brief Turns to face a target point
     * 
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     * @param velocity The turn velocity
     * @param reversed Whether or not to turn to face away from the point
     * @param direction The turn direction
     */
    void turnToPoint(double x, double y, double velocity, bool reversed = false, control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

    /**
     * @brief Checks if the turn target has been reached
     * 
     * @return true The turn target has been reached
     * @return false The turn target has not been reached
     */
    bool turnTargetReached();

    /**
     * @brief Checks if a point exists
     * 
     * @param point The input point
     * @return true The point exists (non-zero values)
     * @return false The point does not exist (zero values)
     */
    bool pointExists(control::path::Point point);

    /**
     * @brief Checks if a point is valid for sentry mode
     * 
     * @param point The point
     * @return true The point is valid
     * @return false The point is invalid
     */
    bool isValid(control::path::Point point);

    /**
     * @brief Updates the search state
     * 
     */
    void updateSearch();

    /**
     * @brief Updates the target state
     * 
     */
    void updateTarget();

    /**
     * @brief Updates the grab state
     * 
     */
    void updateGrab();

    /**
     * @brief Updates the hold state
     * 
     */
    void updateHold();

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

public:
    /**
     * @brief Construct a new Sentry Mode object
     * 
     * @param alliance The alliance
     * @param clock The rtos clock
     * @param delayer The rtos delayer
     * @param mutex The rtos mutex
     * @param task The rtos task
     * @param control_system The control system
     * @param robot The robot
     */
    SentryMode(const std::shared_ptr<IAlliance>& alliance,
               const std::shared_ptr<rtos::IClock>& clock,
               const std::unique_ptr<rtos::IDelayer>& delayer,
               std::unique_ptr<rtos::IMutex>& mutex,
               std::unique_ptr<rtos::ITask>& task,
               const std::shared_ptr<control::ControlSystem>& control_system,
               const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Runs sentry mode
     *  
     */
    void run();

    /**
     * @brief Does a sentry mode routine
     * 
     * @param end_angle The angle to end at if no balls are found
     * @param direction The direction to turn
     */
    void doSentryMode(double end_agle, control::motion::ETurnDirection direction);

    /**
     * @brief Pauses sentry mode
     * 
     */
    void pause();

    /**
     * @brief Resumes sentry mode
     * 
     */
    void resume();

    /**
     * @brief Checks if a ball has been found
     * 
     * @return true A ball has been found
     * @return false A ball has not been found
     */
    bool ballFound();

    /**
     * @brief Get the coordinates of the ball
     * 
     * @return control::path::Point The coordinates of the ball
     */
    control::path::Point getBall();

    /**
     * @brief Checks if sentry mode is finished
     * 
     * @return true Sentry mode is finished
     * @return false Sentry mode is not finished
     */
    bool isFinished();
};
} // namespace routines
} // namespace wisco

#endif