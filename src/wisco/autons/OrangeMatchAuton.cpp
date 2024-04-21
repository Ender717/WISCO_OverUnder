#include "wisco/autons/OrangeMatchAuton.hpp"

namespace wisco
{
namespace autons
{
std::string OrangeMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void OrangeMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					              std::shared_ptr<robot::Robot> robot)
{

}

void OrangeMatchAuton::run(std::shared_ptr<IAlliance> alliance,
						   std::shared_ptr<rtos::IClock> clock,
						   std::unique_ptr<rtos::IDelayer>& delayer,
						   std::shared_ptr<control::ControlSystem> control_system, 
					       std::shared_ptr<robot::Robot> robot)
{
    
}
}
}