#include "wisco/robot/subsystems/hang/PistonClaw.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
void PistonClaw::initialize()
{
    // No initialize code
}

void PistonClaw::run()
{
    // No run code
}

void PistonClaw::close()
{
    m_pistons.setState(m_closed_state);
}

void PistonClaw::open()
{
    m_pistons.setState(!m_closed_state);
}

bool PistonClaw::isClosed()
{
    return m_pistons.getState() == m_closed_state;
}

bool PistonClaw::isOpen()
{
    return m_pistons.getState() != m_closed_state;
}

void PistonClaw::setPistons(hal::PistonGroup& pistons)
{
    m_pistons = pistons;
}

void PistonClaw::setClosedState(bool closed_state)
{
    m_closed_state = closed_state;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco