#include "wisco/autons/BlueSkillsAuton.hpp"

namespace wisco
{
namespace autons
{
std::string BlueSkillsAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueSkillsAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					             std::shared_ptr<robot::Robot> robot)
{

}

void BlueSkillsAuton::run(std::shared_ptr<IAlliance> alliance,
						  std::shared_ptr<rtos::IClock> clock,
						  std::unique_ptr<rtos::IDelayer>& delayer,
						  std::shared_ptr<control::ControlSystem> control_system, 
					      std::shared_ptr<robot::Robot> robot)
{
    std::unique_ptr<rtos::IMutex> sentry_mutex{std::make_unique<pros_adapters::ProsMutex>()};
	std::unique_ptr<rtos::ITask> sentry_task{std::make_unique<pros_adapters::ProsTask>()};
	static routines::SentryMode sentry_mode{alliance, clock, delayer, sentry_mutex, sentry_task, control_system, robot};
	sentry_mode.run();

	sentry_mode.doSentryMode(-5 * M_PI / 12, control::motion::ETurnDirection::COUNTERCLOCKWISE);
	while (!sentry_mode.isFinished())
		delayer->delay(10);
}
}
}