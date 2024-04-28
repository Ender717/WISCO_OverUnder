#include "wisco/control/motion/PIDDriveStraight.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
void PIDDriveStraight::taskLoop(void* params)
{
    PIDDriveStraight* instance{static_cast<PIDDriveStraight*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDDriveStraight::setDriveVelocity(double left, double right)
{
    if (control_robot)
        control_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

robot::subsystems::position::Position PIDDriveStraight::getOdometryPosition()
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

double PIDDriveStraight::getOdometryVelocity()
{
    auto position{getOdometryPosition()};
    return std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2));;
}

void PIDDriveStraight::updateVelocity(double control_distance, double theta)
{
    double linear_control{m_linear_pid.getControlValue(0, control_distance)};
    double rotational_control{m_rotational_pid.getControlValue(0, bindRadians(target_angle - theta))};
    
    if (std::abs(linear_control) > motion_velocity)
        linear_control *= motion_velocity / std::abs(linear_control);
    double left_velocity{linear_control - rotational_control};
    double right_velocity{linear_control + rotational_control};
    setDriveVelocity(left_velocity, right_velocity);
}

void PIDDriveStraight::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    if (!target_reached && !paused)
    {
        auto position{getOdometryPosition()};
        double start_distance{distance(start_x, start_y, position.x, position.y)};
        double start_angle{angle(start_x, start_y, position.x, position.y)};
        if (target_distance < 0)
        {
            start_distance *= -1;
            start_angle = bindRadians(start_angle + M_PI);
        }
        double control_distance{target_distance - (start_distance * std::cos(bindRadians(start_angle - target_angle)))};
        double velocity{getOdometryVelocity()};
        if (std::abs(control_distance) < m_target_tolerance && velocity < m_target_velocity)
            target_reached = true;
        else
            updateVelocity(control_distance, position.theta);
    }
    if (m_mutex)
        m_mutex->give();
    if (m_delayer)
        m_delayer->delay(TASK_DELAY);
}

void PIDDriveStraight::initialize()
{
    m_linear_pid.reset();
    m_rotational_pid.reset();
}

void PIDDriveStraight::run()
{
    if (m_task)
        m_task->start(&PIDDriveStraight::taskLoop, this);
}

void PIDDriveStraight::pause()
{
    if (m_mutex)
        m_mutex->take();
    
    paused = true;
    setDriveVelocity(0, 0);

    if (m_mutex)
        m_mutex->give();
}

void PIDDriveStraight::resume()
{
    if (m_mutex)
        m_mutex->take();

    paused = false;
    m_linear_pid.reset();
    m_rotational_pid.reset();

    if (m_mutex)
        m_mutex->give();
}

void PIDDriveStraight::driveStraight(std::shared_ptr<robot::Robot> robot,
                                     double distance, double velocity, double theta)
{
    if (m_mutex)
        m_mutex->take();
    
    m_linear_pid.reset();
    m_rotational_pid.reset();
    control_robot = robot;
    motion_velocity = velocity;
    auto position{getOdometryPosition()};
    start_x = position.x;
    start_y = position.y;
    target_distance = distance;
    target_angle = theta;
    target_reached = false;
    paused = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDDriveStraight::setVelocity(double velocity)
{
    if (m_mutex)
        m_mutex->take();
    motion_velocity = velocity;
    if (m_mutex)
        m_mutex->give();
}

bool PIDDriveStraight::targetReached()
{
    return target_reached;
}

void PIDDriveStraight::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDDriveStraight::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}   

void PIDDriveStraight::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDDriveStraight::setLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
}

void PIDDriveStraight::setRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
}

void PIDDriveStraight::setTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
}

void PIDDriveStraight::setTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
}
} // namespace motion
} // namespace control
} // namespace wisco