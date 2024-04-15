#include "wisco/robot/subsystems/drive/DirectDifferentialDrive.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
void DirectDifferentialDrive::initialize()
{
    m_left_motors.initialize();
    m_right_motors.initialize();
}

void DirectDifferentialDrive::run()
{

}

Velocity DirectDifferentialDrive::getVelocity()
{
    Velocity velocity
    {
        m_left_motors.getAngularVelocity() * m_wheel_radius / m_gear_ratio,
        m_right_motors.getAngularVelocity() * m_wheel_radius / m_gear_ratio
    };
    return velocity;
}

void DirectDifferentialDrive::setVelocity(Velocity velocity)
{
    m_left_motors.setVoltage(velocity.left_velocity * m_velocity_to_voltage);
    m_right_motors.setVoltage(velocity.right_velocity * m_velocity_to_voltage);
} 

void DirectDifferentialDrive::setVoltage(double left_voltage, double right_voltage)
{
    m_left_motors.setVoltage(left_voltage);
    m_right_motors.setVoltage(right_voltage);
}

double DirectDifferentialDrive::getRadius()
{
    return m_radius;
}

void DirectDifferentialDrive::setLeftMotors(hal::MotorGroup& left_motors)
{
    m_left_motors = left_motors;
}

void DirectDifferentialDrive::setRightMotors(hal::MotorGroup& right_motors)
{
    m_right_motors = right_motors;
}

void DirectDifferentialDrive::setVelocityToVoltage(double velocity_to_voltage)
{
    m_velocity_to_voltage = velocity_to_voltage;
}

void DirectDifferentialDrive::setGearRatio(double gear_ratio)
{
    m_gear_ratio = gear_ratio;
}

void DirectDifferentialDrive::setWheelRadius(double wheel_radius)
{
    m_wheel_radius = wheel_radius;
}

void DirectDifferentialDrive::setRadius(double radius)
{
    m_radius = radius;
}
}
}
}
}