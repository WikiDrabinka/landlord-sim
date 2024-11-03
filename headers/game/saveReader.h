#include "game.h"
namespace saveReader {
    void loadGame(std::string filePath, game::Game &newGame);
    void saveGame(std::string filePath, game::Game &newGame);
}