#include "app_flashlight.h"
#include "Arduino.h"
#include <LilyGoLib.h>

extern LilyGoLib watch;

static void toggle_flashlight_event_cb(lv_event_t *e);
static bool flashlight_on = false;
lv_obj_t *background;
lv_obj_t *label;

void app_flashlight_load(lv_obj_t *cont) {
  // Create a black background view
  background = lv_obj_create(cont);
  lv_obj_set_size(background, 240, 240);
  lv_obj_set_style_bg_color(background, lv_color_hex(0x000000), 0);
  lv_obj_add_event_cb(background, toggle_flashlight_event_cb, LV_EVENT_CLICKED, NULL);

  // Create a label in the middle of the screen
  label = lv_label_create(cont);
  lv_label_set_text(label, "Turn On");
  lv_obj_align(label,LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
}

static void toggle_flashlight_event_cb(lv_event_t *e) {
  if (flashlight_on) {
    // Turn off flashlight
    lv_obj_set_style_bg_color(background, lv_color_hex(0x000000), 0);
    watch.setBrightness((uint8_t)50);
    lv_label_set_text(label, "Turn On");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    flashlight_on = false;
  } else {
    // Turn on flashlight
    lv_obj_set_style_bg_color(background, lv_color_hex(0xFFFFFF), 0);
    watch.setBrightness((uint8_t)100);
    lv_label_set_text(label, "Turn Off");
    lv_obj_set_style_text_color(label, lv_color_hex(0x000000), LV_PART_MAIN);
    flashlight_on = true;
  }
}

app_t app_flashlight = {
    .setup_func_cb = app_flashlight_load,
    .exit_func_cb = nullptr,
    .user_data = nullptr,
};
