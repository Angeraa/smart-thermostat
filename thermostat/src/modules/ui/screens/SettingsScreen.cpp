#include "modules/ui/screens/SettingsScreen.h"
#include "modules/ui/ui_events.h"
#include "utils/uiPrefabs.h"
#include <iomanip>
#include <sstream>
#include <string>

char* options[] = {"Preferences", "Thresholds", "About"};
size_t numOptions = sizeof(options) / sizeof(options[0]);

static void onBackButtonClicked(lv_event_t*) {
    postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Home)});
}

static void onOptionSelected(lv_event_t* e) {
    size_t index = reinterpret_cast<size_t>(lv_event_get_user_data(e));
    switch (index) {
        case 0: // Preferences
            postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Settings)});
            break;
        case 1: // Thresholds
            postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Settings)});
            break;
        case 2: // About
            postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Settings)});
            break;
        default:
            break;
    }
}

void SettingsScreen::create(lv_obj_t* root) {
    container = root;
    lv_obj_set_style_pad_top(container, MENU_TOPBAR_HEIGHT, 0);

    lv_obj_t* content = lv_obj_create(container);
    lv_obj_set_size(content, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(content, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content, 0, 0);
    lv_obj_set_style_pad_all(content, 0, 0);

    lv_obj_t* optionsList = lv_obj_create(content);
    lv_obj_set_size(optionsList, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(optionsList, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(optionsList, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_opa(optionsList, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(optionsList, 0, 0);
    lv_obj_set_style_pad_all(optionsList, 0, 0);
    lv_obj_set_style_pad_row(optionsList, 0, 0);
    lv_obj_set_scrollbar_mode(optionsList, LV_SCROLLBAR_MODE_OFF);

    for (size_t i = 0; i < numOptions; ++i) {
        lv_obj_t* button = createButton(optionsList, options[i], 0, 100, &lv_font_montserrat_32, onOptionSelected, reinterpret_cast<void*>(i));
        lv_obj_set_style_border_width(button, 2, 0);
        lv_obj_set_style_border_color(button, lv_color_hex(COLOR_TEXT_MAIN), 0);
        lv_obj_set_style_border_side(button, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP, 0);
    }

    created = true;
}

void SettingsScreen::show() {
    lv_obj_clear_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void SettingsScreen::hide() {
    lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void SettingsScreen::update(const AppState& appState) {}