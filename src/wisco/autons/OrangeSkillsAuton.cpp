#include "wisco/autons/OrangeSkillsAuton.hpp"

namespace wisco
{
namespace autons
{
std::string OrangeSkillsAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void OrangeSkillsAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					               std::shared_ptr<robot::Robot> robot)
{

}

void OrangeSkillsAuton::run(std::shared_ptr<IAlliance> alliance,
							std::shared_ptr<rtos::IClock> clock,
						  	std::unique_ptr<rtos::IDelayer>& delayer,
						  	std::shared_ptr<control::ControlSystem> control_system, 
					      	std::shared_ptr<robot::Robot> robot)
{
    
}
}
}