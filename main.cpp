#include "headers/objects/apartments/apartment.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include <vector>

int main() {
    game::Game newGame = game::Game();
    std::cout << *newGame.getApartments()[0];
    return 0;
}

//TO DO : probably make class time, write class market, generating utilities, (!) finish saving and loading files, class game, unit tests, make room state relevant