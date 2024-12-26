#pragma once
#include <functional>
#include "../display/screen.h"

namespace action {
    //screen, apartment, message
    template<typename T>
    class Action {
        public:
        std::string name;
        int cost;
        int time;
        std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>)> function;
        std::vector<std::function<bool(std::shared_ptr<game::Game>)>> gameRequirements;
        std::vector<std::function<bool(std::shared_ptr<T>)>> objectRequirements;
        Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<game::Game>)>> actionGameRequirements,std::vector<std::function<bool(std::shared_ptr<T>)>> actionObjectRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            function = actionFunction;
            gameRequirements = actionGameRequirements;
            objectRequirements = actionObjectRequirements;
        }
        Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<T>)>> actionObjectRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            function = actionFunction;
            objectRequirements = actionObjectRequirements;
        }
        Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<game::Game>)>> actionGameRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            function = actionFunction;
            gameRequirements = actionGameRequirements;
        }
        int execute(std::shared_ptr<screen::Screen> screen,std::shared_ptr<T> object) {
            if (screen->getGame()->getMoney()>=cost) {
                screen->getGame()->setMoney(screen->getGame()->getMoney()-cost);
                screen->getGame()->addTime(time);
                function(screen, object);
                return 0;
            }
            // insufficient balance
            return 1;
        }
        void addRequirement(std::function<bool(std::shared_ptr<game::Game>)> newRequirement) {
            gameRequirements.push_back(newRequirement);
        }
        void addRequirement(std::function<bool(std::shared_ptr<T>)> newRequirement) {
            objectRequirements.push_back(newRequirement);
        }
        bool checkRequirements(std::shared_ptr<screen::Screen> screen, std::shared_ptr<T> object) {
            for (std::function<bool(std::shared_ptr<game::Game>)> requirement : gameRequirements) {
                if (!requirement(screen->getGame())) {
                    return false;
                }
            }
            for (std::function<bool(std::shared_ptr<T>)> requirement : objectRequirements) {
                if (!requirement(object)) {
                    return false;
                }
            }
            return true;
            }
    };
}