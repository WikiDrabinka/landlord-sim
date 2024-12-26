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
        displayActions.push_back(Action<display::Display>("OpenMessage",0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display){
            int messageIdx;
            std::cin >> messageIdx;
            if (messageIdx<0 || messageIdx>=screen->getGame()->getMessages().size()) {
                screen->addLog("Incorrect message index.");
            } else {
                display->changeDisplay(display::conversation,"Conversation");
                display->changeDisplay({messageIdx});
                screen->getGame()->getMessages()[messageIdx]->read = true;
            }
            display->updateDisplay();
        }),{std::function<bool(std::shared_ptr<game::Game>)>([](std::shared_ptr<game::Game> game){
            return (game->getMessages().size()>0);
        })},{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::messages);
        })}));
        displayActions.push_back(Action<display::Display>("CloseMessage",0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display){
            display->changeDisplay(display::messages,"Messages");
            display->updateDisplay();
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::conversation);
        })}));
    }
}