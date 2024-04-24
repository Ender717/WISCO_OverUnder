#include "wisco/autons/OrangeMatchAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "wisco/io/EVisionObjectID.hpp"
#include <iostream>

namespace wisco
{
namespace autons
{
uint32_t OrangeMatchAuton::getTime()
{
	uint32_t time{};
	if (m_clock)
		time = m_clock->getTime();
	return time;
}

void OrangeMatchAuton::delay(uint32_t millis)
{
	if (m_delayer)
		m_delayer->delay(millis);
}

void OrangeMatchAuton::pauseControlSystem()
{
	if (m_control_system)
		m_control_system->pause();
}

void OrangeMatchAuton::resumeControlSystem()
{
	if (m_control_system)
		m_control_system->resume();
}

void OrangeMatchAuton::goToPoint(double x, double y, double theta, double velocity, uint32_t timeout)
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

bool OrangeMatchAuton::boomerangTargetReached()
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

void OrangeMatchAuton::driveStraight(double distance, double velocity, uint32_t timeout)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta, timeout);
}

void OrangeMatchAuton::driveStraight(double distance, double velocity, double theta, uint32_t timeout)
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

void OrangeMatchAuton::driveStraightToPoint(double x, double y, double velocity, uint32_t timeout)
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

void OrangeMatchAuton::setDriveStraightVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET DRIVE STRAIGHT VELOCITY", velocity);
}

bool OrangeMatchAuton::driveStraightTargetReached()
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

void OrangeMatchAuton::turnToAngle(double theta, double velocity, bool reversed, uint32_t timeout,
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

void OrangeMatchAuton::turnToPoint(double x, double y, double velocity, bool reversed, uint32_t timeout,
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

bool OrangeMatchAuton::turnTargetReached()
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

void OrangeMatchAuton::followPath(std::vector<control::path::Point>& path, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("PATH FOLLOWING", "FOLLOW PATH", &m_robot, &path, velocity);
}

void OrangeMatchAuton::setPathFollowingVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("PATH FOLLOWING", "SET VELOCITY", velocity);
}

bool OrangeMatchAuton::pathFollowingTargetReached()
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

void OrangeMatchAuton::setDriveVelocity(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

void OrangeMatchAuton::setDriveVoltage(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", left, right);
}

robot::subsystems::drive::Velocity OrangeMatchAuton::getDriveVelocity()
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

double OrangeMatchAuton::getDriveRadius()
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

void OrangeMatchAuton::setElevatorPosition(double position, uint32_t timeout)
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

void OrangeMatchAuton::calibrateElevator()
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "CALIBRATE");
}

double OrangeMatchAuton::getElevatorPosition()
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

bool OrangeMatchAuton::elevatorIsCalibrating()
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

double OrangeMatchAuton::getCapDistance()
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

void OrangeMatchAuton::closeClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "CLOSE CLAW");
}

void OrangeMatchAuton::openClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "OPEN CLAW");
}

void OrangeMatchAuton::raiseArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "RAISE ARM");
}

void OrangeMatchAuton::lowerArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "LOWER ARM");
}

void OrangeMatchAuton::engageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "ENGAGE WINCH");
}

void OrangeMatchAuton::disengageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "DISENGAGE WINCH");
}

bool OrangeMatchAuton::clawClosed()
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

bool OrangeMatchAuton::clawOpen()
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

bool OrangeMatchAuton::armRaised()
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

bool OrangeMatchAuton::armLowered()
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

bool OrangeMatchAuton::winchEngaged()
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

bool OrangeMatchAuton::winchDisengaged()
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

void OrangeMatchAuton::setIntakeVelocity(double velocity)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VELOCITY", velocity);
}

void OrangeMatchAuton::setIntakeVoltage(double voltage)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

double OrangeMatchAuton::getIntakeVelocity()
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

double OrangeMatchAuton::getBallDistance()
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

std::vector<io::VisionObject> OrangeMatchAuton::getBallVisionObjects()
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

void OrangeMatchAuton::loadLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO LOAD");
}

void OrangeMatchAuton::readyLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO READY");
}

bool OrangeMatchAuton::isLoaderLoaded()
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

bool OrangeMatchAuton::isLoaderReady()
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

void OrangeMatchAuton::setOdometryPosition(double x, double y, double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET POSITION", x, y, theta);
}

void OrangeMatchAuton::setOdometryX(double x)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET X", x);
}

void OrangeMatchAuton::setOdometryY(double y)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET Y", y);
}

void OrangeMatchAuton::setOdometryTheta(double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET THETA", theta);
}

void OrangeMatchAuton::resetOdometryX()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET X");
}

void OrangeMatchAuton::resetOdometryY()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET Y");
}

robot::subsystems::position::Position OrangeMatchAuton::getOdometryPosition()
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

double OrangeMatchAuton::getOdometryVelocity()
{
	auto position{getOdometryPosition()};
	double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
	return velocity;
}

void OrangeMatchAuton::setUmbrellaIn()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET IN");
}

void OrangeMatchAuton::setUmbrellaOut()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET OUT");
}

bool OrangeMatchAuton::isUmbrellaIn()
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

bool OrangeMatchAuton::isUmbrellaOut()
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

void OrangeMatchAuton::setLeftWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET LEFT WING", static_cast<int>(out));
}

void OrangeMatchAuton::setRightWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET RIGHT WING", static_cast<int>(out));
}

bool OrangeMatchAuton::isLeftWingOut()
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

bool OrangeMatchAuton::isRightWingOut()
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

std::string OrangeMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void OrangeMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
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

void OrangeMatchAuton::run(std::shared_ptr<IAlliance> alliance,
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
	double start_x{38.75}, start_y{15.5}, start_theta{95.0 * M_PI / 180.0};
	setOdometryPosition(start_x, start_y, start_theta);

	// Grab some basic variables for general use
	auto position{getOdometryPosition()};
	double velocity{getOdometryVelocity()};

	// Move next to the first triball
	double rush_velocity{48.0};
	double rush_start_x{34.0}, rush_start_y{58.0};
	uint32_t rush_start_timeout{2000};
	driveStraightToPoint(rush_start_x, rush_start_y, rush_velocity, rush_start_timeout);

	// Turn to face the front triball
	double front_triball_x{48.0}, front_triball_y{72.0};
	uint32_t front_triball_turn_timeout{1000};
	turnToPoint(front_triball_x, front_triball_y, TURN_VELOCITY, false, front_triball_turn_timeout);

	// Grab the front triball
	position = getOdometryPosition();
	double elevator_distance{distance(position.x, position.y, front_triball_x, front_triball_y)};
	double rush_front_elevator_offset{2.0};
	uint32_t rush_front_elevator_timeout{1000};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(elevator_distance + rush_front_elevator_offset - ELEVATOR_OFFSET, rush_front_elevator_timeout);
	setIntakeVoltage(0);

	// Pull the elevator in
	double ball_elevator{3.25};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(ball_elevator);

	// Turn to sweep the back triball off the line
	double rush_middle_x{52.0}, rush_middle_y{58.0};
	uint32_t rush_middle_turn_timeout{500};
	turnToPoint(rush_middle_x, rush_middle_y, TURN_VELOCITY, false, rush_middle_turn_timeout);

	// Move next to the bar triballs
	uint32_t rush_middle_timeout{3000};
	goToPoint(rush_middle_x, rush_middle_y, 0.0, MOTION_VELOCITY, rush_middle_timeout);

	// Turn in front of the bar triballs
	double rush_middle_start_angle{5 * M_PI / 12};
	uint32_t rush_middle_start_timeout{1000};
	turnToAngle(rush_middle_start_angle, TURN_VELOCITY, false, rush_middle_start_timeout);

	// Extend the elevator
	double rush_middle_elevator{16.0};
	uint32_t rush_middle_elevator_timeout{1000};
	setElevatorPosition(rush_middle_elevator, rush_middle_elevator_timeout);

	// Turn to sweep the bar triballs back
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(ball_elevator);
	double rush_far_x{62.0}, rush_far_y{60.0};
	uint32_t rush_far_turn_timeout{1000};
	turnToPoint(rush_far_x, rush_far_y, TURN_VELOCITY, false, rush_far_turn_timeout);

	// Move next to the bar
	uint32_t rush_far_timeout{3000};
	goToPoint(rush_far_x, rush_far_y, 0.0, MOTION_VELOCITY, rush_far_timeout);

	// Turn in front of the far triballs
	double rush_far_start_angle{5 * M_PI / 12};
	uint32_t rush_far_start_timeout{1000};
	turnToAngle(rush_middle_start_angle, TURN_VELOCITY, false, rush_middle_start_timeout);

	// Extend the elevator
	setIntakeVoltage(0);
	double rush_far_elevator{16.0};
	uint32_t rush_far_elevator_timeout{1000};
	setElevatorPosition(rush_middle_elevator, rush_middle_elevator_timeout);

	// Turn to displace the far triballs
	double rush_far_end_angle{M_PI / 5};
	uint32_t rush_far_end_timeout{1000};
	turnToAngle(rush_far_end_angle, TURN_VELOCITY, false, rush_far_end_timeout);

	// Turn back, retract the elevator and back up
	double short_barrier_start_x{64.0}, short_barrier_start_y{52.0};
	uint32_t short_barrier_start_turn_timeout{1500};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(ball_elevator);
	turnToPoint(short_barrier_start_x, short_barrier_start_y, TURN_VELOCITY, true, short_barrier_start_turn_timeout);
	uint32_t rush_backup_timeout{1000};
	driveStraightToPoint(short_barrier_start_x, short_barrier_start_y, MOTION_VELOCITY, rush_backup_timeout);

	// Turn to face the short barrier
	double short_barrier_x_1{67.0}, short_barrier_y{24.0};
	uint32_t short_barrier_turn_1_timeout{1000};
	turnToPoint(short_barrier_x_1, short_barrier_y, TURN_VELOCITY, false, short_barrier_turn_1_timeout);

	// Outtake the held ball
	setIntakeVoltage(-MAX_VOLTAGE);
	uint32_t outtake_elevator_timeout{1000};
	setElevatorPosition(0, outtake_elevator_timeout);

	// Extend the elevator completely
	double barrier_elevator_position{16.0};
	uint32_t barrier_elevator_timeout{1000};
	setElevatorPosition(barrier_elevator_position, barrier_elevator_timeout);

	// Push the first set of balls over the bar
	double short_barrier_velocity{6.0};
	uint32_t short_barrier_timeout{4000};

	// Push forward to outtake balls over the bar
	double push_offset{-3.0};
	position = getOdometryPosition();
	double short_barrier_distance{position.y - short_barrier_y - barrier_elevator_position + push_offset};
	driveStraight(short_barrier_distance, short_barrier_velocity, short_barrier_timeout);

	// Pull back to reset
	double short_barrier_backup_distance{-2.0};
	uint32_t backup_timeout{1000};
	driveStraight(short_barrier_backup_distance, MOTION_VELOCITY, backup_timeout);

	// Turn to face the second set of balls
	double short_barrier_x_2{56.0};
	uint32_t short_barrier_turn_2_timeout{500};
	turnToPoint(short_barrier_x_2, short_barrier_y, TURN_VELOCITY, false, short_barrier_turn_2_timeout);

	// Push forward to outtake balls over the bar
	position = getOdometryPosition();
	short_barrier_distance = position.y - short_barrier_y - barrier_elevator_position + push_offset;
	driveStraight(short_barrier_distance, short_barrier_velocity, short_barrier_timeout);

	return;

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
	driveStraightToPoint(alley_start_x, alley_start_y, MOTION_VELOCITY, alley_start_timeout);

	// Turn to face down the alley
	uint32_t alley_turn_timeout{500};
	turnToAngle(alley_theta, TURN_VELOCITY, false, alley_turn_timeout);

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

	// Touch the bar for win point (remove for elims)
	turnToPoint(72.0, 24.0, TURN_VELOCITY, false, 2000);
	setElevatorPosition(16.0);
	position = getOdometryPosition();
	double target_distance{distance(position.x, position.y, 72.0, 24.0)};
	driveStraight(target_distance - 20, MOTION_VELOCITY, (uint32_t)2000);
	setElevatorPosition(getElevatorPosition());
	pros::screen::print(pros::E_TEXT_LARGE_CENTER, 7, "End Time: %5.2f", (getTime() - auton_start_time) / 1000.0);
}
}
}