#include "MenuAdapter.hpp"

namespace wisco
{
namespace menu
{  
void MenuAdapter::addAlliance(std::unique_ptr<IAlliance>& alliance)
{
    bool unique{true};
    for (std::unique_ptr<IAlliance>& existing_alliance : alliances)
        if (existing_alliance->getName() == alliance->getName())
            unique = false;
    if (unique)
        alliances.push_back(std::move(alliance));
}

void MenuAdapter::addAutonomous(std::unique_ptr<IAutonomous>& autonomous)
{
    bool unique{true};
    for (std::unique_ptr<IAutonomous>& existing_autonomous : autonomous_routines)
        if (existing_autonomous->getName() == autonomous->getName())
            unique = false;
    if (unique)
        autonomous_routines.push_back(std::move(autonomous));
}

void MenuAdapter::addConfiguration(std::unique_ptr<IConfiguration>& configuration)
{
    bool unique{true};
    for (std::unique_ptr<IConfiguration>& existing_configuration : hardware_configurations)
        if (existing_configuration->getName() == configuration->getName())
            unique = false;
    if (unique)
        hardware_configurations.push_back(std::move(configuration));
}

void MenuAdapter::addProfile(std::unique_ptr<IProfile>& profile)
{
    bool unique{true};
    for (std::unique_ptr<IProfile>& existing_profile : driver_profiles)
        if (existing_profile->getName() == profile->getName())
            unique = false;
    if (unique)
        driver_profiles.push_back(std::move(profile));
}

void MenuAdapter::display()
{
    
}

bool MenuAdapter::isStarted()
{
    return false;
}

SystemConfiguration MenuAdapter::getSystemConfiguration()
{
    return SystemConfiguration{};
}
}
}