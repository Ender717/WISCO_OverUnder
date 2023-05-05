// Included headers
#include "devices/AnalogInput.h"
#include "pros/ext_adi.h"

AnalogInput::AnalogInput()
{
    port = '\0';
    ext_port = 0;
}

AnalogInput::AnalogInput(uint8_t _port, uint8_t _ext_port) : port(_port), ext_port(_ext_port)
{
    if (ext_port == 0)
        pros::c::adi_port_set_config(port, pros::E_ADI_ANALOG_IN);
    else
        pros::c::ext_adi_port_set_config(ext_port, port, pros::E_ADI_ANALOG_IN);
}

AnalogInput::AnalogInput(const AnalogInput& copy) : port(copy.port), ext_port(copy.ext_port)
{

}

void AnalogInput::set_port(uint8_t _port, uint8_t _ext_port)
{
    mutex.take();
    port = _port;
    ext_port = _ext_port;
    if (ext_port == 0)
        pros::c::adi_port_set_config(port, pros::E_ADI_ANALOG_IN);
    else
        pros::c::ext_adi_port_set_config(ext_port, port, pros::E_ADI_ANALOG_IN);
    mutex.give();
}

uint8_t AnalogInput::get_port()
{
    mutex.take();
    uint8_t result = port;
    mutex.give();
    return result;
}

uint8_t AnalogInput::get_ext_port()
{
    mutex.take();
    uint8_t result = ext_port;
    mutex.give();
    return result;
}

int AnalogInput::calibrate()
{
    int result;
    mutex.take();
    if (ext_port == 0)
        result = pros::c::adi_analog_calibrate(port);
    else
        result = pros::c::ext_adi_analog_calibrate(ext_port, port);
    mutex.give();
    return result;
}

int AnalogInput::get_value()
{
    int result;
    mutex.take();
    if (ext_port == 0)
        result = pros::c::adi_analog_read(port);
    else
        result = pros::c::ext_adi_analog_read(ext_port, port);
    mutex.give();
    return result;
}

int AnalogInput::get_value_calibrated()
{
    int result;
    mutex.take();
    if (ext_port == 0)
        result = pros::c::adi_analog_read_calibrated(port);
    else
        result = pros::c::ext_adi_analog_read_calibrated(ext_port, port);
    mutex.give();
    return result;
}

int AnalogInput::get_value_calibrated_HR()
{
    int result;
    mutex.take();
    if (ext_port == 0)
        result = pros::c::adi_analog_read_calibrated_HR(port);
    else
        result = pros::c::ext_adi_analog_read_calibrated_HR(ext_port, port);
    mutex.give();
    return result;
}

AnalogInput& AnalogInput::operator=(const AnalogInput& rhs)
{
    mutex.take();
    port = rhs.port;
    ext_port = rhs.ext_port;
    mutex.give();
    return *this;
}