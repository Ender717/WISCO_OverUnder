#include "wisco/robot/subsystems/hang/HangSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
HangSubsystem::HangSubsystem(std::unique_ptr<IClaw>& claw, std::unique_ptr<IToggleArm>& toggle_arm, std::unique_ptr<io::IDistanceSensor>& distance_sensor) 
    : ASubsystem{SUBSYSTEM_NAME}, 
      m_claw{std::move(claw)},
      m_toggle_arm{std::move(toggle_arm)},
      m_distance_sensor{std::move(distance_sensor)}
{

}

void HangSubsystem::initialize()
{
    if (m_claw)
        m_claw->initialize();
    if (m_toggle_arm)
        m_toggle_arm->initialize();
    if (m_distance_sensor)
        m_distance_sensor->initialize();
}

void HangSubsystem::run()
{
    if (m_claw)
        m_claw->run();
    if (m_toggle_arm)
        m_toggle_arm->run();
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
    else if (state_name == CAP_DISTANCE_STATE_NAME)
    {
        if (m_distance_sensor)
        {
            double* distance{new double{m_distance_sensor->getDistance()}};
            result = distance;
        }
    }

    return result;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco