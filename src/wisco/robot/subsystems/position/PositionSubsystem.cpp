#include "wisco/robot/subsystems/position/PositionSubsystem.hpp"
#include "pros/screen.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
PositionSubsystem::PositionSubsystem(std::unique_ptr<IPositionTracker>& position_tracker,
                                     std::unique_ptr<IPositionResetter>& position_resetter)
    : ASubsystem{SUBSYSTEM_NAME}, 
    m_position_tracker{std::move(position_tracker)},
    m_position_resetter{std::move(position_resetter)}
{

}

void PositionSubsystem::initialize()
{
    if (m_position_tracker)
        m_position_tracker->initialize();
    if (m_position_resetter)
        m_position_resetter->initialize();
}

void PositionSubsystem::run()
{
    if (m_position_tracker)
        m_position_tracker->run();
    if (m_position_resetter)
        m_position_resetter->run();
}

void PositionSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_POSITION_COMMAND_NAME)
    {
        Position position{va_arg(args, double), va_arg(args, double), va_arg(args, double)};
        m_position_tracker->setPosition(position);
    }
    else if (command_name == SET_X_COMMAND_NAME)
    {
        if (m_position_tracker)
        {
            double x{va_arg(args, double)};
            m_position_tracker->setX(x);
        }
    }
    else if (command_name == SET_Y_COMMAND_NAME)
    {
        if (m_position_tracker)
        {
            double y{va_arg(args, double)};
            m_position_tracker->setY(y);
        }
    }
    else if (command_name == SET_THETA_COMMAND_NAME)
    {
        if (m_position_tracker)
        {
            double theta{va_arg(args, double)};
            m_position_tracker->setTheta(theta);
        }
    }
    else if (command_name == RESET_X_COMMAND_NAME)
    {
        if (m_position_tracker && m_position_resetter)
        {
            Position position{m_position_tracker->getPosition()};
            double reset_x{m_position_resetter->getResetX(position.theta)};
            m_position_tracker->setX(reset_x);
        }
    }
    else if (command_name == RESET_Y_COMMAND_NAME)
    {
        if (m_position_tracker && m_position_resetter)
        {
            Position position{m_position_tracker->getPosition()};
            double reset_y{m_position_resetter->getResetY(position.theta)};
            m_position_tracker->setY(reset_y);
        }
    }
}

void* PositionSubsystem::state(std::string state_name)
{
    void* result{};

    if (state_name == GET_POSITION_STATE_NAME)
    {
        Position* position{new Position{m_position_tracker->getPosition()}};
        result = position;
    }

    return result;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco