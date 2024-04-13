#include "wisco/robot/subsystems/umbrella/PistonUmbrella.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace umbrella
{
void PistonUmbrella::initialize()
{
    // No initialization code
}

void PistonUmbrella::run()
{
    // No running code
}

void PistonUmbrella::setIn()
{
    m_pistons.setState(!m_out_state);
}

void PistonUmbrella::setOut()
{
    m_pistons.setState(m_out_state);
}

bool PistonUmbrella::isIn()
{
    return m_pistons.getState() != m_out_state;
}

bool PistonUmbrella::isOut()
{
    return m_pistons.getState() == m_out_state;
}

void PistonUmbrella::setPistons(hal::PistonGroup& pistons)
{
    m_pistons = pistons;
}

void PistonUmbrella::setOutState(bool out_state)
{
    m_out_state = out_state;
}
}
}
}
}