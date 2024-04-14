#include "wisco/control/motion/PIDTurn.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
void PIDTurn::taskLoop(void* params)
{
    void** parameters{static_cast<void**>(params)};
    PIDTurn* instance{static_cast<PIDTurn*>(parameters[0])};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDTurn::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    
    if (!paused && !target_reached)
    {
        auto position{getOdometryPosition()};
        double target_angle{calculateAngleToTarget(position)};
        if (bindRadians(target_angle - position.theta) < m_target_tolerance)
        {
            target_reached = true;
            robot::subsystems::drive::Velocity stop{0, 0};
            setDriveVelocity(stop);
        }
        else
        {
            robot::subsystems::drive::Velocity velocity{calculateDriveVelocity(position.theta, target_angle)};
            setDriveVelocity(velocity);
        }
    }

    if (m_mutex)
        m_mutex->give();

    m_delayer->delay(TASK_DELAY);
}

void PIDTurn::setDriveVelocity(robot::subsystems::drive::Velocity velocity)
{
    if (control_robot)
        control_robot->sendCommand(DRIVE_SUBSYSTEM_NAME, DRIVE_SET_VELOCITY_COMMAND_NAME, velocity);
}

robot::subsystems::position::Position PIDTurn::getOdometryPosition()
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

double PIDTurn::calculateAngleToTarget(wisco::robot::subsystems::position::Position position)
{
    double x_error{target_x - position.x};
    double y_error{target_y - position.y};
    double angle{std::atan2(y_error, x_error)};
    return angle;
}

robot::subsystems::drive::Velocity PIDTurn::calculateDriveVelocity(double robot_angle, double target_angle)
{
    double error{bindRadians(target_angle - robot_angle)};
    if (turn_direction == ETurnDirection::CLOCKWISE && error > 0)
        error -= 2 * M_PI;
    else if (turn_direction == ETurnDirection::COUNTERCLOCKWISE && error < 0)
        error += 2 * M_PI;

    double control_value{m_pid.getControlValue(0, error)};
    if (std::abs(control_value) > turn_velocity)
        control_value *= turn_velocity / std::abs(control_value);
    robot::subsystems::drive::Velocity velocity{-control_value, control_value};
    return velocity;
}

void PIDTurn::initialize()
{
    m_pid.reset();
}

void PIDTurn::run()
{
    if (m_task)
    {
        void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
        params[0] = this;
        m_task->start(&PIDTurn::taskLoop, params);
    }
}

void PIDTurn::turnToAngle(const std::shared_ptr<robot::Robot>& robot, double velocity, double theta, ETurnDirection direction)
{
    if (m_mutex)
        m_mutex->take();

    m_pid.reset();

    control_robot = robot;
    auto position{getOdometryPosition()};

    turn_direction = direction;
    turn_velocity = velocity;
    target_x = position.x + (TURN_TO_ANGLE_DISTANCE * std::cos(theta));
    target_y = position.y + (TURN_TO_ANGLE_DISTANCE * std::sin(theta));
    target_reached = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDTurn::turnToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, ETurnDirection direction)
{
    if (m_mutex)
        m_mutex->take();

    m_pid.reset();

    control_robot = robot;
    auto position{getOdometryPosition()};

    turn_direction = direction;
    turn_velocity = velocity;
    target_x = x;
    target_y = y;
    target_reached = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDTurn::pause()
{
    if (m_mutex)
        m_mutex->take();
    
    paused = true;
    robot::subsystems::drive::Velocity stop{0, 0};
    setDriveVelocity(stop);

    if (m_mutex)
        m_mutex->give();
}

void PIDTurn::resume()
{
    if (m_mutex)
        m_mutex->take();

    paused = false;

    if (m_mutex)
        m_mutex->give();
}

bool PIDTurn::targetReached()
{
    return target_reached;
}

void PIDTurn::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDTurn::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDTurn::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDTurn::setPID(PID pid)
{
    m_pid = pid;
}

void PIDTurn::PIDTurn::setTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
}
} // namespace motion
} // namespace control
} // namespace wisco