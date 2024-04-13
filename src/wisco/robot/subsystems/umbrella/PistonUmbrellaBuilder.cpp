#include "wisco/robot/subsystems/umbrella/PistonUmbrellaBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace umbrella
{
PistonUmbrellaBuilder* PistonUmbrellaBuilder::withPiston(std::unique_ptr<io::IPiston>& piston)
{
    m_pistons.addPiston(piston);
    return this;
}

PistonUmbrellaBuilder* PistonUmbrellaBuilder::withOutState(bool out_state)
{
    m_out_state = out_state;
    return this;
}

std::unique_ptr<IUmbrella> PistonUmbrellaBuilder::build()
{
    std::unique_ptr<PistonUmbrella> piston_umbrella{std::make_unique<PistonUmbrella>()};
    piston_umbrella->setPistons(m_pistons);
    piston_umbrella->setOutState(m_out_state);
    return piston_umbrella;
}
} // namespace umbrella
} // namespace subsystems
} // namespace robot
} // namespace wisco