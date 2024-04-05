#include "wisco/robot/subsystems/elevator/ElevatorSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace elevator
{
ElevatorSubsystem::ElevatorSubsystem(std::unique_ptr<IElevator>& elevator) : m_elevator{std::move(elevator)}
{

}

void ElevatorSubsystem::initialize()
{
    if (m_elevator)
        m_elevator->initialize();
}

void ElevatorSubsystem::run()
{
    if (m_elevator)
        m_elevator->run();
}

void ElevatorSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_POSITION_COMMAND_NAME)
    {
        double position{va_arg(args, double)};
        m_elevator->setPosition(position);
    }
}

void* ElevatorSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == GET_POSITION_STATE_NAME)
    {
        double* position{new double{m_elevator->getPosition()}};
        result = position;
    }

    return result;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco