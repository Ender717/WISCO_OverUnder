#include "pros_adapters/ProsPiston.hpp"

namespace pros_adapters
{
ProsPiston::ProsPiston(std::unique_ptr<pros::adi::DigitalOut>& digital_out, bool extended_value)
    : m_digital_out{std::move(digital_out)}, m_extended_value{extended_value}
{

}

void ProsPiston::extend()
{
    if (m_digital_out)
    {
        extended = true;
        m_digital_out->set_value(m_extended_value);
    }
}

void ProsPiston::retract()
{
    if (m_digital_out)
    {
        extended = false;
        m_digital_out->set_value(!m_extended_value);
    }
}

void ProsPiston::toggle()
{
    if (m_digital_out)
    {
        m_digital_out->set_value(m_extended_value ^ extended);
        extended = !extended;
    }
}

bool ProsPiston::isExtended()
{
    return extended;
}

bool ProsPiston::isRetracted()
{
    return !extended;
}
} // namespace pros_adapters