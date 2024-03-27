#include "pros_adapters/ProsDistance.hpp"

namespace pros_adapters
{
ProsDistance::ProsDistance(std::unique_ptr<pros::Distance>& sensor, double tuning_constant, double tuning_offset) : 
    m_sensor{std::move(sensor)}, m_tuning_constant{tuning_constant}, m_tuning_offset{tuning_offset}
{

}

void ProsDistance::initialize()
{

}

void ProsDistance::reset()
{

}

double ProsDistance::getDistance()
{
    double distance{};
    if (m_sensor)
    {
        distance = (m_sensor->get() * UNIT_CONVERTER * m_tuning_constant) + m_tuning_offset;
    }
    return distance;
}
}