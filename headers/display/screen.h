#pragma once
#include "../game/game.h"
#include "display.h"
#include <memory>
#include <deque>
#include <string>
#include <iostream>
namespace screen {
    class Screen {
        private:
        std::shared_ptr<game::Game> game;
        int logBoxMemory;
        public:
        std::vector<std::shared_ptr<display::Display>> displays;
        std::deque<std::string> logBox;
        std::vector<int> displayWidths;
        std::vector<int> displayHeights;
        int logBoxHeight;
        int logBoxWidth;
        int displaysX;
        std::vector<int> displaysY;
        //std::tuple<std::vector<action::Action<display::Display>>,std::vector<action::Action<apartment::Apartment>>,std::vector<action::Action<room::Room>>,std::vector<action::Action<tenant::Tenant>>> actions;
        Screen();
        Screen(std::shared_ptr<game::Game> screenGame);
        std::shared_ptr<game::Game> getGame();
        std::deque<std::string> getLogBox();
        void addLog(std::string newLog);
        void update();
        void updateLine(int idx);
        void updateDisplays();
        void updateDisplay(int idx);
        std::vector<std::string> getScreen();
    };
    std::ostream& operator<<(std::ostream& os, Screen screen);
}