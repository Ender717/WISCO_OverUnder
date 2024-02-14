#include "wisco/robot/subsystems/position/InertialOdometry.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
void InertialOdometry::taskLoop(void* params)
{
    void** parameters{static_cast<void**>(params)};
    InertialOdometry* instance{static_cast<InertialOdometry*>(parameters[0])};

    while (true)
    {
        instance->taskUpdate();
    }
}

void InertialOdometry::taskUpdate()
{
    if (m_mutex)
    {
        m_mutex->take();
    }
    updatePosition();
    if (m_mutex)
    {
        m_mutex->give();
    }
    m_delayer->delay(TASK_DELAY);
}

void InertialOdometry::updatePosition()
{

}

void InertialOdometry::initialize()
{
    if (m_heading_sensor)
    {
        m_heading_sensor->initialize();
        last_heading = m_heading_sensor->getRotation();
    }
    if (m_linear_distance_tracking_sensor)
    {
        m_linear_distance_tracking_sensor->initialize();
        last_linear_distance = m_linear_distance_tracking_sensor->getDistance();
    }
    if (m_strafe_distance_tracking_sensor)
    {
        m_strafe_distance_tracking_sensor->initialize();
        last_strafe_distance = m_strafe_distance_tracking_sensor->getDistance();
    }
    if (m_clock)
    {
        last_time = m_clock->getTime();
    }
}

void InertialOdometry::run()
{
    if (m_task)
    {
        void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
        params[0] = this;
        m_task->start(&InertialOdometry::taskLoop, params);
    }
}

void InertialOdometry::setPosition(Position position)
{
    if (m_mutex)
    {
        m_mutex->take();
    }
    m_position = position;
    if (m_mutex)
    {
        m_mutex->give();
    }
}

Position InertialOdometry::getPosition()
{
    return m_position;
}

void InertialOdometry::setClock(std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = std::move(clock);
}

void InertialOdometry::setDelayer(std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = std::move(delayer);
}

void InertialOdometry::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void InertialOdometry::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void InertialOdometry::setHeadingSensor(std::unique_ptr<sensors::IHeadingSensor>& heading_sensor)
{
    m_heading_sensor = std::move(heading_sensor);
}

void InertialOdometry::setLinearDistanceTrackingSensor(std::unique_ptr<sensors::IDistanceTrackingSensor>& linear_distance_tracking_sensor)
{   
    m_linear_distance_tracking_sensor = std::move(linear_distance_tracking_sensor);
}

void InertialOdometry::setLinearDistanceTrackingOffset(double linear_distance_tracking_offset)
{
    m_linear_distance_tracking_offset = linear_distance_tracking_offset;
}

void InertialOdometry::setStrafeDistanceTrackingSensor(std::unique_ptr<sensors::IDistanceTrackingSensor>& strafe_distance_tracking_sensor)
{
    m_strafe_distance_tracking_sensor = std::move(strafe_distance_tracking_sensor);
}

void InertialOdometry::setStrafeDistanceTrackingOffset(double strafe_distance_tracking_offset)
{
    m_strafe_distance_tracking_offset = strafe_distance_tracking_offset;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco