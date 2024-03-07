#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_BUILDER_HPP

#include "InertialOdometry.hpp"

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
 * @brief Builder class for the inertial odometry class
 * @author Nathan Sandvig
 * 
 */
class InertialOdometryBuilder
{
private:
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

public:
    /**
     * @brief Adds a system clock to the builder
     * 
     * @param clock The system clock
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withClock(std::unique_ptr<wisco::rtos::IClock>& clock);

    /**
     * @brief Adds a system delayer to the builder
     * 
     * @param delayer The system delayer
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withDelayer(std::unique_ptr<wisco::rtos::IDelayer>& delayer);

    /**
     * @brief Adds a system mutex to the builder
     * 
     * @param mutex The system mutex
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withMutex(std::unique_ptr<wisco::rtos::IMutex>& mutex);

    /**
     * @brief Adds a system task to the builder
     * 
     * @param task The system task
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withTask(std::unique_ptr<wisco::rtos::ITask>& task);

    /**
     * @brief Adds a heading sensor to the builder
     * 
     * @param heading_sensor The heading sensor
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withHeadingSensor(std::unique_ptr<wisco::io::IHeadingSensor>& heading_sensor);

    /**
     * @brief Adds a linear distance tracking sensor to the builder
     * 
     * @param linear_distance_tracking_sensor The linear distance tracking sensor
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withLinearDistanceTrackingSensor(std::unique_ptr<wisco::io::IDistanceTrackingSensor>& linear_distance_tracking_sensor);

    /**
     * @brief Adds a linear distance tracking offset to the builder
     * 
     * @param linear_distance_tracking_offset The linear distance tracking offset
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withLinearDistanceTrackingOffset(double linear_distance_tracking_offset);

    /**
     * @brief Adds a strafe distance tracking sensor to the builder
     * 
     * @param strafe_distance_tracking_sensor The strafe distance tracking sensor
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withStrafeDistanceTrackingSensor(std::unique_ptr<wisco::io::IDistanceTrackingSensor>& strafe_distance_tracking_sensor);

    /**
     * @brief Adds a strafe distance tracking offset to the builder
     * 
     * @param strafe_distance_tracking_offset The strafe distance tracking offset
     * @return InertialOdometryBuilder* This builder for build chaining
     */
    InertialOdometryBuilder* withStrafeDistanceTrackingOffset(double strafe_distance_tracking_offset); 

    /**
     * @brief Builds the inertial odometry system
     * 
     * @return std::unique_ptr<IPositionTracker> The inertial odometry system as a position tracking interface
     */
    std::unique_ptr<IPositionTracker> build();
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif