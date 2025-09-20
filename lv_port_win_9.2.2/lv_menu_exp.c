#include "widgets.h"
#include "lv_menu_exp.h"

// Private Variables
lv_obj_t * kb_wifi_pswd = NULL;         // object pointer for the keyboard
lv_obj_t * txt_box_wifi_pswd = NULL;    // object pointer for the text area to enter WiFi password

// Private Function Prototypes
static lv_obj_t * create_text( lv_obj_t * parent, const char * icon, const char * txt, lv_menu_builder_variant_t builder_variant );
static lv_obj_t * create_slider( lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val, slider_callback_t cb );
static void create_wifi_settings_page( lv_obj_t * parent );
static void generic_slider_event_cb( lv_event_t * e );
static void txt_box_wifi_pswd_event_cb( lv_event_t * e );
static void btn_connect_event_cb( lv_event_t * e );
static void btn_disconnect_event_cb( lv_event_t * e );
static void btn_rescan_event_cb( lv_event_t * e );
static void check_box_show_pswd_event_cb( lv_event_t * e );
static void display_brightness_event( int32_t value );
static void display_contrast_event( int32_t value );

// Public Function Definitions
/**
 * Creates and displays a comprehensive menu on the LVGL interface.
 *
 * This function initializes a menu that allows users to control display settings
 * such as brightness and contrast, as well as select and switch between available WiFi networks.
 * It demonstrates how to set up menu components, add interactive items for display control,
 * and provide options for WiFi connectivity management.
 *
 * @param none
 */
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
  create_slider( disp_section, LV_SYMBOL_SETTINGS, "Brightness", 0, 100, 50, display_brightness_event );
  create_slider( disp_section, LV_SYMBOL_SETTINGS, "Contrast", 0, 100, 30, display_contrast_event);

  // WiFi Sub Page
  lv_obj_t * wifi_page = lv_menu_page_create( menu, "WiFi Settings" );
  create_wifi_settings_page( wifi_page );
  // lv_menu_separator_create( wifi_page );
  // lv_obj_t * wifi_section = lv_menu_section_create( wifi_page );
  // lv_obj_t * wifi_label = lv_label_create( wifi_section );
  // lv_label_set_text( wifi_label, "WiFi Setting Coming Soon..." );

  // Create Main Page
  lv_obj_t * main_page = lv_menu_page_create( menu, "Settings" );
  // creating sections instead of containers to have better padding and spacing
  lv_obj_t * btn_disp = lv_menu_section_create( main_page );
  // alternatively, create_text() can be used
  create_text( btn_disp, LV_SYMBOL_SETTINGS, "Display", LV_MENU_ITEM_BUILDER_VARIANT_1 );
  // lv_obj_t * label = lv_label_create( btn_disp );
  // lv_label_set_text( label, "Display" );
  lv_menu_set_load_page_event( menu, btn_disp, disp_page );

  // creating sections instead of containers to have better padding and spacing
  lv_obj_t * btn_wifi = lv_menu_section_create( main_page );
  create_text( btn_wifi, LV_SYMBOL_WIFI, "WiFi", LV_MENU_ITEM_BUILDER_VARIANT_1 );
  // lv_obj_t * lbl_wifi = lv_label_create( btn_wifi );
  // lv_label_set_text(lbl_wifi, "WiFi");
  lv_menu_set_load_page_event( menu, btn_wifi, wifi_page );

  // set the page
  // lv_menu_set_page(menu, main_page);
  lv_menu_set_sidebar_page( menu, main_page );
}

// Private Function Definitions
static lv_obj_t * create_text( lv_obj_t * parent, const char * icon, const char * txt, lv_menu_builder_variant_t builder_variant )
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

  // if both icon and text are provided, make the icon start a new row and swap their order
  // so that the text appears first followed by the icon
  if ( (builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2) && icon && txt )
  {
    lv_obj_add_flag( img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK );
    lv_obj_swap( img, label );
  }

  return obj;
}

