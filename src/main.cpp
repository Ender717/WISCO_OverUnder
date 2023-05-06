#include "main.h"

/**
 * Show an example to scroll snap
 */
void lv_example_scroll_2(void)
{
    lv_obj_t* panel = lv_obj_create(lv_scr_act());
    lv_obj_set_size(panel, 480, 120);
    lv_obj_set_style_bg_color(panel, lv_color_black(), 0);
    lv_obj_set_style_border_color(panel, lv_color_black(), 0);
    lv_obj_refresh_style(panel, LV_PART_MAIN, LV_STYLE_BG_COLOR);
    lv_obj_refresh_style(panel, LV_PART_MAIN, LV_STYLE_BORDER_COLOR);
    lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_align(panel, LV_ALIGN_BOTTOM_MID, 0, 0);

    int button_width = 150;
    for(uint32_t i = 0; i < 10; i++)
    {
        lv_obj_t* btn = lv_btn_create(panel);
        lv_obj_set_size(btn, button_width, lv_pct(100));

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Panel %" LV_PRIu32, i);

        lv_obj_center(label);
    }

    lv_obj_update_snap(panel, LV_ANIM_OFF);

    int currentScroll = lv_obj_get_scroll_x(panel);
    lv_obj_t* btn = lv_obj_get_child(panel, 0);
    int scrollWidth = lv_obj_get_width(btn) + (lv_obj_get_style_pad_left(btn, 0) >> 1);
    int minScroll = -scrollWidth;
    int maxScroll = scrollWidth * (lv_obj_get_child_cnt(panel) - 1);
    while (true)
    {
        if (pros::c::controller_get_digital_new_press(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_LEFT))
        {
            currentScroll = std::max(minScroll, currentScroll - scrollWidth);
            lv_obj_scroll_to_x(panel, currentScroll, LV_ANIM_ON);
        }
        else if (pros::c::controller_get_digital_new_press(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_RIGHT))
        {
            currentScroll = std::min(maxScroll, currentScroll + scrollWidth);
            lv_obj_scroll_to_x(panel, currentScroll, LV_ANIM_ON);
        }
        pros::delay(50);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    pros::delay(50);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    lv_obj_refresh_style(lv_scr_act(), LV_PART_MAIN, LV_STYLE_BG_COLOR);

    lv_example_scroll_2();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{

}