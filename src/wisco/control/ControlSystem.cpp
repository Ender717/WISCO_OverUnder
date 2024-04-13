#include "wisco/control/ControlSystem.hpp"

namespace wisco
{
namespace control
{
void ControlSystem::addControl(std::unique_ptr<AControl>& control)
{
	controls.push_back(std::move(control));
}

bool ControlSystem::removeControl(std::string control_name)
{
	bool removed{false};
	for (auto it{controls.begin()}; it != controls.end(); ++it)
	{
		if ((*it)->getName() == control_name)
		{
			controls.erase(it);
			removed = true;
			break;
		}
	}
	return removed;
}

void ControlSystem::initialize()
{
	for (auto& control : controls)
		control->initialize();
	for (auto& control : controls)
		control->run();
}

void ControlSystem::sendCommand(std::string control_name, std::string command_name, ...)
{
	va_list args;
	va_start(args, command_name);
	for (auto& control : controls)
	{
		if (control->getName() == control_name)
		{
			control->command(command_name, args);
			break;
		}
	}
	va_end(args);
}

void* ControlSystem::getState(std::string control_name, std::string state_name)
{
	void* state{nullptr};
	for (auto& control : controls)
	{
		if (control->getName() == control_name)
		{
			state = control->state(state_name);
			break;
		}
	}
	return state;
}
} // namespace controlsystem
} // namespace wisco