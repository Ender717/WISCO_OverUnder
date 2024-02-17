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
    robot::subsystems::position::Position position{};
    while (true)
    {
        position = *(robot::subsystems::position::Position*)(robot->getState("POSITION TRACKER", "GET POSITION"));
        touch_screen->print(0, 0, "X: %7.2f\nY: %7.2f\nTheta: %9.2f", position.x, position.y, position.theta * 180 / 3.1415);
        delayer->delay(CONTROL_DELAY);
    }
}
}