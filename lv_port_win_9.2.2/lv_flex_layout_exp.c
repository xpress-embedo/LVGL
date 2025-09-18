#include "lv_flex_layout_exp.h"

// Public Function Definitions
void flex_layout_exp_1( void )
{
  // Row Layout Experiments
  lv_obj_t * container_row = lv_obj_create( lv_scr_act() );
  lv_obj_set_size( container_row, LV_PCT(90), LV_PCT(90) );
  lv_obj_center( container_row );
  // Optional: Set a background color to visualize the container
  // lv_obj_set_style_bg_color( container_row, lv_color_hex( 0xC0C0C0 ), 0 );
  // better way to visualize the container controlling the brightness of the color
  lv_obj_set_style_bg_color( container_row, lv_color_darken( lv_color_hex( 0xC0C0C0 ), 10) , 0 );
  
  // Flow Configurations
  // this will make the container's children layout in a row but without wrapping
  // lv_obj_set_flex_flow( container_row, LV_FLEX_FLOW_ROW );
  // this will make the container's children layout in a row with wrapping
  lv_obj_set_flex_flow( container_row, LV_FLEX_FLOW_ROW_WRAP );

  // Alignment Configuration
  lv_obj_set_flex_align( container_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER );
  
  uint32_t i;
  for( i = 0; i < 10; i++ )
  {
    lv_obj_t * button;
    lv_obj_t * label;
    button = lv_btn_create( container_row );
    lv_obj_set_size( button, 100, LV_PCT(20) );
    label = lv_label_create( button );
    // lv_label_set_text_fmt( label, "Button %d", i + 1 );
    lv_label_set_text_fmt( label, "Btn %" LV_PRIu32"", i + 1 );
    lv_obj_center( label );
  }
}

void flex_layout_exp_2( void )
{
  // Column Layout Experiments
  lv_obj_t * container_col = lv_obj_create( lv_scr_act() );
  lv_obj_set_size( container_col, LV_PCT(90), LV_PCT(90) );
  lv_obj_center( container_col );
  // Optional: Set a background color to visualize the container
  // lv_obj_set_style_bg_color( container_col, lv_color_hex( 0xC0C0C0 ), 0 );
  // better way to visualize the container controlling the brightness of the color
  lv_obj_set_style_bg_color( container_col, lv_color_darken( lv_color_hex( 0xC0C0C0 ), 10) , 0 );
  
  // Flow Configurations
  // this will make the container's children layout in a column but without wrapping
  // lv_obj_set_flex_flow( container_col, LV_FLEX_FLOW_COLUMN );
  // this will make the container's children layout in a COLUMN with wrapping
  lv_obj_set_flex_flow( container_col, LV_FLEX_FLOW_COLUMN_WRAP );

  // Alignment Configuration
  lv_obj_set_flex_align( container_col, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER );
  
  uint32_t i;
  for( i = 0; i < 10; i++ )
  {
    lv_obj_t * button;
    lv_obj_t * label;
    button = lv_btn_create( container_col );
    lv_obj_set_size( button, 100, LV_PCT(20) );
    label = lv_label_create( button );
    // lv_label_set_text_fmt( label, "Button %d", i + 1 );
    lv_label_set_text_fmt( label, "Btn %" LV_PRIu32"", i + 1 );
    lv_obj_center( label );
  }
}
