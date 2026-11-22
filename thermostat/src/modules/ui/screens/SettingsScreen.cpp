#include "modules/ui/screens/SettingsScreen.h"
#include "modules/ui/ui_events.h"
#include "utils/ui_prefabs.h"
#include <iomanip>
#include <sstream>
#include <string>

static void onBackButtonClicked(lv_event_t*) {
    postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Home)});
}

void SettingsScreen::create(lv_obj_t* root) {
    container = root;
    lv_obj_set_style_pad_top(container, MENU_TOPBAR_HEIGHT, 0);

    lv_obj_t* content = lv_obj_create(container);
    lv_obj_set_style_pad_top(content, MENU_TOPBAR_HEIGHT, 0);
    lv_obj_set_size(content, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(content, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_opa(content, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content, 0, 0);

    iaqLabel = lv_label_create(content);
    lv_obj_set_style_text_color(iaqLabel, lv_color_hex(COLOR_TEXT_MAIN), 0);
    lv_obj_set_style_text_font(iaqLabel, &lv_font_montserrat_24, 0);

    created = true;
}

void SettingsScreen::show() {
    lv_obj_clear_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void SettingsScreen::hide() {
    lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void SettingsScreen::update(const AppState& appState) {
    lv_label_set_text(iaqLabel, ("IAQ: " + std::to_string(appState.currIAQ)).c_str());
}
