#ifndef WISCO_MATCH_CONTROLLER_FACTORY
#define WISCO_MATCH_CONTROLLER_FACTORY

// Menu includes
#include "wisco/alliances/BlueAlliance.hpp"
#include "wisco/alliances/RedAlliance.hpp"
#include "wisco/alliances/SkillsAlliance.hpp"
#include "wisco/autons/BlueMatchAuton.hpp"
#include "wisco/autons/BlueSkillsAuton.hpp"
#include "wisco/autons/OrangeMatchAuton.hpp"
#include "wisco/autons/OrangeSkillsAuton.hpp"
#include "wisco/configs/BlueConfiguration.hpp"
#include "wisco/configs/OrangeConfiguration.hpp"
#include "wisco/profiles/HenryProfile.hpp"
#include "wisco/profiles/JohnProfile.hpp"
#include "wisco/menu/MenuAdapter.hpp"

#include "pros_adapters/ProsController.hpp"
#include "pros_adapters/ProsTouchScreen.hpp"
#include "pros_adapters/ProsDelayer.hpp"

#include "wisco/MatchController.hpp"

/**
 * @brief Class to create match controllers
 * @author Nathan Sandvig
 * 
 */
class MatchControllerFactory
{
public:
    /**
     * @brief Create a Match Controller
     * 
     * @return MatchController The new match controller
     */
    static wisco::MatchController createMatchController();
};

#endif