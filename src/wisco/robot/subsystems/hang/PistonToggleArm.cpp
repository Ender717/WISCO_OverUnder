#include "wisco/robot/subsystems/hang/PistonToggleArm.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
void PistonToggleArm::initialize()
{
    // No initialization code
}

void PistonToggleArm::run()
{
    // No running code
}

void PistonToggleArm::setDown()
{
    m_pistons.setState(!m_up_state);
}

void PistonToggleArm::setUp()
{
    m_pistons.setState(m_up_state);
}

bool PistonToggleArm::isDown()
{
    return m_pistons.getState() != m_up_state;
}

bool PistonToggleArm::isUp()
{
    return m_pistons.getState() == m_up_state;
}

void PistonToggleArm::setPistons(hal::PistonGroup& pistons)
{
    m_pistons = pistons;
}

void PistonToggleArm::setUpState(bool up_state)
{
    m_up_state = up_state;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco