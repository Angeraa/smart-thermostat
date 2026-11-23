#pragma once

#include <array>

#include "modules/ui/screens/Screen.h"
#include "modules/ui/screens/HomeScreen.h"
#include "modules/ui/screens/SettingsScreen.h"
#include "modules/ui/screens/SetpointScreen.h"
#include "modules/ui/screens/ItemSelectorScreen.h"

extern const std::array<Screen*, static_cast<size_t>(ScreenId::Count)> screenTable;
extern const std::array<ScreenId, 1> screens_that_need_global_topbar;
