#ifndef WISCO_MENU_OPTION_HPP
#define WISCO_MENU_OPTION_HPP

#include <string>
#include <vector>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Interface for the menu system
 * @author Nathan Sandvig
 *
 */
namespace menu
{
/**
 * @brief An option in the menu system
 * @author Nathan Sandvig
 * 
 */
struct Option
{
    /**
     * @brief The name of the option
     * 
     */
    std::string name{};

    /**
     * @brief The choices available for that option
     * 
     */
    std::vector<std::string> choices{};

    /**
     * @brief The index of the selected choice
     * 
     */
    int selected{};
};
}
}

#endif