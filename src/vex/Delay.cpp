#include "vex/Delay.hpp"
#include "pros/rtos.hpp"

namespace vex
{
void Delay::delayMS(uint32_t milliseconds)
{
    pros::rtos::delay(milliseconds);
}

void Delay::delayUS(uint32_t microseconds)
{
    pros::rtos::delay(microseconds / US_PER_MS);
}
}