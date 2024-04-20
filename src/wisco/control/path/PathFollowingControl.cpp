#include "wisco/control/path/PathFollowingControl.hpp"

namespace wisco
{
namespace control
{
namespace path
{
PathFollowingControl::PathFollowingControl(std::unique_ptr<IPathFollower>& path_follower)
    : AControl{CONTROL_NAME}, m_path_follower{std::move(path_follower)}
{

}

void PathFollowingControl::initialize()
{
    if (m_path_follower)
        m_path_follower->initialize();
}

void PathFollowingControl::run()
{
    if (m_path_follower)
        m_path_follower->run();
}

void PathFollowingControl::pause()
{
    if (m_path_follower)
        m_path_follower->pause();
}

void PathFollowingControl::resume()
{
    if (m_path_follower)
        m_path_follower->resume();
}

void PathFollowingControl::command(std::string command_name, va_list& args)
{
    if (command_name == FOLLOW_PATH_COMMAND_NAME)
    {
        void* robot_ptr{va_arg(args, void*)};
        std::shared_ptr<robot::Robot> robot{*static_cast<std::shared_ptr<robot::Robot>*>(robot_ptr)};
        void* path_ptr{va_arg(args, void*)};
        std::vector<Point> path{*static_cast<std::vector<Point>*>(path_ptr)};
        double velocity{va_arg(args, double)};
        m_path_follower->followPath(robot, path, velocity);
    }
    else if (command_name == SET_VELOCITY_COMMAND_NAME)
    {
        double velocity{va_arg(args, double)};
        m_path_follower->setVelocity(velocity);
    }
}

void* PathFollowingControl::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == TARGET_REACHED_STATE_NAME)
    {
        bool* velocity{new bool{m_path_follower->targetReached()}};
        result = velocity;
    }

    return result;
}
} // namespace path
} // namespace control
} // namespace wisco