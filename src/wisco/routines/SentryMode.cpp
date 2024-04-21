#include "wisco/routines/SentryMode.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
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
        valid = (point.getX() > 75.0 && point.getX() < 112.0) &&
                (point.getY() > 3.0 && point.getY() < 83.0);
    }
    
    return valid;
}

void SentryMode::updateStart()
{
    if (m_clock->getTime() >= start_time + TURN_START_DELAY)
    {
        std::cout << "Search" << std::endl;
	    turnToAngle(m_end_angle, SCAN_VELOCITY, false, m_direction);
        state = EState::SEARCH;
    }
}

void SentryMode::updateSearch()
{
    auto position{getOdometryPosition()};
    double angular_velocity{position.theta - last_theta};
    last_theta = position.theta;
    if (std::abs(bindRadians(position.theta - m_end_angle)) < AIM_TOLERANCE)
    {
        std::cout << "Finished" << std::endl;
        finished = true;
    }
	else
	{
        if (skip)
        {
            std::cout << "Skipping" << std::endl;
            if (std::abs(bindRadians(position.theta - skip_angle)) < AIM_TOLERANCE)
            {
                skip = false;
            }
        }
        else
        {
            auto objects{getBallVisionObjects()};
            std::vector<io::VisionObject> ball_objects{};
            for (auto object : objects)
            {
                for (auto object_id : m_alliance->getVisionObjectIDs("TRIBALL"))
                {
                    if (object.id == object_id)
                    {
                        ball_objects.push_back(object);
                    }
                }
            }
            double closest_ball{};
            for (auto ball_object : ball_objects)
            {
                if (ball_object.horizontal > -IGNORE_RANGE)
                {
                    if (closest_ball == 0.0 || ball_object.horizontal < closest_ball)
                    {
                        closest_ball = ball_object.horizontal;
                    }
                }
            }
            if (closest_ball != 0.0)
            {
                std::cout << "Closest ball: " << closest_ball << std::endl;
                turnToPoint(ball.getX(), ball.getY(), TURN_VELOCITY);
                if (closest_ball < AIM_TOLERANCE)
                {
                    std::cout << "Within aim tolerance" << std::endl;
                    double ball_distance{getBallDistance()};
                    if (!measuring_distance)
                    {
                        last_distance = ball_distance;
                        measuring_distance = true;
                    }
                    else if (ball_distance != last_distance)
                    {
                        std::cout << "Measured distance: " << ball_distance << std::endl;
                        measuring_distance = false;
                        double ball_x{position.x + (ball_distance * std::cos(position.theta))};
                        double ball_y{position.y + (ball_distance * std::sin(position.theta))};
                        control::path::Point ball_point_temp{ball_x, ball_y};
                        if (!isValid(ball_point_temp))
                        {
                            std::cout << "Starting skip" << std::endl;
                            skip = true;
                            skip_angle = position.theta + (3 * IGNORE_RANGE / 2);
                        }
                        else 
                        {
                            ball = ball_point_temp;
                            double target_angle{angle(position.x, position.y, ball.getX(), ball.getY())};
                            std::cout << "Grab" << std::endl;
                            m_control_system->pause();
                            setElevatorPosition(ELEVATOR_OUT);
                            setIntakeVoltage(INTAKE_VOLTAGE);
                            boomerangGoToPoint(ball.getX(), ball.getY(), target_angle, BOOMERANG_VELOCITY);
                            state = EState::GRAB;
                        }
                    }
                }
            }
            else
            {
                turnToAngle(m_end_angle, TURN_VELOCITY, false, m_direction);
            }
        }

        /*
		double ball_distance{getBallDistance()};
		double ball_x{position.x + (ball_distance * std::cos(position.theta))};
		double ball_y{position.y + (ball_distance * std::sin(position.theta))};
        std::cout << "Distance: " << ball_distance << ", X: " << ball_x << ", Y: " << ball_y << std::endl;
		control::path::Point ball_point_temp{ball_x, ball_y};
		if (isValid(ball_point_temp))
		{
            ball_point = ball_point_temp;
            // Estimate error from ball edge to first point
            double scan_distance{ball_distance * std::sin(angular_velocity)};
            double assumed_error{std::min(BALL_WIDTH - scan_distance, scan_distance) / 2};

            // Find the estimated ball coordinate
            double scan_angle{position.theta + (M_PI / 2)};
            ball.setX(ball_point.getX() + (((BALL_WIDTH / 2) - assumed_error) * std::cos(scan_angle)));
            ball.setY(ball_point.getY() + (((BALL_WIDTH / 2) - assumed_error) * std::sin(scan_angle)));

            std::cout << "Turn" << std::endl;
            turnToPoint(ball.getX(), ball.getY(), TURN_VELOCITY);
            state = EState::TURN;
		}
        */
	} 
}

void SentryMode::updateTurn()
{
    auto position{getOdometryPosition()};
    double target_angle{angle(position.x, position.y, ball.getX(), ball.getY())};
    if (std::abs(bindRadians(target_angle - position.theta)) < AIM_TOLERANCE)
    {
        std::cout << "Grab" << std::endl;
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
        std::cout << "Hold" << std::endl;
        m_control_system->pause();
        setElevatorPosition(ELEVATOR_BALL);
        state = EState::HOLD;
    }
}

void SentryMode::updateHold()
{
    if (getElevatorPosition() < ELEVATOR_BALL + ELEVATOR_TOLERANCE)
    {
        std::cout << "Finished" << std::endl;
        finished = true;
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
    ball_point.setX(0);
    ball_point.setY(0);
    last_theta = getOdometryPosition().theta;
    last_distance = getBallDistance();
    skip = false;
    skip_angle = 0;
    measuring_distance = false;
    m_end_angle = end_angle;
    m_direction = direction;
    ball.setX(0);
    ball.setY(0);
    start_time = m_clock->getTime();
    elevator_distance = 0;
    paused = false;
    finished = false;
    m_control_system->pause();
    turnToAngle(m_end_angle, TURN_VELOCITY, false, m_direction);
    std::cout << "Start" << std::endl;
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
    return pointExists(ball_point);
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