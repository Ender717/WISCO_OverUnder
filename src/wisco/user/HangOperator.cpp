#include "wisco/user/HangOperator.hpp"

namespace wisco
{
namespace user
{
HangOperator::HangOperator(const std::shared_ptr<user::IController>& controller, 
                           const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller}, m_robot{robot}
{

}

void HangOperator::closeClaw()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, CLOSE_CLAW_COMMAND_NAME);
}

void HangOperator::openClaw()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, OPEN_CLAW_COMMAND_NAME);
}

void HangOperator::lowerArm()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, LOWER_ARM_COMMAND_NAME);
}

void HangOperator::raiseArm()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, RAISE_ARM_COMMAND_NAME);
}

void HangOperator::engageWinch()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, ENGAGE_WINCH_COMMAND_NAME);
}

void HangOperator::disengageWinch()
{
    m_robot->sendCommand(HANG_SUBSYSTEM_NAME, DISENGAGE_WINCH_COMMAND_NAME);
}

void HangOperator::setInactiveState()
{
    toggle_state = EToggleState::INACTIVE;
    openClaw();
    lowerArm();
    disengageWinch();
}

void HangOperator::setRaisedState()
{
    toggle_state = EToggleState::RAISED;
    openClaw();
    raiseArm();
    disengageWinch();
}

void HangOperator::setGrabbedState()
{
    toggle_state = EToggleState::GRABBED;
    closeClaw();
    raiseArm();
    disengageWinch();
}

void HangOperator::setHungState()
{
    toggle_state = EToggleState::HUNG;
    closeClaw();
    lowerArm();
    engageWinch();
}

void HangOperator::updatePresetSplit(EControllerDigital inactive, EControllerDigital raise, EControllerDigital grab, EControllerDigital hang)
{
    bool set_inactive{m_controller->getNewDigital(inactive)};
    bool set_raise{m_controller->getNewDigital(raise)};
    bool set_grab{m_controller->getNewDigital(grab)};
    bool set_hang{m_controller->getNewDigital(hang)};

    if (set_inactive && !set_raise && !set_grab && !set_hang)
        setInactiveState();
    else if (!set_inactive && set_raise && !set_grab && !set_hang)
        setRaisedState();
    else if (!set_inactive && !set_raise && set_grab && !set_hang)
        setGrabbedState();
    else if (!set_inactive && !set_raise && !set_grab && set_hang)
        setHungState();
}

void HangOperator::updatePresetToggle(EControllerDigital toggle)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};

    if (set_toggle)
    {
        switch (toggle_state)
        {
        case EToggleState::INACTIVE:
            setRaisedState();
            break;
        case EToggleState::RAISED:
            setGrabbedState();
            break;
        case EToggleState::GRABBED:
            setHungState();
            break;
        case EToggleState::HUNG:
            setInactiveState();
            break;
        }
    }
}

void HangOperator::updatePresetLadder(EControllerDigital next, EControllerDigital previous)
{
    bool set_next{m_controller->getNewDigital(next)};
    bool set_previous{m_controller->getNewDigital(previous)};

    if (set_next && !set_previous)
    {
        switch (toggle_state)
        {
        case EToggleState::INACTIVE:
            setRaisedState();
            break;
        case EToggleState::RAISED:
            setGrabbedState();
            break;
        case EToggleState::GRABBED:
            setHungState();
            break;
        case EToggleState::HUNG:
            break;
        }
    }
    else if (!set_next && set_previous)
    {
        switch (toggle_state)
        {
        case EToggleState::INACTIVE:
            break;
        case EToggleState::RAISED:
            setInactiveState(); 
            break;
        case EToggleState::GRABBED:
            setRaisedState();
            break;
        case EToggleState::HUNG:
            setGrabbedState();
            break;
        }
    }
}

void HangOperator::updatePresetReset(EControllerDigital toggle, EControllerDigital reset)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};
    bool set_reset{m_controller->getNewDigital(reset)};

    if (set_toggle && !set_reset)
    {
        switch (toggle_state)
        {
        case EToggleState::INACTIVE:
            setRaisedState();
            break;
        case EToggleState::RAISED:
            setGrabbedState();
            break;
        case EToggleState::GRABBED:
            setHungState();
            break;
        case EToggleState::HUNG:
            setInactiveState();
            break;
        }
    }
    else if (!set_toggle && set_reset)
    {
        setInactiveState();
    }
}

void HangOperator::setHangState(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital grab{profile->getDigitalControlMapping(EControl::HANG_GRAB)};
    EControllerDigital hang{profile->getDigitalControlMapping(EControl::HANG_HANG)};
    EControllerDigital inactive{profile->getDigitalControlMapping(EControl::HANG_INACTIVE)};
    EControllerDigital next{profile->getDigitalControlMapping(EControl::HANG_NEXT)};
    EControllerDigital previous{profile->getDigitalControlMapping(EControl::HANG_PREVIOUS)};
    EControllerDigital raise{profile->getDigitalControlMapping(EControl::HANG_RAISE)};
    EControllerDigital reset{profile->getDigitalControlMapping(EControl::HANG_RESET)};
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::HANG_TOGGLE)};

    switch (static_cast<EHangControlMode>(profile->getControlMode(EControlType::HANG)))
    {
        case EHangControlMode::PRESET_SPLIT:
            updatePresetSplit(inactive, raise, grab, hang);
            break;
        case EHangControlMode::PRESET_TOGGLE_LADDER:
            updatePresetLadder(next, previous);
            break;
        case EHangControlMode::PRESET_TOGGLE_RESET:
            updatePresetReset(toggle, reset);
            break;
        case EHangControlMode::PRESET_TOGGLE_SINGLE:
            updatePresetToggle(toggle);
            break;
    }
}
} // namespace user
} // namespace wisco