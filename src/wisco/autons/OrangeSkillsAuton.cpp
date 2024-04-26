#include "wisco/autons/OrangeSkillsAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "wisco/io/EVisionObjectID.hpp"
#include <iostream>

namespace wisco
{
namespace autons
{
uint32_t OrangeSkillsAuton::getTime()
{
	uint32_t time{};
	if (m_clock)
		time = m_clock->getTime();
	return time;
}

void OrangeSkillsAuton::delay(uint32_t millis)
{
	if (m_delayer)
		m_delayer->delay(millis);
}

void OrangeSkillsAuton::pauseControlSystem()
{
	if (m_control_system)
		m_control_system->pause();
}

void OrangeSkillsAuton::resumeControlSystem()
{
	if (m_control_system)
		m_control_system->resume();
}

void OrangeSkillsAuton::boomerangGoToPoint(double x, double y, double theta, double velocity, uint32_t timeout, double tolerance)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("BOOMERANG", "GO TO POSITION", &m_robot, velocity, x, y, theta);
		auto position{getOdometryPosition()};
		uint32_t start_time{getTime()};
		double target_distance{distance(position.x, position.y, x, y)};
		while (!boomerangTargetReached() && getTime() < start_time + timeout && target_distance > tolerance)
		{
			delay(LOOP_DELAY);
			position = getOdometryPosition();
			target_distance = distance(position.x, position.y, x, y);
		}
		if (timeout || tolerance != 0.0)
			pauseControlSystem();
	}
}

bool OrangeSkillsAuton::boomerangTargetReached()
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

void OrangeSkillsAuton::driveStraight(double distance, double velocity, uint32_t timeout, double tolerance)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta, timeout, tolerance);
}

void OrangeSkillsAuton::driveStraight(double motion_distance, double velocity, double theta, uint32_t timeout, double tolerance)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "DRIVE STRAIGHT", &m_robot, motion_distance, velocity, theta);
		uint32_t start_time{getTime()};
		auto start_position{getOdometryPosition()};
		auto position{start_position};
		double moved_distance{};
		while (!driveStraightTargetReached() && getTime() < start_time + timeout && std::abs(motion_distance - moved_distance) > tolerance)
		{
			delay(LOOP_DELAY);
			position = getOdometryPosition();
			double start_distance{distance(start_position.x, start_position.y, position.x, position.y)};
			double start_angle{angle(start_position.x, start_position.y, position.x, position.y)};
			if (motion_distance < 0)
			{
				start_distance *= -1;
				start_angle = bindRadians(start_angle + M_PI);
			}
			moved_distance = start_distance * std::cos(bindRadians(start_angle - theta));
		}
		if (timeout || tolerance != 0.0)
			pauseControlSystem();
	}
}

void OrangeSkillsAuton::driveStraightToPoint(double x, double y, double velocity, uint32_t timeout, double tolerance)
{
	auto position{getOdometryPosition()};
	double target_distance{distance(position.x, position.y, x, y)};
	double target_angle{angle(position.x, position.y, x, y)};
	if (std::abs(bindRadians(target_angle - position.theta)) > M_PI / 2)
	{
		target_distance *= -1;
		target_angle = bindRadians(target_angle + M_PI);
	}
	driveStraight(target_distance, velocity, target_angle, timeout, tolerance);
}

void OrangeSkillsAuton::setDriveStraightVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET DRIVE STRAIGHT VELOCITY", velocity);
}

bool OrangeSkillsAuton::driveStraightTargetReached()
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

void OrangeSkillsAuton::goToPoint(double x, double y, double velocity, uint32_t timeout, double tolerance)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "GO TO POINT", &m_robot, velocity, x, y);
		auto position{getOdometryPosition()};
		uint32_t start_time{getTime()};
		double target_distance{distance(position.x, position.y, x, y)};
		while (!goToPointTargetReached() && getTime() < start_time + timeout && target_distance > tolerance)
		{
			delay(LOOP_DELAY);
			position = getOdometryPosition();
			target_distance = distance(position.x, position.y, x, y);
		}
		if (timeout || tolerance != 0.0)
			pauseControlSystem();
	}
}

void OrangeSkillsAuton::setGoToPointVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET GO TO POINT VELOCITY", velocity);
}

