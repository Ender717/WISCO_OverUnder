#include "wisco/user/loader/LoaderOperator.hpp"

namespace wisco
{
namespace user
{
namespace loader
{
LoaderOperator::LoaderOperator(const std::shared_ptr<user::IController>& controller, 
                const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller}, 
      m_robot{robot}
{

}

void LoaderOperator::doLoad()
{
    m_robot->sendCommand(SUBSYSTEM_NAME, DO_LOAD_COMMAND_NAME);
}

void LoaderOperator::doReady()
{
    m_robot->sendCommand(SUBSYSTEM_NAME, DO_READY_COMMAND_NAME);
}

bool LoaderOperator::isLoaded()
{
    bool loaded{};
    if (m_robot)
    {
        bool* result{static_cast<bool*>(m_robot->getState(SUBSYSTEM_NAME, IS_LOADED_STATE_NAME))};
        if (result)
        {
            loaded = *result;
            delete result;
        }
    }
    return loaded;
}

bool LoaderOperator::isReady()
{
    bool ready{};
    if (m_robot)
    {
        bool* result{static_cast<bool*>(m_robot->getState(SUBSYSTEM_NAME, IS_READY_STATE_NAME))};
        if (result)
        {
            ready = *result;
            delete result;
        }
    }
    return ready;
}

void LoaderOperator::updateHold(EControllerDigital hold)
{
    bool set_hold{m_controller->getDigital(hold)};

    if (set_hold)
        doLoad();
    else
        doReady();
}

void LoaderOperator::updateMacro(EControllerDigital toggle)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};

    if (set_toggle && isReady())
        doLoad();
    else if (isLoaded())
        doReady();
}

void LoaderOperator::updateSingleToggle(EControllerDigital toggle)
{
    bool set_toggle{m_controller->getNewDigital(toggle)};

    if (set_toggle)
    {
        switch (toggle_state)
        {
        case EToggleState::LOAD:
            toggle_state = EToggleState::READY;
            doReady();
            break;
        case EToggleState::READY:
            toggle_state = EToggleState::LOAD;
            doLoad();
            break;
        }
    }
}

void LoaderOperator::updateSplitToggle(EControllerDigital load, EControllerDigital ready)
{
    bool set_load{m_controller->getNewDigital(load)};
    bool set_ready{m_controller->getNewDigital(ready)};

    if (set_load && !set_ready)
    {
        toggle_state = EToggleState::LOAD;
        doLoad();
    }
    else if (!set_load && set_ready)
    {
        toggle_state = EToggleState::READY;
        doReady();
    }
}

void LoaderOperator::setLoaderPosition(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital hold{profile->getDigitalControlMapping(EControl::LOADER_HOLD)};
    EControllerDigital load{profile->getDigitalControlMapping(EControl::LOADER_LOAD)};
    EControllerDigital ready{profile->getDigitalControlMapping(EControl::LOADER_READY)};
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::LOADER_TOGGLE)};

    switch (static_cast<ELoaderControlMode>(profile->getControlMode(EControlType::LOADER)))
    {
    case ELoaderControlMode::HOLD:
        updateHold(hold);
        break;
    case ELoaderControlMode::MACRO:
        updateMacro(toggle);
        break;
    case ELoaderControlMode::SINGLE_TOGGLE:
        updateSingleToggle(toggle);
        break;
    case ELoaderControlMode::SPLIT_TOGGLE:
        updateSplitToggle(load, ready);
        break;
    }
}
} // namespace loader
} // namespace user
} // namespace wisco