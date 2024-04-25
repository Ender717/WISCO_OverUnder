#include "pros_adapters/ProsHeading.hpp"

namespace pros_adapters
{
ProsHeading::ProsHeading(std::unique_ptr<pros::Imu>& sensor, double tuning_constant) : 
    m_sensor{std::move(sensor)}, m_tuning_constant{tuning_constant}
{

}

void ProsHeading::initialize()
{
    if (m_sensor)
    {
        if (m_sensor->is_installed())
        {
            m_sensor->reset();
            pros::delay(3000);
            m_sensor->set_data_rate(5);
        }
    }
}

void ProsHeading::reset()
{
    if (m_sensor)
    {
        uint8_t port{m_sensor->get_port()};
        pros::Device device{port};
        pros::DeviceType sensor_type{device.get_plugged_type()};
        if (sensor_type == pros::DeviceType::imu)
        {
            m_sensor->reset();
            pros::delay(3000);
        }
    }
}

double ProsHeading::getHeading()
{
    double heading{};
    if (m_sensor)
    {
        heading = (m_sensor->get_heading() / UNIT_CONVERTER) * m_tuning_constant;
    }
    return heading;
}

void ProsHeading::setHeading(double heading)
{
    if (m_sensor)
        m_sensor->set_heading(heading * UNIT_CONVERTER);
}

double ProsHeading::getRotation()
{
    double rotation{};
    if (m_sensor)
    {
        rotation = (m_sensor->get_rotation() / UNIT_CONVERTER) * m_tuning_constant;
    }
    return rotation;
}

void ProsHeading::setRotation(double rotation)
{
    if (m_sensor)
        m_sensor->set_rotation(rotation * UNIT_CONVERTER);
}
}