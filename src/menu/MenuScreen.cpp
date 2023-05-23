// Included header
#include "menu/MenuScreen.hpp"
#include "liblvgl/font/lv_font.h"

namespace menu
{
    namespace screen
    {
        void startButtonEventHandler(lv_event_t *event)
        {
            lv_obj_clean(lv_scr_act());
        }

        void settingsButtonEventHandler(lv_event_t *event)
        {
            lv_obj_clean(lv_scr_act());
            Data* data = (Data*)lv_event_get_user_data(event);
            drawSettingsMenu(data);
        }

        void drawMainMenu(Data* data)
        {
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
            if (data != nullptr)
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
            lv_obj_add_event_cb(start_button, startButtonEventHandler, LV_EVENT_CLICKED, nullptr);
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

        }
    } // End namespace screen
} // End namespace menu