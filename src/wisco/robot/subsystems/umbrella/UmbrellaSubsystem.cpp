#include "wisco/robot/subsystems/umbrella/UmbrellaSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace umbrella
{
UmbrellaSubsystem::UmbrellaSubsystem(std::unique_ptr<IUmbrella>& umbrella)
    : ASubsystem{SUBSYSTEM_NAME}, m_umbrella{std::move(umbrella)}
{

}

void UmbrellaSubsystem::initialize()
{
    if (m_umbrella)
        m_umbrella->initialize();
}

void UmbrellaSubsystem::run()
{
    if (m_umbrella)
        m_umbrella->run();
}

void UmbrellaSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_IN_COMMAND_NAME)
    {
        m_umbrella->setIn();
    }
    else if (command_name == SET_OUT_COMMAND_NAME)
    {
        m_umbrella->setOut();
    }
}

void* UmbrellaSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == IS_IN_STATE_NAME)
    {
        bool* loaded{new bool{m_umbrella->isIn()}};
        result = loaded;
    }
    else if (state_name == IS_OUT_STATE_NAME)
    {
        bool* ready{new bool{m_umbrella->isOut()}};
        result = ready;
    }

    return result;
}
} // namespace umbrella
} // namespace subsystems
} // namespace robot
} // namespace wisco