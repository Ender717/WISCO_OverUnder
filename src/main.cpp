#include "main.h"

static void scroll_event_v2(lv_event_t* e)
{
    lv_obj_t* container = lv_event_get_target(e);

    lv_area_t container_area;
    lv_obj_get_coords(container, &container_area);
    lv_coord_t container_y_center = container_area.y1 + (lv_area_get_height(&container_area) >> 1);

    lv_coord_t radius = lv_obj_get_height(container) * 7 / 10;
    uint32_t child_count = lv_obj_get_child_cnt(container);
    for(uint32_t i = 0; i < child_count; i++)
    {
        lv_obj_t* child = lv_obj_get_child(container, i);
        lv_area_t child_area;
        lv_obj_get_coords(child, &child_area);

        lv_coord_t child_y_center = child_area.y1 + (lv_area_get_height(&child_area) >> 1);

        lv_coord_t diff_y = LV_ABS(child_y_center - container_y_center);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x = radius;
        if (diff_y < radius)
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            lv_sqrt_res_t res;
            lv_sqrt(radius * radius - diff_y * diff_y, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x -= res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);
    }
}

static void scroll_event_cb(lv_event_t * e)
{
    lv_obj_t* cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        /*
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
        */
    }
}

/**
 * Translate the object as they scroll
 */
void lv_example_scroll_6(void)
{
    lv_obj_t* container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(container, 200, 200);
    lv_obj_center(container);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(container, scroll_event_v2, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(container, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(container, true, 0);
    lv_obj_set_scroll_dir(container, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(container, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);

    for(int i = 0; i < 10; i++)
    {
        lv_obj_t * btn = lv_btn_create(container);
        lv_obj_set_width(btn, lv_pct(100));

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %d", i);
    }

    // Update the buttons position manually for starting position
    lv_event_send(container, LV_EVENT_SCROLL, NULL);

    // Be sure the first button is in the middle
    lv_obj_scroll_to_view(lv_obj_get_child(container, 0), LV_ANIM_OFF);
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

    lv_example_scroll_6();
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