#include "wisco/control/boomerang/PIDBoomerang.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

namespace wisco
{
namespace control
{
namespace boomerang
{
void PIDBoomerang::taskLoop(void* params)
{
    PIDBoomerang* instance{static_cast<PIDBoomerang*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDBoomerang::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    
    if (!paused && !target_reached)
    {
        auto position{getOdometryPosition()};
        double distance{calculateDistanceToTarget(position)};
        double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
        if (distance < m_target_tolerance && velocity < m_target_velocity)
        {
            target_reached = true;
            robot::subsystems::drive::Velocity stop{0, 0};
            setDriveVelocity(stop);
        }
        else
        {
            path::Point carrot_point{calculateCarrotPoint(distance)};
            updateVelocity(position, carrot_point);
        }
    }

    if (m_mutex)
        m_mutex->give();

    m_delayer->delay(TASK_DELAY);
}

void PIDBoomerang::setDriveVelocity(robot::subsystems::drive::Velocity velocity)
{
    if (control_robot)
        control_robot->sendCommand(DRIVE_SUBSYSTEM_NAME, DRIVE_SET_VELOCITY_COMMAND_NAME, velocity);
}

robot::subsystems::position::Position PIDBoomerang::getOdometryPosition()
{
    robot::subsystems::position::Position position{};

    if (control_robot)
    {
        robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(control_robot->getState(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_GET_POSITION_STATE_NAME))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }

    return position;
}

double PIDBoomerang::calculateDistanceToTarget(wisco::robot::subsystems::position::Position position)
{
    double x2{std::pow(target_x - position.x, 2)};
    double y2{std::pow(target_y - position.y, 2)};
    double distance{std::sqrt(x2 + y2)};
    return distance;
}

path::Point PIDBoomerang::calculateCarrotPoint(double distance)
{
    double carrot_x{target_x - (distance * std::cos(target_theta)) * m_lead};
    double carrot_y{target_y - (distance * std::sin(target_theta)) * m_lead};
    return path::Point{carrot_x, carrot_y};
}

void PIDBoomerang::updateVelocity(robot::subsystems::position::Position position, path::Point carrot_point)
{
    double x_error{carrot_point.getX() - position.x};
    double y_error{carrot_point.getY() - position.y};
    
    double rotational_error{bindRadians(std::atan2(y_error, x_error) - position.theta)};
    double linear_error{std::cos(rotational_error) * std::sqrt(std::pow(x_error, 2) + std::pow(y_error, 2))};
    if (linear_error < 0)
        rotational_error = bindRadians(rotational_error + M_PI);

    double linear_control{m_linear_pid.getControlValue(0, linear_error)};
    if (std::abs(linear_control) > motion_velocity)
        linear_control *= motion_velocity / std::abs(linear_control);
    double rotational_control{};
    if (distance(position.x, position.y, target_x, target_y) > m_aim_distance)
        rotational_control = m_rotational_pid.getControlValue(0, rotational_error);

    double left_velocity{linear_control - rotational_control};
    double right_velocity{linear_control + rotational_control};
    robot::subsystems::drive::Velocity velocity{left_velocity, right_velocity};
    setDriveVelocity(velocity);
}

void PIDBoomerang::initialize()
{
    m_linear_pid.reset();
    m_rotational_pid.reset();
}

void PIDBoomerang::run()
{
    if (m_task)
        m_task->start(&PIDBoomerang::taskLoop, this);
}

void PIDBoomerang::goToPosition(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, double theta)
{
    if (m_mutex)
        m_mutex->take();

    control_robot = robot;
    motion_velocity = velocity;
    target_x = x;
    target_y = y;
    target_theta = theta;
    target_reached = false;

    auto position{getOdometryPosition()};
    double target_angle{angle(position.x, position.y, target_x, target_y)};
    double angle_error{bindRadians(target_angle - position.theta)};
    if (std::abs(angle_error) > M_PI / 2)
        target_theta = bindRadians(target_theta + M_PI);

    if (m_mutex)
        m_mutex->give();
}

void PIDBoomerang::pause()
{
    if (m_mutex)
        m_mutex->take();
    
    paused = true;
    robot::subsystems::drive::Velocity stop{0, 0};
    setDriveVelocity(stop);

    if (m_mutex)
        m_mutex->give();
}

void PIDBoomerang::resume()
{
    if (m_mutex)
        m_mutex->take();

    paused = false;

    if (m_mutex)
        m_mutex->give();
}

bool PIDBoomerang::targetReached()
{
    return target_reached;
}

void PIDBoomerang::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDBoomerang::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDBoomerang::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDBoomerang::setLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
}

void PIDBoomerang::setRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
}

void PIDBoomerang::setLead(double lead)
{
    m_lead = lead;
}

void PIDBoomerang::setAimDistance(double aim_distance)
{
    m_aim_distance = aim_distance;
}

void PIDBoomerang::setTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
}

void PIDBoomerang::setTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
}
} // namespace boomerang
} // namespace control
} // namespace wisco