// Included header
#include "menu/MenuTypes.hpp"

namespace menu
{
    namespace types
    {
        std::string to_string(Alliance alliance)
        {
            switch (alliance)
            {
                case Alliance::BLUE: { return "BLUE"; }
                case Alliance::RED: { return "RED"; }
                case Alliance::SKILLS: { return "SKILLS"; }
                default: { return "INVALID ALLIANCE"; }
            }
        }

        std::string to_string(Autonomous autonomous)
        {
            switch (autonomous)
            {
                case Autonomous::BLUE_DEFENSIVE: { return "BLUE DEFENSIVE"; }
                case Autonomous::BLUE_OFFENSIVE: { return "BLUE OFFENSIVE"; }
                case Autonomous::RED_DEFENSIVE: { return "RED DEFENSIVE"; }
                case Autonomous::RED_OFFENSIVE: { return "RED OFFENSIVE"; }
                case Autonomous::SKILLS_DEFENSIVE: { return "SKILLS DEFENSIVE"; }
                case Autonomous::SKILLS_OFFENSIVE: { return "SKILLS OFFENSIVE"; }
                default: { return "INVALID AUTONOMOUS"; }
            }
        }

        std::string to_string(Configuration configuration)
        {
            switch (configuration)
            {
                case Configuration::BLUE: { return "BLUE"; }
                case Configuration::ORANGE: { return "ORANGE"; }
                default: { return "INVALID CONFIGURATION"; }
            }
        }

        std::string to_string(Profile profile)
        {
            switch (profile)
            {
                case Profile::HENRY: { return "HENRY"; }
                case Profile::JOHN: { return "JOHN"; }
                case Profile::NATHAN: { return "NATHAN"; }
                default: { return "INVALID PROFILE"; }
            }
        }
    } // End namespace types
} // End namespace menu