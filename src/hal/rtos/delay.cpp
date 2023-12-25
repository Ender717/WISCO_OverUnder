#include "hal/rtos/delay.hpp"

namespace hal
{
namespace rtos
{
void delay(const uint32_t millis)
{
	pros::delay(millis);
}
} // namespace rtos
} // namespace hal