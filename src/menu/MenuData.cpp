// Included header
#include "menu/MenuData.hpp"
#include "MenuTypes.hpp"

namespace menu
{
    Data::Data()
    {
        alliance = types::Alliance::COUNT;
        autonomous = types::Autonomous::COUNT;
        configuration = types::Configuration::COUNT;
        profile = types::Profile::COUNT;
    }

    Data::Data(const Data& copy)
    {
        alliance = copy.alliance;
        autonomous = copy.autonomous;
        configuration = copy.configuration;
        profile = copy.profile;
    }

    void Data::setAlliance(types::Alliance _alliance)
    {
        mutex.take();
        alliance = _alliance;
        mutex.give();
    }

    types::Alliance Data::getAlliance()
    {
        mutex.take();
        types::Alliance result = alliance;
        mutex.give();
        return result;
    }

    void Data::setAutonomous(types::Autonomous _autonomous)
    {
        mutex.take();
        autonomous = _autonomous;
        mutex.give();
    }

    types::Autonomous Data::getAutonomous()
    {
        mutex.take();
        types::Autonomous result = autonomous;
        mutex.give();
        return result;
    }

    void Data::setConfiguration(types::Configuration _configuration)
    {
        mutex.take();
        configuration = _configuration;
        mutex.give();
    }

    types::Configuration Data::getConfiguration()
    {
        mutex.take();
        types::Configuration result = configuration;
        mutex.give();
        return result;
    }

    void Data::setProfile(types::Profile _profile)
    {
        mutex.take();
        profile = _profile;
        mutex.give();
    }

    types::Profile Data::getProfile()
    {
        mutex.take();
        types::Profile result = profile;
        mutex.give();
        return result;
    }

    void Data::readFile(std::string filename)
    {
        // Open the file
        std::ifstream file(filename);
        if (file.fail())
            return;
        std::string input;

        mutex.take();

        // Read the alliance
        std::getline(file, input);
        alliance = types::to_alliance(input);

        // Read the autonomous
        std::getline(file, input);
        autonomous = types::to_autonomous(input);

        // Read the configuration
        std::getline(file, input);
        configuration = types::to_configuration(input);

        // Read the profile
        std::getline(file, input);
        profile = types::to_profile(input);

        mutex.give();

        file.close();
    }

    void Data::writeFile(std::string filename)
    {
        // Open the file
        std::ofstream file(filename);
        if (file.fail())
            return;

        mutex.take();

        // Output the data
        file << types::to_string(alliance) << '\n';
        file << types::to_string(autonomous) << '\n';
        file << types::to_string(configuration) << '\n';
        file << types::to_string(profile) << '\n';

        mutex.give();

        file.close();
    }

    Data& Data::operator=(const Data& rhs)
    {
        mutex.take();
        alliance = rhs.alliance;
        autonomous = rhs.autonomous;
        configuration = rhs.configuration;
        profile = rhs.profile;
        mutex.take();
        return *this;
    }
} // End namespace menu