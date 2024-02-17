#include "wisco/robot/subsystems/position/InertialOdometryBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
InertialOdometryBuilder* InertialOdometryBuilder::withClock(std::unique_ptr<wisco::rtos::IClock>& clock)
{
    m_clock = std::move(clock);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withDelayer(std::unique_ptr<wisco::rtos::IDelayer>& delayer)
{
    m_delayer = std::move(delayer);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withMutex(std::unique_ptr<wisco::rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withTask(std::unique_ptr<wisco::rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withHeadingSensor(std::unique_ptr<wisco::io::IHeadingSensor>& heading_sensor)
{
    m_heading_sensor = std::move(heading_sensor);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withLinearDistanceTrackingSensor(std::unique_ptr<wisco::io::IDistanceTrackingSensor>& linear_distance_tracking_sensor)
{
    m_linear_distance_tracking_sensor = std::move(linear_distance_tracking_sensor);
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withLinearDistanceTrackingOffset(double linear_distance_tracking_offset)
{
    m_linear_distance_tracking_offset = linear_distance_tracking_offset;
    return this;
}

InertialOdometryBuilder* InertialOdometryBuilder::withStrafeDistanceTrackingSensor(std::unique_ptr<wisco::io::IDistanceTrackingSensor>& strafe_distance_tracking_sensor)
{
    m_strafe_distance_tracking_sensor = std::move(strafe_distance_tracking_sensor);
    return this;
}   

InertialOdometryBuilder* InertialOdometryBuilder::withStrafeDistanceTrackingOffset(double strafe_distance_tracking_offset)
{
    m_strafe_distance_tracking_offset = strafe_distance_tracking_offset;
    return this;
}

std::unique_ptr<IPositionTracker> InertialOdometryBuilder::build()
{
    std::unique_ptr<InertialOdometry> inertial_odometry{std::make_unique<InertialOdometry>()};
    inertial_odometry->setClock(m_clock);
    inertial_odometry->setDelayer(m_delayer);
    inertial_odometry->setMutex(m_mutex);
    inertial_odometry->setTask(m_task);
    inertial_odometry->setHeadingSensor(m_heading_sensor);
    inertial_odometry->setLinearDistanceTrackingSensor(m_linear_distance_tracking_sensor);
    inertial_odometry->setLinearDistanceTrackingOffset(m_linear_distance_tracking_offset);
    inertial_odometry->setStrafeDistanceTrackingSensor(m_strafe_distance_tracking_sensor);
    inertial_odometry->setStrafeDistanceTrackingOffset(m_strafe_distance_tracking_offset);
    return inertial_odometry;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco