#pragma once
#include <functional>
#include "game.h"

namespace action {
    //screen, apartment, message
    template<typename T>
    class Action {
        public:
        std::string name;
        int cost;
        int time;
        std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<T>)> function;
        std::vector<std::function<bool(std::shared_ptr<game::Game>)>> requirements;
        Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<T>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<game::Game>)>> actionRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            function = actionFunction;
            requirements = actionRequirements;
        }
        int execute(std::shared_ptr<game::Game> game,std::shared_ptr<T> object) {
            if (game->getMoney()>=cost) {
                game->setMoney(game->getMoney()-cost);
                game->addTime(time);
                function(game, object);
                return 0;
            }
            // insufficient balance
            return 1;
        }
        void addRequirement(std::function<bool(std::shared_ptr<game::Game>)> newRequirement) {
            requirements.push_back(newRequirement);
        }
        bool checkRequirements(std::shared_ptr<game::Game> game) {
            for (std::function<bool(std::shared_ptr<game::Game>)> requirement : requirements) {
                if (!requirement(game)) {
                    return false;
                }
            }
            return true;
            }
    };
}