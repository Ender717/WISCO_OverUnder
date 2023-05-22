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

        Alliance to_alliance(std::string string)
        {
            Alliance alliance = Alliance::COUNT;
            for (int i = 0; i < types::get_count<types::Alliance>(); i++)
                if (string == types::to_string(static_cast<types::Alliance>(i)))
                    alliance = static_cast<types::Alliance>(i);
            return alliance;
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

        Autonomous to_autonomous(std::string string)
        {
            Autonomous autonomous = Autonomous::COUNT;
            for (int i = 0; i < types::get_count<types::Autonomous>(); i++)
                if (string == types::to_string(static_cast<types::Autonomous>(i)))
                    autonomous = static_cast<types::Autonomous>(i);
            return autonomous;
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

        Configuration to_configuration(std::string string)
        {
            Configuration configuration = Configuration::COUNT;
            for (int i = 0; i < types::get_count<types::Configuration>(); i++)
                if (string == types::to_string(static_cast<types::Configuration>(i)))
                    configuration = static_cast<types::Configuration>(i);
            return configuration;
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

        Profile to_profile(std::string string)
        {
            Profile profile = Profile::COUNT;
            for (int i = 0; i < types::get_count<types::Profile>(); i++)
                if (string == types::to_string(static_cast<types::Profile>(i)))
                    profile = static_cast<types::Profile>(i);
            return profile;
        }
    } // End namespace types
} // End namespace menu