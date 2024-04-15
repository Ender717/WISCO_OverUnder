#include "wisco/control/motion/MotionControl.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
MotionControl::MotionControl(std::unique_ptr<ITurn>& turn)
    : AControl{CONTROL_NAME}, m_turn{std::move(turn)}
{

}

void MotionControl::initialize()
{
    if (m_turn)
        m_turn->initialize();
}

void MotionControl::run()
{
    if (m_turn)
        m_turn->run();
}

void MotionControl::command(std::string command_name, va_list& args)
{
    if (command_name == TURN_TO_ANGLE_COMMAND_NAME)
    {
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double velocity{va_arg(args, double)};
        double theta{va_arg(args, double)};
        ETurnDirection direction{va_arg(args, ETurnDirection)};
        m_turn->turnToAngle(robot, velocity, theta, direction);
    }
    else if (command_name == TURN_TO_POINT_COMMAND_NAME)
    {
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double velocity{va_arg(args, double)};
        double x{va_arg(args, double)};
        double y{va_arg(args, double)};
        ETurnDirection direction{va_arg(args, ETurnDirection)};
        m_turn->turnToPoint(robot, velocity, x, y, direction);
    }
    else if (command_name == PAUSE_TURN_COMMAND_NAME)
    {
        m_turn->pause();
    }
    else if (command_name == RESUME_TURN_COMMAND_NAME)
    {
        m_turn->resume();
    }
}

void* MotionControl::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == TURN_TARGET_REACHED_STATE_NAME)
    {
        bool* velocity{new bool{m_turn->targetReached()}};
        result = velocity;
    }

    return result;
}
} // namespace motion
} // namespace control
} // namespace wisco