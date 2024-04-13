#include "wisco/autons/BlueMatchAuton.hpp"

namespace wisco
{
namespace autons
{
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
    
}
}
}