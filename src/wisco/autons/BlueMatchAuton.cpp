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

std::string BlueMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{

}

void BlueMatchAuton::run(std::shared_ptr<control::ControlSystem> control_system, 
					     std::shared_ptr<robot::Robot> robot)
{
    boomerangGoToPoint(control_system, robot, 48.0, 24.0, 0.0, 0.0);
}
}
}