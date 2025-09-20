
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#include "lv_flex_layout_exp.h"
#include "lv_slider_exp.h"
#include "lv_menu_exp.h"
#include "widgets.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void w_slider_event_cb( lv_event_t * e );
static void w_button_event_cb( lv_event_t * e );

/**********************
 *  STATIC VARIABLES
 **********************/
static const wchar_t * title = L"LVGL port Windows CodeBlocks";

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 800, 480, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);

    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    /*Run the demo*/
    // lv_demo_widgets();
    //char * demo_str[] = {"widgets"};
    //lv_demos_create(demo_str, strlen((char * )demo_str));
    // lv_example_menu_5();

    // menu_exp();  // onsolete function
    menu_example_1();
    // create_wifi_settings_page( lv_screen_active() );

    // Flex Layout Demo Examples
    // flex_layout_exp_1();
    // flex_layout_exp_2();

    // Slider Experiments with Flex Layout
    // slider_exp_1();

    // slider widget creation
    // w_slider_t * my_slider = w_slider_create( lv_screen_active(), 0, 100, 50, w_slider_event_cb );
    // if( my_slider != NULL )
    // {
    //   LV_LOG_USER("Slider widget created successfully");
    // }
    // else
    // {
    //   LV_LOG_ERROR("Failed to create slider widget");
    // }

    // Button widget creation
    // w_button_t * my_button = w_button_create( lv_screen_active(), "Click Me", w_button_event_cb );
    // if( my_button != NULL )
    // {
    //   LV_LOG_USER("Button widget created successfully");
    // }
    // else
    // {
    //   LV_LOG_ERROR("Failed to create button widget");
    // }

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}


static void w_slider_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_VALUE_CHANGED )
  {
    lv_obj_t * slider = lv_event_get_target( e );
    int32_t v = lv_slider_get_value( slider );
    LV_LOG_USER( "Slider value: %d", v );
  }
}

static void w_button_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_CLICKED )
  {
    LV_LOG_USER( "Button Clicked" );
  }
}
