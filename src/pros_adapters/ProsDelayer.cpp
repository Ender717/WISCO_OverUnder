#include "pros_adapters/ProsDelayer.hpp"

namespace pros_adapters
{
void ProsDelayer::delay(uint32_t millis)
{
    pros::delay(millis);
}
}