bool OrangeSkillsAuton::goToPointTargetReached()
{
	bool target_reached{};
	if (m_control_system)
	{
		bool* result{static_cast<bool*>(m_control_system->getState("MOTION", "GO TO POINT TARGET REACHED"))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

void OrangeSkillsAuton::turnToAngle(double theta, double velocity, bool reversed, uint32_t timeout, double tolerance,
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "TURN TO ANGLE", &m_robot, velocity, theta, static_cast<int>(reversed), direction);
		uint32_t start_time{getTime()};
		auto position{getOdometryPosition()};
		while (!turnTargetReached() && getTime() < start_time + timeout && std::abs(bindRadians(theta - position.theta)) > tolerance)
		{
			delay(LOOP_DELAY);
			position = getOdometryPosition();
		}
		if (timeout || tolerance != 0.0)
			pauseControlSystem();
	}
}

void OrangeSkillsAuton::turnToPoint(double x, double y, double velocity, bool reversed, uint32_t timeout, double tolerance,
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "TURN TO POINT", &m_robot, velocity, x, y, static_cast<int>(reversed), direction);
		uint32_t start_time{getTime()};
		auto position{getOdometryPosition()};
		double target_angle{angle(position.x, position.y, x, y)};
		while (!turnTargetReached() && getTime() < start_time + timeout && std::abs(bindRadians(target_angle - position.theta)) > tolerance)
		{
			delay(LOOP_DELAY);
			position = getOdometryPosition();
			target_angle = angle(position.x, position.y, x, y);
		}
		if (timeout || tolerance != 0.0)
			pauseControlSystem();
	}
}

bool OrangeSkillsAuton::turnTargetReached()
{
	bool target_reached{};
	if (m_control_system)
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

void OrangeSkillsAuton::followPath(std::vector<control::path::Point>& path, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("PATH FOLLOWING", "FOLLOW PATH", &m_robot, &path, velocity);
}

void OrangeSkillsAuton::setPathFollowingVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("PATH FOLLOWING", "SET VELOCITY", velocity);
}

bool OrangeSkillsAuton::pathFollowingTargetReached()
{
	bool target_reached{};
	if (m_control_system)
	{
		bool* result{static_cast<bool*>(m_control_system->getState("PATH FOLLOWING", "TARGET REACHED"))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}


void OrangeSkillsAuton::setDriveVelocity(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

void OrangeSkillsAuton::setDriveVoltage(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", left, right);
}

robot::subsystems::drive::Velocity OrangeSkillsAuton::getDriveVelocity()
{
	robot::subsystems::drive::Velocity velocity{};
	if (m_robot)
	{
		robot::subsystems::drive::Velocity* result{static_cast<robot::subsystems::drive::Velocity*>(m_robot->getState("DIFFERENTIAL DRIVE", "GET VELOCITY"))};
		if (result)
		{
			velocity = *result;
			delete result;
		}
	}
	return velocity;
}

double OrangeSkillsAuton::getDriveRadius()
{
	double radius{};
	if (m_robot)
	{
		double* result{static_cast<double*>(m_robot->getState("DIFFERENTIAL DRIVE", "GET RADIUS"))};
		if (result)
		{
			radius = *result;
			delete result;
		}
	}
	return radius;
}

void OrangeSkillsAuton::setElevatorPosition(double position, uint32_t timeout)
{
	if (m_robot)
	{
		m_robot->sendCommand("ELEVATOR", "SET POSITION", position);
		if (timeout != UINT32_MAX)
		{
			uint32_t start_time{getTime()};
			while (std::abs(position - getElevatorPosition()) > ELEVATOR_TOLERANCE
				&& getTime() < start_time + timeout)
			{
				delay(LOOP_DELAY);
			}
		}
	}
}

void OrangeSkillsAuton::calibrateElevator()
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "CALIBRATE");
}

double OrangeSkillsAuton::getElevatorPosition()
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

bool OrangeSkillsAuton::elevatorIsCalibrating()
{
	bool calibrating{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("ELEVATOR", "IS CALIBRATING"))};
		if (result)
		{
			calibrating = *result;
			delete result;
		}
	}
	return calibrating;
}

double OrangeSkillsAuton::getCapDistance()
{
	double distance{};
	if (m_robot)
	{
		double* result{static_cast<double*>(m_robot->getState("ELEVATOR", "CAP DISTANCE"))};
		if (result)
		{
			distance = *result;
			delete result;
		}
	}
	return distance;
}

