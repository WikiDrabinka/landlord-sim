#include "headers/objects/apartments/apartment.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include <vector>

int main() {
    std::cout << "line 1 uwuwuwuwuwuwuuwuwuwu" << std::endl;
    std::cout << "line 2 uwuwuwuwuwuwuuwuwuwu" << std::endl;
    std::cout << "line 3 uwuwuwuwuwuwuuwuwuwu" << std::endl;
    std::cout << "\033[2A\033[0Kheeeeeej\033[2E";
    screen::Screen *screen = new screen::Screen();
    screen->addLog("uwu1");
    screen->addLog("uwu2");
    screen->addLog("uwu3");
    screen->addLog("uwu4");
    std::cout << *screen;
    return 0;
}

//TO DO : probably make class time, write class market, generating utilities, (!) finish saving and loading files, class game, unit tests, make room state relevant