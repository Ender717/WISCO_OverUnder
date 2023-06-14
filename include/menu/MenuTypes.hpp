// Inclusion guard
#ifndef MENU_TYPES_HPP
#define MENU_TYPES_HPP

// Included standard libraries
#include <string>

namespace menu
{
    namespace types
    {
        /**
         * The available alliances for menu selection
         */
        enum class Alliance
        {
            BLUE,
            RED,
            SKILLS,
            COUNT
        };
        extern std::string to_string(Alliance alliance);
        extern Alliance to_alliance(std::string string);

        /**
         * The available autonomous routines for menu selection
         */
        enum class Autonomous
        {
            BLUE_DEFENSIVE,
            BLUE_OFFENSIVE,
            RED_DEFENSIVE,
            RED_OFFENSIVE,
            SKILLS_DEFENSIVE,
            SKILLS_OFFENSIVE,
            COUNT
        };
        extern std::string to_string(Autonomous autonomous);
        extern Autonomous to_autonomous(std::string string);

        /**
         * The available configurations for menu selection
         */
        enum class Configuration
        {
            BLUE,
            ORANGE,
            COUNT
        };
        extern std::string to_string(Configuration configuration);
        extern Configuration to_configuration(std::string string);

        /**
         * The available profiles for menu selection
         */
        enum class Profile
        {
            HENRY,
            JOHN,
            NATHAN,
            COUNT
        };
        extern std::string to_string(Profile profile);
        extern Profile to_profile(std::string string);

        /**
         * The available settings in menu selection
         */
        enum class Setting
        {
            ALLIANCE,
            AUTONOMOUS,
            CONFIGURATION,
            PROFILE,
            COUNT
        };
        extern std::string to_string(Setting setting);
        extern Setting to_setting(std::string string);

        /**
         * Gets the count for any enum type
         * @param t The enum type being counted
         */
        template<class t>
        int get_count() { return static_cast<int>(t::COUNT); }
    } // End namespace types
} // End namespace menu

#endif