void OrangeSkillsAuton::closeClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "CLOSE CLAW");
}

void OrangeSkillsAuton::openClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "OPEN CLAW");
}

void OrangeSkillsAuton::raiseArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "RAISE ARM");
}

void OrangeSkillsAuton::lowerArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "LOWER ARM");
}

void OrangeSkillsAuton::engageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "ENGAGE WINCH");
}

void OrangeSkillsAuton::disengageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "DISENGAGE WINCH");
}

bool OrangeSkillsAuton::clawClosed()
{
	bool closed{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "CLAW CLOSED"))};
		if (result)
		{
			closed = *result;
			delete result;
		}
	}
	return closed;
}

bool OrangeSkillsAuton::clawOpen()
{
	bool open{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "CLAW OPEN"))};
		if (result)
		{
			open = *result;
			delete result;
		}
	}
	return open;
}

bool OrangeSkillsAuton::armRaised()
{
	bool raised{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "ARM RAISED"))};
		if (result)
		{
			raised = *result;
			delete result;
		}
	}
	return raised;
}

bool OrangeSkillsAuton::armLowered()
{
	bool lowered{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "ARM LOWERED"))};
		if (result)
		{
			lowered = *result;
			delete result;
		}
	}
	return lowered;
}

bool OrangeSkillsAuton::winchEngaged()
{
	bool engaged{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "WINCH ENGAGED"))};
		if (result)
		{
			engaged = *result;
			delete result;
		}
	}
	return engaged;
}

bool OrangeSkillsAuton::winchDisengaged()
{
	bool disengaged{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("HANG", "WINCH DISENGAGED"))};
		if (result)
		{
			disengaged = *result;
			delete result;
		}
	}
	return disengaged;
}

void OrangeSkillsAuton::setIntakeVelocity(double velocity)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VELOCITY", velocity);
}

void OrangeSkillsAuton::setIntakeVoltage(double voltage)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

double OrangeSkillsAuton::getIntakeVelocity()
{
	double velocity{};
	if (m_robot)
	{
		double* result{static_cast<double*>(m_robot->getState("INTAKE", "GET VELOCITY"))};
		if (result)
		{
			velocity = *result;
			delete result;
		}
	}
	return velocity;
}

double OrangeSkillsAuton::getBallDistance()
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

std::vector<io::VisionObject> OrangeSkillsAuton::getBallVisionObjects()
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

void OrangeSkillsAuton::loadLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO LOAD");
}

void OrangeSkillsAuton::readyLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO READY");
}

bool OrangeSkillsAuton::isLoaderLoaded()
{
	bool loaded{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("LOADER", "IS LOADED"))};
		if (result)
		{
			loaded = *result;
			delete result;
		}
	}
	return loaded;
}

bool OrangeSkillsAuton::isLoaderReady()
{
	bool ready{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("LOADER", "IS READY"))};
		if (result)
		{
			ready = *result;
			delete result;
		}
	}
	return ready;
}

void OrangeSkillsAuton::setOdometryPosition(double x, double y, double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET POSITION", x, y, theta);
}

void OrangeSkillsAuton::setOdometryX(double x)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET X", x);
}

void OrangeSkillsAuton::setOdometryY(double y)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET Y", y);
}

void OrangeSkillsAuton::setOdometryTheta(double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET THETA", theta);
}

void OrangeSkillsAuton::resetOdometryX()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET X");
}

void OrangeSkillsAuton::resetOdometryY()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET Y");
}

robot::subsystems::position::Position OrangeSkillsAuton::getOdometryPosition()
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

double OrangeSkillsAuton::getOdometryVelocity()
{
	auto position{getOdometryPosition()};
	double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
	return velocity;
}

void OrangeSkillsAuton::setUmbrellaIn()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET IN");
}

void OrangeSkillsAuton::setUmbrellaOut()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET OUT");
}

bool OrangeSkillsAuton::isUmbrellaIn()
{
	bool in{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("UMBRELLA", "IS IN"))};
		if (result)
		{
			in = *result;
			delete result;
		}
	}
	return in;
}

bool OrangeSkillsAuton::isUmbrellaOut()
{
	bool out{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("UMBRELLA", "IS OUT"))};
		if (result)
		{
			out = *result;
			delete result;
		}
	}
	return out;
}

