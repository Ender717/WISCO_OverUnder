#include "wisco/robot/subsystems/position/PositionSubsystem.hpp"
#include "pros/screen.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
PositionSubsystem::PositionSubsystem(std::unique_ptr<IPositionTracker>& position_tracker)
    : ASubsystem{SUBSYSTEM_NAME}, m_position_tracker{std::move(position_tracker)}
{

}

void PositionSubsystem::initialize()
{
    m_position_tracker->initialize();
}

void PositionSubsystem::run()
{
    m_position_tracker->run();
}

void PositionSubsystem::command(std::string command_name, ...)
{
    std::va_list args;
    va_start(args, command_name);
    
    if (command_name == SET_POSITION_COMMAND_NAME)
    {
        Position position{va_arg(args, double), va_arg(args, double), va_arg(args, double)};
        m_position_tracker->setPosition(position);
    }

    va_end(args);
}

void* PositionSubsystem::state(std::string state_name)
{
    void* result{};

    if (state_name == GET_POSITION_STATE_NAME)
    {
        Position* position{new Position{m_position_tracker->getPosition()}};
        result = position;
    }

    return result;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco