#include "pros_adapters/ProsDelayer.hpp"

namespace pros_adapters
{
void ProsDelayer::delay(uint32_t millis)
{
    pros::Task::delay(millis);
}

void ProsDelayer::delayUntil(uint32_t time)
{
    uint32_t current_time{pros::millis()};
    pros::Task::delay_until(&current_time, time - current_time);
}
}