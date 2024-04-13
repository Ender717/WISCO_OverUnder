#include "wisco/user/umbrella/UmbrellaOperator.hpp"

namespace wisco
{
namespace user
{
namespace umbrella
{
UmbrellaOperator::UmbrellaOperator(const std::shared_ptr<user::IController>& controller, 
                                   const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller},
      m_robot{robot}
{

}

void UmbrellaOperator::setIn()
{
    toggle_state = EToggleState::IN;
    m_robot->sendCommand(UMBRELLA_SUBSYSTEM_NAME, SET_IN_COMMAND);
}

void UmbrellaOperator::setOut()
{
    toggle_state = EToggleState::OUT;
    m_robot->sendCommand(UMBRELLA_SUBSYSTEM_NAME, SET_OUT_COMMAND);
}

void UmbrellaOperator::updateHold(EControllerDigital hold)
{
    bool set_hold{m_controller->getDigital(hold)};

    if (set_hold)
        setOut();
    else
        setIn();
}

void UmbrellaOperator::updateSplit(EControllerDigital in, EControllerDigital out)
{
    bool set_in{m_controller->getNewDigital(in)};
    bool set_out{m_controller->getNewDigital(out)};

    if (set_in && !set_out)
        setIn();
    else if (!set_in && set_out)
        setOut();
}

void UmbrellaOperator::updateToggle(EControllerDigital toggle)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};

    if (set_toggle)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            setOut();
            break;
        case EToggleState::OUT:
            setIn();
            break;
        }
    }
}

void UmbrellaOperator::setUmbrellaPosition(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital hold{profile->getDigitalControlMapping(EControl::UMBRELLA_HOLD)};
    EControllerDigital in{profile->getDigitalControlMapping(EControl::UMBRELLA_IN)};
    EControllerDigital out{profile->getDigitalControlMapping(EControl::UMBRELLA_OUT)};
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::UMBRELLA_TOGGLE)};

    switch (static_cast<EUmbrellaControlMode>(profile->getControlMode(EControlType::UMBRELLA)))
    {
    case EUmbrellaControlMode::HOLD:
        updateHold(hold);
        break;
    case EUmbrellaControlMode::SINGLE_TOGGLE:
        updateToggle(toggle);
        break;
    case EUmbrellaControlMode::SPLIT_TOGGLE:
        updateSplit(in, out);
        break;
    }
}
}
}
}