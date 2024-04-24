#include "wisco/routines/SentryMode.hpp"
#include <iostream>

namespace wisco
{
namespace routines
{
SentryMode::SentryMode(const std::shared_ptr<IAlliance>& alliance,
                       const std::shared_ptr<rtos::IClock>& clock,
                       const std::unique_ptr<rtos::IDelayer>& delayer,
                       std::unique_ptr<rtos::IMutex>& mutex,
                       std::unique_ptr<rtos::ITask>& task,
                       const std::shared_ptr<control::ControlSystem>& control_system,
                       const std::shared_ptr<robot::Robot>& robot)
    : m_alliance{alliance},
      m_clock{clock->clone()}, m_delayer{delayer->clone()},
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

std::vector<io::VisionObject> SentryMode::getBallVisionObjects()
{
    std::vector<io::VisionObject> objects{};
    if (m_robot)
    {
        std::vector<io::VisionObject>* result{static_cast<std::vector<io::VisionObject>*>(m_robot->getState("INTAKE", "GET BALL VISION OBJECTS"))};
        if (result)
        {
            objects = *result;
            delete result;
        }
    }
    return objects;
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

void SentryMode::driveStraight(double distance, double velocity, double theta, uint32_t timeout)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "DRIVE STRAIGHT", &m_robot, distance, velocity, theta);
		if (timeout != UINT32_MAX)
		{
			uint32_t start_time{m_clock->getTime()};
			while (!driveStraightTargetReached() && m_clock->getTime() < start_time + timeout)
				m_delayer->delay(10);
		}
	}
}

bool SentryMode::driveStraightTargetReached()
{
	bool target_reached{};
	if (m_control_system)
	{
		bool* result{static_cast<bool*>(m_control_system->getState("MOTION", "DRIVE STRAIGHT TARGET REACHED"))};
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
                (point.getY() > 26.0 && point.getY() < 71.0);
    }
    else
    {
        valid = (point.getX() > 73.5 && point.getX() < 112.0) &&
                (point.getY() > 24.5 && point.getY() < 86.0);
    }
    
    return valid;
}

void SentryMode::updateSearch()
{
    auto position{getOdometryPosition()};
    if (turnTargetReached())
    {
        std::cout << "Finished" << std::endl;
        finished = true;
    }
    else if (skip_angle == 0.0
        || (m_direction == control::motion::ETurnDirection::CLOCKWISE && bindRadians(skip_angle - position.theta) > 0)
        || (m_direction == control::motion::ETurnDirection::COUNTERCLOCKWISE && bindRadians(skip_angle - position.theta) < 0))
    {
        auto objects{getBallVisionObjects()};
        double triball_angle{m_direction == control::motion::ETurnDirection::CLOCKWISE ? -DBL_MAX : DBL_MAX};
        for (auto object : objects)
        {
            for (auto object_id : m_alliance->getVisionObjectIDs("TRIBALL"))
            {
                double total_angle{bindRadians(position.theta + object.horizontal)};
                bool in_range{(sign(bindRadians(m_end_angle - total_angle))
                    == sign(bindRadians(m_end_angle - position.theta)))
                    || std::abs(bindRadians(m_end_angle - total_angle)) > M_PI / 2};
                if (object.id == object_id && object.width > MINIMUM_OBJECT_SIZE && in_range
                    && ((object.horizontal > 0.0 && object.horizontal < triball_angle && m_direction == control::motion::ETurnDirection::COUNTERCLOCKWISE)
                    || (object.horizontal < 0.0 && object.horizontal > triball_angle && m_direction == control::motion::ETurnDirection::CLOCKWISE)))
                {
                    triball_angle = object.horizontal;
                }
            }
        }
        if (triball_angle != DBL_MAX && triball_angle != -DBL_MAX)
        {
            distance_time = 0;
            target_angle = triball_angle + position.theta;
            turnToAngle(target_angle, TURN_VELOCITY);
            state = EState::TARGET;
            std::cout << "Target Angle: " << target_angle << std::endl;
        }
    }
}

void SentryMode::updateTarget()
{
    auto position{getOdometryPosition()};
    double ball_distance{getBallDistance()};
    std::cout << "Angle: " << position.theta << std::endl;
    if (std::abs(bindRadians(target_angle - position.theta)) < AIM_TOLERANCE || turnTargetReached())
    {
        if (distance_time == 0)
        {
            last_distance = ball_distance;
            distance_time = m_clock->getTime();
            std::cout << "Time: " << distance_time << std::endl;
        }
        else if (m_clock->getTime() > distance_time + DISTANCE_DELAY || last_distance != ball_distance)
        {
            std::cout << "Distance: " << ball_distance << std::endl;
            double ball_x{position.x + (ball_distance * std::cos(position.theta))};
            double ball_y{position.y + (ball_distance * std::sin(position.theta))};
            control::path::Point ball_point_temp{ball_x, ball_y};
            if (isValid(ball_point_temp))
            {
                ball = ball_point_temp;
                m_control_system->pause();
                setElevatorPosition(ELEVATOR_OUT);
                setIntakeVoltage(INTAKE_VOLTAGE);
                double line_location{position.x < 72.0 ? 62.0 : 74.0};
                double line_distance{(line_location - position.y) / std::sin(position.theta)};
                if (line_distance < 0)
                    line_distance = DBL_MAX;
                driveStraight(std::min(ball_distance, line_distance), 48.0, target_angle);
                state = EState::GRAB;
                std::cout << "Grab Ball: " << ball.getX() << ", " << ball.getY() << std::endl;
            }
            else
            {
                skip_angle = bindRadians(position.theta + SKIP_DISTANCE);
                turnToAngle(m_end_angle, TURN_VELOCITY, false, m_direction);
                state = EState::SEARCH;
                std::cout << "Skip to " << skip_angle * 180 / M_PI << std::endl;
            }
        }
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
        std::cout << "Hold" << std::endl;
    }
}

void SentryMode::updateHold()
{
    if (getElevatorPosition() < ELEVATOR_BALL + ELEVATOR_TOLERANCE)
    {
        finished = true;
        std::cout << "Finished" << std::endl;
    }
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
        case EState::TARGET:
            updateTarget();
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
    state = EState::SEARCH;
    last_distance = 0;
    m_end_angle = end_angle;
    target_angle = 0;
    skip_angle = 0;
    distance_time = 0;
    m_direction = direction;
    ball.setX(0);
    ball.setY(0);
    elevator_distance = 0;
    finished = false;
    paused = false;
    m_control_system->pause();
    turnToAngle(m_end_angle, TURN_VELOCITY, false, m_direction);
    std::cout << "Search" << std::endl;
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
    return pointExists(ball);
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