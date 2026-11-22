#pragma once

#include "lvgl/lvgl.h"

lv_obj_t* createButton(lv_obj_t* parent, const char* text, int32_t width, int32_t height, const lv_font_t* font, lv_event_cb_t event_cb, void* user_data = nullptr, lv_obj_t** outLabel = nullptr);

