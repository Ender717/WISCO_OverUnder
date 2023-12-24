#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "liblvgl/lvgl.h"

#include "wisco/menu/MenuData.hpp"

/**
 * @brief Program data related to the menu system
 *
 * @author Nathan Sandvig
 */
namespace menu
{
/**
 * @brief Screen management for the menu system
 *
 * @author Nathan Sandvig
 */
namespace screen
{
    /**
     * @brief The number of buttons to display on a line
     *
     */
    constexpr int BUTTONS_PER_LINE = 2;

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
     * Initializes the styles
     */
    extern void initializeStyles();

    /**
     * Event handler function for the back button in the settings menu
     * @param event The event data
     */
    extern void settingsBackButtonEventHandler(lv_event_t* event);

    /**
     * Event handler function for the button matrices in settings
     * @param event The event data
     */
    extern void settingsButtonMatrixEventHandler(lv_event_t* event);

    /**
     * Draws the main menu screen
     * @param data The current menu selection data
     */
    extern void drawMainMenu(Data* data = nullptr);

    /**
     * Draws the settings menu screen
     * @param data The current menu selection data
     */
    extern void drawSettingsMenu(Data* data);
} // namespace screen
} // namespace menu

#endif