#pragma once
#include "game.h"
#include <memory>

namespace fileReader {
    class FileReader {
        private:
        std::string saves[4];
        std::string help;
        std::string titlescreen;
        public:
        FileReader();
        std::shared_ptr<game::Game> loadGame(int idx);
        std::shared_ptr<canvas::Canvas> loadTitleScreeen();
        void saveGame(int idx, std::shared_ptr<game::Game> game);
        std::vector<format::FormattedString> loadHelp(std::string actionName);
    };
}