void OrangeSkillsAuton::setLeftWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET LEFT WING", static_cast<int>(out));
}

void OrangeSkillsAuton::setRightWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET RIGHT WING", static_cast<int>(out));
}

bool OrangeSkillsAuton::isLeftWingOut()
{
	bool out{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("WINGS", "GET LEFT WING"))};
		if (result)
		{
			out = *result;
			delete result;
		}
	}
	return out;
}

bool OrangeSkillsAuton::isRightWingOut()
{
	bool out{};
	if (m_robot)
	{
		bool* result{static_cast<bool*>(m_robot->getState("WINGS", "GET RIGHT WING"))};
		if (result)
		{
			out = *result;
			delete result;
		}
	}
	return out;
}

std::string OrangeSkillsAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void OrangeSkillsAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{
	m_control_system = control_system;
	m_robot = robot;

	std::vector<control::path::Point> alley_path_control_points
	{
		control::path::Point{21.0, 144 - 21.0},
		control::path::Point{30.0, 144 - 10.0},
		control::path::Point{40.0, 144 - 10.0},
		control::path::Point{60.0, 144 - 9.0},
		control::path::Point{75.0, 144 - 9.0},
		control::path::Point{84.0, 144 - 9.0},
		control::path::Point{100.0, 144 - 10.0},
		control::path::Point{116.0, 144 - 14.0},
		control::path::Point{122.0, 144 - 18.0},
		control::path::Point{128.0, 144 - 24.0},
	};
	alley_path = control::path::QuinticBezierSpline::calculate(alley_path_control_points);

	std::vector<control::path::Point> alley_return_path_control_points
	{
		control::path::Point{130.0, 144 - 36.0},
		control::path::Point{120.0, 144 - 24.0},
		control::path::Point{114.0, 144 - 18.0},
		control::path::Point{96.0, 144 - 11.0},
		control::path::Point{76.0, 144 - 11.0},
		control::path::Point{68.0, 144 - 11.0},
		control::path::Point{48.0, 144 - 11.0},
		control::path::Point{36.0, 144 - 14.0},
		control::path::Point{28.0, 144 - 20.0},
		control::path::Point{24.0, 144 - 24.0},
	};
	alley_return_path = control::path::QuinticBezierSpline::calculate(alley_return_path_control_points);
}

