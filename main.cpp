#include "headers/objects/apartments/apartment.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include <vector>
#include <unistd.h>

int main() {
    std::shared_ptr<screen::Screen> screen(new screen::Screen());
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getDisplayedApartment(),600,30,false));
    screen->getGame()->addLease(lol);
    std::vector<std::shared_ptr<furniture::Furniture>> backup;
    std::cout << *screen;
    display::Display *d = new display::Display("D1",20,2,display::displayType::furniture,screen->getGame(),point::Point(0,0));
    for (std::string line:d->getDisplay()) {
        std::cout<<line<<std::endl;
    }
    d->scrollDown(3);
    d->scrollUp(3);
    std::cout<<std::endl;
    for (std::string line:d->getDisplay()) {
        std::cout<<line<<std::endl;
    }
    // std::string line;
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    // std::cin >> line;
    // std::cout << "\033[1A\033[0K";
    // screen->addLog(line);
    //std::cout << *bob;
    return 0;
}

//TO DO : probably make class time, (!) finish saving and loading files, class game, unit tests, make room state relevant