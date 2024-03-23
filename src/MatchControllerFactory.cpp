#include "MatchControllerFactory.hpp"

wisco::MatchController MatchControllerFactory::createMatchController()
{
    // Menu creation
    std::unique_ptr<wisco::IMenu> lvgl_menu{std::make_unique<wisco::menu::MenuAdapter>()};
    std::unique_ptr<wisco::IAlliance> blue_alliance{std::make_unique<wisco::alliances::BlueAlliance>()};
    lvgl_menu->addAlliance(blue_alliance);
    std::unique_ptr<wisco::IAlliance> red_alliance{std::make_unique<wisco::alliances::RedAlliance>()};
    lvgl_menu->addAlliance(red_alliance);
    std::unique_ptr<wisco::IAlliance> skills_alliance{std::make_unique<wisco::alliances::SkillsAlliance>()};
    lvgl_menu->addAlliance(skills_alliance);
    std::unique_ptr<wisco::IAutonomous> blue_match_autonomous{std::make_unique<wisco::autons::BlueMatchAuton>()};
    lvgl_menu->addAutonomous(blue_match_autonomous);
    std::unique_ptr<wisco::IAutonomous> blue_skills_autonomous{std::make_unique<wisco::autons::BlueSkillsAuton>()};
    lvgl_menu->addAutonomous(blue_skills_autonomous);
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

    // Other creation
    std::unique_ptr<pros::Controller> pros_controller_controller{std::make_unique<pros::Controller>(pros::E_CONTROLLER_MASTER)};
    std::shared_ptr<wisco::user::IController> pros_controller{std::make_unique<pros_adapters::ProsController>(pros_controller_controller)};
    std::shared_ptr<wisco::io::ITouchScreen> pros_touch_screen{std::make_shared<pros_adapters::ProsTouchScreen>(pros::E_TEXT_LARGE)};
    std::shared_ptr<wisco::rtos::IDelayer> pros_delayer{std::make_shared<pros_adapters::ProsDelayer>()};
    return wisco::MatchController{lvgl_menu, pros_touch_screen, pros_delayer, pros_controller};
}