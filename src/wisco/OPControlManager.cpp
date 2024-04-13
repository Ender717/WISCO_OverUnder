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
    user::drive::DifferentialDriveOperator drive_operator{controller, robot};
    user::elevator::ElevatorOperator elevator_operator{controller, robot};
    user::hang::HangOperator hang_operator{controller, robot};
    user::intake::IntakeOperator intake_operator{controller, robot};
    user::loader::LoaderOperator loader_operator{controller, robot};
    user::wings::WingsOperator wings_operator{controller, robot};
    uint32_t current_time{};
    while (true)
    {
        current_time = m_clock->getTime();
        
        drive_operator.setDriveVoltage(static_cast<user::drive::EChassisControlMode>(m_profile->getControlMode(user::EControlType::DRIVE)));
        elevator_operator.setElevatorPosition(m_profile);
        hang_operator.setHangState(m_profile);
        intake_operator.setIntakeVoltage(m_profile);
        loader_operator.setLoaderPosition(m_profile);
        wings_operator.setWingsPosition(m_profile);

        m_delayer->delayUntil(current_time + CONTROL_DELAY);
    }
}
}