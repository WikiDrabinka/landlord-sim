#pragma once
#include "../game/game.h"
#include <memory>
#include <deque>
#include <string>
#include <iostream>
namespace screen {
    enum sideDisplay {empty,furniture,tenant,store,apartments,rooms};
    class Screen {
        private:
        std::shared_ptr<game::Game> game;
        int selectedApartment;
        sideDisplay display;
        std::vector<int> selectedSideDisplay;
        std::deque<std::string> logBox;
        int logBoxMemory;
        std::vector<std::string> displayActions;
        std::vector<std::string> actionActions;
        public:
        int apartmentWidth;
        int sideDisplayWidth;
        int totalWidth;
        int topHeight;
        int logBoxHeight;
        Screen();
        std::shared_ptr<apartment::Apartment> getDisplayedApartment();
        std::shared_ptr<game::Game> getGame();
        std::deque<std::string> getLogBox();
        void setSelectedApartment(int idx);
        void setSideDisplay(sideDisplay newDisplay);
        void setSelectedSideDisplay(int idx);
        void addLog(std::string newLog);
        void updateLine(int idx);
        void updateLogBoxDisplay();
        void update();
    };
    std::ostream& operator<<(std::ostream& os, Screen screen);
}