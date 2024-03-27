#include "pros_adapters/ProsClock.hpp"

namespace pros_adapters
{
std::unique_ptr<wisco::rtos::IClock> ProsClock::clone() const
{
    return std::unique_ptr<wisco::rtos::IClock>(std::make_unique<ProsClock>(*this));
}

uint32_t ProsClock::getTime()
{
    return pros::millis();
}
}