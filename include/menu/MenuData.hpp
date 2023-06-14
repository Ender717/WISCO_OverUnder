#ifndef MENU_DATA_HPP
#define MENU_DATA_HPP

#include <fstream>

#include "menu/MenuTypes.hpp"

/**
 * @brief Program data related to the menu system
 *
 * @author Nathan Sandvig
 */
namespace menu
{
    #pragma pack(push)
    #pragma pack(1)
    /**
     * @brief Holds the data for menu selection in a packed format
     *
     * @author Nathan Sandvig
     */
    struct Data
    {
        /**
         * @brief The alliance selection
         *
         */
        types::Alliance alliance;

        /**
         * @brief The autonomous selection
         *
         */
        types::Autonomous autonomous;

        /**
         * @brief The configuration selection
         *
         */
        types::Configuration configuration;

        /**
         * @brief The profile selection
         *
         */
        types::Profile profile;

        /**
         * @brief Writes the selection data to a binary file
         *
         */
        void write() const
        {
            std::ofstream output{"menu_data.bin", std::ios::binary};
            output.write((char*)this, sizeof(Data));
            output.close();
        }

        /**
         * @brief Reads the selection data from a binary file
         *
         */
        void read()
        {
            std::ifstream input{"menu_data.bin", std::ios::binary};
            input.read((char*)this, sizeof(Data));
            input.close();
        }
    };
    #pragma pack(pop)
} // namespace menu

#endif