#include "MatchControllerFactory.hpp"

wisco::MatchController MatchControllerFactory::createMatchController()
{
    std::unique_ptr<wisco::IMenu> menu{std::make_unique<wisco::menu::MenuAdapter>()};

    std::unique_ptr<wisco::IAlliance> blue_alliance{std::make_unique<wisco::alliances::BlueAlliance>()};
    menu->addAlliance(blue_alliance);
    std::unique_ptr<wisco::IAlliance> red_alliance{std::make_unique<wisco::alliances::RedAlliance>()};
    menu->addAlliance(red_alliance);
    std::unique_ptr<wisco::IAlliance> skills_alliance{std::make_unique<wisco::alliances::SkillsAlliance>()};
    menu->addAlliance(skills_alliance);

    std::unique_ptr<wisco::IAutonomous> blue_match_autonomous{std::make_unique<wisco::autons::BlueMatchAuton>()};
    menu->addAutonomous(blue_match_autonomous);
    std::unique_ptr<wisco::IAutonomous> blue_skills_autonomous{std::make_unique<wisco::autons::BlueSkillsAuton>()};
    menu->addAutonomous(blue_skills_autonomous);
    std::unique_ptr<wisco::IAutonomous> orange_match_autonomous{std::make_unique<wisco::autons::OrangeMatchAuton>()};
    menu->addAutonomous(orange_match_autonomous);
    std::unique_ptr<wisco::IAutonomous> orange_skills_autonomous{std::make_unique<wisco::autons::OrangeSkillsAuton>()};
    menu->addAutonomous(orange_skills_autonomous);

    std::unique_ptr<wisco::IConfiguration> blue_configuration{std::make_unique<wisco::configs::BlueConfiguration>()};
    menu->addConfiguration(blue_configuration);
    std::unique_ptr<wisco::IConfiguration> orange_configuration{std::make_unique<wisco::configs::OrangeConfiguration>()};
    menu->addConfiguration(orange_configuration);

    std::unique_ptr<wisco::IProfile> henry_profile{std::make_unique<wisco::profiles::HenryProfile>()};
    menu->addProfile(henry_profile);
    std::unique_ptr<wisco::IProfile> john_profile{std::make_unique<wisco::profiles::JohnProfile>()};
    menu->addProfile(john_profile);

    return wisco::MatchController{menu};
}