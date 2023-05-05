// Included headers
#include "devices/RotationSensor.h"
#include "pros/rotation.h"

RotationSensor::RotationSensor()
{

}

RotationSensor::RotationSensor(uint8_t _port, bool _reversed) : port(_port)
{
    if (_reversed != pros::c::rotation_get_reversed(port))
        pros::c::rotation_reverse(port);
}

RotationSensor::RotationSensor(const RotationSensor& copy) : port(copy.port)
{

}

void RotationSensor::set_port(uint8_t _port)
{
    mutex.take();
    port = _port;
    mutex.give();
}

uint8_t RotationSensor::get_port()
{
    mutex.take();
    uint8_t result = port;
    mutex.give();
    return result;
}

int RotationSensor::reset()
{
    mutex.take();
    int result = pros::c::rotation_reset(port);
    mutex.give();
    return result;
}

int RotationSensor::set_position(uint32_t position)
{
    mutex.take();
    int result = pros::c::rotation_set_position(port, position);
    mutex.give();
    return result;
}

int RotationSensor::reset_position()
{
    mutex.take();
    int result = pros::c::rotation_reset_position(port);
    mutex.give();
    return result;
}

int RotationSensor::get_position()
{
    mutex.take();
    int position = pros::c::rotation_get_position(port);
    mutex.give();
    return position;
}

int RotationSensor::get_velocity()
{
    mutex.take();
    int velocity = pros::c::rotation_get_velocity(port);
    mutex.give();
    return velocity;
}

int RotationSensor::get_angle()
{
    mutex.take();
    int angle = pros::c::rotation_get_angle(port);
    mutex.give();
    return angle;
}

int RotationSensor::set_reversed(bool _reversed)
{
    mutex.take();
    int result = pros::c::rotation_set_reversed(port, _reversed);
    mutex.give();
    return result;
}

int RotationSensor::reverse()
{
    mutex.take();
    int result = pros::c::rotation_reverse(port);
    mutex.give();
    return result;
}

int RotationSensor::get_reversed()
{
    mutex.take();
    int reversed = pros::c::rotation_get_reversed(port);
    mutex.give();
    return reversed;
}

int RotationSensor::set_data_rate(uint32_t rate)
{
    mutex.take();
    int result = pros::c::rotation_set_data_rate(port, rate);
    mutex.give();
    return result;
}

RotationSensor& RotationSensor::operator=(const RotationSensor& rhs)
{
    mutex.take();
    port = rhs.port;
    mutex.give();

    return *this;
}