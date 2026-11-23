#include "modules/ui/screens/ItemSelectorScreen.h"
#include "modules/ui/ui_events.h"
#include "utils/uiPrefabs.h"
#include <cstring>

constexpr uint8_t TITLE_FONT_SIZE_THRESHOLD = 12;

static void onItemSelectorBackClick(lv_event_t* e) {
    ItemSelectorScreen* screen = static_cast<ItemSelectorScreen*>(lv_event_get_user_data(e));
    postUIEvent({UIEventId::ItemSelectorSelected, screen->getSelectedValue()});
}

static void onItemSelectorOptionClick(lv_event_t* e) {
    ItemSelectorScreen* screen = static_cast<ItemSelectorScreen*>(lv_event_get_user_data(e));
    screen->selectOption(static_cast<lv_obj_t*>(lv_event_get_target(e)));
}

void ItemSelectorScreen::create(lv_obj_t* root) {
    container = root;

    lv_obj_t* topbar = lv_obj_create(container);
    lv_obj_set_size(topbar, LV_PCT(100), 100);
    lv_obj_set_style_pad_all(topbar, 0, 0);
    lv_obj_set_style_bg_opa(topbar, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(topbar, 0, 0);

    titleLabel = lv_label_create(topbar);
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(titleLabel, lv_color_hex(COLOR_TEXT_MAIN), 0);
    lv_obj_set_align(titleLabel, LV_ALIGN_CENTER);
    lv_label_set_text(titleLabel, "");

    backButton = createButton(topbar, LV_SYMBOL_LEFT, 75, 75, &lv_font_montserrat_32,
                              onItemSelectorBackClick, this);
    lv_obj_set_align(backButton, LV_ALIGN_LEFT_MID);

    buttonContainer = lv_obj_create(container);
    lv_obj_set_width(buttonContainer, 600);
    lv_obj_set_height(buttonContainer, LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(buttonContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(buttonContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_align(buttonContainer, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(buttonContainer, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(buttonContainer,
                          LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_all(buttonContainer, 10, 0);
    lv_obj_set_style_pad_row(buttonContainer, 10, 0);
    lv_obj_set_style_pad_column(buttonContainer, 10, 0);
    lv_obj_set_style_border_color(buttonContainer, lv_color_hex(COLOR_TEXT_MAIN), 0);
    lv_obj_set_style_border_width(buttonContainer, 3, 0);
    lv_obj_set_style_radius(buttonContainer, 25, 0);
    lv_obj_set_style_bg_opa(buttonContainer, LV_OPA_TRANSP, 0);

    created = true;
}

void ItemSelectorScreen::configure(const char* title,
                                   const ItemSelectorOption* options,
                                   size_t optionCount,
                                   int selectedValue) {
    if (optionCount > MAX_ITEM_SELECTOR_OPTIONS) {
        optionCount = MAX_ITEM_SELECTOR_OPTIONS;
    }
    configuredOptionCount = optionCount;
    optionButtons.fill(nullptr);
    optionLabels.fill(nullptr);
    for (size_t i = 0; i < optionCount; ++i) {
        labelStrings[i] = options[i].label ? options[i].label : "";
        configuredOptions[i] = {labelStrings[i].c_str(), options[i].value};
    }
    lv_label_set_text(titleLabel, title ? title : "");
    if (title && std::strlen(title) > TITLE_FONT_SIZE_THRESHOLD) {
        lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_32, 0);
    } else {
        lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_48, 0);
    }

    if (!optionCount) {
        this->selectedValue = selectedValue;
        lv_obj_clean(buttonContainer);
        lv_obj_set_height(buttonContainer, LV_SIZE_CONTENT);
        return;
    }

    this->selectedValue = selectedValue;
    lv_obj_clean(buttonContainer);

    for (size_t i = 0; i < configuredOptionCount; ++i) {
        lv_obj_t* label = nullptr;
        lv_obj_t* button = createButton(buttonContainer,
                                        configuredOptions[i].label ? configuredOptions[i].label : "",
                                        0,
                                        100,
                                        &lv_font_montserrat_32,
                                        onItemSelectorOptionClick,
                                        this,
                                        &label);
        lv_obj_set_style_bg_color(button, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
        lv_obj_set_style_border_width(button, 0, LV_PART_MAIN);
        lv_obj_set_style_text_color(label, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);

        if (configuredOptions[i].value == selectedValue) {
            lv_obj_set_style_bg_color(button, lv_color_hex(COLOR_TEXT_MAIN), LV_PART_MAIN);
            lv_obj_set_style_text_color(label, lv_color_hex(COLOR_BACKGROUND), LV_PART_MAIN);
            lv_obj_set_style_bg_opa(button, LV_OPA_COVER, LV_PART_MAIN);
            this->selectedValue = selectedValue;
        }
 
        optionButtons[i] = button;
        optionLabels[i] = label;
    }

    if (configuredOptionCount > 5) {
        lv_obj_set_height(buttonContainer, 550);
    } else {
        lv_obj_set_height(buttonContainer, LV_SIZE_CONTENT);
    }
    lv_obj_scroll_to(buttonContainer, 0, 0, LV_ANIM_OFF);
}

void ItemSelectorScreen::show() {
    lv_obj_clear_flag(container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_scroll_to(buttonContainer, 0, 0, LV_ANIM_OFF);
}

void ItemSelectorScreen::hide() {
    lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN);
}

void ItemSelectorScreen::update(const AppState&) {}

void ItemSelectorScreen::selectOption(size_t index) {
    if (index >= configuredOptionCount) return;
    selectedValue = configuredOptions[index].value;
    postUIEvent({UIEventId::ItemSelectorSelected, selectedValue});
}

void ItemSelectorScreen::selectOption(lv_obj_t* target) {
    for (size_t i = 0; i < configuredOptionCount; ++i) {
        if (optionButtons[i] == target) {
            selectOption(i);
            return;
        }
    }
}
