#include "MenuAdapter.hpp"
#include "wisco/IAutonomous.hpp"

namespace wisco
{
namespace menu
{  
void MenuAdapter::addAlliance(const std::shared_ptr<IAlliance>& alliance)
{
    bool unique{true};
    for (auto& existing_alliance : alliances)
        if (existing_alliance->getName() == alliance->getName())
            unique = false;
    if (unique)
        alliances.push_back(alliance);
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
    std::vector<std::string> alliance_options{};
    for (auto& alliance : alliances)
        alliance_options.push_back(alliance->getName());
    Option alliance_option{ALLIANCE_OPTION_NAME, alliance_options};

    std::vector<std::string> autonomous_options{};
    for (std::unique_ptr<IAutonomous>& autonomous : autonomous_routines)
        autonomous_options.push_back(autonomous->getName());
    Option autonomous_option{AUTONOMOUS_OPTION_NAME, autonomous_options};

    std::vector<std::string> configuration_options{};
    for (std::unique_ptr<IConfiguration>& configuration : hardware_configurations)
        configuration_options.push_back(configuration->getName());
    Option configuration_option{CONFIGURATION_OPTION_NAME, configuration_options};

    std::vector<std::string> profile_options{};
    for (std::unique_ptr<IProfile>& profile : driver_profiles)
        profile_options.push_back(profile->getName());
    Option profile_option{PROFILE_OPTION_NAME, profile_options};

    lvgl_menu.addOption(alliance_option);
    lvgl_menu.addOption(autonomous_option);
    lvgl_menu.addOption(configuration_option);
    lvgl_menu.addOption(profile_option);

    lvgl_menu.displayMenu();
}

bool MenuAdapter::isStarted()
{
    return lvgl_menu.selectionComplete();
}

SystemConfiguration MenuAdapter::getSystemConfiguration(bool read_only)
{
    SystemConfiguration system_configuration{};

    if (read_only)
        lvgl_menu.readConfiguration();

    for (auto& alliance : alliances)
    {
        if (lvgl_menu.getSelection(ALLIANCE_OPTION_NAME) == alliance->getName())
        {
            system_configuration.alliance = alliance;
            break;
        }
    }

    for (std::unique_ptr<IAutonomous>& autonomous : autonomous_routines)
    {
        if (lvgl_menu.getSelection(AUTONOMOUS_OPTION_NAME) == autonomous->getName())
        {
            system_configuration.autonomous = std::move(autonomous);
            break;
        }
    }

    for (std::unique_ptr<IConfiguration>& configuration : hardware_configurations)
    {
        if (lvgl_menu.getSelection(CONFIGURATION_OPTION_NAME) == configuration->getName())
        {
            system_configuration.configuration = std::move(configuration);
            break;
        }
    }

    for (std::unique_ptr<IProfile>& profile : driver_profiles)
    {
        if (lvgl_menu.getSelection(PROFILE_OPTION_NAME) == profile->getName())
        {
            system_configuration.profile = std::move(profile);
            break;
        }
    }

    return system_configuration;
}
}
}