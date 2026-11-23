#include "modules/ui/screenRegistry.h"

static HomeScreen homeScreen;
static SettingsScreen settingsScreen;
static SetpointScreen setpointScreen;
static ItemSelectorScreen itemSelectorScreen;

const std::array<Screen*, static_cast<size_t>(ScreenId::Count)> screenTable = {
    &homeScreen,
    &settingsScreen,
    &setpointScreen,
    &itemSelectorScreen
};

const std::array<ScreenId, 1> screens_that_need_global_topbar = {
    ScreenId::Settings,
    // ScreenId::Sensors,
    // ScreenId::AirQuality,
    // ScreenId::Settings, current Settings changes to Menu
};
