#include "wisco/control/motion/MotionControl.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
MotionControl::MotionControl(std::unique_ptr<IDriveStraight>& drive_straight, std::unique_ptr<ITurn>& turn)
    : AControl{CONTROL_NAME}, m_drive_straight{std::move(drive_straight)}, m_turn{std::move(turn)}
{

}

void MotionControl::initialize()
{
    if (m_drive_straight)
        m_drive_straight->initialize();
    if (m_turn)
        m_turn->initialize();
}

void MotionControl::run()
{
    if (m_drive_straight)
        m_drive_straight->run();
    if (m_turn)
        m_turn->run();
}

void MotionControl::pause()
{
    switch (active_motion)
    {
    case EMotion::DRIVE_STRAIGHT:
        if (m_drive_straight)
            m_drive_straight->pause();
        break;
    case EMotion::TURN:
        if (m_turn)
            m_turn->pause();
        break;
    default:
        break;
    }
}

void MotionControl::resume()
{
    switch (active_motion)
    {
    case EMotion::DRIVE_STRAIGHT:
        if (m_drive_straight)
            m_drive_straight->resume();
        break;
    case EMotion::TURN:
        if (m_turn)
            m_turn->resume();
        break;
    default:
        break;
    }
}

void MotionControl::command(std::string command_name, va_list& args)
{
    if (command_name == DRIVE_STRAIGHT_COMMAND_NAME)
    {
        if (active_motion != EMotion::DRIVE_STRAIGHT)
        {
            pause();
            active_motion = EMotion::DRIVE_STRAIGHT;
        }
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double distance{va_arg(args, double)};
        double velocity{va_arg(args, double)};
        double theta{va_arg(args, double)};
        if (m_drive_straight)
            m_drive_straight->driveStraight(robot, distance, velocity, theta);
    }
    else if (command_name == TURN_TO_ANGLE_COMMAND_NAME)
    {
        if (active_motion != EMotion::TURN)
        {
            pause();
            active_motion = EMotion::TURN;
        }
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double velocity{va_arg(args, double)};
        double theta{va_arg(args, double)};
        bool reversed{static_cast<bool>(va_arg(args, int))};
        ETurnDirection direction{va_arg(args, ETurnDirection)};
        m_turn->turnToAngle(robot, velocity, theta, reversed, direction);
    }
    else if (command_name == TURN_TO_POINT_COMMAND_NAME)
    {
        if (active_motion != EMotion::TURN)
        {
            pause();
            active_motion = EMotion::TURN;
        }
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        double velocity{va_arg(args, double)};
        double x{va_arg(args, double)};
        double y{va_arg(args, double)};
        bool reversed{static_cast<bool>(va_arg(args, int))};
        ETurnDirection direction{va_arg(args, ETurnDirection)};
        m_turn->turnToPoint(robot, velocity, x, y, reversed, direction);
    }
}

void* MotionControl::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == DRIVE_STRAIGHT_TARGET_REACHED_STATE_NAME)
    {
        bool* velocity{new bool{m_drive_straight->targetReached()}};
        result = velocity;
    }
    else if (state_name == TURN_TARGET_REACHED_STATE_NAME)
    {
        bool* velocity{new bool{m_turn->targetReached()}};
        result = velocity;
    }

    return result;
}
} // namespace motion
} // namespace control
} // namespace wisco