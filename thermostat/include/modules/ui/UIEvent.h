#pragma once

#include <cstddef>

enum class UIEventId {
    SwitchScreen,
    Back,
    OpenSetpointDialog,
    SetpointSelected,
    OpenItemSelectorDialog,
    ItemSelectorSelected,

    // State Change Events
    HeatSetpointChanged,
    CoolSetpointChanged,
    HvacModeChanged,
};

typedef void (*UIEventCallback)(void*, int);

struct ItemSelectorOption {
    const char* label = nullptr;
    int value = 0;
};

struct UIEvent {
    UIEventId id = UIEventId::SwitchScreen;
    int value = 0;
    UIEventCallback callback = nullptr;
    void* context = nullptr;
    const char* title = nullptr;
    const ItemSelectorOption* options = nullptr;
    size_t optionCount = 0;
};