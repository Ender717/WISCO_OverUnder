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

    return MatchController{menu};
}
}