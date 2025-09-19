#include "lv_menu_exp.h"

// Private Function Prototypes
static lv_obj_t * create_text( lv_obj_t * parent, const char * icon, const char * txt );
static lv_obj_t * create_slider( lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val );

// Public Function Definitions
void menu_example_1( void )
{
  lv_obj_t * menu = lv_menu_create( lv_screen_active() );
  lv_menu_set_mode_root_back_button( menu, LV_MENU_ROOT_BACK_BUTTON_ENABLED );
  // configure back button event handler later
  lv_obj_set_size( menu, lv_display_get_horizontal_resolution(NULL), lv_display_get_vertical_resolution(NULL) );
  lv_obj_center( menu );
  lv_obj_set_scrollbar_mode( menu, LV_SCROLLBAR_MODE_OFF );

  // Display Sub Page
  lv_obj_t * disp_page = lv_menu_page_create( menu, "Dislay Settings" );
  lv_menu_separator_create( disp_page );
  lv_obj_t * disp_section = lv_menu_section_create( disp_page );
  create_slider( disp_section, LV_SYMBOL_SETTINGS, "Brightness", 0, 100, 50 );
  create_slider( disp_section, LV_SYMBOL_SETTINGS, "Contrast", 0, 100, 30 );

  // WiFi Sub Page
  lv_obj_t * wifi_page = lv_menu_page_create( menu, "WiFi" );
  lv_menu_separator_create( wifi_page );
  lv_obj_t * wifi_section = lv_menu_section_create( wifi_page );
  lv_obj_t * wifi_label = lv_label_create( wifi_section );
  lv_label_set_text( wifi_label, "WiFi Setting Coming Soon..." );

  // Create Main Page
  lv_obj_t * main_page = lv_menu_page_create( menu, "Settings" );

  lv_obj_t * btn_disp = lv_menu_cont_create( main_page );
  lv_obj_t * label = lv_label_create( btn_disp );
  lv_label_set_text( label, "Display" );
  lv_menu_set_load_page_event( menu, btn_disp, disp_page );

  lv_obj_t * btn_wifi = lv_menu_cont_create( main_page );
  lv_obj_t * lbl_wifi = lv_label_create( btn_wifi );
  lv_label_set_text(lbl_wifi, "WiFi");
  lv_menu_set_load_page_event( menu, btn_wifi, wifi_page );

  // set the page
  lv_menu_set_page(menu, main_page);
  // lv_menu_set_sidebar_page( menu, main_page );
}

