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
        int displaysX;
        int displaysY;
        Screen();
        Screen(std::shared_ptr<game::Game> screenGame);
        std::shared_ptr<game::Game> getGame();
        std::deque<std::string> getLogBox();
        void addLog(std::string newLog);
        void updateLogBoxDisplay();
        void update();
    };
    std::ostream& operator<<(std::ostream& os, Screen screen);
}