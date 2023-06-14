// Inclusion guard
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

// Included external library headers
#include "liblvgl/lvgl.h"
#include "pros/rtos.h"

// Included internal headers
#include "menu/MenuData.hpp"

/**
 * @brief Program data related to the menu system
 *
 * @author Nathan Sandvig
 */
namespace menu
{
    namespace screen
    {
        /**
         * @brief The number of buttons to display on a line
         *
         */
        static constexpr int BUTTONS_PER_LINE = 2;

        /**
         * LVGL styles
         */
        static lv_style_t button_default_style;
        static lv_style_t button_pressed_style;
        static lv_style_t container_default_style;
        static lv_style_t container_pressed_style;
        static lv_style_t button_matrix_main_style;
        static lv_style_t button_matrix_items_style;

        /**
         * Available settings
         * USED FOR MEMORY ADDRESS
         */
        static const types::Setting ALLIANCE_SETTING = types::Setting::ALLIANCE;
        static const types::Setting AUTONOMOUS_SETTING = types::Setting::AUTONOMOUS;
        static const types::Setting CONFIGURATION_SETTING = types::Setting::CONFIGURATION;
        static const types::Setting PROFILE_SETTING = types::Setting::PROFILE;

        /**
         * Initializes the styles
         */
        extern void initializeStyles();

        /**
         * Event handler function for the start button in the main menu
         * @param event The event data
         */
        extern void startButtonEventHandler(lv_event_t* event);

        /**
         * Event handler function for the settings button in the main menu
         * @param event The event data
         */
        extern void settingsButtonEventHandler(lv_event_t* event);

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
        extern void drawMainMenu(Data* data);

        /**
         * Draws the settings menu screen
         * @param data The current menu selection data
         */
        extern void drawSettingsMenu(Data* data);
    } // namespace screen
} // namespace menu

#endif