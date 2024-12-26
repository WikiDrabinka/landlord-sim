#include "../../headers/game/actionHandler.h"

namespace action {
    ActionHandler::ActionHandler() {
        displayActions.push_back(Action<display::Display>("SwitchStorage",0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display){
            if (display->getType()==display::storage) {
                display->changeDisplay(display::store,"Store");
            } else {
                display->changeDisplay(display::storage,"Storage");
            }
            display->updateDisplay();
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::store || display->getType()==display::storage);
        })}));
    }
}