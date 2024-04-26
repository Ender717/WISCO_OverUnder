#include "wisco/control/motion/PIDGoToPoint.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
void PIDGoToPoint::taskLoop(void* params)
{
    PIDGoToPoint* instance{static_cast<PIDGoToPoint*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDGoToPoint::setDriveVelocity(double left, double right)
{
    if (control_robot)
        control_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

robot::subsystems::position::Position PIDGoToPoint::getOdometryPosition()
{
    robot::subsystems::position::Position position{};
    if (control_robot)
    {
        robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(control_robot->getState("POSITION TRACKER", "GET POSITION"))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }
    return position;
}

double PIDGoToPoint::getOdometryVelocity()
{
    auto position{getOdometryPosition()};
    return std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2));;
}

void PIDGoToPoint::updateVelocity(double forward_distance, double target_angle, double theta)
{
    double linear_control{m_linear_pid.getControlValue(0, forward_distance)};

    double rotational_offset{bindRadians(target_angle - theta)};
    double error{};
    if (rotational_offset < 0)
        error = ((2 / M_PI) * std::abs(rotational_offset + (M_PI / 2))) - 1;
    else if (rotational_offset > 0)
        error = ((-2 / M_PI) * std::abs(rotational_offset - (M_PI / 2))) + 1;
    else
        error = 0;
    double rotational_control{m_rotational_pid.getControlValue(0, error)};

    if (std::abs(linear_control) > motion_velocity)
        linear_control *= motion_velocity / std::abs(linear_control);

    double left_velocity{linear_control * (1 + rotational_control)};
    double right_velocity{linear_control * (1 - rotational_control)};

    setDriveVelocity(left_velocity, right_velocity);
}

void PIDGoToPoint::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    if (!target_reached && !paused)
    {
        // Check if finished
        auto position{getOdometryPosition()};
        double target_distance{distance(position.x, position.y, target_x, target_y)};
        double target_angle{angle(position.x, position.y, target_x, target_y)};
        double forward_distance{target_distance * std::cos(target_angle - position.theta)};
        double velocity{getOdometryVelocity()};
        if (std::abs(forward_distance) < m_target_tolerance && velocity < m_target_velocity)
            target_reached = true;
        else
            updateVelocity(forward_distance, target_angle, position.theta);
    }
    if (m_mutex)
        m_mutex->give();
    if (m_delayer)
        m_delayer->delay(TASK_DELAY);
}

void PIDGoToPoint::initialize()
{
    m_linear_pid.reset();
    m_rotational_pid.reset();
}

void PIDGoToPoint::run()
{
    if (m_task)
        m_task->start(&PIDGoToPoint::taskLoop, this);
}

void PIDGoToPoint::pause()
{
    if (m_mutex)
        m_mutex->take();
    
    paused = true;
    setDriveVelocity(0, 0);

    if (m_mutex)
        m_mutex->give();
}

void PIDGoToPoint::resume()
{
    if (m_mutex)
        m_mutex->take();

    paused = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDGoToPoint::goToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y)
{
    if (m_mutex)
        m_mutex->take();
    
    m_linear_pid.reset();
    m_rotational_pid.reset();
    control_robot = robot;
    motion_velocity = velocity;
    target_x = x;
    target_y = y;
    target_reached = false;
    paused = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDGoToPoint::setVelocity(double velocity)
{
    if (m_mutex)
        m_mutex->take();
    motion_velocity = velocity;
    if (m_mutex)
        m_mutex->give();
}

bool PIDGoToPoint::targetReached()
{
    return target_reached;
}

void PIDGoToPoint::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDGoToPoint::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}   

void PIDGoToPoint::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDGoToPoint::setLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
}

void PIDGoToPoint::setRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
}

void PIDGoToPoint::setTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
}

void PIDGoToPoint::setTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
}
} // namespace motion
} // namespace control
} // namespace wisco