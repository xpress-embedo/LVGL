#ifndef LV_MENU_EXP_H_INCLUDED
#define LV_MENU_EXP_H_INCLUDED

#include "lvgl/lvgl.h"

// Enumerations
typedef enum
{
  LV_MENU_ITEM_BUILDER_VARIANT_1,
  LV_MENU_ITEM_BUILDER_VARIANT_2
} lv_menu_builder_variant_t;

// Function pointer typedefs
typedef void (*slider_callback_t)( int32_t value );

// Public Function Prototypes
void menu_example_1( void );
void create_wifi_settings_page( lv_obj_t * parent );

#endif // LV_MENU_EXP_H_INCLUDED
