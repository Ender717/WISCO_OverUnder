#include "wisco/robot/subsystems/hang/PistonWinchBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
PistonWinchBuilder* PistonWinchBuilder::withPiston(std::unique_ptr<io::IPiston>& piston)
{
    m_pistons.addPiston(piston);
    return this;
}

PistonWinchBuilder* PistonWinchBuilder::withEngagedState(bool engaged_state)
{
    m_engaged_state = engaged_state;
    return this;
}

std::unique_ptr<IWinch> PistonWinchBuilder::build()
{
    std::unique_ptr<PistonWinch> piston_winch{std::make_unique<PistonWinch>()};
    piston_winch->setPistons(m_pistons);
    piston_winch->setEngagedState(m_engaged_state);
    return piston_winch;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco