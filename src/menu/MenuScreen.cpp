// Included header
#include "menu/MenuScreen.hpp"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/extra/layouts/flex/lv_flex.h"
#include "liblvgl/extra/widgets/menu/lv_menu.h"
#include "liblvgl/font/lv_font.h"

namespace menu
{
    namespace screen
    {
        void initializeStyles()
        {
            #ifndef MENU_SCREEN_STYLES
            #define MENU_SCREEN_STYLES
            // Create the default button style
            lv_style_init(&button_default_style);
            lv_style_set_radius(&button_default_style, 5);
            lv_style_set_bg_opa(&button_default_style, LV_OPA_100);
            lv_style_set_bg_color(&button_default_style, lv_color_make(192, 192, 192));
            lv_style_set_bg_grad_color(&button_default_style, lv_color_darken(lv_color_make(192, 192, 192), 8));
            lv_style_set_border_opa(&button_default_style, LV_OPA_100);
            lv_style_set_border_width(&button_default_style, 2);
            lv_style_set_border_color(&button_default_style, lv_color_black());
            lv_style_set_text_color(&button_default_style, lv_color_black());
            lv_style_set_text_font(&button_default_style, &lv_font_montserrat_20);

            // Create the pressed button style
            lv_style_init(&button_pressed_style);
            lv_style_set_radius(&button_pressed_style, 5);
            lv_style_set_bg_opa(&button_pressed_style, LV_OPA_100);
            lv_style_set_translate_y(&button_pressed_style, 3);
            lv_style_set_shadow_ofs_y(&button_pressed_style, 3);
            lv_style_set_bg_color(&button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 16));
            lv_style_set_bg_grad_color(&button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 24));
            lv_style_set_border_opa(&button_pressed_style, LV_OPA_100);
            lv_style_set_border_width(&button_pressed_style, 2);
            lv_style_set_border_color(&button_pressed_style, lv_color_black());
            lv_style_set_text_color(&button_pressed_style, lv_color_black());
            lv_style_set_text_font(&button_pressed_style, &lv_font_montserrat_20);

            // Create the default container style
            lv_style_init(&container_default_style);
            lv_style_set_radius(&container_default_style, 0);
            lv_style_set_bg_opa(&container_default_style, LV_OPA_100);
            lv_style_set_bg_color(&container_default_style, lv_color_make(0, 104, 179));
            lv_style_set_border_width(&container_pressed_style, 0);
            lv_style_set_text_color(&container_default_style, lv_color_white());
            lv_style_set_text_align(&container_default_style, LV_TEXT_ALIGN_CENTER);
            lv_style_set_pad_ver(&container_default_style, 10);

