#include "pros_adapters/ProsClock.hpp"

namespace pros_adapters
{
uint32_t ProsClock::getTime()
{
    return pros::millis();
}
}