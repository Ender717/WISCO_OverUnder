#include "wisco/routines/SentryMode.hpp"

namespace wisco
{
namespace routines
{
SentryMode::SentryMode(const std::shared_ptr<rtos::IClock>& clock,
                       const std::unique_ptr<rtos::IDelayer>& delayer,
                       std::unique_ptr<rtos::IMutex>& mutex,
                       std::unique_ptr<rtos::ITask>& task,
                       const std::shared_ptr<control::ControlSystem>& control_system,
                       const std::shared_ptr<robot::Robot>& robot)
    : m_clock{clock->clone()}, m_delayer{delayer->clone()},
      m_mutex{std::move(mutex)}, m_task{std::move(task)},
      m_control_system{control_system}, m_robot{robot}
{

}
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

bool SentryMode::pointExists(control::path::Point point)
{
    return point.getX() != 0 || point.getY() != 0;
}

bool SentryMode::isValid(control::path::Point point)
{
    bool valid{false};
    auto position{getOdometryPosition()};
    
    if (position.x < 72.0)
    {
        valid = (point.getX() > 27.0 && point.getX() < 69.0) &&
                (point.getY() > 3.0 && point.getY() < 71.0);
    }
    else
    {
        valid = (point.getX() > 75.0 && point.getX() < 117.0) &&
                (point.getY() > 3.0 && point.getY() < 83.0);
    }
    
    return valid;
}

void SentryMode::updateStart()
{
    if (m_clock->getTime() >= start_time + TURN_START_DELAY)
    {
	    turnToAngle(m_end_angle, SCAN_VELOCITY, false, m_direction);
        state = EState::SEARCH;
    }
}

void SentryMode::updateSearch()
{
	if (!pointExists(ball_point_2) && !turnTargetReached())
	{
		auto position{getOdometryPosition()};
		double ball_distance{getBallDistance()};
		double ball_x{position.x + (ball_distance * std::cos(position.theta))};
		double ball_y{position.y + (ball_distance * std::sin(position.theta))};
		control::path::Point ball_point{ball_x, ball_y};
		if (isValid(ball_point))
		{
			if (!pointExists(ball_point_1))
            {
				ball_point_1 = ball_point;
            }
            else
            {
                ball_point_2 = ball_point;

                // Estimate error from ball edge to first point
                double scan_distance{distance(ball_point_1.getX(), ball_point_1.getY(), ball_point_2.getX(), ball_point_2.getY())};
                double assumed_error{std::min(BALL_WIDTH - scan_distance, scan_distance) / 2};

                // Find the estimated ball coordinate
                double scan_angle{std::atan2(ball_point_2.getX() - ball_point_1.getX(), ball_point_2.getY() - ball_point_1.getY())};
                ball.setX(ball_point_1.getX() + (((BALL_WIDTH / 2) - assumed_error) * std::cos(scan_angle)));
                ball.setY(ball_point_1.getY() + (((BALL_WIDTH / 2) - assumed_error) * std::sin(scan_angle)));

                turnToPoint(ball.getX(), ball.getY(), TURN_VELOCITY);
                state = EState::TURN;
            }
		}
	} 
    else if (turnTargetReached())
    {
        finished = true;
    }

}

void SentryMode::updateTurn()
{
    auto position{getOdometryPosition()};
    double target_angle{angle(position.x, position.y, ball.getX(), ball.getY())};
    if (std::abs(bindRadians(target_angle - position.theta)) < AIM_TOLERANCE)
    {
        m_control_system->pause();
        setElevatorPosition(ELEVATOR_OUT);
        setIntakeVoltage(INTAKE_VOLTAGE);
        boomerangGoToPoint(ball.getX(), ball.getY(), target_angle, BOOMERANG_VELOCITY);
        state = EState::GRAB;
    }
}

void SentryMode::updateGrab()
{
    auto position{getOdometryPosition()};
    double ball_distance{distance(position.x, position.y, ball.getX(), ball.getY())};
    double elevator_position{getElevatorPosition()};
    if (ball_distance + MOTION_OFFSET < elevator_position + ELEVATOR_OFFSET)
    {
        m_control_system->pause();
        setElevatorPosition(ELEVATOR_BALL);
        state = EState::HOLD;
    }
}

void SentryMode::updateHold()
{
    if (getElevatorPosition() < ELEVATOR_BALL + ELEVATOR_TOLERANCE)
        finished = true;
}

void SentryMode::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    if (!paused && !finished)
    {
        switch (state)
        {
        case EState::START:
            updateStart();
            break;
        case EState::SEARCH:
            updateSearch();
            break;
        case EState::TURN:
            updateTurn();
            break;
        case EState::GRAB:
            updateGrab();
            break;
        case EState::HOLD:
            updateHold();
            break;
        }
    }
    if (m_mutex)
        m_mutex->give();
    if (m_delayer)
        m_delayer->delay(TASK_DELAY);
}

void SentryMode::run()
{
    if (m_task)
        m_task->start(&SentryMode::taskLoop, this);
}

void SentryMode::doSentryMode(double end_angle, control::motion::ETurnDirection direction)
{
    if (m_mutex)
        m_mutex->take();
    state = EState::START;
    ball_point_1.setX(0);
    ball_point_1.setY(0);
    ball_point_2.setX(0);
    ball_point_2.setY(0);
    m_end_angle = end_angle;
    m_direction = direction;
    ball.setX(0);
    ball.setY(0);
    start_time = m_clock->getTime();
    elevator_distance = 0;
    paused = false;
    finished = false;
    turnToAngle(m_end_angle, TURN_VELOCITY, false, m_direction);
    if (m_mutex)
        m_mutex->give();
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

control::path::Point SentryMode::getBall()
{
    return ball;
}

bool SentryMode::isFinished()
{
    return finished;
}
} // namespace routines
} // namespace wisco