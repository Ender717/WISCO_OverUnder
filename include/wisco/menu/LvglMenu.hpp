#ifndef WISCO_MENU_LVGL_MENU_HPP
#define WISCO_MENU_LVGL_MENU_HPP

#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "liblvgl/lvgl.h"

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
 * @brief Event handler function for the start button
 * 
 * @param event The event data
 */
extern void startButtonEventHandler(lv_event_t* event);

/**
 * @brief Event handler function for the settings button
 * 
 * @param event The event data
 */
extern void settingsButtonEventHandler(lv_event_t* event);

/**
 * @brief Event handler function for the back button in the settings menu
 * 
 * @param event The event data
 */
extern void settingsBackButtonEventHandler(lv_event_t* event);

/**
 * @brief Event handler function for the button matrices in settings
 * 
 * @param event The event data
 */
extern void settingsButtonMatrixEventHandler(lv_event_t* event);

/**
 * @brief Controls an lvgl-based menu selection system
 * @author Nathan Sandvig
 * 
 */
class LvglMenu
{
private:
    /**
     * @brief The path of the file that stores the configuration
     * 
     */
    static constexpr char CONFIGURATION_FILE[]{"/usd/system/menu_data.txt"};

    /**
     * @brief The width of a column on the status page
     * 
     */
    static constexpr int COLUMN_WIDTH{16};

    /**
     * @brief The number of buttons to display on a line
     *
     */
    static constexpr int BUTTONS_PER_LINE{2};

    /**
     * @brief The default style for a button
     *
     */
    static lv_style_t button_default_style;

    /**
     * @brief The pressed style for a button
     *
     */
    static lv_style_t button_pressed_style;

    /**
     * @brief The default style for a container
     *
     */
    static lv_style_t container_default_style;

    /**
     * @brief The pressed style for a container
     *
     */
    static lv_style_t container_pressed_style;

    /**
     * @brief The background style for a button matrix
     *
     */
    static lv_style_t button_matrix_main_style;

    /**
     * @brief The button style for a button matrix
     *
     */
    static lv_style_t button_matrix_items_style;

    /**
     * @brief Whether or not the styles have been initialized
     * 
     */
    static bool styles_initialized;

    /**
     * @brief The options available in the menu
     * 
     */
    std::vector<Option> options{};

    /**
     * @brief Whether or not selection is complete
     * 
     */
    bool complete{false};

    /**
     * @brief Initializes the styles for the class
     * 
     */
    static void initializeStyles();

public:
    /**
     * @brief Adds an option to the menu system
     * 
     * @param option The option being added
     */
    void addOption(Option option);

    /**
     * @brief Removes an option from the menu system
     * 
     * @param option_name The name of the option to remove
     */
    void removeOption(const std::string& option_name);

    /**
     * @brief Draws the main menu screen
     * 
     */
    void drawMainMenu();

    /**
     * @brief Draws the settings menu screen
     * 
     */
    void drawSettingsMenu();

    /**
     * @brief Set the menu selection to complete
     * 
     */
    void setComplete();

    /**
     * @brief Reads the configuration of the menu
     * 
     */
    void readConfiguration();

    /**
     * @brief Writes the configuration of the menu
     * 
     */
    void writeConfiguration();

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
     * @param option_name The name of the option
     * @return std::string The selection for that option
     */
    std::string getSelection(const std::string& option_name);
};
}
}

#endif