#include "wisco/menu/LvglMenu.hpp"

namespace wisco
{
namespace menu
{
bool LvglMenu::styles_initialized = false;

void settingsBackButtonEventHandler(lv_event_t* event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    void** user_data = (void**)lv_event_get_user_data(event);
    lv_obj_t * menu = (lv_obj_t*)(user_data[0]);

    if(obj == lv_menu_get_sidebar_header_back_btn(menu))
    {
        lv_obj_clean(lv_scr_act());
        //drawMainMenu();
    }
}

void settingsButtonMatrixEventHandler(lv_event_t *event)
{
    lv_obj_t* obj = lv_event_get_target(event);
    uint32_t button_id = lv_btnmatrix_get_selected_btn(obj);
    void** user_data = (void**)lv_event_get_user_data(event);

    /*
    types::Setting* setting = (types::Setting*)(user_data[0]);
    switch(*setting)
    {
        case types::Setting::ALLIANCE: { data->alliance = static_cast<types::Alliance>(button_id); }
        case types::Setting::AUTONOMOUS: { data->autonomous = static_cast<types::Autonomous>(button_id); }
        case types::Setting::CONFIGURATION: { data->configuration = static_cast<types::Configuration>(button_id); }
        case types::Setting::PROFILE: { data->profile = static_cast<types::Profile>(button_id); }
    }
    */
}

void LvglMenu::initializeStyles()
{
    if (styles_initialized)
        return;

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

    // Create the button matrix main style
    lv_style_init(&button_matrix_main_style);
    lv_style_set_bg_color(&button_matrix_main_style, lv_color_make(173, 205, 234));
    lv_style_set_border_width(&button_matrix_main_style, 0);

    // Create the button matrix items style
    lv_style_init(&button_matrix_items_style);

    // Set the style initialization flag
    styles_initialized = true;
}

void LvglMenu::drawMainMenu()
{
    // Set the background color to light blue
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(173, 205, 234), 0);
    lv_obj_refresh_style(lv_scr_act(), LV_PART_MAIN, LV_STYLE_BG_COLOR);

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
    lv_style_set_text_font(&team_name_label_style, &pros_font_dejavu_mono_30);
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
    std::string status_text{};
    for (Option& option : options)
    {
        if (option.name != options.front().name)
            status_text += '\n';
        status_text += option.name;
        status_text += ": ";
        status_text += option.choices[option.selected];
    }
    lv_label_set_text_fmt(status_label, "%s", status_text.c_str());
    lv_obj_align(status_label, LV_ALIGN_TOP_LEFT, 20, 100);

    // Add the start button
    lv_obj_t * start_button = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(start_button);
    lv_obj_add_style(start_button, &button_default_style, 0);
    lv_obj_add_style(start_button, &button_pressed_style, LV_STATE_PRESSED);
    lv_obj_set_size(start_button, 160, 70);
    lv_obj_align(start_button, LV_ALIGN_TOP_LEFT, 20, 15);
    lv_obj_add_event_cb(start_button,
                        [](lv_event_t* event)
                        {
                            lv_obj_clean(lv_scr_act());
                            //data->write();
                        },
                        LV_EVENT_CLICKED, nullptr);
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
    lv_obj_add_event_cb(settings_button,
                        [](lv_event_t* event)
                        {
                            lv_obj_clean(lv_scr_act());
                            //drawSettingsMenu();
                        },
                        LV_EVENT_CLICKED, nullptr);
    lv_obj_t * settings_button_label = lv_label_create(settings_button);
    lv_label_set_text(settings_button_label, LV_SYMBOL_SETTINGS);
    lv_obj_center(settings_button_label);
}

void LvglMenu::addOption(Option option)
{
    options.push_back(option);
}

void LvglMenu::removeOption(const std::string& option_name)
{
    for (auto it{options.begin()}; it != options.end(); ++it)
    {
        if (option_name == it->name)
        {
            options.erase(it);
            break;
        }
    }
}

void LvglMenu::displayMenu()
{
    initializeStyles();
    drawMainMenu();
}

bool LvglMenu::selectionComplete()
{
    return complete;
}

std::string LvglMenu::getSelection(const std::string& option_name)
{
    std::string selection{};
    for (Option& option : options)
        if (option_name == option.name)
            selection = option.choices[option.selected];
    return selection;
}
}
}