#include "modules/ui/screens/HvacModeSelectScreen.h"
#include "modules/ui/ui_events.h"

void onAutoButtonClick(lv_event_t *e) {
    postUIEvent({UIEventId::HvacModeChanged, static_cast<int>(HvacMode::AUTO)});
    postUIEvent({UIEventId::Back});
}

void onHeatButtonClick(lv_event_t *e) {
    postUIEvent({UIEventId::HvacModeChanged, static_cast<int>(HvacMode::HEAT)});
    postUIEvent({UIEventId::Back});
}

void onCoolButtonClick(lv_event_t *e) {
    postUIEvent({UIEventId::HvacModeChanged, static_cast<int>(HvacMode::COOL)});
    postUIEvent({UIEventId::Back});
}

void onOffButtonClick(lv_event_t *e) {
    postUIEvent({UIEventId::HvacModeChanged, static_cast<int>(HvacMode::OFF)});
    postUIEvent({UIEventId::Back});
}

void onBackgroundClick(lv_event_t *e) {
    postUIEvent({UIEventId::Back});
}

void HvacModeSelectScreen::create(lv_obj_t *root) {
    container = root;
    lv_obj_add_flag(container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(container, onBackgroundClick, LV_EVENT_CLICKED, NULL);

    lv_obj_t* buttonContainer = lv_obj_create(container);
    lv_obj_set_width(buttonContainer, 600);
    lv_obj_set_height(buttonContainer, LV_SIZE_CONTENT);
    lv_obj_align(buttonContainer, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(buttonContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(buttonContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(buttonContainer, 10, 0);
    lv_obj_set_style_border_color(buttonContainer, lv_color_hex(COLOR_TEXT_MAIN), 0);
    lv_obj_set_style_border_width(buttonContainer, 3, 0);
    lv_obj_set_style_radius(buttonContainer, 25, 0);
    lv_obj_set_style_bg_opa(buttonContainer, LV_OPA_TRANSP, 0);

    autoButton = lv_btn_create(buttonContainer);
    lv_obj_set_size(autoButton, lv_pct(100), 100);
    lv_obj_align(autoButton, LV_ALIGN_CENTER, -150, -50);
    lv_obj_add_event_cb(autoButton, onAutoButtonClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(autoButton, 0, LV_PART_MAIN);
    autoLabel = lv_label_create(autoButton);
    lv_label_set_text(autoLabel, "Auto");
    lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    lv_obj_set_style_text_font(autoLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(autoLabel);

    heatButton = lv_btn_create(buttonContainer);
    lv_obj_set_size(heatButton, lv_pct(100), 100);
    lv_obj_align(heatButton, LV_ALIGN_CENTER, 150, -50);
    lv_obj_add_event_cb(heatButton, onHeatButtonClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(heatButton, 0, LV_PART_MAIN);
    heatLabel = lv_label_create(heatButton);
    lv_label_set_text(heatLabel, "Heat");
    lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    lv_obj_set_style_text_font(heatLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(heatLabel);

    coolButton = lv_btn_create(buttonContainer);
    lv_obj_set_size(coolButton, lv_pct(100), 100);
    lv_obj_align(coolButton, LV_ALIGN_CENTER, -150, 50);
    lv_obj_add_event_cb(coolButton, onCoolButtonClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(coolButton, 0, LV_PART_MAIN);
    coolLabel = lv_label_create(coolButton);
    lv_label_set_text(coolLabel, "Cool");
    lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    lv_obj_set_style_text_font(coolLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(coolLabel);

    offButton = lv_btn_create(buttonContainer);
    lv_obj_set_size(offButton, lv_pct(100), 100);
    lv_obj_align(offButton, LV_ALIGN_CENTER, 150, 50);
    lv_obj_add_event_cb(offButton, onOffButtonClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(offButton, 0, LV_PART_MAIN);
    offLabel = lv_label_create(offButton);
    lv_label_set_text(offLabel, "Off");
    lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    lv_obj_set_style_text_font(offLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(offLabel);

    created = true;
}

void HvacModeSelectScreen::show() {
    lv_obj_clear_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void HvacModeSelectScreen::hide() {
    lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void HvacModeSelectScreen::update(const AppState& appState) {
    if (appState.mode == HvacMode::AUTO) {
        lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);

        lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    } else if (appState.mode == HvacMode::HEAT) {
        lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);

        lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    } else if (appState.mode == HvacMode::COOL) {
        lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);

        lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    } else if (appState.mode == HvacMode::OFF) {
        lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);

        lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
        lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
    }
}