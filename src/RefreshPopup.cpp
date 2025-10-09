#include "include/Popups/RefreshPopup.hpp"

RefreshPopup::RefreshPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath,
    ScreenManager& mgr) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    mgr(mgr),
    refresh("", {900, 600}, .8)
{
    hasEnough = (mgr.getCalories() >= refreshCost);
    if (hasEnough) refresh.SetTexture("Graphics/Buttons/refreshButtonGreen.png", .8);
    else refresh.SetTexture("Graphics/Buttons/refreshButtonGray.png", .8);
}

void RefreshPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (cancelButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        return;
    }

    if (hasEnough) {
        if (refresh.isPressed(mousePos, mouseClicked)) {
            mgr.getCaloriesVar() -= refreshCost;
            mgr.getShop()->resetShop();
            visible = false;
        }
    }
}

void RefreshPopup::Draw() {
    if (!visible) return;
    IndefinitePopup::Draw();

    string text = "Would you like to";
    int textWidth = MeasureText(text.c_str(), 50);
    DrawText(text.c_str(), box.x + (box.width - textWidth)/2, box.y + 200, 50, BLACK);
    string text2 = "refresh the shop items?";
    int text2Width = MeasureText(text2.c_str(), 50);
    DrawText(text2.c_str(), box.x + (box.width - text2Width)/2, box.y + 260, 50, BLACK);
    string costText = "Cost: " + to_string(refreshCost);
    int costTextWidth = MeasureText(costText.c_str(), 40);
    DrawText(costText.c_str(), box.x + (box.width - costTextWidth)/2, box.y + 400, 40, BLACK);

    refresh.Draw();
}

void RefreshPopup::showPopup() {
    hasEnough = (mgr.getCalories() >= refreshCost);
    if (hasEnough) refresh.SetTexture("Graphics/Buttons/refreshButtonGreen.png", .8);
    else refresh.SetTexture("Graphics/Buttons/refreshButtonGray.png", .8);
    visible = true;
}