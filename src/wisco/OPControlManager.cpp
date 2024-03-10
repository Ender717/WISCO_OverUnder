#include "wisco/OPControlManager.hpp"

namespace wisco
{
void OPControlManager::setProfile(std::unique_ptr<IProfile>& profile)
{
    m_profile = std::move(profile);
}

void OPControlManager::initializeOpcontrol(std::shared_ptr<robot::Robot> robot)
{

}

void OPControlManager::runOpcontrol(std::shared_ptr<robot::Robot> robot, std::shared_ptr<io::ITouchScreen> touch_screen, std::shared_ptr<rtos::IDelayer> delayer)
{
    robot->sendCommand("DIFFERENTIAL DRIVE", "SET VELOCITY", 1.0, 1.0);
    robot::subsystems::position::Position* position{};
    robot::subsystems::drive::Velocity* velocity{};
    while (true)
    {
        /*
        position = (robot::subsystems::position::Position*)(robot->getState("POSITION TRACKER", "GET POSITION"));
        if (position)
        {
            touch_screen->print(0, 0, "X: %7.2f", position->x);
            touch_screen->print(0, 40, "Y: %7.2f", position->y);
            touch_screen->print(0, 80, "Theta: %9.2f", position->theta * 180 / 3.1415);
            delete position;
        }

        velocity = (robot::subsystems::drive::Velocity*)(robot->getState("DIFFERENTIAL DRIVE", "GET VELOCITY"));
        if (velocity)
        {
            touch_screen->print(0, 120, "Left: %7.2f", velocity->left_velocity);
            touch_screen->print(0, 160, "Right: %7.2f", velocity->right_velocity);
            delete velocity;
        }
        */
       
        delayer->delay(CONTROL_DELAY);
    }
}
}