#include "wisco/hal/DistanceBooleanSensor.hpp"

namespace wisco
{
namespace hal
{
DistanceBooleanSensor::DistanceBooleanSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor, 
                                             DistanceBooleanMode mode, 
                                             double lower_threshold)
    : m_distance_sensor{std::move(distance_sensor)}, m_mode{mode}, m_lower_threshold{lower_threshold}, m_upper_threshold{lower_threshold}
{

}

DistanceBooleanSensor::DistanceBooleanSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor, 
                                             DistanceBooleanMode mode, 
                                             double lower_threshold,
                                             double upper_threshold)
    : m_distance_sensor{std::move(distance_sensor)}, m_mode{mode}, m_lower_threshold{lower_threshold}, m_upper_threshold{upper_threshold}
{
    
}

void DistanceBooleanSensor::initialize()
{
    reset();
}

void DistanceBooleanSensor::reset()
{
    if (!m_distance_sensor)
        return;

    double distance{m_distance_sensor->getDistance()};
    switch (m_mode)
    {
    case DistanceBooleanMode::ABOVE_THRESHOLD:
        value = distance > m_upper_threshold;
        break;
    case DistanceBooleanMode::BELOW_THRESHOLD:
        value = distance < m_lower_threshold;
        break;
    case DistanceBooleanMode::BETWEEN_THRESHOLD:
        value = (distance > m_lower_threshold && distance < m_upper_threshold);
        break;
    }
}

bool DistanceBooleanSensor::getValue()
{
    double distance{};
    if (m_distance_sensor)
        distance = m_distance_sensor->getDistance();
    
    switch (m_mode)
    {
    case DistanceBooleanMode::ABOVE_THRESHOLD:
        if (value)
            value = distance > m_lower_threshold;
        else
            value = distance > m_upper_threshold;
        break;
    case DistanceBooleanMode::BELOW_THRESHOLD:
        if (value)
            value = distance < m_upper_threshold;
        else
            value = distance < m_lower_threshold;
        break;
    case DistanceBooleanMode::BETWEEN_THRESHOLD:
        value = (distance > m_lower_threshold && distance < m_upper_threshold);
        break;
    }

    return value;
}
} // namespace hal
} // namespace wisco