            // Create the pressed container style
            lv_style_init(&container_pressed_style);
            lv_style_set_radius(&container_pressed_style, 0);
            lv_style_set_bg_opa(&container_pressed_style, LV_OPA_100);
            lv_style_set_bg_color(&container_pressed_style, lv_color_make(244, 115, 33));
            lv_style_set_border_width(&container_pressed_style, 0);
            lv_style_set_text_color(&container_pressed_style, lv_color_black());
            lv_style_set_text_align(&container_pressed_style, LV_TEXT_ALIGN_CENTER);
            lv_style_set_pad_ver(&container_default_style, 10);
            #endif
        }

        void startButtonEventHandler(lv_event_t *event)
        {
            lv_obj_clean(lv_scr_act());
            Data* data = (Data*)lv_event_get_user_data(event);
            data->writeFile(FILENAME);
        }

        void settingsButtonEventHandler(lv_event_t *event)
        {
            lv_obj_clean(lv_scr_act());
            Data* data = (Data*)lv_event_get_user_data(event);
            drawSettingsMenu(data);
        }

        void settingsBackButtonEventHandler(lv_event_t* event)
        {
            lv_obj_t * obj = lv_event_get_target(event);
            void** user_data = (void**)lv_event_get_user_data(event);
            lv_obj_t * menu = (lv_obj_t*)(user_data[0]);
            Data* data = (Data*)(user_data[1]);

            if(obj == lv_menu_get_sidebar_header_back_btn(menu))
            {
                lv_obj_clean(lv_scr_act());
                drawMainMenu(data);
            }
        }

        void drawMainMenu(Data* data)
        {
            initializeStyles();

            // Verify data
            if (data == nullptr)
            {
                data = new Data;
                data->readFile(FILENAME);
            }

            // Set the background color to light blue
            lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(173, 205, 234), 0);
            lv_obj_refresh_style(lv_scr_act(), LV_PART_MAIN, LV_STYLE_BG_COLOR);
            pros::delay(50);

            // Create the big line at the bottom
            static lv_point_t big_line_points[] = { {0, 205}, {480, 205} };
            static lv_style_t big_line_style;
            lv_style_init(&big_line_style);
            lv_style_set_line_width(&big_line_style, 55);
            lv_style_set_line_color(&big_line_style, lv_color_make(0, 104, 179));
            lv_style_set_line_rounded(&big_line_style, false);
            lv_obj_t* big_line = lv_line_create(lv_scr_act());
            lv_line_set_points(big_line, big_line_points, 2);
            lv_obj_add_style(big_line, &big_line_style, 0);

            // Create the stripe on the line at the bottom
            static lv_point_t stripe_line_points[] = { {0, 220}, {480, 220} };
            static lv_style_t stripe_line_style;
            lv_style_init(&stripe_line_style);
            lv_style_set_line_width(&stripe_line_style, 13);
            lv_style_set_line_color(&stripe_line_style, lv_color_make(244, 115, 33));
            lv_style_set_line_rounded(&stripe_line_style, false);
            lv_obj_t* stripe_line = lv_line_create(lv_scr_act());
            lv_line_set_points(stripe_line, stripe_line_points, 2);
            lv_obj_add_style(stripe_line, &stripe_line_style, 0);

            // Create the left diagonal line
            static lv_point_t left_diagonal_line_points[] = { {320, 190}, {510, 0} };
            static lv_style_t left_diagonal_line_style;
            lv_style_init(&left_diagonal_line_style);
            lv_style_set_line_width(&left_diagonal_line_style, 23);
            lv_style_set_line_color(&left_diagonal_line_style, lv_color_make(0, 104, 179));
            lv_style_set_line_rounded(&left_diagonal_line_style, false);
            lv_obj_t* left_diagonal_line = lv_line_create(lv_scr_act());
            lv_line_set_points(left_diagonal_line, left_diagonal_line_points, 2);
            lv_obj_add_style(left_diagonal_line, &left_diagonal_line_style, 0);

            // Create the right diagonal line
            static lv_point_t right_diagonal_line_points[] = { {370, 190}, {560, 0} };
            static lv_style_t right_diagonal_line_style;
            lv_style_init(&right_diagonal_line_style);
            lv_style_set_line_width(&right_diagonal_line_style, 23);
            lv_style_set_line_color(&right_diagonal_line_style, lv_color_make(0, 104, 179));
            lv_style_set_line_rounded(&right_diagonal_line_style, false);
            lv_obj_t* right_diagonal_line = lv_line_create(lv_scr_act());
            lv_line_set_points(right_diagonal_line, right_diagonal_line_points, 2);
            lv_obj_add_style(right_diagonal_line, &right_diagonal_line_style, 0);

            // Add the WISCOBOTS text
            static lv_style_t team_name_label_style;
            lv_style_init(&team_name_label_style);
            #if USE_FONT_BLADERUNNER_30
            lv_style_set_text_font(&team_name_label_style, &font_bladerunner_30);
            #else
            lv_style_set_text_font(&team_name_label_style, &pros_font_dejavu_mono_30);
            #endif
            lv_style_set_text_color(&team_name_label_style, lv_color_make(244, 115, 33));
            lv_obj_t* team_name_label = lv_label_create(lv_scr_act());
            lv_obj_add_style(team_name_label, &team_name_label_style, 0);
            lv_label_set_text(team_name_label, "wiscobots");
            lv_obj_align(team_name_label, LV_ALIGN_BOTTOM_MID, 0, -26);

            // Add the status label
            static lv_style_t status_label_style;
            lv_style_init(&status_label_style);
            lv_style_set_border_width(&status_label_style, 2);
            lv_style_set_pad_all(&status_label_style, 3);
            lv_style_set_border_color(&status_label_style, lv_color_make(0, 104, 179));
            lv_obj_t* status_label = lv_label_create(lv_scr_act());
            lv_obj_add_style(status_label, &status_label_style, 0);
            lv_label_set_text_fmt(status_label, "ALLIANCE: %s\nAUTONOMOUS: %s\nCONFIGURATION: %s\nPROFILE: %s",
                                                menu::types::to_string(data->getAlliance()).c_str(),
                                                menu::types::to_string(data->getAutonomous()).c_str(),
                                                menu::types::to_string(data->getConfiguration()).c_str(),
                                                menu::types::to_string(data->getProfile()).c_str());
            lv_obj_align(status_label, LV_ALIGN_TOP_LEFT, 20, 100);

            // Add the start button
            lv_obj_t * start_button = lv_btn_create(lv_scr_act());
            lv_obj_remove_style_all(start_button);
            lv_obj_add_style(start_button, &button_default_style, 0);
            lv_obj_add_style(start_button, &button_pressed_style, LV_STATE_PRESSED);
            lv_obj_set_size(start_button, 160, 70);
            lv_obj_align(start_button, LV_ALIGN_TOP_LEFT, 20, 15);
            lv_obj_add_event_cb(start_button, startButtonEventHandler, LV_EVENT_CLICKED, data);
            lv_obj_t * start_button_label = lv_label_create(start_button);
            lv_label_set_text(start_button_label, "START");
            lv_obj_center(start_button_label);

            // Add the settings button
            lv_obj_t * settings_button = lv_btn_create(lv_scr_act());
            lv_obj_remove_style_all(settings_button);
            lv_obj_add_style(settings_button, &button_default_style, 0);
            lv_obj_add_style(settings_button, &button_pressed_style, LV_STATE_PRESSED);
            lv_obj_set_size(settings_button, 70, 70);
            lv_obj_align(settings_button, LV_ALIGN_TOP_LEFT, 190, 15);
            lv_obj_add_event_cb(settings_button, settingsButtonEventHandler, LV_EVENT_CLICKED, data);
            lv_obj_t * settings_button_label = lv_label_create(settings_button);
            lv_label_set_text(settings_button_label, LV_SYMBOL_SETTINGS);
            lv_obj_center(settings_button_label);
        }

        void drawSettingsMenu(Data* data)
        {
            initializeStyles();

            // Verify data
            if (data == nullptr)
            {
                data = new Data;
                data->readFile(FILENAME);
            }

            // Create the menu
            lv_obj_t * menu = lv_menu_create(lv_scr_act());
            lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
            lv_obj_set_style_bg_color(menu, lv_color_make(0, 104, 179), 0);
            lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
            lv_obj_center(menu);

            // Create the alliance settings page
            lv_obj_t * alliance_page = lv_menu_page_create(menu, NULL);
            lv_obj_set_style_pad_hor(alliance_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
            lv_menu_separator_create(alliance_page);
            lv_obj_t* alliance_page_section = lv_menu_section_create(alliance_page);
            lv_obj_set_style_bg_color(alliance_page_section, lv_color_make(173, 205, 234), 0);
            lv_obj_set_size(alliance_page_section, 300, 220);

            // Create the autonomous settings page
            lv_obj_t * autonomous_page = lv_menu_page_create(menu, NULL);
            lv_obj_set_style_pad_hor(autonomous_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
            lv_menu_separator_create(autonomous_page);
            lv_obj_t* autonomous_page_section = lv_menu_section_create(autonomous_page);
            lv_obj_set_style_bg_color(autonomous_page_section, lv_color_make(173, 205, 234), 0);
            lv_obj_set_size(autonomous_page_section, 300, 220);

            // Create the configuration settings page
            lv_obj_t * configuration_page = lv_menu_page_create(menu, NULL);
            lv_obj_set_style_pad_hor(configuration_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
            lv_menu_separator_create(configuration_page);
            lv_obj_t* configuration_page_section = lv_menu_section_create(configuration_page);
            lv_obj_set_style_bg_color(configuration_page_section, lv_color_make(173, 205, 234), 0);
            lv_obj_set_size(configuration_page_section, 300, 220);

            // Create the profile settings page
            lv_obj_t * profile_page = lv_menu_page_create(menu, NULL);
            lv_obj_set_style_pad_hor(profile_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
            lv_menu_separator_create(profile_page);
            lv_obj_t* profile_page_section = lv_menu_section_create(profile_page);
            lv_obj_set_style_bg_color(profile_page_section, lv_color_make(173, 205, 234), 0);
            lv_obj_set_size(profile_page_section, 300, 220);

            // Create a root page
            lv_obj_t* root_page = lv_menu_page_create(menu, NULL);
            lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
            lv_obj_t* section = lv_menu_section_create(root_page);
            lv_menu_set_sidebar_page(menu, root_page);

            // Create the back button
            lv_obj_t * back_btn = lv_menu_get_sidebar_header_back_btn(menu);
            lv_obj_remove_style_all(back_btn);
            lv_obj_add_style(back_btn, &button_default_style, 0);
            lv_obj_add_style(back_btn, &button_pressed_style, LV_STATE_PRESSED);
            lv_obj_set_style_text_font(back_btn, &lv_font_montserrat_14, 0);
            lv_obj_set_style_text_font(back_btn, &lv_font_montserrat_14, LV_STATE_PRESSED);
            lv_obj_set_style_pad_all(back_btn, 3, 0);
            lv_obj_set_style_pad_all(back_btn, 3, LV_STATE_PRESSED);
            lv_obj_set_style_translate_y(back_btn, 0, LV_STATE_PRESSED);
            lv_obj_set_style_shadow_ofs_y(back_btn, 0, LV_STATE_PRESSED);
            lv_obj_t * back_btn_label = lv_label_create(back_btn);
            lv_label_set_text(back_btn_label, "   Back");
            static void* user_data[] = { nullptr, nullptr };
            user_data[0] = menu;
            user_data[1] = data;
            lv_obj_add_event_cb(menu, settingsBackButtonEventHandler, LV_EVENT_CLICKED, user_data);

            // Add a container for the alliance menu
            lv_obj_t* alliance_menu_container = lv_menu_cont_create(section);
            lv_obj_remove_style_all(alliance_menu_container);
            lv_obj_add_style(alliance_menu_container, &container_default_style, 0);
            lv_obj_add_style(alliance_menu_container, &container_pressed_style, LV_STATE_CHECKED);
            lv_obj_t* alliance_menu_container_label = lv_label_create(alliance_menu_container);
            lv_label_set_text(alliance_menu_container_label, "Alliance");
            lv_menu_set_load_page_event(menu, alliance_menu_container, alliance_page);

            // Add a container for the autonomous menu
            lv_obj_t* autonomous_menu_container = lv_menu_cont_create(section);
            lv_obj_remove_style_all(autonomous_menu_container);
            lv_obj_add_style(autonomous_menu_container, &container_default_style, 0);
            lv_obj_add_style(autonomous_menu_container, &container_pressed_style, LV_STATE_CHECKED);
            lv_obj_t* autonomous_menu_container_label = lv_label_create(autonomous_menu_container);
            lv_label_set_text(autonomous_menu_container_label, "Auton");
            lv_menu_set_load_page_event(menu, autonomous_menu_container, autonomous_page);

            // Add a container for the configuration menu
            lv_obj_t* configuration_menu_container = lv_menu_cont_create(section);
            lv_obj_remove_style_all(configuration_menu_container);
            lv_obj_add_style(configuration_menu_container, &container_default_style, 0);
            lv_obj_add_style(configuration_menu_container, &container_pressed_style, LV_STATE_CHECKED);
            lv_obj_t* configuration_menu_container_label = lv_label_create(configuration_menu_container);
            lv_label_set_text(configuration_menu_container_label, "Config");
            lv_menu_set_load_page_event(menu, configuration_menu_container, configuration_page);

            // Add a container for the profile menu
            lv_obj_t* profile_menu_container = lv_menu_cont_create(section);
            lv_obj_remove_style_all(profile_menu_container);
            lv_obj_add_style(profile_menu_container, &container_default_style, 0);
            lv_obj_add_style(profile_menu_container, &container_pressed_style, LV_STATE_CHECKED);
            lv_obj_t* profile_menu_container_label = lv_label_create(profile_menu_container);
            lv_label_set_text(profile_menu_container_label, "Profile");
            lv_menu_set_load_page_event(menu, profile_menu_container, profile_page);

            lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
        }
    } // End namespace screen
} // End namespace menu