#include "pros_adapters/ProsDistance.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

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
        pros::screen::print(pros::E_TEXT_LARGE_CENTER, 1, "Distance: %7.2f", distance);
    }
    return distance;
}
}