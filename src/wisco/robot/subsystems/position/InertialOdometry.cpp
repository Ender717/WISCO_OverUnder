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
    updatePosition();
    m_delayer->delay(TASK_DELAY);
}

void InertialOdometry::updatePosition()
{
    if (m_mutex)
        m_mutex->take();

    double current_heading{};
    double current_linear_distance{};
    double current_strafe_distance{};
    uint32_t current_time{};

    if (m_heading_sensor)
        current_heading = m_heading_sensor->getRotation();
    if (m_linear_distance_tracking_sensor)
        current_linear_distance = m_linear_distance_tracking_sensor->getDistance();
    if (m_strafe_distance_tracking_sensor)
        current_strafe_distance = m_strafe_distance_tracking_sensor->getDistance();
    if (m_clock)
        current_time = m_clock->getTime();

    double heading_change{current_heading - last_heading};
    double linear_change{current_linear_distance - last_linear_distance};
    double strafe_change{current_strafe_distance - last_strafe_distance};
    uint32_t time_change{current_time - last_time};

    double local_x{};
    double local_y{};
    double local_theta{};
    if (heading_change != 0.0)
    {
        local_x = (2 * std::sin(heading_change / 2)) * ((strafe_change / heading_change) + m_strafe_distance_tracking_offset);
        local_y = (2 * std::sin(heading_change / 2)) * ((linear_change / heading_change) + m_linear_distance_tracking_offset);
        local_theta = (last_heading + current_heading) / 2;
    }
    else
    {
        local_x = strafe_change;
        local_y = linear_change;
        local_theta = current_heading;
    }


    double global_x{(-local_x * std::sin(local_theta)) + (local_y * std::cos(local_theta))};
    double global_y{(local_y * std::sin(local_theta)) + (local_x * std::cos(local_theta))};

    m_position.x += global_x;
    m_position.y += global_y;
    m_position.theta = current_heading;

    if (m_clock)
    {
        m_position.xV = global_x * time_change / TIME_UNIT_CONVERTER;
        m_position.yV = global_y * time_change / TIME_UNIT_CONVERTER;
        m_position.thetaV = heading_change * time_change / TIME_UNIT_CONVERTER;
    }

    last_heading = current_heading;
    last_linear_distance = current_linear_distance;
    last_strafe_distance = current_strafe_distance;
    last_time = current_time;

    if (m_mutex)
        m_mutex->give();
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
        last_time = m_clock->getTime();
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
        m_mutex->take();
    m_position = position;
    if (m_mutex)
        m_mutex->give();
}

Position InertialOdometry::getPosition()
{
    Position position{};
    if (m_mutex)
        m_mutex->take();
    position = m_position;
    if (m_mutex)
        m_mutex->give();
    return position;
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

void InertialOdometry::setHeadingSensor(std::unique_ptr<io::IHeadingSensor>& heading_sensor)
{
    m_heading_sensor = std::move(heading_sensor);
}

void InertialOdometry::setLinearDistanceTrackingSensor(std::unique_ptr<io::IDistanceTrackingSensor>& linear_distance_tracking_sensor)
{   
    m_linear_distance_tracking_sensor = std::move(linear_distance_tracking_sensor);
}

void InertialOdometry::setLinearDistanceTrackingOffset(double linear_distance_tracking_offset)
{
    m_linear_distance_tracking_offset = linear_distance_tracking_offset;
}

void InertialOdometry::setStrafeDistanceTrackingSensor(std::unique_ptr<io::IDistanceTrackingSensor>& strafe_distance_tracking_sensor)
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