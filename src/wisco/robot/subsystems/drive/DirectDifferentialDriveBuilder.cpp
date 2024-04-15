#include "wisco/robot/subsystems/drive/DirectDifferentialDriveBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withLeftMotor(std::unique_ptr<io::IMotor>& left_motor)
{
    m_left_motors.addMotor(left_motor);
    return this;
}

DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withRightMotor(std::unique_ptr<io::IMotor>& right_motor)
{
    m_right_motors.addMotor(right_motor);
    return this;
}

DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withVelocityToVoltage(double velocity_to_voltage)
{
    m_velocity_to_voltage = velocity_to_voltage;
    return this;
}

DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withGearRatio(double gear_ratio)
{
    m_gear_ratio = gear_ratio;
    return this;
}

DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withWheelRadius(double wheel_radius)
{
    m_wheel_radius = wheel_radius;
    return this;
}

DirectDifferentialDriveBuilder* DirectDifferentialDriveBuilder::withRadius(double radius)
{
    m_radius = radius;
    return this;
}

std::unique_ptr<IDifferentialDrive> DirectDifferentialDriveBuilder::build()
{
    std::unique_ptr<DirectDifferentialDrive> differential_drive{std::make_unique<DirectDifferentialDrive>()};
    differential_drive->setLeftMotors(m_left_motors);
    differential_drive->setRightMotors(m_right_motors);
    differential_drive->setVelocityToVoltage(m_velocity_to_voltage);
    differential_drive->setRadius(m_radius);
    return differential_drive;
}
}
}
}
}