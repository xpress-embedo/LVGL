#include <stdio.h>
#include "lv_slider_exp.h"

// Private Variables
static lv_obj_t * sld_container;    // slider container
static lv_obj_t * sld_dsc;          // slider description label
static lv_obj_t * sld;              // slider object
static lv_obj_t * sld_value;        // slider value label

// Private Function Prototypes
static void slider_event_cb( lv_event_t * e );

// Public Function Definitions
void slider_exp_1( void )
{
  // custom slider
  sld_container = lv_obj_create( lv_scr_act() );
  lv_obj_set_size( sld_container, LV_PCT(30), LV_PCT(20) );
  lv_obj_center( sld_container );
  lv_obj_set_flex_flow( sld_container, LV_FLEX_FLOW_ROW_WRAP );
  // lv_obj_set_flex_align( sld_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER );
  // experiment with different flex settings
  lv_obj_set_flex_align( sld_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER );

  // slider description label
  sld_dsc = lv_label_create( sld_container );
  lv_label_set_text( sld_dsc, "Slider Description" );
  lv_obj_set_style_text_font( sld_dsc, &lv_font_montserrat_18, 0 );

  // actual slider
  sld = lv_slider_create( sld_container );
  // lv_obj_set_size( sld, LV_PCT(60), LV_PCT(10) );
  // let the slider grow to fill the container
  lv_obj_set_flex_grow( sld, 1 );
  lv_slider_set_value( sld, 40, LV_ANIM_OFF );
  lv_slider_set_range( sld, 0, 100 );
  // the NULL is the place where we can pass some user data to the event callback
  lv_obj_add_event( sld, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL );
  lv_obj_add_flag( sld, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK );

  // slider value label
  sld_value = lv_label_create( sld_container );
  lv_obj_set_size( sld_value, LV_PCT(30), LV_SIZE_CONTENT );
  lv_label_set_text( sld_value, "40%" );
  lv_obj_set_style_text_font( sld_value, &lv_font_montserrat_18, 0 );

  // lv_obj_set_style_pad_row( sld_dsc, 10, 0 );
  // lv_obj_set_style_pad_left( sld, 10, 0 );
  lv_obj_set_style_pad_left( sld_value, 10, 0 );
  // lv_obj_set_style_pad_right( sld_value, 5, 0 );
}

// Private Function Definitions
static void slider_event_cb( lv_event_t * e )
{
  lv_obj_t * slider = lv_event_get_target( e );
  int32_t v = lv_slider_get_value( slider );
  // update the value label
  char buf[8];
  snprintf( buf, sizeof(buf), "%d%%", v );
  lv_label_set_text( sld_value, buf );
  LV_LOG_USER( "Slider value: %d", v );
}
