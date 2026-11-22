#include "modules/ui/screens/HvacModeSelectScreen.h"
#include "modules/ui/ui_events.h"
#include "utils/ui_prefabs.h"

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

    autoButton = createButton(buttonContainer, "Auto", LV_PCT(100), 100, &lv_font_montserrat_32, onAutoButtonClick, nullptr, &autoLabel);
    lv_obj_align(autoButton, LV_ALIGN_CENTER, -150, -50);
    lv_obj_set_style_bg_color(autoButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(autoButton, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(autoLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);

    heatButton = createButton(buttonContainer, "Heat", LV_PCT(100), 100, &lv_font_montserrat_32, onHeatButtonClick, nullptr, &heatLabel);
    lv_obj_align(heatButton, LV_ALIGN_CENTER, 150, -50);
    lv_obj_set_style_bg_color(heatButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(heatButton, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(heatLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);

    coolButton = createButton(buttonContainer, "Cool", LV_PCT(100), 100, &lv_font_montserrat_32, onCoolButtonClick, nullptr, &coolLabel);
    lv_obj_align(coolButton, LV_ALIGN_CENTER, -150, 50);
    lv_obj_set_style_bg_color(coolButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(coolButton, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(coolLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);

    offButton = createButton(buttonContainer, "Off", LV_PCT(100), 100, &lv_font_montserrat_32, onOffButtonClick, nullptr, &offLabel);
    lv_obj_align(offButton, LV_ALIGN_CENTER, 150, 50);
    lv_obj_set_style_bg_color(offButton, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
    lv_obj_set_style_border_width(offButton, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(offLabel, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);

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