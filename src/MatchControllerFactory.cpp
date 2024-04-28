#include "MatchControllerFactory.hpp"

wisco::MatchController MatchControllerFactory::createMatchController()
{
    // Menu creation
    std::unique_ptr<wisco::IMenu> lvgl_menu{std::make_unique<wisco::menu::MenuAdapter>()};
    std::shared_ptr<wisco::IAlliance> blue_alliance{std::make_shared<wisco::alliances::BlueAlliance>()};
    lvgl_menu->addAlliance(blue_alliance);
    std::shared_ptr<wisco::IAlliance> red_alliance{std::make_shared<wisco::alliances::RedAlliance>()};
    lvgl_menu->addAlliance(red_alliance);
    std::shared_ptr<wisco::IAlliance> skills_alliance{std::make_shared<wisco::alliances::SkillsAlliance>()};
    lvgl_menu->addAlliance(skills_alliance);
    std::unique_ptr<wisco::IAutonomous> block_autonomous{std::make_unique<wisco::autons::BlockAuton>()};
    lvgl_menu->addAutonomous(block_autonomous);
    std::unique_ptr<wisco::IAutonomous> blue_elim_autonomous{std::make_unique<wisco::autons::BlueElimAuton>()};
    lvgl_menu->addAutonomous(blue_elim_autonomous);
    std::unique_ptr<wisco::IAutonomous> blue_match_autonomous{std::make_unique<wisco::autons::BlueMatchAuton>()};
    lvgl_menu->addAutonomous(blue_match_autonomous);
    std::unique_ptr<wisco::IAutonomous> blue_skills_autonomous{std::make_unique<wisco::autons::BlueSkillsAuton>()};
    lvgl_menu->addAutonomous(blue_skills_autonomous);
    std::unique_ptr<wisco::IAutonomous> orange_elim_autonomous{std::make_unique<wisco::autons::OrangeElimAuton>()};
    lvgl_menu->addAutonomous(orange_elim_autonomous);
    std::unique_ptr<wisco::IAutonomous> orange_match_autonomous{std::make_unique<wisco::autons::OrangeMatchAuton>()};
    lvgl_menu->addAutonomous(orange_match_autonomous);
    std::unique_ptr<wisco::IAutonomous> orange_skills_autonomous{std::make_unique<wisco::autons::OrangeSkillsAuton>()};
    lvgl_menu->addAutonomous(orange_skills_autonomous);
    std::unique_ptr<wisco::IConfiguration> blue_configuration{std::make_unique<wisco::configs::BlueConfiguration>()};
    lvgl_menu->addConfiguration(blue_configuration);
    std::unique_ptr<wisco::IConfiguration> orange_configuration{std::make_unique<wisco::configs::OrangeConfiguration>()};
    lvgl_menu->addConfiguration(orange_configuration);
    std::unique_ptr<wisco::IProfile> henry_profile{std::make_unique<wisco::profiles::HenryProfile>()};
    lvgl_menu->addProfile(henry_profile);
    std::unique_ptr<wisco::IProfile> john_profile{std::make_unique<wisco::profiles::JohnProfile>()};
    lvgl_menu->addProfile(john_profile);

    // RTOS creation
    std::shared_ptr<wisco::rtos::IClock> pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};

    return wisco::MatchController{lvgl_menu, pros_clock, pros_delayer};
}