#include "pros_adapters/ProsDelayer.hpp"

namespace pros_adapters
{
std::unique_ptr<wisco::rtos::IDelayer> ProsDelayer::clone() const
{
    return std::unique_ptr<wisco::rtos::IDelayer>(std::make_unique<ProsDelayer>(*this));
}

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