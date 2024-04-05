#include "wisco/user/ElevatorOperator.hpp"

namespace wisco
{
namespace user
{
ElevatorOperator::ElevatorOperator(const std::shared_ptr<user::IController>& controller, 
                                   const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller}, m_robot{robot}
{

}

void ElevatorOperator::updateElevatorPosition(double position)
{

}

void ElevatorOperator::updateManual(EControllerDigital in, EControllerDigital out)
{

}

void ElevatorOperator::updatePresetSplit(EControllerDigital in, EControllerDigital field, EControllerDigital match_load, EControllerDigital out)
{

}

void ElevatorOperator::updatePresetToggle(EControllerDigital toggle)
{

}

void ElevatorOperator::updatePresetLadder(EControllerDigital in, EControllerDigital out)
{

}

void ElevatorOperator::setElevatorPosition(const std::unique_ptr<IProfile>& profile)
{
    
}
} // namespace user
} // namespace wisco