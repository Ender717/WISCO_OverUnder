#include "wisco/autons/BlueMatchAuton.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

namespace wisco
{
namespace autons
{
void BlueMatchAuton::boomerangGoToPoint(std::shared_ptr<control::ControlSystem> control_system, 
						std::shared_ptr<robot::Robot> robot, 
						double velocity, double x, double y, double theta)
{
	if (control_system)
		control_system->sendCommand(BOOMERANG_CONTROL_NAME, BOOMERANG_GO_TO_POSITION_COMMAND_NAME, &robot, velocity, x, y, theta);
}

bool BlueMatchAuton::boomerangTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(BOOMERANG_CONTROL_NAME, BOOMERANG_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

void BlueMatchAuton::odometrySetPosition(std::shared_ptr<robot::Robot> robot,
										 double x, double y, double theta)
{
	if (robot)
	{
		robot::subsystems::position::Position position{x, y, theta};
		robot->sendCommand(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_SET_POSITION_COMMAND_NAME, position);
	}
}

robot::subsystems::position::Position BlueMatchAuton::odometryGetPosition(std::shared_ptr<robot::Robot> robot)
{
	robot::subsystems::position::Position position{};

	if (robot)
	{
		robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(robot->getState(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_GET_POSITION_STATE_NAME))};
		if (result)
		{
			position = *result;
			delete result;
		}
	}

	return position;
}

void BlueMatchAuton::motionTurnToAngle(std::shared_ptr<control::ControlSystem> control_system, 
									   std::shared_ptr<robot::Robot> robot, 
									   double velocity, double theta, bool reversed,
									   control::motion::ETurnDirection direction)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_ANGLE_COMMAND_NAME, &robot, velocity, theta, static_cast<int>(reversed), direction);
}

void BlueMatchAuton::motionTurnToPoint(std::shared_ptr<control::ControlSystem> control_system, 
									   std::shared_ptr<robot::Robot> robot, 
									   double velocity, double x, double y, bool reversed,
									   control::motion::ETurnDirection direction)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_POINT_COMMAND_NAME, &robot, velocity, x, y, static_cast<int>(reversed), direction);
}

bool BlueMatchAuton::motionTurnTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(MOTION_CONTROL_NAME, MOTION_TURN_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

void BlueMatchAuton::pathFollowingFollowPath(std::shared_ptr<control::ControlSystem> control_system, 
											 std::shared_ptr<robot::Robot> robot, 
											 std::vector<control::path::Point> path,
											 double velocity)
{
	if (control_system)
		control_system->sendCommand(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_FOLLOW_PATH_COMMAND_NAME, &robot, &path, velocity);
}

void BlueMatchAuton::pathFollowingSetVelocity(std::shared_ptr<control::ControlSystem> control_system,
											  double velocity)
{
	if (control_system)
		control_system->sendCommand(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_SET_VELOCITY_COMMAND_NAME, velocity);
}

bool BlueMatchAuton::pathFollowingTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

std::string BlueMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{
	std::vector<control::path::Point> test_path_control_points
	{
		control::path::Point{0.0, 0.0},
		control::path::Point{24.0, 0.0},
		control::path::Point{48.0, 0.0},
		control::path::Point{48.0, 24.0},
		control::path::Point{48.0, 48.0},
		control::path::Point{24.0, 48.0},
		control::path::Point{0.0, 48.0}
	};
	test_path = control::path::QuinticBezierSpline::calculate(test_path_control_points);
}

void BlueMatchAuton::run(std::shared_ptr<rtos::IClock> clock,
						  std::unique_ptr<rtos::IDelayer>& delayer,
						  std::shared_ptr<control::ControlSystem> control_system, 
					      std::shared_ptr<robot::Robot> robot)
{
	odometrySetPosition(robot, 0, 0, 0);
    pathFollowingFollowPath(control_system, robot, test_path, 36.0);
	bool paused{false};
	while (!pathFollowingTargetReached(control_system))
	{
		auto position{odometryGetPosition(robot)};
		pros::screen::print(pros::E_TEXT_LARGE_CENTER, 1, "xV: %7.2f", position.xV);
		if (position.y > 42.0 && position.x < 36.0 && std::abs(position.xV) < 8.0 && !paused)
		{
			control_system->pause();
			paused = true;
			robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", robot::subsystems::drive::Velocity{-24, -24});
			delayer->delay(300);
			control_system->resume();
		}
		if (delayer)
			delayer->delay(10);
	}
}
}
}