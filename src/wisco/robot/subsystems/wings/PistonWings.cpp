#include "wisco/robot/subsystems/wings/PistonWings.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace wings
{
void PistonWings::initialize()
{
    // No initialization code
}

void PistonWings::run()
{
    // No running code
}

void PistonWings::setLeftWing(bool out)
{
    if (out)
        m_left_pistons.setState(m_out_state);
    else
        m_left_pistons.setState(!m_out_state);
}

void PistonWings::setRightWing(bool out)
{
    if (out)
        m_right_pistons.setState(m_out_state);
    else
        m_right_pistons.setState(!m_out_state);
}

bool PistonWings::getLeftWing()
{
    return m_left_pistons.getState() == m_out_state;
}

bool PistonWings::getRightWing()
{
    return m_right_pistons.getState() == m_out_state;
}

void PistonWings::setLeftPistons(hal::PistonGroup& left_pistons)
{
    m_left_pistons = left_pistons;
}

void PistonWings::setRightPistons(hal::PistonGroup& right_pistons)
{
    m_right_pistons = right_pistons;
}

void PistonWings::setOutState(bool out_state)
{
    m_out_state = out_state;
}
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco