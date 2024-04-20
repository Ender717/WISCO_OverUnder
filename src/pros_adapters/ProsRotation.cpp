#include "pros_adapters/ProsRotation.hpp"

namespace pros_adapters
{
ProsRotation::ProsRotation(std::unique_ptr<pros::Rotation>& sensor) : m_sensor{std::move(sensor)}
{

}

void ProsRotation::initialize()
{
    if (m_sensor)
    {
        m_sensor->reset();
        m_sensor->set_data_rate(5);
    }
}

void ProsRotation::reset()
{
    if (m_sensor)
    {
        m_sensor->reset();
    }
}

double ProsRotation::getRotation()
{
    double rotation{};
    if (m_sensor)
    {
        rotation = m_sensor->get_position() / UNIT_CONVERSION;
    }
    return rotation;
}

void ProsRotation::setRotation(double rotation)
{
    if (m_sensor)
    {
        m_sensor->set_position(rotation * UNIT_CONVERSION);
    }
}

double ProsRotation::getAngle()
{
    double angle{};
    if (m_sensor)
    {
        angle = m_sensor->get_angle() / UNIT_CONVERSION;
    }
    return angle;
}
}