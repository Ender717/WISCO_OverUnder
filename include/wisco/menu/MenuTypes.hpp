#ifndef MENU_TYPES_HPP
#define MENU_TYPES_HPP

#include <cstdint>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Program data related to the menu system
 *
 * @author Nathan Sandvig
 */
namespace menu
{
/**
 * @brief The enumerated types used in the menu system
 *
 * @author Nathan Sandvig
 */
namespace types
{
    /**
     * @brief The alliances available for selection in the menu
     *
     */
    enum class Alliance : uint8_t
    {
        BLUE,
        RED,
        SKILLS
    };

    /**
     * @brief The string form of the Alliance enumerated values
     *
     */
    constexpr const char* ALLIANCE_STRINGS[] = { "BLUE", "RED", "SKILLS" };

    /**
     * @brief The number of Alliance values
     *
     */
    constexpr int ALLIANCE_COUNT = 3;

    /**
     * @brief The autonomous routines available for selection in the menu
     *
     */
    enum class Autonomous : uint8_t
    {
        BLUE_DEFENSIVE,
        BLUE_OFFENSIVE,
        RED_DEFENSIVE,
        RED_OFFENSIVE,
        SKILLS_DEFENSIVE,
        SKILLS_OFFENSIVE
    };

    /**
     * @brief The string form of the Autonomous enumerated values
     *
     */
    constexpr const char* AUTONOMOUS_STRINGS[] = { "BLUE DEFENSIVE", "BLUE OFFENSIVE", "RED DEFENSIVE", "RED OFFENSIVE", "SKILLS DEFENSIVE", "SKILLS OFFENSIVE" };

    /**
     * @brief The number of Autonomous values
     *
     */
    constexpr int AUTONOMOUS_COUNT = 6;

    /**
     * @brief The configurations available for selection in the menu
     *
     */
    enum class Configuration : uint8_t
    {
        BLUE,
        ORANGE
    };

    /**
     * @brief The string form of the Configuration enumerated values
     *
     */
    constexpr const char* CONFIGURATION_STRINGS[] = { "BLUE", "ORANGE" };

    /**
     * @brief The number of Configuration values
     *
     */
    constexpr int CONFIGURATION_COUNT = 2;

    /**
     * @brief The profiles available for selection in the menu
     *
     */
    enum class Profile : uint8_t
    {
        HENRY,
        JOHN,
        NATHAN
    };

    /**
     * @brief The string form of the Profile enumerated values
     *
     */
    constexpr const char* PROFILE_STRINGS[] = { "HENRY", "JOHN", "NATHAN" };

    /**
     * @brief The number of Profile values
     *
     */
    constexpr int PROFILE_COUNT = 3;

    /**
     * @brief The available settings in the menu system
     *
     */
    enum class Setting
    {
        ALLIANCE,
        AUTONOMOUS,
        CONFIGURATION,
        PROFILE
    };
} // namespace types
} // namespace menu
} // namespace wisco

#endif