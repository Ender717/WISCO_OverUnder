#include "wisco/hal/PistonGroup.hpp"

namespace wisco
{
namespace hal
{
void PistonGroup::addPiston(std::unique_ptr<io::IPiston>& piston)
{
    pistons.push_back(std::move(piston));
}

void PistonGroup::setState(bool state)
{
    if (m_state != state)
    {
        m_state = state;
        for (auto& piston : pistons)
            if (piston)
                piston->toggle();
    }
}

bool PistonGroup::getState()
{
    return m_state;
}

PistonGroup& PistonGroup::operator=(PistonGroup& rhs)
{
    pistons.clear();
    for (uint8_t i{0}; i < rhs.pistons.size(); ++i)
        pistons.push_back(std::move(rhs.pistons.at(i)));
    rhs.pistons.clear();
    return *this;
}
} // namespace hal
} // namespace wisco