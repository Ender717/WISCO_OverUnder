#include "wisco/robot/subsystems/hang/PistonClawBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
PistonClawBuilder* PistonClawBuilder::withPiston(std::unique_ptr<io::IPiston>& piston)
{
    m_pistons.addPiston(piston);
    return this;
}

PistonClawBuilder* PistonClawBuilder::withClosedState(bool closed_state)
{
    m_closed_state = closed_state;
    return this;
}

std::unique_ptr<IClaw> PistonClawBuilder::build()
{
    std::unique_ptr<PistonClaw> piston_claw{std::make_unique<PistonClaw>()};
    piston_claw->setPistons(m_pistons);
    piston_claw->setClosedState(m_closed_state);
    return piston_claw;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco