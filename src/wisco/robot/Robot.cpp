#include "wisco/robot/Robot.hpp"

namespace wisco
{
namespace robot
{
void Robot::addSubsystem(std::unique_ptr<ASubsystem>& subsystem)
{
	subsystems.push_back(std::move(subsystem));
}

bool Robot::removeSubsystem(std::string subsystem_name)
{
	bool removed{false};
	for (auto it{subsystems.begin()}; it != subsystems.end(); ++it)
	{
		if ((*it)->getName() == subsystem_name)
		{
			subsystems.erase(it);
			removed = true;
			break;
		}
	}
	return removed;
}

void Robot::initialize()
{
	for (auto& subsystem : subsystems)
	{
		subsystem->initialize();
	}
}

void Robot::sendCommand(std::string subsystem_name, std::string command_name, ...)
{
	va_list args;
	for (auto& subsystem : subsystems)
	{
		if (subsystem->getName() == subsystem_name)
		{
			subsystem->command(command_name, args);
			break;
		}
	}
}

void* Robot::getState(std::string subsystem_name, std::string state_name)
{
	void* state{nullptr};
	for (auto& subsystem : subsystems)
	{
		if (subsystem->getName() == subsystem_name)
		{
			state = subsystem->state(state_name);
			break;
		}
	}
	return state;
}
} // namespace robot
} // namespace wisco