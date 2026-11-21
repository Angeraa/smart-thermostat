#pragma once

#include "modules/ui/screens/Screen.h"

class HvacModeSelectScreen final : public Screen {
public:
    void create(lv_obj_t *root) override;
    void show() override;
    void hide() override;
    void update(const AppState& appState) override;

private:
    lv_obj_t* autoButton = nullptr;
    lv_obj_t* heatButton = nullptr;
    lv_obj_t* coolButton = nullptr;
    lv_obj_t* offButton = nullptr;

    lv_obj_t* autoLabel = nullptr;
    lv_obj_t* heatLabel = nullptr;
    lv_obj_t* coolLabel = nullptr;
    lv_obj_t* offLabel = nullptr;
};