static lv_obj_t * create_slider( lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val, slider_callback_t cb )
{
  lv_obj_t * obj = create_text( parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2 );

  lv_obj_t * slider = lv_slider_create( obj );
  lv_obj_set_flex_grow( slider, 1 );
  lv_slider_set_range( slider, min, max );
  lv_slider_set_value( slider, val, LV_ANIM_OFF );

  lv_obj_add_event_cb( slider, generic_slider_event_cb, LV_EVENT_VALUE_CHANGED, (void *)cb );

  // if no icon is provided, make the slider start in a new row
  if ( icon == NULL )
  {
    lv_obj_add_flag( slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK );
  }

  return obj;
}

static void generic_slider_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_VALUE_CHANGED )
  {
    // handle value change
    lv_obj_t * slider = lv_event_get_target( e );
    int32_t val = lv_slider_get_value( slider );
    // retrieve the callback function pointer
    slider_callback_t cb = (slider_callback_t)lv_event_get_user_data( e );
    if ( cb )
    {
      cb( val );
    }
  }
}

static void create_wifi_settings_page( lv_obj_t * parent )
{
  // create main container
  lv_obj_t * main_cont = lv_obj_create( parent );
  // remove default styles
  lv_obj_remove_style_all( main_cont );
  lv_obj_set_width( main_cont, LV_PCT(100) );
  lv_obj_set_height( main_cont, LV_PCT(100) );
  lv_obj_set_align( main_cont, LV_ALIGN_CENTER );
  lv_obj_set_flex_flow( main_cont, LV_FLEX_FLOW_COLUMN );
  lv_obj_set_flex_align( main_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER );
  lv_obj_remove_flag( main_cont, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );
  lv_obj_set_style_pad_left( main_cont, 5, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_pad_right( main_cont, 5, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_pad_top( main_cont, 5, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_pad_bottom( main_cont, 5, LV_PART_MAIN | LV_STATE_DEFAULT );

  // create 4 containers inside main container
  // 1. WiFi SSID Text and WiFi List
  lv_obj_t * cont_ssid = lv_obj_create( main_cont );
  lv_obj_remove_style_all( cont_ssid );
  lv_obj_set_width( cont_ssid, LV_PCT(100) );
  lv_obj_set_height( cont_ssid, LV_PCT(20) );
  lv_obj_set_align( cont_ssid, LV_ALIGN_TOP_MID );
  lv_obj_set_flex_flow( cont_ssid, LV_FLEX_FLOW_ROW_WRAP );
  lv_obj_set_flex_align( cont_ssid, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY );
  lv_obj_remove_flag( cont_ssid, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );

  lv_obj_t * lbl_wifi = lv_label_create( cont_ssid );
  lv_obj_set_width( lbl_wifi, LV_SIZE_CONTENT );
  lv_obj_set_height( lbl_wifi, LV_SIZE_CONTENT );
  lv_obj_set_align( lbl_wifi, LV_ALIGN_CENTER );
  lv_label_set_text( lbl_wifi, "WiFi SSID" );
  lv_obj_set_style_text_font( lbl_wifi, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT );

  lv_obj_t * cb_wifi = lv_dropdown_create( cont_ssid );
  lv_dropdown_set_options( cb_wifi, "FIRST\nSECOND\nGROUND\nFIRST_EXT\n" );
  lv_obj_set_width( cb_wifi, 250 );
  lv_obj_set_height( cb_wifi, 50 );
  lv_obj_set_align( cb_wifi, LV_ALIGN_CENTER );
  lv_obj_add_flag( cb_wifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS );
  lv_obj_set_style_text_font( cb_wifi, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT );

  // 2. WiFi Password Test and Password Input
  lv_obj_t * cont_pswd = lv_obj_create( main_cont );
  lv_obj_remove_style_all( cont_pswd );
  lv_obj_set_width( cont_pswd, LV_PCT(100) );
  lv_obj_set_height( cont_pswd, LV_PCT(20) );
  lv_obj_set_align( cont_pswd, LV_ALIGN_TOP_MID );
  lv_obj_set_flex_flow( cont_pswd, LV_FLEX_FLOW_ROW_WRAP );
  lv_obj_set_flex_align( cont_pswd, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY );
  lv_obj_remove_flag( cont_pswd, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );

  lv_obj_t * lbl_wifi_pswd = lv_label_create( cont_pswd );
  lv_obj_set_width( lbl_wifi_pswd, LV_SIZE_CONTENT );
  lv_obj_set_height( lbl_wifi_pswd, LV_SIZE_CONTENT );
  lv_obj_set_align( lbl_wifi_pswd, LV_ALIGN_CENTER );
  lv_label_set_text( lbl_wifi_pswd, "Password" );
  lv_obj_set_style_text_font( lbl_wifi_pswd, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT );

  txt_box_wifi_pswd = lv_textarea_create( cont_pswd );
  lv_obj_set_width( txt_box_wifi_pswd, 250 );
  lv_obj_set_height( txt_box_wifi_pswd, 50 );
  lv_obj_set_align( txt_box_wifi_pswd, LV_ALIGN_CENTER );
  lv_textarea_set_placeholder_text( txt_box_wifi_pswd, "Enter Password" );
  lv_textarea_set_password_mode( txt_box_wifi_pswd, true );

  lv_obj_t * check_box_show_pswd = lv_checkbox_create( cont_pswd );
  lv_checkbox_set_text( check_box_show_pswd, "Show Password" );
  lv_obj_set_width( check_box_show_pswd, LV_SIZE_CONTENT );
  lv_obj_set_height( check_box_show_pswd, LV_SIZE_CONTENT );
  lv_obj_set_align( check_box_show_pswd, LV_ALIGN_CENTER );
  // we may need to tune this again, based on the display size
  lv_obj_set_x( check_box_show_pswd, 10 );
  lv_obj_set_y( check_box_show_pswd, 35 );
  // here the flag LV_OBJ_FLAG_IGNORE_LAYOUT is added to avoid the checkbox being squished in the flex layout
  // else whole layout will be broken
  lv_obj_add_flag( check_box_show_pswd, LV_OBJ_FLAG_IGNORE_LAYOUT | LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );
  lv_obj_set_style_text_font( check_box_show_pswd, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_set_style_border_color( check_box_show_pswd, lv_color_hex(0x808080), LV_PART_INDICATOR | LV_STATE_DEFAULT );
  lv_obj_set_style_border_color( check_box_show_pswd, lv_color_hex(0x808080), LV_PART_INDICATOR | LV_STATE_CHECKED );
  lv_obj_set_style_bg_color( check_box_show_pswd, lv_color_hex(0x808080), LV_PART_INDICATOR | LV_STATE_CHECKED );
  lv_obj_set_style_border_opa( check_box_show_pswd, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT );

  // add event callback to the checkbox
  lv_obj_add_event_cb( check_box_show_pswd, check_box_show_pswd_event_cb, LV_EVENT_ALL, NULL );

  // 3. Button Row (Connect, Disconnect, Re-Scan)
  lv_obj_t * cont_btn = lv_obj_create( main_cont );
  lv_obj_remove_style_all( cont_btn );
  lv_obj_set_width( cont_btn, LV_PCT(100) );
  lv_obj_set_height( cont_btn, LV_PCT(20) );
  lv_obj_set_align( cont_btn, LV_ALIGN_TOP_MID );
  lv_obj_set_flex_flow( cont_btn, LV_FLEX_FLOW_ROW_WRAP );
  lv_obj_set_flex_align( cont_btn, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY );
  lv_obj_remove_flag( cont_btn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );

  // w_button_t * connect_btn = w_button_create( cont_btn, "Connect", NULL );
  // w_button_t * disconnect_btn = w_button_create( cont_btn, "Disconnect", NULL );
  // w_button_t * rescan_btn = w_button_create( cont_btn, "Re Scan", NULL );
  // NOTE: using the below lines to avoid warnings
  w_button_create( cont_btn, "Connect", btn_connect_event_cb );
  w_button_create( cont_btn, "Disconnect", btn_disconnect_event_cb );
  w_button_create( cont_btn, "Re Scan", btn_rescan_event_cb );

  // 4. Keyboard (hidden by default, shown when text area is focused)
  kb_wifi_pswd = lv_keyboard_create( main_cont );
  lv_obj_set_width( kb_wifi_pswd, LV_PCT(100) );
  lv_obj_set_height( kb_wifi_pswd, LV_PCT(40) );
  lv_obj_set_align( kb_wifi_pswd, LV_ALIGN_CENTER );

  // Assign a Text Area to the Keyboard. The pressed characters will be put there.
  lv_keyboard_set_textarea( kb_wifi_pswd, txt_box_wifi_pswd );
  lv_obj_add_event_cb( txt_box_wifi_pswd, txt_box_wifi_pswd_event_cb, LV_EVENT_ALL, NULL );
  // Hide the keyboard by default
  lv_obj_add_flag( kb_wifi_pswd, LV_OBJ_FLAG_HIDDEN );
}

static void txt_box_wifi_pswd_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  lv_obj_t * target = lv_event_get_target( e );
  switch ( code )
  {
  case LV_EVENT_FOCUSED:
  case LV_EVENT_CLICKED:
    // show the keyboard
    LV_LOG_USER( "Text Area Focused/Clicked" );
    // link the keyboard to the text area (in case not already done)
    lv_keyboard_set_textarea( kb_wifi_pswd, target );
    lv_obj_remove_flag( kb_wifi_pswd, LV_OBJ_FLAG_HIDDEN );
    break;
  case LV_EVENT_DEFOCUSED:
  case LV_EVENT_READY:
    // hide the keyboard
    LV_LOG_USER( "Text Area Defocused/Ready" );
    // Unlink the keyboard from the text area to avoid further input
    lv_keyboard_set_textarea( kb_wifi_pswd, NULL );
    lv_obj_add_flag( kb_wifi_pswd, LV_OBJ_FLAG_HIDDEN );
    break;
  default:
    break;
  }
}

static void btn_connect_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_CLICKED )
  {
    // lv_obj_t * btn = lv_event_get_target( e );
    LV_LOG_USER( "Connect Button Clicked" );
    // handle connect button click
  }
}

static void btn_disconnect_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_CLICKED )
  {
    // lv_obj_t * btn = lv_event_get_target( e );
    LV_LOG_USER( "Disconnect Button Clicked" );
    // handle disconnect button click
  }
}

static void btn_rescan_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_CLICKED )
  {
    // lv_obj_t * btn = lv_event_get_target( e );
    LV_LOG_USER( "Re-Scan Button Clicked" );
    // handle re-scan button click
  }
}

static void check_box_show_pswd_event_cb( lv_event_t * e )
{
  lv_event_code_t code = lv_event_get_code( e );
  if ( code == LV_EVENT_VALUE_CHANGED )
  {
    lv_obj_t * cb = lv_event_get_target( e );
    bool checked = lv_obj_has_state( cb, LV_STATE_CHECKED );
    LV_LOG_USER( "Show Password Checkbox: %s", checked ? "Checked" : "Unchecked" );
    if ( txt_box_wifi_pswd != NULL )
    {
      lv_textarea_set_password_mode( txt_box_wifi_pswd, !checked );
    }
  }
}

static void display_brightness_event( int32_t value )
{
  LV_LOG_USER("Display Brightness: %d", value);
}

static void display_contrast_event( int32_t value )
{
  LV_LOG_USER("Display Contrast: %d", value);
}

/*
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
    lv_obj_remove_flag(slider_row, LV_OBJ_FLAG_SCROLLABLE);

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

    // set the page
    // lv_menu_set_page(menu, main_page);
    lv_menu_set_sidebar_page( menu, main_page );
}

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
