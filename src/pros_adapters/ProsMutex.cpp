#include "pros_adapters/ProsMutex.hpp"

namespace pros_adapters
{
void ProsMutex::take()
{
    mutex.take();
}

void ProsMutex::give()
{
    mutex.give();
}
}