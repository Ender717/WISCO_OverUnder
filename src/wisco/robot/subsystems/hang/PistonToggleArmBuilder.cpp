#include "wisco/robot/subsystems/hang/PistonToggleArmBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace hang
{
PistonToggleArmBuilder* PistonToggleArmBuilder::withPiston(std::unique_ptr<io::IPiston>& piston)
{
    m_pistons.addPiston(piston);
    return this;
}

PistonToggleArmBuilder* PistonToggleArmBuilder::withUpState(bool up_state)
{
    m_up_state = up_state;
    return this;
}

std::unique_ptr<IToggleArm> PistonToggleArmBuilder::build()
{
    std::unique_ptr<PistonToggleArm> piston_toggle_arm{std::make_unique<PistonToggleArm>()};
    piston_toggle_arm->setPistons(m_pistons);
    piston_toggle_arm->setUpState(m_up_state);
    return piston_toggle_arm;
}
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco