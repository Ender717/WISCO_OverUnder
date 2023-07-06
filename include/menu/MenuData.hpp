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
    /**
     * @brief The name of the file for data storage
     *
     */
    constexpr const char* DATA_FILENAME = "/usd/menu_data.bin";

    #pragma pack(push, 1)
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
        types::Alliance alliance{types::Alliance::BLUE};

        /**
         * @brief The autonomous selection
         *
         */
        types::Autonomous autonomous{types::Autonomous::BLUE_DEFENSIVE};

        /**
         * @brief The configuration selection
         *
         */
        types::Configuration configuration{types::Configuration::BLUE};

        /**
         * @brief The profile selection
         *
         */
        types::Profile profile{types::Profile::HENRY};

        /**
         * @brief Writes the selection data to a binary file
         *
         */
        void write() const
        {
            std::ofstream output{DATA_FILENAME, std::ios::binary};
            output.write((char*)this, sizeof(Data));
            output.close();
        }

        /**
         * @brief Reads the selection data from a binary file
         *
         */
        void read()
        {
            std::ifstream input{DATA_FILENAME, std::ios::binary};
            input.read((char*)this, sizeof(Data));
            input.close();
        }
    };
    #pragma pack(pop)
} // namespace menu

#endif