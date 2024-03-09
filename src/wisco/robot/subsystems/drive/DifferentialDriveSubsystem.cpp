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

void DifferentialDriveSubsystem::command(std::string command_name, ...)
{
    std::va_list args;
    va_start(args, command_name);
    
    if (command_name == SET_VELOCITY_COMMAND_NAME)
    {
        Velocity velocity{va_arg(args, double), va_arg(args, double)};
        m_differential_drive->setVelocity(velocity);
    }

    va_end(args);
}

void* DifferentialDriveSubsystem::state(std::string state_name)
{
    void* result{};

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