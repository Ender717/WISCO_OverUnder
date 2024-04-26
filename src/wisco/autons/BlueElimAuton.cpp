#include "wisco/autons/BlueElimAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "wisco/io/EVisionObjectID.hpp"
#include <iostream>

namespace wisco
{
namespace autons
{
uint32_t BlueElimAuton::getTime()
{
	uint32_t time{};
	if (m_clock)
		time = m_clock->getTime();
	return time;
}

void BlueElimAuton::delay(uint32_t millis)
{
	if (m_delayer)
		m_delayer->delay(millis);
}

void BlueElimAuton::pauseControlSystem()
{
	if (m_control_system)
		m_control_system->pause();
}

void BlueElimAuton::resumeControlSystem()
{
	if (m_control_system)
		m_control_system->resume();
}

void BlueElimAuton::goToPoint(double x, double y, double theta, double velocity, uint32_t timeout, double tolerance)
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

bool BlueElimAuton::boomerangTargetReached()
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

void BlueElimAuton::driveStraight(double distance, double velocity, uint32_t timeout, double tolerance)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta, timeout, tolerance);
}

void BlueElimAuton::driveStraight(double motion_distance, double velocity, double theta, uint32_t timeout, double tolerance)
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

void BlueElimAuton::driveStraightToPoint(double x, double y, double velocity, uint32_t timeout, double tolerance)
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

void BlueElimAuton::setDriveStraightVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET DRIVE STRAIGHT VELOCITY", velocity);
}

bool BlueElimAuton::driveStraightTargetReached()
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

void BlueElimAuton::turnToAngle(double theta, double velocity, bool reversed, uint32_t timeout, double tolerance,
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

void BlueElimAuton::turnToPoint(double x, double y, double velocity, bool reversed, uint32_t timeout, double tolerance,
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

bool BlueElimAuton::turnTargetReached()
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

void BlueElimAuton::followPath(std::vector<control::path::Point>& path, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("PATH FOLLOWING", "FOLLOW PATH", &m_robot, &path, velocity);
}

void BlueElimAuton::setPathFollowingVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("PATH FOLLOWING", "SET VELOCITY", velocity);
}

bool BlueElimAuton::pathFollowingTargetReached()
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

void BlueElimAuton::setDriveVelocity(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

void BlueElimAuton::setDriveVoltage(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", left, right);
}

robot::subsystems::drive::Velocity BlueElimAuton::getDriveVelocity()
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

double BlueElimAuton::getDriveRadius()
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

void BlueElimAuton::setElevatorPosition(double position, uint32_t timeout)
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

void BlueElimAuton::calibrateElevator()
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "CALIBRATE");
}

double BlueElimAuton::getElevatorPosition()
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

bool BlueElimAuton::elevatorIsCalibrating()
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

double BlueElimAuton::getCapDistance()
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

void BlueElimAuton::closeClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "CLOSE CLAW");
}

void BlueElimAuton::openClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "OPEN CLAW");
}

void BlueElimAuton::raiseArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "RAISE ARM");
}

void BlueElimAuton::lowerArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "LOWER ARM");
}

void BlueElimAuton::engageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "ENGAGE WINCH");
}

void BlueElimAuton::disengageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "DISENGAGE WINCH");
}

bool BlueElimAuton::clawClosed()
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

bool BlueElimAuton::clawOpen()
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

bool BlueElimAuton::armRaised()
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

bool BlueElimAuton::armLowered()
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

bool BlueElimAuton::winchEngaged()
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

bool BlueElimAuton::winchDisengaged()
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

void BlueElimAuton::setIntakeVelocity(double velocity)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VELOCITY", velocity);
}

void BlueElimAuton::setIntakeVoltage(double voltage)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

double BlueElimAuton::getIntakeVelocity()
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

double BlueElimAuton::getBallDistance()
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

std::vector<io::VisionObject> BlueElimAuton::getBallVisionObjects()
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

void BlueElimAuton::loadLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO LOAD");
}

void BlueElimAuton::readyLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO READY");
}

bool BlueElimAuton::isLoaderLoaded()
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

bool BlueElimAuton::isLoaderReady()
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

void BlueElimAuton::setOdometryPosition(double x, double y, double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET POSITION", x, y, theta);
}

void BlueElimAuton::setOdometryX(double x)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET X", x);
}

void BlueElimAuton::setOdometryY(double y)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET Y", y);
}

void BlueElimAuton::setOdometryTheta(double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET THETA", theta);
}

void BlueElimAuton::resetOdometryX()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET X");
}

void BlueElimAuton::resetOdometryY()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET Y");
}

robot::subsystems::position::Position BlueElimAuton::getOdometryPosition()
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

double BlueElimAuton::getOdometryVelocity()
{
	auto position{getOdometryPosition()};
	double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
	return velocity;
}

void BlueElimAuton::setUmbrellaIn()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET IN");
}

void BlueElimAuton::setUmbrellaOut()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET OUT");
}

bool BlueElimAuton::isUmbrellaIn()
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

bool BlueElimAuton::isUmbrellaOut()
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

void BlueElimAuton::setLeftWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET LEFT WING", static_cast<int>(out));
}

void BlueElimAuton::setRightWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET RIGHT WING", static_cast<int>(out));
}

bool BlueElimAuton::isLeftWingOut()
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

bool BlueElimAuton::isRightWingOut()
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

std::string BlueElimAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueElimAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
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

void BlueElimAuton::run(std::shared_ptr<IAlliance> alliance,
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
	double start_x{39.25}, start_y{15.5}, start_theta{95.0 * M_PI / 180.0};
	setOdometryPosition(start_x, start_y, start_theta);

	// Grab some basic variables for general use
	auto position{getOdometryPosition()};
	double velocity{getOdometryVelocity()};

	// Move next to the first triball
	double rush_velocity{48.0};
	double rush_start_x{34.0}, rush_start_y{55.0};
	uint32_t rush_start_timeout{2000};
	setElevatorPosition(5.0);
	driveStraightToPoint(rush_start_x, rush_start_y, rush_velocity, rush_start_timeout);

	// Turn to face the front triball
	double front_triball_turn_tolerance{5.0 * M_PI / 180};
	double front_triball_x{48.0}, front_triball_y{72.0};
	uint32_t front_triball_turn_timeout{1000};
	setElevatorPosition(8.0);
	turnToPoint(front_triball_x, front_triball_y, TURN_VELOCITY, false, front_triball_turn_timeout, front_triball_turn_tolerance);

	// Grab the front triball
	position = getOdometryPosition();
	double elevator_distance{distance(position.x, position.y, front_triball_x, front_triball_y)};
	double rush_front_elevator_offset{1.0};
	uint32_t rush_front_elevator_timeout{1000};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(elevator_distance + rush_front_elevator_offset - ELEVATOR_OFFSET, rush_front_elevator_timeout);

	// Pull the elevator in
	double sweep_elevator{6.0};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(sweep_elevator);

	// Turn to sweep the back triball off the line
	turnToAngle(-M_PI / 3, M_PI, false, 1500, 3.0 * M_PI / 180);

	// Let go of the triball
	setIntakeVoltage(-MAX_VOLTAGE / 1.5);
	setElevatorPosition(0.0, 1000);

	// Turn to face the third ball
	double rush_middle_turn_tolerance{3.0 * M_PI / 180};
	double rush_middle_x{70.0}, rush_middle_y{60.0};
	uint32_t rush_middle_turn_timeout{500};
	turnToPoint(rush_middle_x, rush_middle_y, TURN_VELOCITY, false, rush_middle_turn_timeout, rush_middle_turn_tolerance);

	// Pick up the third triball
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(3.25);
	driveStraightToPoint(rush_middle_x - 8, rush_middle_y, 48.0, 1000, 2.0);

	// Turn to face the start of the alley
	double return_x{36.0}, return_y{26.0};
	turnToPoint(return_x, return_y, TURN_VELOCITY, true, 1000, 3.0 * M_PI / 180);

	// Move to the start of the alley
	setLeftWing(true);
	setRightWing(true);
	driveStraightToPoint(return_x, return_y, 48.0, 2000, 2.0);

	// Turn into the alley
	setLeftWing(false);
	setRightWing(false);
	turnToPoint(48.0, 0.0, TURN_VELOCITY, false, 1000, 3.0 * M_PI / 180);

	// Outtake into the alley
	setIntakeVoltage(-MAX_VOLTAGE);
	setElevatorPosition(0.0, 1000);

	// Turn to face the near wall
	double load_wall_x{16.0}, load_wall_y{36.0}, load_wall_turn_tolerance{3.0 * M_PI / 180};
	uint32_t load_wall_turn_timeout{1500};
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(3.25);
	turnToPoint(load_wall_x, load_wall_y, TURN_VELOCITY, false, load_wall_turn_timeout);

	// Move to the near wall
	double load_wall_tolerance{2.0};
	uint32_t load_wall_timeout{1500};
	driveStraightToPoint(load_wall_x, load_wall_y, MOTION_VELOCITY, load_wall_timeout, load_wall_tolerance);

	// Reset the y-coordinate
	resetOdometryY();

	// Tuen to reset X
	turnToAngle(M_PI / 2, TURN_VELOCITY, false, 1000, 2 * M_PI / 180);

	// Reset the x-coordinate
	resetOdometryX();

	// Turn towards the elim load zone
	double elim_load_distance{25.0}, elim_load_angle{M_PI / 4};
	double elim_load_x{elim_load_distance * std::cos(elim_load_angle)};
	double elim_load_y{elim_load_distance * std::sin(elim_load_angle)};
	double elim_load_turn_tolerance{2.0 * M_PI / 180};
	uint32_t elim_load_turn_timeout{1500};
	turnToPoint(elim_load_x, elim_load_y, TURN_VELOCITY, false, elim_load_turn_timeout, elim_load_turn_tolerance);
	setIntakeVoltage(0);

	// Move to the front of the elim load zone
	uint32_t elim_load_setup_timeout{1000};
	driveStraightToPoint(elim_load_x, elim_load_y, MOTION_VELOCITY, elim_load_setup_timeout);

	// Outtake any ball
	uint32_t elevator_timeout{1000};
	setIntakeVoltage(-MAX_VOLTAGE);
	setElevatorPosition(0, elevator_timeout);
	setIntakeVoltage(0);

	// Turn to face the elim loads
	turnToPoint(0, 0, TURN_VELOCITY, false, elim_load_turn_timeout);

	// Move into elim loading position
	double elim_load_drive_distance{5.0}, elim_load_drive_velocity{12.0};
	uint32_t elim_load_drive_timeout{1000};
	driveStraight(elim_load_drive_distance, elim_load_drive_velocity, -3 * M_PI / 4, elim_load_drive_timeout);

	// She wangle my jangle until I finish
	uint8_t elim_loads{6};
	uint32_t elim_load_delay{300};
	uint32_t elim_load_timeout{500};
	bool timeout{false};
	for (uint8_t i{}; i < elim_loads && !timeout; ++i)
	{
		// Load the triball into the field
		loadLoader();
		uint32_t load_start_time{getTime()};
		while (!isLoaderLoaded() && !timeout)
		{
			timeout = getTime() > load_start_time + elim_load_timeout;
			delay(LOOP_DELAY);
		}

		// Reset the elim loading mechanism
		readyLoader();
		uint32_t ready_start_time{getTime()};
		while (!isLoaderReady() && !timeout)
		{
			timeout = getTime() > ready_start_time + elim_load_timeout;
			delay(LOOP_DELAY);
		}

		// Wait for the next elim load
		if (i < elim_loads - 1)
			delay(elim_load_delay);
	}
	if (timeout)
	{
		// Grab the failed elim load
		double failed_triball_x{8.0}, failed_triball_y{8.0};
		uint32_t failed_triball_timeout{1000};
		double failed_triball_offset{4.0};
		position = getOdometryPosition();
		double triball_distance{distance(position.x, position.y, failed_triball_x, failed_triball_y)};
		double elevator_position{triball_distance - ELEVATOR_OFFSET + failed_triball_offset};
		setIntakeVoltage(MAX_VOLTAGE);
		uint32_t elevator_timeout{1000};
		setElevatorPosition(elevator_position, elevator_timeout);

		// Secure the failed elim load
		double triball_backup_distance{-4.0};
		uint32_t backup_timeout{500};
		driveStraight(triball_backup_distance, MOTION_VELOCITY, backup_timeout);
		elevator_position = 3.25;
		setElevatorPosition(elevator_position, elevator_timeout);
	}

	// Turn to the start of the alley
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
	double alley_end_x{109.0};
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
			alley_velocity = slow_alley_velocity;
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

	// Turn to face the goal shove start point
	double goal_shove_x{130.0}, goal_shove_y{28.0};
	uint32_t goal_shove_turn_timeout{500};
	turnToPoint(goal_shove_x, goal_shove_y - 2, TURN_VELOCITY, true, goal_shove_turn_timeout);

	// Move to the goal shove start point
	uint32_t goal_shove_timeout{2000};
	driveStraightToPoint(goal_shove_x, goal_shove_y - 2, MOTION_VELOCITY, goal_shove_timeout);

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
		if (getBallDistance() > 4.0)
		{
			sentry_mode.doSentryMode(-5 * M_PI / 12, control::motion::ETurnDirection::COUNTERCLOCKWISE);
			while (!sentry_mode.isFinished())
				delay(LOOP_DELAY);
			sentry = sentry_mode.ballFound();
		}

		// If it got a ball, score it
		if (sentry && getTime() - auton_start_time < 40000)
		{
			// Store the found ball coordinates
			position = getOdometryPosition();
			last_ball = sentry_mode.getBall();
			double last_angle = angle(position.x, position.y, last_ball.getX(), last_ball.getY());

			// Move in front of the goal
			driveStraightToPoint(sentry_goal_x, sentry_goal_y, 48.0, 1000, 3.0);
			
			// Release the ball
			turnToAngle(0, 2 * M_PI, false, 1000, 4.0 * M_PI / 180);
			setIntakeVoltage(-MAX_VOLTAGE);
			setElevatorPosition(0.0, 1000);

			robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", 12.0, 12.0);
			delay(800);
			position = getOdometryPosition();
			while (position.xV > 16.0)
			{
				delay(LOOP_DELAY);
				position = getOdometryPosition();
			}
			
			driveStraightToPoint(sentry_x, sentry_y, 48.0, 1000, 2.0);

			turnToAngle(last_angle, TURN_VELOCITY, false, 1000, 2.0 * M_PI / 180);
		}
	}

	// TODO win point stuff
	turnToPoint(72.0, 24.0, TURN_VELOCITY, false, 2000);
	setElevatorPosition(16.0);
	position = getOdometryPosition();
	double target_distance{distance(position.x, position.y, 72.0, 24.0)};
	driveStraight(target_distance - 10, MOTION_VELOCITY, (uint32_t)2000);
	setElevatorPosition(getElevatorPosition());
	setIntakeVoltage(0);
	pros::screen::print(pros::E_TEXT_LARGE_CENTER, 7, "End Time: %5.2f", (getTime() - auton_start_time) / 1000.0);
}
}
}