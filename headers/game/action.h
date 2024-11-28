#pragma once
#include <functional>
#include "game.h"

namespace action {
    //display,tenant,apartment,room,furniture,message
    template<typename T>
    class Action {
        public:
        std::string name;
        int cost;
        int time;
        std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<T>)> function;
        Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<T>)> actionFunction);
        int execute(std::shared_ptr<game::Game> game,std::shared_ptr<T> object);
    };
}