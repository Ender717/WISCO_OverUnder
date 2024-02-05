#ifndef WISCO_MATCH_CONTROLLER_FACTORY
#define WISCO_MATCH_CONTROLLER_FACTORY

#include "alliances/BlueAlliance.hpp"
#include "alliances/RedAlliance.hpp"
#include "alliances/SkillsAlliance.hpp"
#include "menu/MenuAdapter.hpp"

#include "MatchController.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
class MatchControllerFactory
{
public:
    /**
     * @brief Create a Match Controller
     * 
     * @return MatchController The new match controller
     */
    static MatchController createMatchController();
};
}

#endif