// Included headers
#include "devices/Piston.h"
#include "pros/adi.h"

Piston::Piston()
{
    port = '\0';
    ext_port = 0;
    toggled = false;
}

Piston::Piston(uint8_t _port, uint8_t _ext_port) : port(_port), ext_port(_ext_port)
{
    toggled = false;
    if (ext_port == 0)
        pros::c::adi_port_set_config(port, pros::E_ADI_DIGITAL_OUT);
    else
        pros::c::ext_adi_port_set_config(ext_port, port, pros::E_ADI_DIGITAL_OUT);
}

Piston::Piston(const Piston& copy) : port(copy.port), toggled(copy.toggled)
{

}

void Piston::set_port(uint8_t _port, uint8_t _ext_port)
{
    mutex.take();
    port = _port;
    ext_port = _ext_port;
    if (ext_port == 0)
        pros::c::adi_port_set_config(port, pros::E_ADI_DIGITAL_OUT);
    else
        pros::c::ext_adi_port_set_config(ext_port, port, pros::E_ADI_DIGITAL_OUT);
    mutex.give();
}

uint8_t Piston::get_port()
{
    mutex.take();
    uint8_t result = port;
    mutex.give();
    return result;
}

uint8_t Piston::get_ext_port()
{
    mutex.take();
    uint8_t result = ext_port;
    mutex.give();
    return result;
}

int Piston::toggle()
{
    mutex.take();
    toggled = !toggled;
    int result;
    if (ext_port == 0)
        result = pros::c::adi_digital_write(port, toggled);
    else
        result = pros::c::ext_adi_digital_write(ext_port, port, toggled);
    mutex.give();
    return result;
}

int Piston::set_toggled(bool _toggled)
{
    mutex.take();
    toggled = _toggled;
    int result;
    if (ext_port == 0)
        result = pros::c::adi_digital_write(port, toggled);
    else
        result = pros::c::ext_adi_digital_write(ext_port, port, toggled);
    mutex.give();
    return result;
}

bool Piston::get_toggled()
{
    mutex.take();
    bool result = toggled;
    mutex.give();
    return result;
}

Piston& Piston::operator=(const Piston& rhs)
{
    mutex.take();
    port = rhs.port;
    ext_port = rhs.ext_port;
    toggled = rhs.toggled;
    mutex.give();
    return *this;
}