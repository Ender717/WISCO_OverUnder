#include "pros_adapters/ProsEXPMotor.hpp"

namespace pros_adapters
{
ProsEXPMotor::ProsEXPMotor(std::unique_ptr<pros::Motor>& motor) : m_motor{std::move(motor)}
{

}

void ProsEXPMotor::initialize()
{
    if (m_motor)
    {
        m_motor->move_voltage(0);
        m_motor->tare_position();
    }
}

double ProsEXPMotor::getTorqueConstant()
{
    return TORQUE_CONSTANT;
}

double ProsEXPMotor::getResistance()
{
    return RESISTANCE;
}

double ProsEXPMotor::getAngularVelocityConstant()
{
    return ANGULAR_VELOCITY_CONSTANT;
}

double ProsEXPMotor::getGearRatio()
{
    return GEAR_RATIO;
}

double ProsEXPMotor::getAngularVelocity()
{
    double angular_velocity{};

    if (m_motor)
        angular_velocity = m_motor->get_actual_velocity() * VELOCITY_CONVERSION;

    return angular_velocity;
}

void ProsEXPMotor::setVoltage(double volts)
{
    if (m_motor)
        m_motor->move_voltage(volts * VOLTAGE_CONVERSION);
}
} // namespace pros_adapters