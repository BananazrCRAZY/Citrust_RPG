#pragma once
#include "include/Buttons/SolidButton.hpp"
#include "include/Buttons/button.hpp"
#include "include/Popups/IndefinitePopup.hpp"
#include "include/Screens/ScreenManager.hpp"
#include "include/Objects/Item.h"
#include <string>

using std::string;

class ItemPopup : public IndefinitePopup {
    protected:
        ScreenManager& manager;
        string itemDesc[3];
        int itemLines;
        string effectDesc[3];
        int effectLines;
        unsigned itemIndex;
        SolidButton icon;
        Button secondButton;
        int maxWidth;
        bool needToUpdateDesc;
        Item* item;

        void reshapeMsg(string text, string (&arr)[3], int& lines, int fsize);
    
    public:
        ItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            unsigned index, ScreenManager& m, const char *secondaryButtonImage);
        void Draw();
        virtual void showItem(unsigned) = 0;
        unsigned getIndex() const;
};