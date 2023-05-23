// Inclusion guard
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

// Included external library headers
#include "liblvgl/lvgl.h"
#include "main.h"

// Included internal headers
#include "menu/MenuData.hpp"

namespace menu
{
    namespace screen
    {
        /**
         * The file name for data writing
         */
        static const std::string FILENAME = "/usd/MenuData.txt";

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
         * Draws the main menu screen
         * @param data The current menu selection data
         */
        extern void drawMainMenu(Data* data);

        /**
         * Draws the settings menu screen
         * @param data The current menu selection data
         */
        extern void drawSettingsMenu(Data* data);
    } // End namespace screen
} // End namespace menu

#endif