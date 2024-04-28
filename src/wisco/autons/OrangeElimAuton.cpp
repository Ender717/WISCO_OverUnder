#include "wisco/autons/OrangeElimAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "wisco/io/EVisionObjectID.hpp"
#include <iostream>

namespace wisco
{
namespace autons
{
uint32_t OrangeElimAuton::getTime()
{
	uint32_t time{};
	if (m_clock)
		time = m_clock->getTime();
	return time;
}

void OrangeElimAuton::delay(uint32_t millis)
{
	if (m_delayer)
		m_delayer->delay(millis);
}

void OrangeElimAuton::pauseControlSystem()
{
	if (m_control_system)
		m_control_system->pause();
}

void OrangeElimAuton::resumeControlSystem()
{
	if (m_control_system)
		m_control_system->resume();
}

void OrangeElimAuton::boomerangGoToPoint(double x, double y, double theta, double velocity, uint32_t timeout, double tolerance)
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

bool OrangeElimAuton::boomerangTargetReached()
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

void OrangeElimAuton::driveStraight(double distance, double velocity, uint32_t timeout, double tolerance)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta, timeout, tolerance);
}

void OrangeElimAuton::driveStraight(double motion_distance, double velocity, double theta, uint32_t timeout, double tolerance)
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

void OrangeElimAuton::driveStraightToPoint(double x, double y, double velocity, uint32_t timeout, double tolerance)
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

void OrangeElimAuton::setDriveStraightVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET DRIVE STRAIGHT VELOCITY", velocity);
}

bool OrangeElimAuton::driveStraightTargetReached()
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

void OrangeElimAuton::goToPoint(double x, double y, double velocity, uint32_t timeout, double tolerance)
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

void OrangeElimAuton::setGoToPointVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("MOTION", "SET GO TO POINT VELOCITY", velocity);
}

bool OrangeElimAuton::goToPointTargetReached()
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

void OrangeElimAuton::turnToAngle(double theta, double velocity, bool reversed, uint32_t timeout, double tolerance,
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

void OrangeElimAuton::turnToPoint(double x, double y, double velocity, bool reversed, uint32_t timeout, double tolerance,
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

bool OrangeElimAuton::turnTargetReached()
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

void OrangeElimAuton::followPath(std::vector<control::path::Point>& path, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("PATH FOLLOWING", "FOLLOW PATH", &m_robot, &path, velocity);
}

void OrangeElimAuton::setPathFollowingVelocity(double velocity)
{
	if (m_control_system)
		m_control_system->sendCommand("PATH FOLLOWING", "SET VELOCITY", velocity);
}

bool OrangeElimAuton::pathFollowingTargetReached()
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


void OrangeElimAuton::setDriveVelocity(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", left, right);
}

void OrangeElimAuton::setDriveVoltage(double left, double right)
{
	if (m_robot)
		m_robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", left, right);
}

robot::subsystems::drive::Velocity OrangeElimAuton::getDriveVelocity()
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

double OrangeElimAuton::getDriveRadius()
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

void OrangeElimAuton::setElevatorPosition(double position, uint32_t timeout)
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

void OrangeElimAuton::calibrateElevator()
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "CALIBRATE");
}

double OrangeElimAuton::getElevatorPosition()
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

bool OrangeElimAuton::elevatorIsCalibrating()
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

double OrangeElimAuton::getCapDistance()
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

void OrangeElimAuton::closeClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "CLOSE CLAW");
}

void OrangeElimAuton::openClaw()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "OPEN CLAW");
}

void OrangeElimAuton::raiseArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "RAISE ARM");
}

void OrangeElimAuton::lowerArm()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "LOWER ARM");
}

void OrangeElimAuton::engageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "ENGAGE WINCH");
}

void OrangeElimAuton::disengageWinch()
{
	if (m_robot)
		m_robot->sendCommand("HANG", "DISENGAGE WINCH");
}

bool OrangeElimAuton::clawClosed()
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

bool OrangeElimAuton::clawOpen()
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

bool OrangeElimAuton::armRaised()
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

bool OrangeElimAuton::armLowered()
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

bool OrangeElimAuton::winchEngaged()
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

bool OrangeElimAuton::winchDisengaged()
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

void OrangeElimAuton::setIntakeVelocity(double velocity)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VELOCITY", velocity);
}

void OrangeElimAuton::setIntakeVoltage(double voltage)
{
	if (m_robot)
		m_robot->sendCommand("INTAKE", "SET VOLTAGE", voltage);
}

double OrangeElimAuton::getIntakeVelocity()
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

double OrangeElimAuton::getBallDistance()
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

std::vector<io::VisionObject> OrangeElimAuton::getBallVisionObjects()
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

void OrangeElimAuton::loadLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO LOAD");
}

void OrangeElimAuton::readyLoader()
{
	if (m_robot)
		m_robot->sendCommand("LOADER", "DO READY");
}

bool OrangeElimAuton::isLoaderLoaded()
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

bool OrangeElimAuton::isLoaderReady()
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

void OrangeElimAuton::setOdometryPosition(double x, double y, double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET POSITION", x, y, theta);
}

void OrangeElimAuton::setOdometryX(double x)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET X", x);
}

void OrangeElimAuton::setOdometryY(double y)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET Y", y);
}

void OrangeElimAuton::setOdometryTheta(double theta)
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "SET THETA", theta);
}

void OrangeElimAuton::resetOdometryX()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET X");
}

void OrangeElimAuton::resetOdometryY()
{
	if (m_robot)
		m_robot->sendCommand("POSITION TRACKER", "RESET Y");
}

robot::subsystems::position::Position OrangeElimAuton::getOdometryPosition()
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

double OrangeElimAuton::getOdometryVelocity()
{
	auto position{getOdometryPosition()};
	double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
	return velocity;
}

double OrangeElimAuton::getOdometryResetterRawValue()
{
	double raw_value{};
	if (m_robot)
	{
		double* result{static_cast<double*>(m_robot->getState("POSITION TRACKER", "GET RAW RESETTER VALUE"))};
		if (result)
		{
			raw_value = *result;
			delete result;
		}
	}
	return raw_value;
}

void OrangeElimAuton::setUmbrellaIn()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET IN");
}

void OrangeElimAuton::setUmbrellaOut()
{
	if (m_robot)
		m_robot->sendCommand("UMBRELLA", "SET OUT");
}

bool OrangeElimAuton::isUmbrellaIn()
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

bool OrangeElimAuton::isUmbrellaOut()
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

void OrangeElimAuton::setLeftWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET LEFT WING", static_cast<int>(out));
}

void OrangeElimAuton::setRightWing(bool out)
{
	if (m_robot)
		m_robot->sendCommand("WINGS", "SET RIGHT WING", static_cast<int>(out));
}

bool OrangeElimAuton::isLeftWingOut()
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

bool OrangeElimAuton::isRightWingOut()
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

std::string OrangeElimAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void OrangeElimAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{
	m_control_system = control_system;
	m_robot = robot;

	std::vector<control::path::Point> rush_path_control_points
	{
		control::path::Point{60.0, 12.0},
		control::path::Point{78.0, 12.0},
		control::path::Point{88.0, 12.0},
		control::path::Point{100.0, 12.0},
		control::path::Point{115.0, 18.0},
		control::path::Point{113.0, 25.0},
		control::path::Point{104.0, 32.0},
		control::path::Point{92.0, 52.0},
		control::path::Point{90.0, 57.0},
		control::path::Point{75.0, 72.0},
	};
	rush_path = control::path::QuinticBezierSpline::calculate(rush_path_control_points);

	far_load_path.push_back(control::path::Point{132.0, 48.0});

	std::vector<control::path::Point> winpoint_path_control_points
	{
		control::path::Point{130.0, 36.0},
		control::path::Point{120.0, 24.0},
		control::path::Point{114.0, 18.0},
		control::path::Point{96.0, 11.0},
		control::path::Point{76.0, 11.0},
		control::path::Point{68.0, 11.0},
		control::path::Point{48.0, 11.0},
	};
	winpoint_path = control::path::QuinticBezierSpline::calculate(winpoint_path_control_points);
}

void OrangeElimAuton::run(std::shared_ptr<IAlliance> alliance,
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
	double start_x{60.0}, start_y{12.0}, start_theta{0};
	setOdometryPosition(start_x, start_y, start_theta);

	// Grab some basic variables for general use
	auto position{getOdometryPosition()};
	double velocity{getOdometryVelocity()};
	uint32_t start_time{getTime()};
	double target_distance{};
	double target_angle{};

	// Reset the Y to be more precise
	resetOdometryY();

	// Start the rush path
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(3.25);
	followPath(rush_path, 48.0);
	while (position.x < 94.0)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
	}

	// Slow down to take the corner
	setPathFollowingVelocity(24.0);
	position = getOdometryPosition();
	while (position.theta < 5 * M_PI / 180)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
	}

	// Outtake the alley ball
	setIntakeVoltage(-MAX_VOLTAGE);
	setElevatorPosition(0, 500);
	position = getOdometryPosition();
	while (position.x > 104.0)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
	}
	
	// Move towards the rush ball
	double rush_ball_x{75.0}, rush_ball_y{72.0};
	setPathFollowingVelocity(42.0);
	setIntakeVoltage(MAX_VOLTAGE);
	setElevatorPosition(3.25);
	position = getOdometryPosition();
	target_distance = distance(position.x, position.y, rush_ball_x, rush_ball_y);
	while (target_distance > 16.0)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
		target_distance = distance(position.x, position.y, rush_ball_x, rush_ball_y);
	}

	// Switch to drive straight to grab the ball
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, rush_ball_x, rush_ball_y);
	target_distance = distance(position.x, position.y, rush_ball_x, rush_ball_y);
	//driveStraight(target_distance - 10.0, 42.0, target_angle, uint32_t{1000});
	goToPoint(rush_ball_x, rush_ball_y, 48.0, 1000, 11.0);

	// Turn to face backwards into the goal
	turnToPoint(120.0, 67.0, TURN_VELOCITY, true, 1000);

	// Push back into the goal
	setLeftWing(true);
	setRightWing(true);
	//driveStraightToPoint(120.0, 67.0, 48.0, 1000);
	goToPoint(120.0, 67.0, 48.0, 1000);

	// Move forward slightly
	driveStraight(4.0, 36.0, -175 * M_PI / 180, uint32_t{500});

	// Turn around
	start_time = getTime();
	turnToAngle(0, TURN_VELOCITY, false, 1500, 5.0 * M_PI / 180, control::motion::ETurnDirection::CLOCKWISE);

	// Let go of the ball
	setIntakeVoltage(-MAX_VOLTAGE);
	setElevatorPosition(0);
	while (getElevatorPosition() > 1.0)
		delay(LOOP_DELAY);

	// Ram the ball into the goal
	driveStraight(9.0, 48.0, uint32_t{700});

	// Back up off the goal
	driveStraight(-24.0, 36.0, 1000, 2.0);

	// Turn to face the goal point
	setLeftWing(false);
	setRightWing(false);
	double far_load_x{124.0}, far_load_y{20.0};
	turnToPoint(far_load_x, far_load_y, TURN_VELOCITY, false, 1000);

	// Drive straight to the point for faster stopping
	//driveStraightToPoint(far_load_x, far_load_y, 36.0, 2000);
	goToPoint(far_load_x, far_load_y, 36.0, 2000);

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

	// Turn to face the goal
	turnToAngle(50.0 * M_PI / 180, TURN_VELOCITY, false, 500);

	// Shove into the goal
	setElevatorPosition(0);
	setIntakeVoltage(-MAX_VOLTAGE);
	followPath(far_load_path, 36.0);
	delay(500);
	position = getOdometryPosition();
	while (position.yV > 12.0)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
	}
	delay(500);
	pauseControlSystem();

	// Back up off the goal
	setIntakeVoltage(0);
	driveStraightToPoint(getOdometryPosition().x, 36.0, 36.0, uint32_t{500});

	// Turn to face the bar
	double bar_x{86.0}, bar_y{38.0};
	turnToPoint(bar_x, bar_y, TURN_VELOCITY, false, 1500, 3.0 * M_PI / 180);

	// Drive up to the bar
	driveStraightToPoint(bar_x, bar_y, 48.0, 2000, 4.0);

	// Drive over the bar
	driveStraight(48.0, 72.0, M_PI, uint32_t{4000}, 3.0);

	// Reset x
	turnToAngle(-75 * M_PI / 180, TURN_VELOCITY, false, 1500);
	resetOdometryX();

	// Reset y
	turnToAngle(0, TURN_VELOCITY, false, uint32_t{1500});
	while (getOdometryResetterRawValue() < 24.0)
		delay(LOOP_DELAY);
	resetOdometryY();

	// Move to the front of the match load
	double near_load_x{23.0}, near_load_y{23.0};
	turnToPoint(near_load_x, near_load_y, TURN_VELOCITY, false, 1000, 3.0 * M_PI / 180);
	driveStraightToPoint(near_load_x, near_load_y, 36.0, 1500);

	// Turn to face the match loads
	turnToPoint(0, 0, TURN_VELOCITY, false, 1000);

	// Run a match load to clear the zone
	loadLoader();
	while (!isLoaderLoaded())
		delay(LOOP_DELAY);
	readyLoader();

	// Move into match loading position
	double match_load_drive_distance{12.0}, match_load_drive_velocity{12.0};
	uint32_t match_load_drive_timeout{2000};
	driveStraight(match_load_drive_distance, match_load_drive_velocity, -3 * M_PI / 4, match_load_drive_timeout);
	delay(500);

	// Do match loads
	uint8_t match_loads{6};
	uint32_t match_load_delay{300};
	uint32_t match_load_timeout{800};
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
			setLeftWing(false);
			setRightWing(false);
			double alley_backup_distance{-6.0};
			uint32_t alley_backup_timeout{1000};
			driveStraight(alley_backup_distance, MOTION_VELOCITY, alley_backup_timeout);

			// Turn down the alley
			turnToAngle(alley_theta, TURN_VELOCITY, false, alley_turn_timeout);

			// Resume the alley push
			setLeftWing(true);
			setRightWing(true);
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

	// Follow the path for winpoint
	followPath(winpoint_path, 36.0);
	delay(800);
	setLeftWing(false);
	setRightWing(false);
	position = getOdometryPosition();
	while (position.x > 68.0)
	{
		delay(LOOP_DELAY);
		position = getOdometryPosition();
	}
	// Turn to the start of win point
	/*
	setRightWing(false);
	double winpoint_start_x{102.0}, winpoint_start_y{10.0};
	double winpoint_start_turn_tolerance{2 * M_PI / 180};
	uint32_t winpoint_start_turn_timeout{1000};
	turnToPoint(winpoint_start_x, winpoint_start_y, TURN_VELOCITY, false, winpoint_start_turn_timeout, winpoint_start_turn_tolerance);

	// Move to the start of win point
	double winpoint_start_tolerance{2.0};
	uint32_t winpoint_start_timeout{2000};
	driveStraightToPoint(winpoint_start_x, winpoint_start_y, MOTION_VELOCITY, winpoint_start_timeout, winpoint_start_tolerance);

	// Turn to the winpoint position
	double winpoint_x{60.0}, winpoint_y{10.0};
	double winpoint_turn_tolerance{2.0 * M_PI / 180}, winpoint_tolerance{2.0};
	uint32_t winpoint_turn_timeout{1000}, winpoint_timeout{2000};
	turnToPoint(winpoint_x, winpoint_y, TURN_VELOCITY, true, winpoint_turn_timeout, winpoint_turn_tolerance);

	// Move to the winpoint position
	driveStraightToPoint(winpoint_x, winpoint_y, MOTION_VELOCITY, winpoint_timeout, winpoint_tolerance);	
	*/

	// Touch the bar for win point (remove for elims)
	turnToPoint(72.0, 24.0, TURN_VELOCITY);
	delay(200);
	setElevatorPosition(16.0, 1500);
	setElevatorPosition(getElevatorPosition());

	pros::screen::print(pros::E_TEXT_LARGE_CENTER, 7, "End Time: %5.2f", (getTime() - auton_start_time) / 1000.0);
}
}
}