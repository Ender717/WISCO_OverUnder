#include "wisco/robot/subsystems/wings/PistonWingsBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace wings
{
PistonWingsBuilder* PistonWingsBuilder::withLeftPiston(std::unique_ptr<io::IPiston>& left_piston)
{
    m_left_pistons.addPiston(left_piston);
    return this;
}

PistonWingsBuilder* PistonWingsBuilder::withRightPiston(std::unique_ptr<io::IPiston>& right_piston)
{
    m_right_pistons.addPiston(right_piston);
    return this;
}

PistonWingsBuilder* PistonWingsBuilder::withOutState(bool out_state)
{
    m_out_state = out_state;
    return this;
}

std::unique_ptr<IWings> PistonWingsBuilder::build()
{
    std::unique_ptr<PistonWings> piston_wings{std::make_unique<PistonWings>()};
    piston_wings->setLeftPistons(m_left_pistons);
    piston_wings->setRightPistons(m_right_pistons);
    piston_wings->setOutState(m_out_state);
    return piston_wings;
}
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco