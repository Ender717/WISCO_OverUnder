#include "wisco/robot/subsystems/drive/DifferentialDriveSubsystem.hpp"
#include "Velocity.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
DifferentialDriveSubsystem::DifferentialDriveSubsystem(std::unique_ptr<IDifferentialDrive>& differential_drive)
    : ASubsystem{SUBSYSTEM_NAME}, m_differential_drive{std::move(differential_drive)}
{

}

void DifferentialDriveSubsystem::initialize()
{
    m_differential_drive->initialize();
}

void DifferentialDriveSubsystem::run()
{
    m_differential_drive->run();
}

void DifferentialDriveSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_VELOCITY_COMMAND_NAME)
    {
        Velocity velocity{va_arg(args, double), va_arg(args, double)};
        m_differential_drive->setVelocity(velocity);
    }
}

void* DifferentialDriveSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == GET_VELOCITY_STATE_NAME)
    {
        Velocity* velocity{new Velocity{m_differential_drive->getVelocity()}};
        result = velocity;
    }

    return result;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco