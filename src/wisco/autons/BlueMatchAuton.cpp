#include "wisco/autons/BlueMatchAuton.hpp"

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

void BlueMatchAuton::boomerangPause(std::shared_ptr<control::ControlSystem> control_system)
{
	if (control_system)
		control_system->sendCommand(BOOMERANG_CONTROL_NAME, BOOMERANG_PAUSE_COMMAND_NAME);
}

void BlueMatchAuton::boomerangResume(std::shared_ptr<control::ControlSystem> control_system)
{
	if (control_system)
		control_system->sendCommand(BOOMERANG_CONTROL_NAME, BOOMERANG_RESUME_COMMAND_NAME);
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
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_ANGLE_COMMAND_NAME, &robot, velocity, theta, reversed, direction);
}

void BlueMatchAuton::motionTurnToPoint(std::shared_ptr<control::ControlSystem> control_system, 
									   std::shared_ptr<robot::Robot> robot, 
									   double velocity, double x, double y, bool reversed,
									   control::motion::ETurnDirection direction)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_POINT_COMMAND_NAME, &robot, velocity, x, y, reversed, direction);
}

void BlueMatchAuton::motionPauseTurn(std::shared_ptr<control::ControlSystem> control_system)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_PAUSE_TURN_COMMAND_NAME);
}

void BlueMatchAuton::motionResumeTurn(std::shared_ptr<control::ControlSystem> control_system)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_RESUME_TURN_COMMAND_NAME);
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

std::string BlueMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{

}

void BlueMatchAuton::run(std::shared_ptr<rtos::IClock> clock,
						  std::unique_ptr<rtos::IDelayer>& delayer,
						  std::shared_ptr<control::ControlSystem> control_system, 
					      std::shared_ptr<robot::Robot> robot)
{
	odometrySetPosition(robot, 0, 0, 0);
    motionTurnToPoint(control_system, robot, 2 * M_PI, 48.0, 48.0, false, control::motion::ETurnDirection::CLOCKWISE);
}
}
}