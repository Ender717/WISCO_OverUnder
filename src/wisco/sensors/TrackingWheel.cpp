#include "wisco/sensors/TrackingWheel.hpp"

namespace wisco
{
namespace sensors
{
TrackingWheel::TrackingWheel(std::unique_ptr<hal::IRotationSensor>& sensor, double wheel_radius) :
    m_sensor{std::move(sensor)}, m_wheel_radius{wheel_radius}
{

}

void TrackingWheel::initialize()
{
    if (m_sensor)
        m_sensor->initialize();
}

void TrackingWheel::reset()
{
    if (m_sensor)
        m_sensor->reset();
}

double TrackingWheel::getDistance()
{
    return m_sensor->getRotation() * m_wheel_radius;
}

void TrackingWheel::setDistance(double distance)
{
    m_sensor->setRotation(distance / m_wheel_radius);
}
}
}