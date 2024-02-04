#ifndef WISCO_MENU_MENU_SYSTEM_HPP
#define WISCO_MENU_MENU_SYSTEM_HPP

#include <string>
#include <vector>

#include "Option.hpp"

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
 * @brief Controls a menu selection system
 * @author Nathan Sandvig
 * 
 */
class MenuSystem
{
private:
    /**
     * @brief The options available in the menu
     * 
     */
    std::vector<Option> options{};

public:
    /**
     * @brief Adds an option to the menu system
     * 
     * @param option The option being added
     */
    void addOption(Option option);

    /**
     * @brief Displays the menu
     * 
     */
    void displayMenu();

    /**
     * @brief Checks if the selection process is complete
     * 
     * @return true The selection process is complete
     * @return false The selection process is not complete
     */
    bool selectionComplete();

    /**
     * @brief Get the selection for an option
     * 
     * @param option_name 
     * @return std::string 
     */
    std::string getSelection(const std::string& option_name);
};
}
}

#endif