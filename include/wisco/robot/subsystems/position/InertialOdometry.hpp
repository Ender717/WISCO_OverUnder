#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_HPP

#include <cmath>
#include <memory>

#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"
#include "wisco/io/IHeadingSensor.hpp"
#include "wisco/io/IDistanceTrackingSensor.hpp"

#include "IPositionTracker.hpp"

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
 * @brief Namespace for all position subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace position
{

/**
 * @brief An odometry system based on a heading sensor with two distance tracking sensors
 * @author Nathan Sandvig
 * 
 */
class InertialOdometry : public IPositionTracker
{
private:
    /**
     * @brief The loop delay on the task
     * 
     */
    static constexpr uint8_t TASK_DELAY{10};

    /**
     * @brief Converts the time units for velocity
     * 
     */
    static constexpr double TIME_UNIT_CONVERTER{1000};

    /**
     * @brief The size of the velocity buffer
     * 
     */
    static constexpr uint8_t VELOCITY_BUFFER{4};

    /**
     * @brief The task loop function for background updates
     * 
     * @param params 
     */
    static void taskLoop(void* params);

    /**
     * @brief The system clock
     * 
     */
    std::unique_ptr<rtos::IClock> m_clock{};

    /**
     * @brief The system delayer
     * 
     */
    std::unique_ptr<rtos::IDelayer> m_delayer{};

    /**
     * @brief The os mutex
     * 
     */
    std::unique_ptr<rtos::IMutex> m_mutex{};

    /**
     * @brief The task handler
     * 
     */
    std::unique_ptr<rtos::ITask> m_task{};

    /**
     * @brief The sensor to track the robot's heading
     * 
     */
    std::unique_ptr<io::IHeadingSensor> m_heading_sensor{};

    /**
     * @brief The sensor to track the robot's linear movement
     * 
     */
    std::unique_ptr<io::IDistanceTrackingSensor> m_linear_distance_tracking_sensor{};

    /**
     * @brief The offset from the linear distance tracking sensor to the tracking center
     *        This value is left-justified, I.E. the offset to the left of center
     * 
     */
    double m_linear_distance_tracking_offset{};

    /**
     * @brief The sensor to track the robot's strafe movement
     * 
     */
    std::unique_ptr<io::IDistanceTrackingSensor> m_strafe_distance_tracking_sensor{};

    /**
     * @brief The offset from the strafe distance tracking sensor to the tracking center
     *        This value is front-justified, I.E. the offset to the front of center
     * 
     */
    double m_strafe_distance_tracking_offset{};

    /**
     * @brief The current position of the system
     * 
     */
    Position m_position{};

    /**
     * @brief The buffer for xV
     * 
     */
    double x_velocity[VELOCITY_BUFFER]{};

    /**
     * @brief The buffer for yV
     * 
     */
    double y_velocity[VELOCITY_BUFFER]{};

    /**
     * @brief The buffer for thetaV
     * 
     */
    double theta_velocity[VELOCITY_BUFFER]{};

    /**
     * @brief The current velocity index
     * 
     */
    uint8_t velocity_index{};

    /**
     * @brief The last value of the heading sensor
     * 
     */
    double last_heading{};

    /**
     * @brief The last value of the linear distance tracking sensor
     * 
     */
    double last_linear_distance{};

    /**
     * @brief The last value of the strafe distance tracking sensor
     * 
     */
    double last_strafe_distance{};

    /**
     * @brief The last value of the system clock time
     * 
     */
    uint32_t last_time{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Updates the position of the system
     * 
     */
    void updatePosition();

public:
    /**
     * @brief Initializes the position tracking system
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the position tracking system
     * 
     */
    void run() override;

    /**
     * @brief Set the position of the position tracking system
     * 
     * @param position The new position
     */
    void setPosition(Position position) override;

    /**
     * @brief Get the position of the system
     * 
     * @return Position The position of the system
     */
    Position getPosition() override;

    /**
     * @brief Set the system clock
     * 
     * @param clock The system clock
     */
    void setClock(std::unique_ptr<rtos::IClock>& clock);

    /**
     * @brief Set the rtos delayer
     * 
     * @param delayer The rtos delayer
     */
    void setDelayer(std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Set the os mutex
     * 
     * @param mutex The os mutex
     */
    void setMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Set the rtos task handler
     * 
     * @param task The rtos task handler
     */
    void setTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Set the heading sensor
     * 
     * @param heading_sensor The heading sensor
     */
    void setHeadingSensor(std::unique_ptr<io::IHeadingSensor>& heading_sensor);

    /**
     * @brief Set the linear distance tracking sensor
     * 
     * @param linear_distance_tracking_sensor The linear distance tracking sensor
     */
    void setLinearDistanceTrackingSensor(std::unique_ptr<io::IDistanceTrackingSensor>& linear_distance_tracking_sensor);

    /**
     * @brief Set the linear distance tracking offset
     * 
     * @param linear_distance_tracking_offset The linear distance tracking offset
     */
    void setLinearDistanceTrackingOffset(double linear_distance_tracking_offset);

    /**
     * @brief Set the strafe distance tracking sensor
     * 
     * @param strafe_distance_tracking_sensor The strafe distance tracking sensor
     */
    void setStrafeDistanceTrackingSensor(std::unique_ptr<io::IDistanceTrackingSensor>& strafe_distance_tracking_sensor);

    /**
     * @brief Set the strafe distance tracking offset
     * 
     * @param strafe_distance_tracking_offset The strafe distance tracking offset
     */
    void setStrafeDistanceTrackingOffset(double strafe_distance_tracking_offset);    
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif