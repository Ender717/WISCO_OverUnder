#include "wisco/MatchControllerFactory.hpp"

namespace wisco
{
MatchController MatchControllerFactory::createMatchController()
{
    std::unique_ptr<IMenu> menu{std::make_unique<menu::MenuAdapter>()};

    std::unique_ptr<IAlliance> blue_alliance{std::make_unique<alliances::BlueAlliance>()};
    menu->addAlliance(blue_alliance);
    std::unique_ptr<IAlliance> red_alliance{std::make_unique<alliances::RedAlliance>()};
    menu->addAlliance(red_alliance);
    std::unique_ptr<IAlliance> skills_alliance{std::make_unique<alliances::SkillsAlliance>()};
    menu->addAlliance(skills_alliance);

    std::unique_ptr<IAutonomous> blue_match_autonomous{std::make_unique<autons::BlueMatchAuton>()};
    menu->addAutonomous(blue_match_autonomous);
    std::unique_ptr<IAutonomous> blue_skills_autonomous{std::make_unique<autons::BlueSkillsAuton>()};
    menu->addAutonomous(blue_skills_autonomous);
    std::unique_ptr<IAutonomous> orange_match_autonomous{std::make_unique<autons::OrangeMatchAuton>()};
    menu->addAutonomous(orange_match_autonomous);
    std::unique_ptr<IAutonomous> orange_skills_autonomous{std::make_unique<autons::OrangeSkillsAuton>()};
    menu->addAutonomous(orange_skills_autonomous);

    return MatchController{menu};
}
}