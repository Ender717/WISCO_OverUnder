#include "wisco/robot/subsystems/intake/IntakeSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace intake
{
IntakeSubsystem::IntakeSubsystem(std::unique_ptr<IIntake>& intake) : m_intake{std::move(intake)}
{

}

void IntakeSubsystem::initialize()
{
    if (m_intake)
        m_intake->initialize();
}

void IntakeSubsystem::run()
{
    if (m_intake)
        m_intake->run();
}

void IntakeSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_VELOCITY_COMMAND_NAME)
    {
        double velocity{va_arg(args, double)};
        m_intake->setVelocity(velocity);
    }
    else if (command_name == SET_VOLTAGE_COMMAND_NAME)
    {
        double voltage{va_arg(args, double)};
        m_intake->setVoltage(voltage);
    }
}

void* IntakeSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == GET_VELOCITY_STATE_NAME)
    {
        double* velocity{new double{m_intake->getVelocity()}};
        result = velocity;
    }

    return result;
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco