#include "utils/ui_prefabs.h"

lv_obj_t* createButton(lv_obj_t* parent, const char* text, int32_t width, int32_t height, const lv_font_t* font, lv_event_cb_t event_cb, void* user_data, lv_obj_t** outLabel) {
    lv_obj_t* button = lv_btn_create(parent);
    lv_obj_set_size(button, width > 0 ? width : lv_pct(100), height > 0 ? height : lv_pct(100));
    lv_obj_set_style_bg_opa(button, LV_OPA_TRANSP, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_add_event_cb(button, event_cb, LV_EVENT_CLICKED, user_data);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_center(label);

    if (outLabel) {
        *outLabel = label;
    }

    return button;
}