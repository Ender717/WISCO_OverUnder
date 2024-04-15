#include "wisco/control/boomerang/BoomerangControl.hpp"

namespace wisco
{
namespace control
{
namespace boomerang
{
BoomerangControl::BoomerangControl(std::unique_ptr<IBoomerang>& boomerang)
    : AControl{CONTROL_NAME}, m_boomerang{std::move(boomerang)}
{

}

void BoomerangControl::initialize()
{
    if (m_boomerang)
        m_boomerang->initialize();
}

void BoomerangControl::run()
{
    if (m_boomerang)
        m_boomerang->run();
}

void BoomerangControl::pause()
{
    if (m_boomerang)
        m_boomerang->pause();
}

void BoomerangControl::resume()
{
    if (m_boomerang)
        m_boomerang->resume();
}

void BoomerangControl::command(std::string command_name, va_list& args)
{
    if (command_name == GO_TO_POSITION_COMMAND_NAME)
    {
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double velocity{va_arg(args, double)};
        double x{va_arg(args, double)};
        double y{va_arg(args, double)};
        double theta{va_arg(args, double)};
        m_boomerang->goToPosition(robot, velocity, x, y, theta);
    }
}

void* BoomerangControl::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == TARGET_REACHED_STATE_NAME)
    {
        bool* velocity{new bool{m_boomerang->targetReached()}};
        result = velocity;
    }

    return result;
}
} // namespace boomerang
} // namespace boomerang
} // namespace boomerang