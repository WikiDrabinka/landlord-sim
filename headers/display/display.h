#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../game/game.h"
#include "format.h"
namespace display {
    enum displayType {apartment,apartments,tenants,rooms,furniture,messages,conversation,utilities,store,storage,other};
    class Display {
        private:
        format::MultiFormattedString name;
        const int width;
        const int height;
        std::vector<int> idx;
        std::shared_ptr<game::Game> game;
        std::vector<format::FormattedString> text;
        int displayStart;
        displayType type;
        public:
        Display(std::string displayName, int displayWidth, int displayHeight, displayType displayType, std::shared_ptr<game::Game> displayGame);
        std::vector<std::string> getDisplay();
        displayType getType();
        void scrollUp(int i=1);
        void scrollDown(int i=1);
        void updateDisplay(std::string newText="");
        void changeDisplay(displayType newType, std::string newName);
        void changeDisplay(std::vector<int> newIdx);
    };
}