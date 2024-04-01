#include "wisco/user/IntakeOperator.hpp"

namespace wisco
{
namespace user
{
void IntakeOperator::updateIntakeVoltage(double voltage)
{
    m_robot->sendCommand(INTAKE_SUBSYSTEM_NAME, SET_VOLTAGE_COMMAND, voltage);
}

void IntakeOperator::updateToggleVoltage()
{
    switch(toggle_state)
    {
    case EToggleState::OFF:
        updateIntakeVoltage(VOLTAGE_SETTING);
        break;
    case EToggleState::IN:
        updateIntakeVoltage(-VOLTAGE_SETTING);
        break;
    case EToggleState::OUT:
        updateIntakeVoltage(0);
        break;
    }
}

void IntakeOperator::updateSingleToggle(EControllerDigital toggle)
{
    if (m_controller->getNewDigital(toggle))
    {
        switch(toggle_state)
        {
        case EToggleState::OFF:
            toggle_state = EToggleState::IN;
            break;
        case EToggleState::IN:
            toggle_state = EToggleState::OUT;
            break;
        case EToggleState::OUT:
            toggle_state = EToggleState::OFF;
            break;
        }
        updateToggleVoltage();
    }
}

void IntakeOperator::updateSplitHold(EControllerDigital in, EControllerDigital out)
{
    double voltage{(m_controller->getDigital(in) - m_controller->getDigital(out)) * VOLTAGE_SETTING};
    updateIntakeVoltage(voltage);
}

void IntakeOperator::updateSplitToggle(EControllerDigital in, EControllerDigital out)
{
    if (m_controller->getNewDigital(in))
    {
        if (toggle_state == EToggleState::IN)
            toggle_state = EToggleState::OFF;
        else
            toggle_state = EToggleState::IN;
        updateToggleVoltage();
    }
    else if (m_controller->getNewDigital(out))
    {
        if (toggle_state == EToggleState::OUT)
            toggle_state = EToggleState::OFF;
        else
            toggle_state = EToggleState::OUT;
        updateToggleVoltage();
    }
}

IntakeOperator::IntakeOperator(const std::shared_ptr<user::IController>& controller, 
                               const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller}, m_robot{robot}
{
    
}

void IntakeOperator::setIntakeVoltage(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::INTAKE_TOGGLE)};
    EControllerDigital in{profile->getDigitalControlMapping(EControl::INTAKE_IN)};
    EControllerDigital out{profile->getDigitalControlMapping(EControl::INTAKE_OUT)};
    switch(static_cast<EIntakeControlMode>(profile->getControlMode(EControlType::INTAKE)))
    {
    case EIntakeControlMode::SINGLE_TOGGLE:
        updateSingleToggle(toggle);
        break;
    case EIntakeControlMode::SPLIT_HOLD:
        updateSplitHold(in, out);
        break;
    case EIntakeControlMode::SPLIT_TOGGLE:
        updateSplitToggle(in, out);
        break;
    }
}
} // namespace user
} // namespace wisco