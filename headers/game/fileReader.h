#pragma once
#include "game.h"
#include <optional>
#include <memory>

namespace fileReader {
    class FileReader {
        private:
        std::optional<std::string> save1;
        std::optional<std::string> save2;
        std::optional<std::string> save3;
        std::optional<std::string> save4;
        public:
        FileReader();
        std::shared_ptr<game::Game> loadGame(int idx);
        std::shared_ptr<canvas::Canvas> loadTitleScreeen();
        void saveGame(int idx, std::shared_ptr<game::Game> game);
    };
}