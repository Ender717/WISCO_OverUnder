#include "wisco/autons/BlueMatchAuton.hpp"

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

void BlueMatchAuton::goToPoint(double x, double y, double theta, double velocity)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("BOOMERANG", "GO TO POSITION", &m_robot, velocity, x, y, theta);
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

void BlueMatchAuton::driveStraight(double distance, double velocity)
{
	auto position{getOdometryPosition()};
	driveStraight(distance, velocity, position.theta);
}

void BlueMatchAuton::driveStraight(double distance, double velocity, double theta)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("MOTION", "DRIVE STRAIGHT", &m_robot, distance, velocity, theta);
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

void BlueMatchAuton::turnToAngle(double theta, double velocity, bool reversed, 
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("MOTION", "TURN TO ANGLE", &m_robot, velocity, theta, static_cast<int>(reversed), direction);
}

void BlueMatchAuton::turnToPoint(double x, double y, double velocity, bool reversed,
								 control::motion::ETurnDirection direction)
{
	if (m_control_system && m_robot)
		m_control_system->sendCommand("MOTION", "TURN TO POINT", &m_robot, velocity, x, y, static_cast<int>(reversed), direction);
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

void BlueMatchAuton::setElevatorPosition(double position)
{
	if (m_robot)
		m_robot->sendCommand("ELEVATOR", "SET POSITION", position);
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

double BlueMatchAuton::getBallAngle()
{
	double angle{};
	if (m_robot)
	{
		double* result{static_cast<double*>(m_robot->getState("INTAKE", "GET BALL ANGLE"))};
		if (result)
		{
			angle = *result;
			delete result;
		}
	}
	return angle;
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

	setOdometryPosition(0, 0, 0);
	driveStraight(36.0, 48.0);
	while (!driveStraightTargetReached())
		delay(LOOP_DELAY);
	return;

	// Set the starting position
	double start_x{17.0}, start_y{17.0}, start_theta{-3 * M_PI / 4};
	setOdometryPosition(start_x, start_y, start_theta);

	// Do match loads
	uint8_t match_loads{6};
	uint32_t match_load_delay{600};
	for (uint8_t i{}; i < match_loads; ++i)
	{
		loadLoader();
		while (!isLoaderLoaded())
			delay(LOOP_DELAY);
		readyLoader();
		while (!isLoaderReady())
			delay(LOOP_DELAY);
		if (i < match_loads - 1)
			delay(match_load_delay);
	}

	// Turn to the start of the alley
	setUmbrellaOut();
	double alley_start_x{25.0}, alley_start_y{13.0}, alley_start_theta{-M_PI / 6};
	turnToPoint(alley_start_x, alley_start_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Extend both wings
	setLeftWing(true);
	setRightWing(true);

	// Move to the start of the alley
	goToPoint(alley_start_x, alley_start_y, alley_start_theta, MOTION_VELOCITY);
	while (!boomerangTargetReached())
		delay(LOOP_DELAY);

	// Turn to face down the alley
	double alley_x{48.0}, alley_y{10.0};
	turnToPoint(alley_x, alley_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Follow the alley path
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

	// Turn to face the goal shove start point
	double goal_shove_x{130.0}, goal_shove_y{29.0};
	turnToPoint(goal_shove_x, goal_shove_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the goal shove start point
	auto position{getOdometryPosition()};
	double target_angle{angle(position.x, position.y, goal_shove_x, goal_shove_y)};
	goToPoint(goal_shove_x, goal_shove_y, target_angle, MOTION_VELOCITY);
	while (!boomerangTargetReached() && (getOdometryPosition().y < 24.0 || getOdometryVelocity() > 4.0))
		delay(LOOP_DELAY);

	// Turn to face the goal
	double side_goal_x{134.0}, side_goal_y{48.0}, side_goal_collision{32.0};
	turnToPoint(side_goal_x, side_goal_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Ram the goal with passion
	setDriveVoltage(-MAX_VOLTAGE, -MAX_VOLTAGE);
	delay(300);
	while (getOdometryVelocity() > STOP_VELOCITY)
		delay(LOOP_DELAY);
	setDriveVoltage(0, 0);

	// Turn to face the goal shove start point
	turnToPoint(goal_shove_x, goal_shove_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the goal shove start point
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, goal_shove_x, goal_shove_y);
	goToPoint(goal_shove_x, goal_shove_y, target_angle, MOTION_VELOCITY);
	while (!boomerangTargetReached() && (getOdometryPosition().y < 24.0 || getOdometryVelocity() > 4.0))
		delay(LOOP_DELAY);

	// Turn to face the goal
	turnToPoint(side_goal_x, side_goal_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Ram the goal with passion part 2
	setDriveVoltage(-MAX_VOLTAGE, -MAX_VOLTAGE);
	delay(300);
	while (getOdometryVelocity() > STOP_VELOCITY)
		delay(LOOP_DELAY);
	setDriveVoltage(0, 0);

	// Turn to face the match load position
	double alliance_ball_x{132.0}, alliance_ball_y{8.0}, alliance_ball_theta{-M_PI / 4};
	double alliance_ball_distance{17.0};
	double alliance_load_x{alliance_ball_x - (alliance_ball_distance * std::cos(alliance_ball_theta))};
	double alliance_load_y{alliance_ball_y - (alliance_ball_distance * std::sin(alliance_ball_theta))};
	turnToPoint(alliance_load_x, alliance_load_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the match load position
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, alliance_load_x, alliance_load_y);
	goToPoint(alliance_load_x, alliance_load_y, target_angle, MOTION_VELOCITY);
	while (!boomerangTargetReached())
		delay(LOOP_DELAY);
	setUmbrellaIn();

	// Turn to face the alliance triball
	setLeftWing(false);
	setRightWing(false);
	turnToPoint(alliance_ball_x, alliance_ball_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Grab the alliance triball
	double alliance_ball_velocity{12.0}, alliance_ball_elevator{7.0}, grab_distance{14};
	goToPoint(alliance_ball_x, alliance_ball_y, alliance_ball_theta, alliance_ball_velocity);
	setElevatorPosition(alliance_ball_elevator);
	setIntakeVoltage(MAX_VOLTAGE);
	while (distance(getOdometryPosition().x, getOdometryPosition().y, alliance_ball_x, alliance_ball_y) > grab_distance)
		delay(LOOP_DELAY);
	while (std::abs(getElevatorPosition() - alliance_ball_elevator) > ELEVATOR_TOLERANCE)
		delay(LOOP_DELAY);
	delay(500);
	pauseControlSystem();

	// Back away from the alliance triball
	double load_bar_distance{-8.0};
	driveStraight(load_bar_distance, MOTION_VELOCITY);
	while (!boomerangTargetReached())
		delay(LOOP_DELAY);

	// Suck in the alliance ball
	double ball_elevator{3.25};
	setElevatorPosition(ball_elevator);
	while (std::abs(getElevatorPosition() - ball_elevator) > ELEVATOR_TOLERANCE)
		delay(LOOP_DELAY);

	// Turn to face the goal shove start point
	turnToPoint(goal_shove_x, goal_shove_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the goal shove start point
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, goal_shove_x, goal_shove_y);
	goToPoint(goal_shove_x, goal_shove_y, target_angle, MOTION_VELOCITY);
	while (!boomerangTargetReached() && (getOdometryPosition().y < 24.0 || getOdometryVelocity() > 4.0))
		delay(LOOP_DELAY);

	// Turn to face the goal
	double front_side_goal_x{side_goal_x - 4};
	turnToPoint(front_side_goal_x, side_goal_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Let go of the alliance triball
	double triball_release_elevator{0};
	setElevatorPosition(triball_release_elevator);
	setIntakeVoltage(-MAX_VOLTAGE);
	while (std::abs(getElevatorPosition() - triball_release_elevator) > ELEVATOR_TOLERANCE)
		delay(LOOP_DELAY);
	setIntakeVoltage(0);
	
	// Ram the goal with passion part 3
	setDriveVoltage(MAX_VOLTAGE, MAX_VOLTAGE);
	delay(300);
	while (getOdometryVelocity() > STOP_VELOCITY)
		delay(LOOP_DELAY);
	setDriveVoltage(0, 0);	

	// Turn to face the midfield entrance
	double entrance_x{104.0}, entrance_y{14.0};
	turnToPoint(entrance_x, entrance_y, TURN_VELOCITY, true);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the goal shove start point
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, entrance_x, entrance_y);
	goToPoint(entrance_x, entrance_y, target_angle, MOTION_VELOCITY);
	while (!boomerangTargetReached())
		delay(LOOP_DELAY);

	// Turn to face the front of the goal
	double sentry_x{104.0}, sentry_y{60.0};
	turnToPoint(sentry_x, sentry_y, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Move to the front of the goal
	double sweep_velocity{26.0};
	position = getOdometryPosition();
	target_angle = angle(position.x, position.y, sentry_x, sentry_y);
	goToPoint(sentry_x, sentry_y, target_angle, sweep_velocity);
	while (!boomerangTargetReached())
		delay(LOOP_DELAY);

	// Turn to face forward
	turnToAngle(5 * M_PI / 12, TURN_VELOCITY);
	while (!turnTargetReached())
		delay(LOOP_DELAY);

	// Start sentry mode
	std::unique_ptr<rtos::IMutex> sentry_mutex{std::make_unique<pros_adapters::ProsMutex>()};
	std::unique_ptr<rtos::ITask> sentry_task{std::make_unique<pros_adapters::ProsTask>()};
	static routines::SentryMode sentry_mode{alliance, m_clock, m_delayer, sentry_mutex, sentry_task, m_control_system, m_robot};
	sentry_mode.run();

	bool sentry{true};
	position = getOdometryPosition();
	control::path::Point last_ball{};
	double sentry_goal_x{104.0}, sentry_goal_y{60.0};
	while (sentry)
	{
		sentry_mode.doSentryMode(-5 * M_PI / 12, control::motion::ETurnDirection::COUNTERCLOCKWISE);
		while (!sentry_mode.isFinished())
			delay(LOOP_DELAY);
		sentry = sentry_mode.ballFound();
		if (sentry)
		{
			position = getOdometryPosition();
			last_ball = sentry_mode.getBall();
			double target_distance{distance(position.x, position.y, sentry_goal_x, sentry_goal_y)};
			if (target_distance > 3.0)
			{
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
}
}
}