// Private Function Definitions
static lv_obj_t * create_text( lv_obj_t * parent, const char * icon, const char * txt )
{
  lv_obj_t * obj = lv_menu_cont_create( parent );
  lv_obj_t * img = NULL;
  lv_obj_t * label = NULL;

  // if icon is provided, create and set it
  if ( icon )
  {
    img = lv_image_create( obj );
    lv_image_set_src( img, icon );
  }

  // if text is provided, create and set it
  if ( txt )
  {
    label = lv_label_create( obj );
    lv_label_set_text( label, txt );
    lv_label_set_long_mode( label, LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_flex_grow( label, 1 );
  }

  // TODO: I don't know why we are doing this. Review later.
  if ( icon && txt )
  {
    lv_obj_add_flag( img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK );
    lv_obj_swap( img, label );
  }
  
  return obj;
}

static lv_obj_t * create_slider( lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val )
{
  lv_obj_t * obj = create_text( parent, icon, txt );

  lv_obj_t * slider = lv_slider_create( obj );
  lv_obj_set_flex_grow( slider, 1 );
  lv_slider_set_range( slider, min, max );
  lv_slider_set_value( slider, val, LV_ANIM_OFF );

  // if no icon is provided, make the slider start in a new row
  if ( icon == NULL )
  {
    lv_obj_add_flag( slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK );
  }

  return obj;
}


// Obsolete function retained for reference
void menu_exp(void)
{
    lv_obj_t * menu = lv_menu_create(lv_screen_active());
    lv_obj_set_size(menu, lv_display_get_horizontal_resolution(NULL), lv_display_get_vertical_resolution(NULL));
    lv_obj_center(menu);
    lv_obj_set_scrollbar_mode(menu, LV_SCROLLBAR_MODE_OFF);

    // Create sub page
    lv_obj_t * disp_sub_page = lv_menu_page_create(menu, NULL);

    // Create container with flex layout
    lv_obj_t * container = lv_menu_cont_create(disp_sub_page);
    lv_obj_set_size(container, lv_display_get_horizontal_resolution(NULL), lv_display_get_vertical_resolution(NULL));
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    // Label: "Display Brightness"
    lv_obj_t * disp_slider_label = lv_label_create(container);
    lv_label_set_text(disp_slider_label, "Display Brightness");
    lv_obj_set_style_text_font(disp_slider_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(disp_slider_label, 40, 0); // Align left

    // Horizontal row for slider + value
    lv_obj_t * slider_row = lv_obj_create(container);
    lv_obj_set_width(slider_row, lv_obj_get_width(container));
    lv_obj_set_height(slider_row, 60);
    lv_obj_set_layout(slider_row, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(slider_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(slider_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(slider_row, LV_OBJ_FLAG_SCROLLABLE);

    // Slider (2/3 of container width)
    lv_coord_t slider_width = (2 * lv_obj_get_width(container)) / 3;
    lv_obj_t * disp_slider = lv_slider_create(slider_row);
    lv_obj_set_size(disp_slider, slider_width, 20);
    lv_slider_set_value(disp_slider, 50, LV_ANIM_OFF);

    // Value label
    lv_obj_t * disp_slider_value = lv_label_create(slider_row);
    lv_label_set_text(disp_slider_value, "50%");
    lv_obj_set_style_text_font(disp_slider_value, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(disp_slider_value, 20, 0);

    // Main page setup
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);
    lv_obj_t * main_container = lv_menu_cont_create(main_page);
    lv_obj_t * label = lv_label_create(main_container);
    lv_label_set_text(label, "Display");
    lv_menu_set_load_page_event(menu, main_container, disp_sub_page);

    main_container = lv_menu_cont_create(main_page);
    label = lv_label_create(main_container);
    lv_label_set_text(label, "WiFi");

    lv_menu_set_page(menu, main_page);
}
/*

void menu_exp( void )
{
  lv_obj_t * container;
  lv_obj_t * label;
  lv_obj_t * disp_label;
  lv_obj_t * disp_slider;
  lv_obj_t * disp_slider_label;
  lv_obj_t * disp_slider_value;

  lv_obj_t * menu = lv_menu_create( lv_screen_active() );
  lv_obj_set_size(menu, lv_display_get_horizontal_resolution(NULL), lv_display_get_vertical_resolution(NULL));
  lv_obj_center(menu);
  lv_obj_set_scrollbar_mode( menu, LV_SCROLLBAR_MODE_OFF );

  // Create sub pages
  lv_obj_t * disp_sub_page = lv_menu_page_create( menu, NULL );
  container = lv_menu_cont_create( disp_sub_page );
  lv_obj_set_size(container, lv_display_get_horizontal_resolution(NULL), lv_display_get_vertical_resolution(NULL));
  disp_slider = lv_slider_create( container );
  lv_obj_set_size( disp_slider, 600, 20 );
  lv_slider_set_value( disp_slider, 50, LV_ANIM_OFF );
  lv_obj_add_flag(disp_slider, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
  lv_obj_center( disp_slider );

  disp_slider_value = lv_label_create( container );
  lv_label_set_text( disp_slider_value, "50%" );
  lv_obj_set_style_text_font(disp_slider_value, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align_to(disp_slider_value, disp_slider, LV_ALIGN_OUT_RIGHT_MID, 20, 0);   // Position right

  disp_slider_label = lv_label_create( container );
  lv_label_set_text( disp_slider_label, "Display Brightness" );
  lv_obj_set_style_text_font(disp_slider_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align_to(disp_slider_label, disp_slider, LV_ALIGN_OUT_TOP_LEFT, -10, 0);  // Position above


  // Create Main Page
  lv_obj_t * main_page = lv_menu_page_create( menu, NULL );
  container = lv_menu_cont_create( main_page );
  label = lv_label_create( container );
  lv_label_set_text( label, "Display" );
  lv_menu_set_load_page_event( menu, container, disp_sub_page );

  container = lv_menu_cont_create( main_page );
  label = lv_label_create( container );
  lv_label_set_text( label, "WiFi" );
  // lv_menu_set_load_page_event( menu, container, disp_sub_page );

  // set the page
  lv_menu_set_page( menu, main_page );
  // lv_menu_set_sidebar_page( menu, main_page );
}
*/
