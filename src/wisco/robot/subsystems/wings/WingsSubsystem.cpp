#include "wisco/robot/subsystems/wings/WingsSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace wings
{
WingsSubsystem::WingsSubsystem(std::unique_ptr<IWings>& wings)
    : m_wings{std::move(wings)}
{

}

void WingsSubsystem::initialize()
{
    if (m_wings)
        m_wings->initialize();
}

void WingsSubsystem::run()
{
    if (m_wings)
        m_wings->run();
}

void WingsSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_LEFT_WING_COMMAND_NAME)
    {
        bool out{va_arg(args, bool)};
        m_wings->setLeftWing(out);
    }
    else if (command_name == SET_RIGHT_WING_COMMAND_NAME)
    {
        bool out{va_arg(args, bool)};
        m_wings->setRightWing(out);
    }
}

void* WingsSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == GET_LEFT_WING_STATE_NAME)
    {
        bool* out{new bool{m_wings->getLeftWing()}};
        result = out;
    }
    else if (state_name == GET_RIGHT_WING_STATE_NAME)
    {
        bool* out{new bool{m_wings->getRightWing()}};
        result = out;
    }

    return result;
}
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco