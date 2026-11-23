#pragma once

#include "modules/ui/screens/Screen.h"
#include "modules/ui/UIEvent.h"
#include <array>
#include <cstddef>
#include <string>

constexpr size_t MAX_ITEM_SELECTOR_OPTIONS = 16;

class ItemSelectorScreen final : public Screen {
public:
    void create(lv_obj_t* root) override;
    void show() override;
    void hide() override;
    void update(const AppState& appState) override;

    void configure(const char* title, const ItemSelectorOption* options, size_t optionCount, int selectedValue);
    template<size_t N>
    void configure(const std::string& title, const std::array<ItemSelectorOption, N>& options, int selectedValue) {
        static_assert(N <= MAX_ITEM_SELECTOR_OPTIONS, "Too many item selector options");
        configure(title.c_str(), options.data(), options.size(), selectedValue);
    }
    template<size_t N>
    void configure(const std::string& title, const std::array<int, N>& values, int selectedValue) {
        static_assert(N <= MAX_ITEM_SELECTOR_OPTIONS, "Too many item selector values");
        std::array<ItemSelectorOption, N> options{};
        std::array<std::string, N> labels{};
        for (size_t i = 0; i < N; ++i) {
            labels[i] = std::to_string(values[i]);
            options[i] = {labels[i].c_str(), values[i]};
        }
        configure(title.c_str(), options.data(), options.size(), selectedValue);
    }
    template<size_t N>
    void configure(const std::string& title, const std::array<std::string, N>& labels, int selectedIndex) {
        static_assert(N <= MAX_ITEM_SELECTOR_OPTIONS, "Too many item selector labels");
        std::array<ItemSelectorOption, N> options{};
        for (size_t i = 0; i < N; ++i) {
            options[i] = {labels[i].c_str(), static_cast<int>(i)};
        }
        configure(title.c_str(), options.data(), options.size(), selectedIndex);
    }

    int getSelectedValue() const { return selectedValue; }
    void selectOption(size_t index);
    void selectOption(lv_obj_t* target);

private:
    lv_obj_t* titleLabel = nullptr;
    lv_obj_t* backButton = nullptr;
    lv_obj_t* buttonContainer = nullptr;
    size_t configuredOptionCount = 0;
    std::array<ItemSelectorOption, MAX_ITEM_SELECTOR_OPTIONS> configuredOptions{};
    std::array<lv_obj_t*, MAX_ITEM_SELECTOR_OPTIONS> optionButtons{};
    std::array<lv_obj_t*, MAX_ITEM_SELECTOR_OPTIONS> optionLabels{};
    std::array<std::string, MAX_ITEM_SELECTOR_OPTIONS> labelStrings{};
    int selectedValue = 0;
};

using GenericItemSelectorScreen = ItemSelectorScreen;
using ItemSelectScreen = ItemSelectorScreen;
