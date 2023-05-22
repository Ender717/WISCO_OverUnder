// Inclusion guard
#ifndef MENU_DATA_HPP
#define MENU_DATA_HPP

// Included standard library headers
#include <fstream>

// Included external library headers
#include "pros/rtos.hpp"

// Included internal headers
#include "menu/MenuTypes.hpp"

namespace menu
{
    /**
     * This class manages the data for the menu system
     * @author Nathan Sandvig
     */
    class Data
    {
    private:
        /**
         * The mutex to keep the data thread safe
         */
        pros::Mutex mutex;

        /**
         * The selected alliance
         */
        types::Alliance alliance;

        /**
         * The selected autonomous
         */
        types::Autonomous autonomous;

        /**
         * The selected configuration
         */
        types::Configuration configuration;

        /**
         * The selected profile
         */
        types::Profile profile;

    public:
        /**
         * Default constructor
         */
        Data();

        /**
         * Copy constructor
         * @param copy The Data object being copied
         */
        Data(const Data& copy);

        /**
         * Sets the alliance selection
         * @param _alliance The new alliance selection
         */
        void setAlliance(types::Alliance _alliance);

        /**
         * Gets the alliance selection
         * @return The current alliance selection
         */
        types::Alliance getAlliance();

        /**
         * Sets the autonomous selection
         * @param _autonomous The new autonomous selection
         */
        void setAutonomous(types::Autonomous _autonomous);

        /**
         * Gets the autonomous selection
         * @return The current autonomous selection
         */
        types::Autonomous getAutonomous();

        /**
         * Sets the configuration selection
         * @param _configuration The new configuration selection
         */
        void setConfiguration(types::Configuration _configuration);

        /**
         * Gets the configuration selection
         * @return The current configuration selection
         */
        types::Configuration getConfiguration();

        /**
         * Sets the profile selection
         * @param _profile The new profile selection
         */
        void setProfile(types::Profile _profile);

        /**
         * Gets the profile selection
         * @return The current profile selection
         */
        types::Profile getProfile();

        /**
         * Reads selection data from a file
         * @param filename The name of the file
         */
        void readFile(std::string filename);

        /**
         * Writes selection data to a file
         * @param filename The name of the file
         */
        void writeFile(std::string filename);

        /**
         * Assignment operator overload
         * @param rhs The Data object on the right hand side of the operator
         * @return This Data object with the assigned values
         */
        Data& operator=(const Data& rhs);
    };
} // end namespace menu

#endif