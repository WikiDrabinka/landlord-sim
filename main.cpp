#include "headers/objects/apartments/apartment.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include <vector>
#include <unistd.h>

int main() {
    screen::Screen *screen = new screen::Screen();
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getDisplayedApartment(),600,30,false));
    screen->getGame()->addLease(lol);
    screen->getGame()->addApartment(screen->getGame()->getApartments()[0]->splitVertically("apt 2",5));
    screen->setSelectedApartment(1);
    std::cout << *screen;
    std::string line;
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cin >> line;
    std::cout << "\033[1A\033[0K";
    screen->addLog(line);
    std::cout << *bob;
    return 0;
}

//TO DO : fix splitting rooms, probably make class time, write class market, generating utilities, (!) finish saving and loading files, class game, unit tests, make room state relevant