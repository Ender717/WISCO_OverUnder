#include "wisco/robot/subsystems/drive/DifferentialDriveSubsystem.hpp"

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
        double left_velocity{va_arg(args, double)};
        double right_velocity{va_arg(args, double)};
        Velocity velocity{left_velocity, right_velocity};
        m_differential_drive->setVelocity(velocity);
    }
    else if (command_name == SET_VOLTAGE_COMMAND_NAME)
    {
        double left_voltage{va_arg(args, double)};
        double right_voltage{va_arg(args, double)};
        m_differential_drive->setVoltage(left_voltage, right_voltage);
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
    else if (state_name == GET_RADIUS_STATE_NAME)
    {
        double* radius{new double{m_differential_drive->getRadius()}};
        result = radius;
    }

    return result;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco