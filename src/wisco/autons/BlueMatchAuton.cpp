#include "wisco/autons/BlueMatchAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "wisco/io/EVisionObjectID.hpp"
#include <iostream>

namespace wisco
{
namespace autons
{
uint32_t BlueMatchAuton::getTime()
{
	uint32_t time{};
	if (m_clock)
		time = m_clock->getTime();
	return time;
}

void BlueMatchAuton::delay(uint32_t millis)
{
	if (m_delayer)
		m_delayer->delay(millis);
}

void BlueMatchAuton::pauseControlSystem()
{
	if (m_control_system)
		m_control_system->pause();
}

void BlueMatchAuton::resumeControlSystem()
{
	if (m_control_system)
		m_control_system->resume();
}

void BlueMatchAuton::goToPoint(double x, double y, double theta, double velocity, uint32_t timeout)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("BOOMERANG", "GO TO POSITION", &m_robot, velocity, x, y, theta);
		if (timeout != UINT32_MAX)
		{
			uint32_t start_time{getTime()};
			while (!boomerangTargetReached() && getTime() < start_time + timeout)
				delay(LOOP_DELAY);
			pauseControlSystem();
		}
	}
}

bool BlueMatchAuton::boomerangTargetReached()
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

void BlueMatchAuton::driveStraight(double distance, double velocity, uint32_t timeout)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta, timeout);
}

void BlueMatchAuton::driveStraight(double distance, double velocity, double theta, uint32_t timeout)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "DRIVE STRAIGHT", &m_robot, distance, velocity, theta);
		if (timeout != UINT32_MAX)
		{
			std::cout << "Timeout: " << timeout << std::endl;
			uint32_t start_time{getTime()};
			while (!driveStraightTargetReached() && getTime() < start_time + timeout)
				delay(LOOP_DELAY);
			pauseControlSystem();
		}
	}
}

void BlueMatchAuton::driveStraightToPoint(double x, double y, double velocity, uint32_t timeout)
{
	auto position{getOdometryPosition()};
	double target_distance{distance(position.x, position.y, x, y)};
	double target_angle{angle(position.x, position.y, x, y)};
	if (std::abs(bindRadians(target_angle - position.theta)) > M_PI / 2)
	{
		target_distance *= -1;
		target_angle = bindRadians(target_angle + M_PI);
	}
	driveStraight(target_distance, velocity, target_angle, timeout);
}

void BlueMatchAuton::setDriveStraightVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET DRIVE STRAIGHT VELOCITY", velocity);
}

bool BlueMatchAuton::driveStraightTargetReached()
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

void BlueMatchAuton::turnToAngle(double theta, double velocity, bool reversed, uint32_t timeout,
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "TURN TO ANGLE", &m_robot, velocity, theta, static_cast<int>(reversed), direction);
		if (timeout != UINT32_MAX)
		{
			uint32_t start_time{getTime()};
			while (!turnTargetReached() && getTime() < start_time + timeout)
				delay(LOOP_DELAY);
			pauseControlSystem();
		}
	}
}

void BlueMatchAuton::turnToPoint(double x, double y, double velocity, bool reversed, uint32_t timeout,
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
	{
		m_control_system->sendCommand("MOTION", "TURN TO POINT", &m_robot, velocity, x, y, static_cast<int>(reversed), direction);
		if (timeout != UINT32_MAX)
		{
			uint32_t start_time{getTime()};
			while (!turnTargetReached() && getTime() < start_time + timeout)
				delay(LOOP_DELAY);
			pauseControlSystem();
		}
	}
}

bool BlueMatchAuton::turnTargetReached()
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

void BlueMatchAuton::followPath(std::vector<control::path::Point>& path, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("PATH FOLLOWING", "FOLLOW PATH", &m_robot, &path, velocity);
}

void BlueMatchAuton::setPathFollowingVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("PATH FOLLOWING", "SET VELOCITY", velocity);
}

bool BlueMatchAuton::pathFollowingTargetReached()
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

void BlueMatchAuton::setDriveVelocity(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

void BlueMatchAuton::setDriveVoltage(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", left, right);
}

robot::subsystems::drive::Velocity BlueMatchAuton::getDriveVelocity()
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

double BlueMatchAuton::getDriveRadius()
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

void BlueMatchAuton::setElevatorPosition(double position, uint32_t timeout)
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

void BlueMatchAuton::calibrateElevator()
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "CALIBRATE");
}

double BlueMatchAuton::getElevatorPosition()
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

bool BlueMatchAuton::elevatorIsCalibrating()
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

double BlueMatchAuton::getCapDistance()
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

void BlueMatchAuton::closeClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "CLOSE CLAW");
}

void BlueMatchAuton::openClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "OPEN CLAW");
}

void BlueMatchAuton::raiseArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "RAISE ARM");
}

void BlueMatchAuton::lowerArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "LOWER ARM");
}

void BlueMatchAuton::engageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "ENGAGE WINCH");
}

void BlueMatchAuton::disengageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "DISENGAGE WINCH");
}

bool BlueMatchAuton::clawClosed()
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

bool BlueMatchAuton::clawOpen()
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

bool BlueMatchAuton::armRaised()
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

bool BlueMatchAuton::armLowered()
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

bool BlueMatchAuton::winchEngaged()
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

bool BlueMatchAuton::winchDisengaged()
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

void BlueMatchAuton::setIntakeVelocity(double velocity)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VELOCITY", velocity);
}

void BlueMatchAuton::setIntakeVoltage(double voltage)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

double BlueMatchAuton::getIntakeVelocity()
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

double BlueMatchAuton::getBallDistance()
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

std::vector<io::VisionObject> BlueMatchAuton::getBallVisionObjects()
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

void BlueMatchAuton::loadLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO LOAD");
}

void BlueMatchAuton::readyLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO READY");
}

bool BlueMatchAuton::isLoaderLoaded()
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

bool BlueMatchAuton::isLoaderReady()
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

void BlueMatchAuton::setOdometryPosition(double x, double y, double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET POSITION", x, y, theta);
}

void BlueMatchAuton::setOdometryX(double x)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET X", x);
}

void BlueMatchAuton::setOdometryY(double y)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET Y", y);
}

void BlueMatchAuton::setOdometryTheta(double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET THETA", theta);
}

void BlueMatchAuton::resetOdometryX()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET X");
}

void BlueMatchAuton::resetOdometryY()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET Y");
}

robot::subsystems::position::Position BlueMatchAuton::getOdometryPosition()
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

double BlueMatchAuton::getOdometryVelocity()
{
	auto position{getOdometryPosition()};
	double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
	return velocity;
}

void BlueMatchAuton::setUmbrellaIn()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET IN");
}

void BlueMatchAuton::setUmbrellaOut()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET OUT");
}

bool BlueMatchAuton::isUmbrellaIn()
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

bool BlueMatchAuton::isUmbrellaOut()
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

void BlueMatchAuton::setLeftWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET LEFT WING", static_cast<int>(out));
}

void BlueMatchAuton::setRightWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET RIGHT WING", static_cast<int>(out));
}

bool BlueMatchAuton::isLeftWingOut()
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

bool BlueMatchAuton::isRightWingOut()
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

std::string BlueMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{
	m_control_system = control_system;
	m_robot = robot;

	std::vector<control::path::Point> alley_path_control_points
	{
		control::path::Point{25.0, 13.0},
		control::path::Point{32.0, 10.0},
		control::path::Point{48.0, 9.0},
		control::path::Point{62.0, 9.0},
		control::path::Point{75.0, 9.0},
		control::path::Point{82.0, 9.0},
		control::path::Point{96.0, 9.0},
		control::path::Point{110.0, 9.0},
		control::path::Point{117.0, 12.0},
		control::path::Point{120.0, 18.0},
	};
	alley_path = control::path::QuinticBezierSpline::calculate(alley_path_control_points);
}

void BlueMatchAuton::run(std::shared_ptr<IAlliance> alliance,
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
	double start_x{17.0}, start_y{17.0}, start_theta{-3 * M_PI / 4};
	setOdometryPosition(start_x, start_y, start_theta);

	// Grab some basic variables for general use
	auto position{getOdometryPosition()};
	double velocity{getOdometryVelocity()};

	// Do match loads
	uint8_t match_loads{6};
	uint32_t match_load_delay{600};
	uint32_t match_load_timeout{500};
	bool timeout{false};
	for (uint8_t i{}; i < match_loads && !timeout; ++i)
	{
		// Load the triball into the field
		loadLoader();
		uint32_t load_start_time{getTime()};
		while (!isLoaderLoaded() && !timeout)
		{
			timeout = getTime() > load_start_time + match_load_timeout;
			delay(LOOP_DELAY);
		}

		// Reset the match loading mechanism
		readyLoader();
		uint32_t ready_start_time{getTime()};
		while (!isLoaderReady() && !timeout)
		{
			timeout = getTime() > ready_start_time + match_load_timeout;
			delay(LOOP_DELAY);
		}

		// Wait for the next match load
		if (i < match_loads - 1)
			delay(match_load_delay);
	}
	if (timeout)
	{
		// Grab the failed match load
		double failed_triball_x{8.0}, failed_triball_y{8.0};
		uint32_t failed_triball_timeout{1000};
		double failed_triball_offset{4.0};
		position = getOdometryPosition();
		double triball_distance{distance(position.x, position.y, failed_triball_x, failed_triball_y)};
		double elevator_position{triball_distance - ELEVATOR_OFFSET + failed_triball_offset};
		setIntakeVoltage(MAX_VOLTAGE);
		uint32_t elevator_timeout{1000};
		setElevatorPosition(elevator_position, elevator_timeout);

		// Secure the failed match load
		double triball_backup_distance{-4.0};
		uint32_t backup_timeout{500};
		driveStraight(triball_backup_distance, MOTION_VELOCITY, backup_timeout);
		elevator_position = 3.25;
		setElevatorPosition(elevator_position, elevator_timeout);
	}

	// Turn to the start of the alley
	setUmbrellaOut();
	double alley_start_x{26.0}, alley_start_y{11.0};
	uint32_t alley_start_turn_timeout{1000};
	turnToPoint(alley_start_x, alley_start_y, TURN_VELOCITY, true, alley_start_turn_timeout);

	// Extend both wings
	setLeftWing(true);
	setRightWing(true);

	// Move to the start of the alley
	double alley_theta{175 * M_PI / 180};
	position = getOdometryPosition();
	uint32_t alley_start_timeout{2000};
	//goToPoint(alley_start_x, alley_start_y, alley_theta, MOTION_VELOCITY, alley_start_timeout);
	driveStraightToPoint(alley_start_x, alley_start_y, MOTION_VELOCITY, alley_start_timeout);

	// Turn to face down the alley
	uint32_t alley_turn_timeout{500};
	turnToAngle(alley_theta, TURN_VELOCITY, false, alley_turn_timeout);

	/*
	double alley_x{48.0}, alley_y{10.0};
	turnToPoint(alley_x, alley_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);
	*/

	// Follow the alley path
	double alley_end_x{104.0};
	double fast_alley_velocity{48.0}, slow_alley_velocity{24.0}, slow_alley_x{76.0};
	double collision_detection{3.0}, collision_end_x{alley_end_x - 4.0};
	uint32_t collision_delay{1000}, collision_start_time{getTime()};
	double alley_distance{(alley_end_x - alley_start_x) * std::cos(alley_theta)};
	double alley_velocity{fast_alley_velocity};
	position = getOdometryPosition();
	velocity = getOdometryVelocity();
	driveStraight(alley_distance, alley_velocity);
	while (!driveStraightTargetReached())
	{
		// If we have reached the slow section of the alley, slow down
		if (position.x > slow_alley_x)
		{
			alley_velocity = slow_alley_velocity;

			// Get rid of extra balls
			if (timeout)
			{
				setElevatorPosition(0);
				setIntakeVoltage(-MAX_VOLTAGE);
			}
		}
		else
			alley_velocity = fast_alley_velocity;
		setDriveStraightVelocity(alley_velocity);

		// Detect getting stuck
		if (position.x < collision_end_x
			&& velocity < alley_velocity / collision_detection 
			&& getTime() > collision_start_time + collision_delay)
		{
			// Back up to get free
			pauseControlSystem();
			double alley_backup_distance{-6.0};
			uint32_t alley_backup_timeout{500};
			driveStraight(alley_backup_distance, MOTION_VELOCITY, alley_backup_timeout);

			// Resume the alley push
			position = getOdometryPosition();
			alley_distance = (alley_end_x - position.x) * std::cos(alley_theta);
			driveStraight(alley_distance, alley_velocity);
			collision_start_time = getTime();
		}
		
		delay(LOOP_DELAY);
		position = getOdometryPosition();
		velocity = getOdometryVelocity();
	}
	/*
	double alley_velocity{40.0}, alley_stop_y{16.0}, alley_stop{6.0};
	followPath(alley_path, alley_velocity);
	while (!pathFollowingTargetReached())
	{
		// Once we get close to the match load bar, slow down
		if (getOdometryPosition().x > 78.0)
			setPathFollowingVelocity(alley_velocity / 2);
		// If we get stuck, back up and retry
		if (getOdometryVelocity() < alley_stop && getOdometryPosition().y < alley_stop_y)
		{
			pauseControlSystem();
			double collision_voltage{-12.0};
			uint32_t collision_time{500};
			setDriveVelocity(collision_voltage, collision_voltage);
			delay(collision_time);
			resumeControlSystem();
		}
		delay(LOOP_DELAY);
	}
	pauseControlSystem();
	*/

	// Turn to face the start of the goal shove move
	double goal_shove_start_x{alley_end_x + 5.0}, goal_shove_start_y{12.0};
	uint32_t goal_shove_start_turn_timeout{500};
	turnToPoint(goal_shove_start_x, goal_shove_start_y, TURN_VELOCITY, true, goal_shove_start_turn_timeout);

	// Move to the start of the goal shove move
	uint32_t goal_shove_start_timeout{500};
	driveStraightToPoint(goal_shove_start_x, goal_shove_start_y, MOTION_VELOCITY, goal_shove_start_timeout);

	// Turn to face the goal shove start point
	double goal_shove_x{130.0}, goal_shove_y{28.0};
	uint32_t goal_shove_turn_timeout{500};
	turnToPoint(goal_shove_x, goal_shove_y, TURN_VELOCITY, true, goal_shove_turn_timeout);

	// Move to the goal shove start point
	uint32_t goal_shove_timeout{2000};
	driveStraightToPoint(goal_shove_x, goal_shove_y, MOTION_VELOCITY, goal_shove_timeout);

	// Turn to face the goal
	setLeftWing(false);
	double side_goal_x{134.0}, side_goal_y{48.0};
	uint32_t side_goal_turn_timeout{1000};
	turnToPoint(side_goal_x, side_goal_y, TURN_VELOCITY, true, side_goal_turn_timeout);

	// Push the alley triballs into the goal
	double push_velocity{60.0};
	uint32_t push_timeout{1000};
	driveStraightToPoint(side_goal_x, side_goal_y, push_velocity, push_timeout);

	// Turn to face the goal shove start point
	turnToPoint(goal_shove_x, goal_shove_y, TURN_VELOCITY, false, goal_shove_turn_timeout);

	// Move to the goal shove start point
	driveStraightToPoint(goal_shove_x, goal_shove_y, MOTION_VELOCITY, goal_shove_timeout);

	// Turn to face the goal
	turnToPoint(side_goal_x, side_goal_y, TURN_VELOCITY, true, side_goal_turn_timeout);

	// Push the alley triballs into the goal
	driveStraightToPoint(side_goal_x, side_goal_y, push_velocity, push_timeout);

	// Turn to face the match load position
	double alliance_ball_x{132.0}, alliance_ball_y{8.0}, alliance_ball_theta{-M_PI / 4};
	double alliance_ball_distance{17.0};
	uint32_t alliance_ball_turn_timeout{1000};
	double alliance_load_x{alliance_ball_x - (alliance_ball_distance * std::cos(alliance_ball_theta))};
	double alliance_load_y{alliance_ball_y - (alliance_ball_distance * std::sin(alliance_ball_theta))};
	turnToPoint(alliance_load_x, alliance_load_y, TURN_VELOCITY, false, alliance_ball_turn_timeout);

	// Move to the match load position
	uint32_t alliance_ball_timeout{2000};
	driveStraightToPoint(alliance_load_x, alliance_load_y, MOTION_VELOCITY, alliance_ball_timeout);
	setUmbrellaIn();

	// Turn to face the alliance triball
	setLeftWing(false);
	setRightWing(false);
	uint32_t alliance_ball_grab_turn_timeout{1000};
	turnToPoint(alliance_ball_x, alliance_ball_y, TURN_VELOCITY, false, alliance_ball_grab_turn_timeout);

	// Visually detect the alliance ball
	double alliance_ball_angle{};
	double largest_alliance_ball{};
	auto objects{getBallVisionObjects()};
	auto object_ids{alliance->getVisionObjectIDs("TRIBALL")};
	for (auto object : objects)
	{
		for (auto object_id : object_ids)
		{
			if (object.id == object_id && object.id != io::EVisionObjectID::GREEN_TRIBALL)
			{
				if (object.width > largest_alliance_ball)
				{
					largest_alliance_ball = object.width;
					alliance_ball_angle = object.horizontal;
				}
			}
		}
	}
	position = getOdometryPosition();
	alliance_ball_angle += position.theta;

	// Turn to exactly face the alliance triball
	uint32_t precise_alliance_turn_timeout{500};
	turnToAngle(alliance_ball_angle, TURN_VELOCITY, false, precise_alliance_turn_timeout);

	// Grab the alliance triball
	double alliance_ball_grab_distance{6.0}, alliance_ball_velocity{12.0}, alliance_ball_elevator{8.0};
	uint32_t alliance_ball_grab_timeout{1000}, alliance_ball_grab_delay{500};
	driveStraight(alliance_ball_grab_distance, alliance_ball_velocity, alliance_ball_angle);
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(alliance_ball_elevator, alliance_ball_grab_timeout);
	delay(alliance_ball_grab_delay);
	pauseControlSystem();

	// Back away from the alliance triball
	double load_bar_distance{-8.0};
	uint32_t load_bar_timeout{500};
	driveStraight(load_bar_distance, MOTION_VELOCITY, load_bar_timeout);

	// Suck in the alliance ball
	double ball_elevator{3.25};
	uint32_t ball_elevator_timeout{500};
	setElevatorPosition(ball_elevator, ball_elevator_timeout);

	// Turn to face the goal shove start point
	double forward_x_offset{-5.0};
	turnToPoint(goal_shove_x + forward_x_offset, goal_shove_y, TURN_VELOCITY, false, goal_shove_turn_timeout);

	// Move to the goal shove start point
	driveStraightToPoint(goal_shove_x + forward_x_offset, goal_shove_y, MOTION_VELOCITY, goal_shove_timeout);

	// Turn to face the goal
	turnToPoint(side_goal_x, side_goal_y, TURN_VELOCITY, false, side_goal_turn_timeout);

	// Let go of the alliance triball
	double triball_release_elevator{0};
	setIntakeVoltage(-MAX_VOLTAGE);
	setElevatorPosition(triball_release_elevator, ball_elevator_timeout);
	
	// Ram the goal with passion part 3
	driveStraightToPoint(side_goal_x, side_goal_y, push_velocity, push_timeout);

	// Turn to face the midfield entrance
	double entrance_x{104.0}, entrance_y{14.0};
	uint32_t entrance_turn_timeout{1500};
	turnToPoint(entrance_x, entrance_y, TURN_VELOCITY, true, entrance_turn_timeout);

	// Move to the goal shove start point
	uint32_t entrance_timeout{3000};
	driveStraightToPoint(entrance_x, entrance_y, MOTION_VELOCITY, entrance_timeout);

	// Turn to face the front of the goal
	double sentry_x{104.0}, sentry_y{60.0};
	uint32_t sentry_turn_timeout{1500};
	turnToPoint(sentry_x, sentry_y, TURN_VELOCITY, sentry_turn_timeout);

	// Move to the front of the goal
	double sweep_velocity{26.0};
	uint32_t sweep_timeout{4000};
	driveStraightToPoint(sentry_x, sentry_y, sweep_velocity, sweep_timeout);

	// Turn to face forward
	uint32_t sentry_start_timeout{500};
	turnToAngle(5 * M_PI / 12, TURN_VELOCITY, sentry_start_timeout);

	// Create the sentry mode routine
	std::unique_ptr<rtos::IMutex> sentry_mutex{std::make_unique<pros_adapters::ProsMutex>()};
	std::unique_ptr<rtos::ITask> sentry_task{std::make_unique<pros_adapters::ProsTask>()};
	static routines::SentryMode sentry_mode{alliance, m_clock, m_delayer, sentry_mutex, sentry_task, m_control_system, m_robot};
	sentry_mode.run();

	// Run sentry mode
	bool sentry{true};
	position = getOdometryPosition();
	control::path::Point last_ball{};
	double sentry_goal_x{104.0}, sentry_goal_y{60.0};
	while (sentry && getTime() - auton_start_time < 40000)
	{
		// Try to grab the next ball
		sentry_mode.doSentryMode(-5 * M_PI / 12, control::motion::ETurnDirection::COUNTERCLOCKWISE);
		while (!sentry_mode.isFinished())
			delay(LOOP_DELAY);
		sentry = sentry_mode.ballFound();

		// If it got a ball, score it
		if (sentry && getTime() - auton_start_time < 40000)
		{
			// Calculate the distance to return to the goal
			position = getOdometryPosition();
			last_ball = sentry_mode.getBall();
			double target_distance{distance(position.x, position.y, sentry_goal_x, sentry_goal_y)};

			// If the distance is large enough to warrant moving back, move back
			if (target_distance > 3.0)
			{
				// Turn to face the front of the goal
				// May be (probably is) unnecessary with drivestraight version
				double target_angle{angle(position.x, position.y, sentry_goal_x, sentry_goal_y)};
				bool reversed{std::abs(bindRadians(target_angle - position.theta)) > M_PI / 2};
				turnToPoint(sentry_goal_x, sentry_goal_y, 2 * M_PI, reversed);
				if (reversed)
					target_angle = bindRadians(target_angle + M_PI);
				while (!turnTargetReached() && std::abs(position.theta - target_angle) > M_PI / 36)
				{
					delay(LOOP_DELAY);
					position = getOdometryPosition();
					target_angle = angle(position.x, position.y, sentry_goal_x, sentry_goal_y);
					if (reversed)
						target_angle = bindRadians(target_angle + M_PI);
				}

				position = getOdometryPosition();
				goToPoint(sentry_goal_x, sentry_goal_y, position.theta, 48.0);
				target_distance = distance(position.x, position.y, sentry_goal_x, sentry_goal_y);
				while (target_distance > 3.0)
				{
					delay(LOOP_DELAY);
					position = getOdometryPosition();
					target_distance = distance(position.x, position.y, sentry_goal_x, sentry_goal_y);
				}
				control_system->pause();
			}

			turnToAngle(0, 2 * M_PI);
			position = getOdometryPosition();
			while (std::abs(bindRadians(position.theta)) > M_PI / 36)
			{
				if (std::abs(bindRadians(position.theta)) < M_PI / 18)
				{
					robot->sendCommand("ELEVATOR", "SET POSITION", 0.0);
					robot->sendCommand("INTAKE", "SET VOLTAGE", -12.0);
				}
				delay(LOOP_DELAY);
				position = getOdometryPosition();
			}
			control_system->pause();

			robot->sendCommand("ELEVATOR", "SET POSITION", 0.0);
			robot->sendCommand("INTAKE", "SET VOLTAGE", -12.0);
			while (getElevatorPosition() > 1.0)
				delay(LOOP_DELAY);
			robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", 12.0, 12.0);
			position = getOdometryPosition();
			while (position.x < 110.0 || position.xV > 16.0)
			{
				delay(LOOP_DELAY);
				position = getOdometryPosition();
			}
			
			position = getOdometryPosition();
			double target_angle{angle(position.x, position.y, sentry_goal_x, sentry_goal_y)};
			goToPoint(sentry_goal_x, sentry_goal_y, target_angle, 48.0);
			while (position.x > sentry_goal_x + 1)
			{
				delay(LOOP_DELAY);
				position = getOdometryPosition();
			}

			position = getOdometryPosition();
			turnToPoint(last_ball.getX(), last_ball.getY(), 2 * M_PI);
			target_angle = angle(position.x, position.y, last_ball.getX(), last_ball.getY());
			while (!turnTargetReached() && std::abs(position.theta - target_angle) > M_PI / 36)
			{
				delay(LOOP_DELAY);
				position = getOdometryPosition();
				target_angle = angle(position.x, position.y, last_ball.getX(), last_ball.getY());
			}
			control_system->pause();
		}
	}

	turnToPoint(72.0, 24.0, TURN_VELOCITY, false, 2000);
	setElevatorPosition(16.0);
	position = getOdometryPosition();
	double target_distance{distance(position.x, position.y, 72.0, 24.0)};
	driveStraight(target_distance - 10, MOTION_VELOCITY, (uint32_t)2000);
	setElevatorPosition(getElevatorPosition());
	pros::screen::print(pros::E_TEXT_LARGE_CENTER, 7, "End Time: %5.2f", (getTime() - auton_start_time) / 1000.0);
}
}
}