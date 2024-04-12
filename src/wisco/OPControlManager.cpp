#include "wisco/OPControlManager.hpp"

namespace wisco
{
OPControlManager::OPControlManager(const std::shared_ptr<rtos::IClock>& clock, const std::unique_ptr<rtos::IDelayer>& delayer) 
    : m_clock{clock}, m_delayer{delayer->clone()}
{

}

void OPControlManager::setProfile(std::unique_ptr<IProfile>& profile)
{
    m_profile = std::move(profile);
}

void OPControlManager::initializeOpcontrol(std::shared_ptr<user::IController> controller, std::shared_ptr<robot::Robot> robot)
{

}

void OPControlManager::runOpcontrol(std::shared_ptr<user::IController> controller, std::shared_ptr<robot::Robot> robot)
{
    user::DifferentialDriveOperator drive_operator{controller, robot};
    user::ElevatorOperator elevator_operator{controller, robot};
    user::HangOperator hang_operator{controller, robot};
    user::IntakeOperator intake_operator{controller, robot};
    uint32_t current_time{};
    while (true)
    {
        current_time = m_clock->getTime();
        
        drive_operator.setDriveVoltage(static_cast<user::EChassisControlMode>(m_profile->getControlMode(user::EControlType::DRIVE)));
        elevator_operator.setElevatorPosition(m_profile);
        hang_operator.setHangState(m_profile);
        intake_operator.setIntakeVoltage(m_profile);

        m_delayer->delayUntil(current_time + CONTROL_DELAY);
    }
}
}