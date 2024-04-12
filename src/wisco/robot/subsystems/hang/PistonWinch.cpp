#include "wisco/robot/subsystems/hang/PistonWinch.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
void PistonWinch::initialize()
{
    // No initialize code
}

void PistonWinch::run()
{
    // No run code
}

void PistonWinch::engage()
{
    m_pistons.setState(m_engaged_state);
}

void PistonWinch::disengage()
{
    m_pistons.setState(!m_engaged_state);
}

bool PistonWinch::isEngaged()
{
    return m_pistons.getState() == m_engaged_state;
}

bool PistonWinch::isDisengaged()
{
    return m_pistons.getState() != m_engaged_state;
}

void PistonWinch::setPistons(hal::PistonGroup& pistons)
{
    m_pistons = pistons;
}

void PistonWinch::setEngagedState(bool engaged_state)
{
    m_engaged_state = engaged_state;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco