#include "wisco/robot/subsystems/hang/HangSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
HangSubsystem::HangSubsystem(std::unique_ptr<IClaw>& claw, 
                             std::unique_ptr<IToggleArm>& toggle_arm, 
                             std::unique_ptr<IWinch>& winch) 
    : ASubsystem{SUBSYSTEM_NAME}, 
      m_claw{std::move(claw)},
      m_toggle_arm{std::move(toggle_arm)},
      m_winch{std::move(winch)}
{

}

void HangSubsystem::initialize()
{
    if (m_claw)
        m_claw->initialize();
    if (m_toggle_arm)
        m_toggle_arm->initialize();
    if (m_winch)
        m_winch->initialize();
}

void HangSubsystem::run()
{
    if (m_claw)
        m_claw->run();
    if (m_toggle_arm)
        m_toggle_arm->run();
    if (m_winch)
        m_winch->run();
}

void HangSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == CLOSE_CLAW_COMMAND_NAME)
    {
        if (m_claw)
            m_claw->close();
    }
    else if (command_name == OPEN_CLAW_COMMAND_NAME)
    {
        if (m_claw)
            m_claw->open();
    }
    else if (command_name == RAISE_ARM_COMMAND_NAME)
    {
        if (m_toggle_arm)
            m_toggle_arm->setUp();
    }
    else if (command_name == LOWER_ARM_COMMAND_NAME)
    {
        if (m_toggle_arm)
            m_toggle_arm->setDown();
    }
    else if (command_name == ENGAGE_WINCH_COMMAND_NAME)
    {
        if (m_winch)
            m_winch->engage();
    }
    else if (command_name == DISENGAGE_WINCH_COMMAND_NAME)
    {
        if (m_winch)
            m_winch->disengage();
    }
}

void* HangSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == CLAW_CLOSED_STATE_NAME)
    {
        if (m_claw)
        {
            bool* closed{new bool{m_claw->isClosed()}};
            result = closed;
        }
    }
    else if (state_name == CLAW_OPEN_STATE_NAME)
    {
        if (m_claw)
        {
            bool* open{new bool{m_claw->isOpen()}};
            result = open;
        }
    }
    else if (state_name == ARM_DOWN_STATE_NAME)
    {
        if (m_toggle_arm)
        {
            bool* down{new bool{m_toggle_arm->isDown()}};
            result = down;
        }
    }
    else if (state_name == ARM_UP_STATE_NAME)
    {
        if (m_toggle_arm)
        {
            bool* up{new bool{m_toggle_arm->isUp()}};
            result = up;
        }
    }
    else if (state_name == WINCH_ENGAGED_STATE_NAME)
    {
        if (m_winch)
        {
            bool* engaged{new bool{m_winch->isEngaged()}};
            result = engaged;
        }
    }
    else if (state_name == WINCH_DISENGAGED_STATE_NAME)
    {
        if (m_winch)
        {
            bool* disengaged{new bool{m_winch->isDisengaged()}};
            result = disengaged;
        }
    }

    return result;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco