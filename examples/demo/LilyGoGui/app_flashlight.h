#pragma once

#include "app_typedef.h"
#include "lvgl.h"

#define LV_COLOR_WHITE LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)
#define LV_COLOR_BLACK LV_COLOR_MAKE(0x00, 0x00, 0x00)

extern app_t app_flashlight;

void app_flashlight_load(lv_obj_t *cont);