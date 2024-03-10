#include "wisco/hal/MotorGroup.hpp"

namespace wisco
{
namespace hal
{
void MotorGroup::addMotor(std::unique_ptr<io::IMotor>& motor)
{
    motors.push_back(std::move(motor));
}

void MotorGroup::initialize()
{
    for (auto& motor : motors)
        if (motor)
            motor->initialize();
}

double MotorGroup::getTorqueConstant()
{
    double sum_constant{};
    for (auto& motor : motors)
        if (motor)
            sum_constant += motor->getTorqueConstant();

    return sum_constant;
}

double MotorGroup::getResistance()
{
    double average_resistance{};
    if (!motors.empty())
    {
        for (auto& motor : motors)
            if (motor)
                average_resistance += motor->getResistance();
        average_resistance /= motors.size();
    }
    
    return average_resistance;
}

double MotorGroup::getAngularVelocityConstant()
{
    double average_constant{};
    if (!motors.empty())
    {
        for (auto& motor : motors)
            if (motor)
                average_constant += motor->getAngularVelocityConstant();
        average_constant /= motors.size();
    }
    
    return average_constant;
}

double MotorGroup::getGearRatio()
{
    double gear_ratio{};
    if (!motors.empty() && motors.front())
        gear_ratio = motors.front()->getGearRatio();
    return gear_ratio;
}

double MotorGroup::getAngularVelocity()
{
    double average_velocity{};
    if (!motors.empty())
    {
        for (auto& motor : motors)
            if (motor)
                average_velocity += motor->getAngularVelocity();
        average_velocity /= motors.size();
    }

    return average_velocity;
}

void MotorGroup::setVoltage(double volts)
{
    for (auto& motor : motors)
        if (motor)
            motor->setVoltage(volts);
}

MotorGroup& MotorGroup::operator=(MotorGroup& rhs)
{
    motors.clear();
    for (uint8_t i{0}; i < rhs.motors.size(); ++i)
        motors.push_back(std::move(rhs.motors.at(i)));
    rhs.motors.clear();
    return *this;
}
} // namespace hal
} // namespace wisco