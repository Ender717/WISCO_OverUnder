#include "wisco/user/wings/WingsOperator.hpp"

namespace wisco
{
namespace user
{
namespace wings
{
WingsOperator::WingsOperator(const std::shared_ptr<user::IController>& controller, 
                             const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller},
      m_robot{robot}
{

}

void WingsOperator::setLeftWing(bool out)
{
    m_robot->sendCommand(WINGS_SUBSYSTEM_NAME, SET_LEFT_WING_COMMAND, static_cast<int>(out));
}

void WingsOperator::setRightWing(bool out)
{
    m_robot->sendCommand(WINGS_SUBSYSTEM_NAME, SET_RIGHT_WING_COMMAND, static_cast<int>(out));
}

void WingsOperator::setWings(bool out)
{
    setLeftWing(out);
    setRightWing(out);
}

void WingsOperator::updateDualHold(EControllerDigital hold)
{
    bool set_hold{m_controller->getDigital(hold)};

    if (set_hold)
        setWings(true);
    else
        setWings(false);
}

void WingsOperator::updateDualSplit(EControllerDigital in, EControllerDigital out)
{
    bool set_in{m_controller->getNewDigital(in)};
    bool set_out{m_controller->getNewDigital(out)};

    if (set_in && !set_out)
        setWings(false);
    else if (!set_in && set_out)
        setWings(true);
}

void WingsOperator::updateDualToggle(EControllerDigital toggle)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};

    if (set_toggle)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            toggle_state = EToggleState::OUT;
            setWings(true);
            break;
        case EToggleState::OUT:
            toggle_state = EToggleState::IN;
            setWings(false);
            break;
        }
    }
}

void WingsOperator::updateSingleHold(EControllerDigital left_hold, EControllerDigital right_hold)
{
    bool set_left_hold{m_controller->getDigital(left_hold)};
    bool set_right_hold{m_controller->getDigital(right_hold)};

    if (set_left_hold)
        setLeftWing(true);
    else
        setLeftWing(false);

    if (set_right_hold)
        setRightWing(true);
    else
        setRightWing(false);
}

void WingsOperator::updateSingleSplit(EControllerDigital left_in, EControllerDigital left_out, EControllerDigital right_in, EControllerDigital right_out)
{
    bool set_left_in{m_controller->getDigital(left_in)};
    bool set_left_out{m_controller->getDigital(left_out)};
    bool set_right_in{m_controller->getDigital(right_in)};
    bool set_right_out{m_controller->getDigital(right_out)};

    if (set_left_in && !set_left_out)
        setLeftWing(false);
    else if (!set_left_in && set_left_out)
        setLeftWing(true);

    if (set_right_in && !set_right_out)
        setRightWing(false);
    else if (!set_right_in && set_right_out)
        setRightWing(true);
}

void WingsOperator::updateSingleToggle(EControllerDigital left_toggle, EControllerDigital right_toggle)
{
    bool set_left_toggle{m_controller->getNewDigital(left_toggle)};
    bool set_right_toggle{m_controller->getNewDigital(right_toggle)};

    if (set_left_toggle)
    {
        switch (left_toggle_state)
        {
        case EToggleState::IN:
            left_toggle_state = EToggleState::OUT;
            setLeftWing(true);
            break;
        case EToggleState::OUT:
            left_toggle_state = EToggleState::IN;
            setLeftWing(false);
            break;
        }
    }

    if (set_right_toggle)
    {
        switch (right_toggle_state)
        {
        case EToggleState::IN:
            right_toggle_state = EToggleState::OUT;
            setRightWing(true);
            break;
        case EToggleState::OUT:
            right_toggle_state = EToggleState::IN;
            setRightWing(false);
            break;
        }
    }
}

void WingsOperator::setWingsPosition(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital hold{profile->getDigitalControlMapping(EControl::WINGS_HOLD)};
    EControllerDigital in{profile->getDigitalControlMapping(EControl::WINGS_IN)};
    EControllerDigital out{profile->getDigitalControlMapping(EControl::WINGS_OUT)};
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::WINGS_TOGGLE)};
    EControllerDigital left_hold{profile->getDigitalControlMapping(EControl::WINGS_LEFT_HOLD)};
    EControllerDigital left_in{profile->getDigitalControlMapping(EControl::WINGS_LEFT_IN)};
    EControllerDigital left_out{profile->getDigitalControlMapping(EControl::WINGS_LEFT_OUT)};
    EControllerDigital left_toggle{profile->getDigitalControlMapping(EControl::WINGS_LEFT_TOGGLE)};
    EControllerDigital right_hold{profile->getDigitalControlMapping(EControl::WINGS_RIGHT_HOLD)};
    EControllerDigital right_in{profile->getDigitalControlMapping(EControl::WINGS_RIGHT_IN)};
    EControllerDigital right_out{profile->getDigitalControlMapping(EControl::WINGS_RIGHT_OUT)};
    EControllerDigital right_toggle{profile->getDigitalControlMapping(EControl::WINGS_RIGHT_TOGGLE)};

    switch(static_cast<EWingsControlMode>(profile->getControlMode(EControlType::WINGS)))
    {
        case EWingsControlMode::DUAL_HOLD:
            updateDualHold(hold);
            break;
        case EWingsControlMode::DUAL_SPLIT:
            updateDualSplit(in, out);
            break;
        case EWingsControlMode::DUAL_TOGGLE:
            updateDualToggle(toggle);
            break;
        case EWingsControlMode::SINGLE_HOLD:
            updateSingleHold(left_hold, right_hold);
            break;
        case EWingsControlMode::SINGLE_SPLIT:
            updateSingleSplit(left_in, left_out, right_in, right_out);
            break;
        case EWingsControlMode::SINGLE_TOGGLE:
            updateSingleToggle(left_toggle, right_toggle);
            break;
    }
}
} // namespace wings
} // namespace user
} // namespace wisco