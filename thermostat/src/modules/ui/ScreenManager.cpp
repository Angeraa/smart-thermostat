#include "modules/ui/ScreenManager.h"
#include "modules/ui/screenRegistry.h"
#include "utils/logging.h"
#include "utils/uiPrefabs.h"
#include "modules/ui/ui_events.h"
#include <algorithm>

lv_obj_t* createTopbar(lv_obj_t* parent) {
    lv_obj_t* topbar = lv_obj_create(parent);
    lv_obj_set_size(topbar, LV_PCT(100), MENU_TOPBAR_HEIGHT);
    lv_obj_set_pos(topbar, 0, 0);
    lv_obj_move_foreground(topbar);
    lv_obj_set_style_layout(topbar, LV_LAYOUT_FLEX, 0);
    lv_obj_set_style_flex_flow(topbar, LV_FLEX_FLOW_ROW, 0);
    lv_obj_set_style_flex_main_place(topbar, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
    lv_obj_set_style_flex_cross_place(topbar, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_track_place(topbar, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_all(topbar, 15, 0);
    lv_obj_set_style_bg_opa(topbar, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(topbar, 0, 0);
    lv_obj_set_style_radius(topbar, 0, 0);
    lv_obj_remove_flag(topbar, LV_OBJ_FLAG_SCROLLABLE);

    // Menu Buttons
    lv_obj_t* backButton = createButton(topbar, LV_SYMBOL_LEFT, 75, 75, &lv_font_montserrat_32, [](lv_event_t* e) {
        postUIEvent({UIEventId::Back});
    }, nullptr);

    lv_obj_t* settingsButton = createButton(topbar, LV_SYMBOL_SETTINGS, 75, 75, &lv_font_montserrat_32, [](lv_event_t* e) {
        postUIEvent({UIEventId::SwitchScreen, static_cast<int>(ScreenId::Settings)});
    }, nullptr);

    return topbar;
}

void updateTopbar(lv_obj_t* topbar, ScreenId id) {
    auto needs_topbar = std::find_if(screens_that_need_global_topbar.begin(), screens_that_need_global_topbar.end(), [id](ScreenId screenId) {
        return screenId == id;
    });
    if (needs_topbar != screens_that_need_global_topbar.end()) {
        lv_obj_remove_flag(topbar, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(topbar);
    } else {
        lv_obj_add_flag(topbar, LV_OBJ_FLAG_HIDDEN);
    }
};

void ScreenManager::init() {

    root = lv_obj_create(NULL);
    lv_obj_set_size(root, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(root, lv_color_hex(COLOR_BACKGROUND), 0);
    lv_obj_set_style_border_width(root, 0, 0);
    lv_obj_set_style_radius(root, 0, 0);
    lv_obj_set_style_pad_all(root, 0, 0);
    lv_obj_remove_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    logDebug("Creating screens...", "UI");
    for (auto i = 0; i < screenCount; i++) {
        lv_obj_t* screenRoot = lv_obj_create(root);
        lv_obj_set_pos(screenRoot, 0, 0);
        lv_obj_set_size(screenRoot, LV_PCT(100), LV_PCT(100));
        lv_obj_set_style_border_width(screenRoot, 0, 0);
        lv_obj_set_style_radius(screenRoot, 0, 0);
        lv_obj_set_style_pad_all(screenRoot, 0, 0);
        lv_obj_set_style_bg_opa(screenRoot, LV_OPA_TRANSP, 0);
        lv_obj_remove_flag(screenRoot, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
        screenTable[i]->create(screenRoot);
        screenTable[i]->hide();
    }

    // Topbar
    topbar = createTopbar(root);
    lv_obj_add_flag(topbar, LV_OBJ_FLAG_HIDDEN);

    screenTable[toIndex(screenStack[stackPointer])]->show();
    lv_screen_load(root);
    logInfo("ScreenManager initialized", "UI");
}

void ScreenManager::set(ScreenId id) {
    if (id == screenStack[stackPointer]) return;
    if (toIndex(id) >= screenCount) return;

    updateTopbar(topbar, id);

    for (int i = stackPointer; i >= 0; i--) {
        if (screenStack[i] == id) {
            screenTable[toIndex(screenStack[stackPointer])]->hide();
            stackPointer = i;
            screenTable[toIndex(screenStack[stackPointer])]->show();
            return;
        }
    }
    screenTable[toIndex(screenStack[stackPointer])]->hide();
    stackPointer++;
    screenStack[stackPointer] = id;
    screenTable[toIndex(screenStack[stackPointer])]->show();
}

void ScreenManager::set(ScreenId id, const AppState& appState) {
    if (id == screenStack[stackPointer]) return;
    if (toIndex(id) >= screenCount) return;

    updateTopbar(topbar, id);

    for (int i = stackPointer; i >= 0; i--) {
        if (screenStack[i] == id) {
            // Pre update the screen before showing it again in the case of cross-screen updates
            screenTable[toIndex(screenStack[i])]->update(appState);
            screenTable[toIndex(screenStack[stackPointer])]->hide();
            stackPointer = i;
            screenTable[toIndex(screenStack[stackPointer])]->show();
            return;
        }
    }
    // Update the new screen with the provided app state
    screenTable[toIndex(id)]->update(appState);
    screenTable[toIndex(screenStack[stackPointer])]->hide();
    stackPointer++;
    screenStack[stackPointer] = id;
    screenTable[toIndex(screenStack[stackPointer])]->show();
}

void ScreenManager::back() {
    if (stackPointer == 0) return;
    screenTable[toIndex(screenStack[stackPointer])]->hide();
    stackPointer--;
    updateTopbar(topbar, screenStack[stackPointer]);
    screenTable[toIndex(screenStack[stackPointer])]->show();
}

void ScreenManager::update(const AppState& appState) {
    screenTable[toIndex(screenStack[stackPointer])]->update(appState);
}

void ScreenManager::openSetpointDialog(const UIEvent& e) {
    if (e.id != UIEventId::OpenSetpointDialog) return;
    if (!e.callback) {
        logError("No callback provided for OpenSetpointDialog event", "UI");
        return;
    }
    if (!e.context) {
        logError("No context provided for OpenSetpointDialog event", "UI");
        return;
    }
    eventCallback = e.callback;
    eventContext = e.context;
    static_cast<SetpointScreen*>(screenTable[toIndex(ScreenId::Setpoint)])->configure(e.value, 150, 300);
    set(ScreenId::Setpoint);
}

void ScreenManager::setpointSelected(int temperature) {
    auto callback = eventCallback;
    auto context = eventContext;

    eventCallback = nullptr;
    eventContext = nullptr;
    if (callback && context) {
        callback(context, temperature);
    }
    back();
}
