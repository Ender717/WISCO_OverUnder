#include "wisco/routines/SentryMode.hpp"

namespace wisco
{
namespace routines
{
void SentryMode::taskLoop(void* params)
{
    SentryMode* instance{static_cast<SentryMode*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

double SentryMode::getElevatorPosition()
{
    double position{};
    if (m_robot)
    {
        double* result{static_cast<double*>(m_robot->getState("ELEVATOR", "GET POSITION"))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }
    return position;
}

double SentryMode::getBallDistance()
{
    double distance{};
    if (m_robot)
    {
        double* result{static_cast<double*>(m_robot->getState("INTAKE", "GET BALL DISTANCE"))};
        if (result)
        {
            distance = *result;
            delete result;
        }
    }
    return distance;
}

robot::subsystems::position::Position SentryMode::getOdometryPosition()
{
    robot::subsystems::position::Position position{};
    if (m_robot)
    {
        robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(m_robot->getState("POSITION TRACKER", "GET POSITION"))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }
    return position;
}

void SentryMode::setElevatorPosition(double position)
{
    if (m_robot)
        m_robot->sendCommand("ELEVATOR", "SET POSITION", position);
}

void SentryMode::setDriveVelocity(double left, double right)
{
    if (m_robot)
    {
        robot::subsystems::drive::Velocity velocity{left, right};
        m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", velocity);
    }
}

void SentryMode::setIntakeVoltage(double voltage)
{
    if (m_robot)
        m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

void SentryMode::boomerangGoToPoint(double x, double y, double theta, double velocity)
{
    if (m_control_system && m_robot)
        m_control_system->sendCommand("BOOMERANG", "GO TO POSITION", &m_robot, velocity, x, y, theta);
}

bool SentryMode::boomerangTargetReached()
{
    bool target_reached{};
    if (m_control_system)
    {
        bool* result{static_cast<bool*>(m_control_system->getState("BOOMERANG", "TARGET REACHED"))};
        if (result)
        {
            target_reached = *result;
            delete result;
        }
    }
    return target_reached;
}

void SentryMode::turnToAngle(double theta, double velocity, bool reversed, control::motion::ETurnDirection direction)
{
    if (m_control_system)
		m_control_system->sendCommand("MOTION", "TURN TO ANGLE", &m_robot, velocity, theta, static_cast<int>(reversed), direction);
}

void SentryMode::turnToPoint(double x, double y, double velocity, bool reversed, control::motion::ETurnDirection direction)
{
    if (m_control_system)
		m_control_system->sendCommand("MOTION", "TURN TO POINT", &m_robot, velocity, x, y, static_cast<int>(reversed), direction);
}

bool SentryMode::turnTargetReached()
{
    bool target_reached{};
    if (m_robot)
    {
        bool* result{static_cast<bool*>(m_control_system->getState("MOTION", "TURN TARGET REACHED"))};
        if (result)
        {
            target_reached = *result;
            delete result;
        }
    }
    return target_reached;
}

bool SentryMode::isValid(control::path::Point point)
{
    bool valid{false};
    auto position{getOdometryPosition()};
    
    if (position.x < 72.0)
        valid = (point.getX() > 27.0 && point.getX() < 69.0) &&
                (point.getY() > 3.0 && point.getY() < 71.0);
    else
        valid = (point.getX() > 75.0 && point.getX() < 117.0) &&
                (point.getY() > 3.0 && point.getY() < 83.0);

    return valid;
}

void SentryMode::updateSearch()
{

}

void SentryMode::updateGrab()
{

}

void SentryMode::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    if (!paused && !finished)
    {
        switch (state)
        {
        case EState::SEARCH:
            updateSearch();
            break;
        case EState::GRAB:
            updateGrab();
            break;
        }
    }
    if (m_mutex)
        m_mutex->give();
    if (m_delayer)
        m_delayer->delay(TASK_DELAY);
}

void SentryMode::run(double end_angle)
{

}

void SentryMode::pause()
{
    if (m_mutex)
        m_mutex->take();
    paused = true;
    if (m_mutex)
        m_mutex->give();
}

void SentryMode::resume()
{
    if (m_mutex)
        m_mutex->take();
    paused = false;
    if (m_mutex)
        m_mutex->give();
}

bool SentryMode::ballFound()
{
    return (ball_point_2.getX() != 0 || ball_point_2.getY() != 0);
}

bool SentryMode::isFinished()
{
    return finished;
}
} // namespace routines
} // namespace wisco