#include "headers/objects/apartments/apartment.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include <vector>

int main() {
    game::Game newGame = game::Game();
    saveReader::loadGame("start",newGame);
    saveReader::saveGame("end",newGame);
    std::cout << *newGame.getApartments()[0];
    std::cout << *newGame.getApartments()[0]->getRooms()[0]->getFurniture()[2];
    return 0;
}

//TO DO : probably make class time, write class market, generating utilities, (!) finish saving and loading files, class game, unit tests, make room state relevant