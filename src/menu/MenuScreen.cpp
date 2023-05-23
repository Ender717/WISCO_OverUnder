// Included header
#include "menu/MenuScreen.hpp"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/font/lv_font.h"

namespace menu
{
    namespace screen
    {
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

            if(lv_menu_back_btn_is_root(menu, obj))
            {
                lv_obj_clean(lv_scr_act());
                drawMainMenu(data);
            }
        }

        void drawMainMenu(Data* data)
        {
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
            static lv_style_t start_button_default_style;
            lv_style_init(&start_button_default_style);
            lv_style_set_radius(&start_button_default_style, 5);
            lv_style_set_bg_opa(&start_button_default_style, LV_OPA_100);
            lv_style_set_bg_color(&start_button_default_style, lv_color_make(192, 192, 192));
            lv_style_set_bg_grad_color(&start_button_default_style, lv_color_darken(lv_color_make(192, 192, 192), 8));
            lv_style_set_border_opa(&start_button_default_style, LV_OPA_100);
            lv_style_set_border_width(&start_button_default_style, 2);
            lv_style_set_border_color(&start_button_default_style, lv_color_black());
            lv_style_set_text_color(&start_button_default_style, lv_color_black());
            lv_style_set_text_font(&start_button_default_style, &pros_font_dejavu_mono_18);
            static lv_style_t start_button_pressed_style;
            lv_style_init(&start_button_pressed_style);
            lv_style_set_radius(&start_button_pressed_style, 5);
            lv_style_set_bg_opa(&start_button_pressed_style, LV_OPA_100);
            lv_style_set_translate_y(&start_button_pressed_style, 3);
            lv_style_set_shadow_ofs_y(&start_button_pressed_style, 3);
            lv_style_set_bg_color(&start_button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 16));
            lv_style_set_bg_grad_color(&start_button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 24));
            lv_style_set_border_opa(&start_button_pressed_style, LV_OPA_100);
            lv_style_set_border_width(&start_button_pressed_style, 2);
            lv_style_set_border_color(&start_button_pressed_style, lv_color_black());
            lv_style_set_text_color(&start_button_pressed_style, lv_color_black());
            lv_style_set_text_font(&start_button_pressed_style, &pros_font_dejavu_mono_18);
            lv_obj_t * start_button = lv_btn_create(lv_scr_act());
            lv_obj_remove_style_all(start_button);
            lv_obj_add_style(start_button, &start_button_default_style, 0);
            lv_obj_add_style(start_button, &start_button_pressed_style, LV_STATE_PRESSED);
            lv_obj_set_size(start_button, 160, 70);
            lv_obj_align(start_button, LV_ALIGN_TOP_LEFT, 20, 15);
            lv_obj_add_event_cb(start_button, startButtonEventHandler, LV_EVENT_CLICKED, data);
            lv_obj_t * start_button_label = lv_label_create(start_button);
            lv_label_set_text(start_button_label, "START");
            lv_obj_center(start_button_label);

            // Add the settings button
            static lv_style_t settings_button_default_style;
            lv_style_init(&settings_button_default_style);
            lv_style_set_radius(&settings_button_default_style, 5);
            lv_style_set_bg_opa(&settings_button_default_style, LV_OPA_100);
            lv_style_set_bg_color(&settings_button_default_style, lv_color_make(192, 192, 192));
            lv_style_set_bg_grad_color(&settings_button_default_style, lv_color_darken(lv_color_make(192, 192, 192), 8));
            lv_style_set_border_opa(&settings_button_default_style, LV_OPA_100);
            lv_style_set_border_width(&settings_button_default_style, 2);
            lv_style_set_border_color(&settings_button_default_style, lv_color_black());
            lv_style_set_text_color(&settings_button_default_style, lv_color_black());
            lv_style_set_text_font(&settings_button_default_style, &lv_font_montserrat_20);
            static lv_style_t settings_button_pressed_style;
            lv_style_init(&settings_button_pressed_style);
            lv_style_set_radius(&settings_button_pressed_style, 5);
            lv_style_set_bg_opa(&settings_button_pressed_style, LV_OPA_100);
            lv_style_set_translate_y(&settings_button_pressed_style, 3);
            lv_style_set_shadow_ofs_y(&settings_button_pressed_style, 3);
            lv_style_set_bg_color(&settings_button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 16));
            lv_style_set_bg_grad_color(&settings_button_pressed_style, lv_color_darken(lv_color_make(192, 192, 192), 24));
            lv_style_set_border_opa(&settings_button_pressed_style, LV_OPA_100);
            lv_style_set_border_width(&settings_button_pressed_style, 2);
            lv_style_set_border_color(&settings_button_pressed_style, lv_color_black());
            lv_style_set_text_color(&settings_button_pressed_style, lv_color_black());
            lv_style_set_text_font(&settings_button_pressed_style, &lv_font_montserrat_20);
            lv_obj_t * settings_button = lv_btn_create(lv_scr_act());
            lv_obj_remove_style_all(settings_button);
            lv_obj_add_style(settings_button, &settings_button_default_style, 0);
            lv_obj_add_style(settings_button, &settings_button_pressed_style, LV_STATE_PRESSED);
            lv_obj_set_size(settings_button, 70, 70);
            lv_obj_align(settings_button, LV_ALIGN_TOP_LEFT, 190, 15);
            lv_obj_add_event_cb(settings_button, settingsButtonEventHandler, LV_EVENT_CLICKED, data);
            lv_obj_t * settings_button_label = lv_label_create(settings_button);
            lv_label_set_text(settings_button_label, LV_SYMBOL_SETTINGS);
            lv_obj_center(settings_button_label);
        }

        void drawSettingsMenu(Data* data)
        {
            lv_obj_t * menu = lv_menu_create(lv_scr_act());

            // Create the back button
            static lv_style_t back_button_style;
            lv_style_init(&back_button_style);
            lv_style_set_radius(&back_button_style, 5);
            lv_style_set_border_opa(&back_button_style, LV_OPA_100);
            lv_style_set_border_width(&back_button_style, 2);
            lv_style_set_border_color(&back_button_style, lv_color_make(0, 104, 179));
            lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
            lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
            lv_obj_add_style(back_btn, &back_button_style, 0);
            lv_obj_t * back_btn_label = lv_label_create(back_btn);
            lv_label_set_text(back_btn_label, "Back");
            static void* user_data[] = { nullptr, nullptr };
            user_data[0] = menu;
            user_data[1] = data;
            lv_obj_add_event_cb(menu, settingsBackButtonEventHandler, LV_EVENT_CLICKED, user_data);
            lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
            lv_obj_center(menu);

            // Create the alliance settings page
            lv_obj_t * alliance_page = lv_menu_page_create(menu, NULL);
            lv_obj_t* alliance_page_container = lv_menu_cont_create(alliance_page);
            lv_obj_t* alliance_menu_label = lv_label_create(alliance_page_container);
            lv_label_set_text(alliance_menu_label, "Alliance selection");

            // Create the autonomous settings page
            lv_obj_t * autonomous_page = lv_menu_page_create(menu, NULL);
            lv_obj_t* autonomous_page_container = lv_menu_cont_create(autonomous_page);
            lv_obj_t* autonomous_menu_label = lv_label_create(autonomous_page_container);
            lv_label_set_text(autonomous_menu_label, "Autonomous selection");

            // Create the configuration settings page
            lv_obj_t * configuration_page = lv_menu_page_create(menu, NULL);
            lv_obj_t* configuration_page_container = lv_menu_cont_create(configuration_page);
            lv_obj_t* configuration_menu_label = lv_label_create(configuration_page_container);
            lv_label_set_text(configuration_menu_label, "Configuration selection");

            // Create the profile settings page
            lv_obj_t * profile_page = lv_menu_page_create(menu, NULL);
            lv_obj_t* profile_page_container = lv_menu_cont_create(profile_page);
            lv_obj_t* profile_menu_label = lv_label_create(profile_page_container);
            lv_label_set_text(profile_menu_label, "Profile selection");

            // Create the main selection page
            lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

            // Add a container for the alliance menu
            lv_obj_t* alliance_menu_container = lv_menu_cont_create(main_page);
            lv_obj_t* alliance_container_label = lv_label_create(alliance_menu_container);
            lv_label_set_text(alliance_container_label, "Alliance menu");
            lv_menu_set_load_page_event(menu, alliance_menu_container, alliance_page);

            // Add a container for the autonomous menu
            lv_obj_t* autonomous_menu_container = lv_menu_cont_create(main_page);
            lv_obj_t* autonomous_container_label = lv_label_create(autonomous_menu_container);
            lv_label_set_text(autonomous_container_label, "Autonomous menu");
            lv_menu_set_load_page_event(menu, autonomous_menu_container, autonomous_page);

            // Add a container for the configuration menu
            lv_obj_t* configuration_menu_container = lv_menu_cont_create(main_page);
            lv_obj_t* configuration_container_label = lv_label_create(configuration_menu_container);
            lv_label_set_text(configuration_container_label, "Configuration menu");
            lv_menu_set_load_page_event(menu, configuration_menu_container, configuration_page);

            // Add a container for the profile menu
            lv_obj_t* profile_menu_container = lv_menu_cont_create(main_page);
            lv_obj_t* profile_container_label = lv_label_create(profile_menu_container);
            lv_label_set_text(profile_container_label, "Profile menu");
            lv_menu_set_load_page_event(menu, profile_menu_container, profile_page);

            lv_menu_set_page(menu, main_page);
        }
    } // End namespace screen
} // End namespace menu