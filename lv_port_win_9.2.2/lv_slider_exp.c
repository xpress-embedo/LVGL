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
  // styles
  static lv_style_t style_main;
  static lv_style_t style_indicator;
  static lv_style_t style_knob;
  static lv_style_t style_pressed_color;

  lv_style_init( &style_main );
  lv_style_set_bg_opa( &style_main, LV_OPA_COVER );
  lv_style_set_bg_color( &style_main, lv_color_hex3(0xbbb) );

  lv_style_init( &style_indicator );
  lv_style_set_bg_opa( &style_indicator, LV_OPA_COVER );
  lv_style_set_bg_color( &style_indicator, lv_palette_main(LV_PALETTE_CYAN) );

  lv_style_init( &style_knob );
  lv_style_set_bg_opa( &style_knob, LV_OPA_COVER );
  lv_style_set_bg_color( &style_knob, lv_palette_main(LV_PALETTE_CYAN) );
  lv_style_set_border_color( &style_knob, lv_palette_darken(LV_PALETTE_CYAN, 3) );
  lv_style_set_border_width( &style_knob, 2 );
  lv_style_set_pad_all( &style_knob, 5 );

  lv_style_init( &style_pressed_color );
  lv_style_set_bg_opa( &style_pressed_color, LV_OPA_COVER );
  lv_style_set_bg_color( &style_knob, lv_palette_darken(LV_PALETTE_CYAN, 2) );

  // custom slider
  sld_container = lv_obj_create( lv_scr_act() );
  lv_obj_set_size( sld_container, LV_PCT(40), LV_PCT(30) );
  lv_obj_center( sld_container );
  // make the container transparent and remove border
  // lv_obj_set_style_bg_opa( sld_container, LV_OPA_TRANSP, 0 );
  // lv_obj_set_style_border_width( sld_container, 0, 0 );

  lv_obj_set_flex_flow( sld_container, LV_FLEX_FLOW_COLUMN );
  lv_obj_set_flex_align(  sld_container, 
                          LV_FLEX_ALIGN_START,    // Top
                          LV_FLEX_ALIGN_START,    // Left
                          LV_FLEX_ALIGN_START );  // Track

  // slider description label
  sld_dsc = lv_label_create( sld_container );
  lv_label_set_text( sld_dsc, "Slider Description" );
  lv_obj_set_style_text_font( sld_dsc, &lv_font_montserrat_18, 0 );

  // create a sub-container for the slider and value label
  lv_obj_t * sld_row_cont = lv_obj_create( sld_container );
  lv_obj_set_size( sld_row_cont, LV_PCT(100), LV_SIZE_CONTENT );
  // make the container transparent and remove border
  lv_obj_set_style_bg_opa( sld_row_cont, LV_OPA_TRANSP, 0 );
  lv_obj_set_style_border_width( sld_row_cont, 0, 0 );

  lv_obj_set_flex_flow( sld_row_cont, LV_FLEX_FLOW_ROW );
  lv_obj_set_flex_align(  sld_row_cont, 
                          LV_FLEX_ALIGN_START,    // Left
                          LV_FLEX_ALIGN_CENTER,   // Vertical Centered
                          LV_FLEX_ALIGN_CENTER );
  
  lv_obj_set_style_pad_row( sld_row_cont, 10, 0 );      // Optional spacing
  lv_obj_set_style_pad_column( sld_row_cont, 10, 0 );   // Space between slider and value

  // actual slider
  sld = lv_slider_create( sld_row_cont );
  // lv_obj_set_size( sld, LV_PCT(60), LV_PCT(10) );
  // let the slider grow to fill the container
  lv_obj_set_flex_grow( sld, 1 );
  lv_slider_set_value( sld, 40, LV_ANIM_OFF );
  lv_slider_set_range( sld, 0, 100 );
  // slider styles application is done below
  lv_obj_add_style( sld, &style_main, LV_PART_MAIN );
  lv_obj_add_style( sld, &style_indicator, LV_PART_INDICATOR );
  lv_obj_add_style( sld, &style_knob, LV_PART_KNOB );
  lv_obj_add_style( sld, &style_pressed_color, LV_PART_KNOB | LV_STATE_PRESSED );
  lv_obj_add_style( sld, &style_pressed_color, LV_PART_INDICATOR | LV_STATE_PRESSED );
  // the NULL is the place where we can pass some user data to the event callback
  lv_obj_add_event( sld, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL );
  // this is added because when slider is reaching 100% the knob is going out of the container and merging with the value label
  lv_obj_set_style_pad_right( sld, 10, 0 );

  // slider value label
  sld_value = lv_label_create( sld_row_cont );
  lv_obj_set_size( sld_value, LV_PCT(30), LV_SIZE_CONTENT );
  lv_label_set_text( sld_value, "40%" );
  lv_obj_set_style_text_font( sld_value, &lv_font_montserrat_18, 0 );

  // lv_obj_set_style_pad_row( sld_dsc, 10, 0 );
  // lv_obj_set_style_pad_left( sld, 10, 0 );
  // lv_obj_set_style_pad_left( sld_value, 10, 0 );
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