void OrangeSkillsAuton::run(std::shared_ptr<IAlliance> alliance,
						 std::shared_ptr<rtos::IClock> clock,
						 std::unique_ptr<rtos::IDelayer>& delayer,
						 std::shared_ptr<control::ControlSystem> control_system, 
					     std::shared_ptr<robot::Robot> robot)
{
	m_clock = clock;
	m_delayer = std::move(delayer);
	m_control_system = control_system;
	m_robot = robot;

	uint32_t auton_start_time{getTime()};
	double start_x{16.0}, start_y{144 - 16.0}, start_theta{-1 * -3 * M_PI / 4};
	setOdometryPosition(start_x, start_y, start_theta);

	// Grab some basic variables for general use
	auto position{getOdometryPosition()};
	double velocity{getOdometryVelocity()};

	uint8_t pushes{2};
	for (uint8_t i{}; i < pushes; ++i)
	{
		// Do skills loads
		uint8_t skills_loads{12};
		uint32_t skills_load_delay{300};
		uint32_t skills_load_timeout{500};
		for (uint8_t j{}; j < skills_loads; ++j)
		{
			// Load the triball into the field
			loadLoader();
			uint32_t load_start_time{getTime()};
			while (!isLoaderLoaded() && getTime() < load_start_time + skills_load_timeout)
				delay(LOOP_DELAY);

			// Reset the skills loading mechanism
			readyLoader();
			uint32_t ready_start_time{getTime()};
			while (!isLoaderReady() && getTime() < ready_start_time + skills_load_timeout)
				delay(LOOP_DELAY);

			// Wait for the next skills load
			if (j < skills_loads - 1)
				delay(skills_load_delay);
		}

		// Turn to face the alley
		turnToAngle(-1 * -M_PI / 4, TURN_VELOCITY, true, 1000, 2.0 * M_PI / 180);

		// Follow the alley path
		setLeftWing(true);
		setRightWing(true);
		followPath(alley_path, 36.0);
		position = getOdometryPosition();
		velocity = getOdometryVelocity();
		uint32_t collision_start_time{getTime()};
		while (!pathFollowingTargetReached())
		{
			// If we have reached the slow section of the alley, slow down
			if (position.x > 72.0)
				setPathFollowingVelocity(30.0);
			else
				setPathFollowingVelocity(48.0);

			// Detect getting stuck
			if (position.x < 120.0 && velocity < 8.0 && getTime() > collision_start_time + 1000)
			{
				// Back up to get free
				pauseControlSystem();
				setDriveVelocity(-24.0, -24.0);
				delay(500);

				// Resume the alley push
				resumeControlSystem();
				collision_start_time = getTime();
			}
			
			delay(LOOP_DELAY);
			position = getOdometryPosition();
			velocity = getOdometryVelocity();
		}

		// Push the triballs in
		double push_x{130.0}, push_y{144 - 24.0};
		setLeftWing(false);
		for (uint8_t j{}; j < 2; ++j)
		{
			// Turn to face the shove point
			if (j)
			{
				turnToPoint(push_x, push_y, TURN_VELOCITY, false, 2000, 2.0 * M_PI / 180);			
				driveStraightToPoint(push_x, push_y, 36.0, 1000, 1.0);
			}

			// Turn to face the goal
			double goal_x{138.0}, goal_y{144 - 60.0};
			turnToPoint(goal_x, goal_y, TURN_VELOCITY, true, 1000, 2.0 * M_PI / 180);

			// Shove into the goal
			driveStraightToPoint(goal_x, goal_y, 72.0, 1000);

			// Reset the x-coordinate
			resetOdometryX();
		}

		// Come back to the match loader
		if (i < pushes - 1)
		{
			// Turn to face down the alley
			turnToAngle(-1 * -3 * M_PI / 4, TURN_VELOCITY, false, 1000, 2.0 * M_PI / 180);

			// Follow the alley return path
			setRightWing(false);
			followPath(alley_return_path, 36.0);
			position = getOdometryPosition();
			double target_distance{distance(position.x, position.y, 24.0, 144 - 24.0)};
			while (!pathFollowingTargetReached() && target_distance > 16.0)
			{
				delay(LOOP_DELAY);
				position = getOdometryPosition();
				target_distance = distance(position.x, position.y, 24.0, 144 - 24.0);
			}

			// Reset the y-coordinate
			resetOdometryY();

			// Turn to precisely face the match loading start point
			turnToPoint(24.0, 144 - 24.0, TURN_VELOCITY, false, 1000);

			// Move to the match loading start point
			setIntakeVoltage(-MAX_VOLTAGE);
			driveStraightToPoint(24.0, 144 - 24.0, 36.0, 1000);

			// Turn to face the match loader
			turnToPoint(0, 144 - 0, TURN_VELOCITY, false, 1000);

			// Move into the match loader
			setIntakeVoltage(0);
			driveStraight(19.0, 18.0, (uint32_t)1000);
		}
	}

	// Move to the hang lineup point
	double hang_lineup_x{110.0}, hang_lineup_y{144 - 23.0};
	turnToPoint(hang_lineup_x, hang_lineup_y, TURN_VELOCITY, false, 1000);
	driveStraightToPoint(hang_lineup_x, hang_lineup_y, 36.0, 2000);
	turnToAngle(M_PI, TURN_VELOCITY, false, 2000);
	resetOdometryY();

	// Move to the hanging pole
	double hang_x{72.0}, hang_y{144 - 24.0};
	turnToPoint(hang_x + 24.0, hang_y, TURN_VELOCITY, true, 2000);
	driveStraightToPoint(hang_x, hang_y, 36.0, 2000);

	/*
	setElevatorPosition(3.0, 300);
	raiseArm();
	delay(1000);
	setElevatorPosition(10.0, 1000);
	closeClaw();
	delay(500);
	engageWinch();
	setElevatorPosition(0);
	setDriveVoltage(MAX_VOLTAGE, MAX_VOLTAGE);
	while (getElevatorPosition() > 1.0)
		delay(LOOP_DELAY);
	setDriveVoltage(0, 0);
	*/

	pros::screen::print(pros::E_TEXT_LARGE_CENTER, 7, "End Time: %5.2f", (getTime() - auton_start_time) / 1000.0);
}
}
}