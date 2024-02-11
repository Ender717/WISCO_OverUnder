#include "pros_adapters/ProsMutex.hpp"

namespace pros_adapters
{
ProsMutex::ProsMutex(std::unique_ptr<pros::Mutex>& mutex) : m_mutex{std::move(mutex)}
{

}

void ProsMutex::take()
{
    if (m_mutex)
        m_mutex->take();
}

void ProsMutex::give()
{
    if (m_mutex)
        m_mutex->give();
}
}