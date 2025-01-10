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
        int argumentsNo;
        std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>,std::vector<int>)> function;
        std::vector<std::function<bool(std::shared_ptr<game::Game>)>> gameRequirements;
        std::vector<std::function<bool(std::shared_ptr<T>)>> objectRequirements;
        Action(std::string actionName, int actionCost, int actionTime, int actionArgumentsNo, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>,std::vector<int>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<game::Game>)>> actionGameRequirements={},std::vector<std::function<bool(std::shared_ptr<T>)>> actionObjectRequirements={}) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            argumentsNo = actionArgumentsNo;
            function = actionFunction;
            gameRequirements = actionGameRequirements;
            objectRequirements = actionObjectRequirements;
        }
        Action(std::string actionName, int actionCost, int actionTime, int actionArgumentsNo, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>,std::vector<int>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<T>)>> actionObjectRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            argumentsNo = actionArgumentsNo;
            function = actionFunction;
            objectRequirements = actionObjectRequirements;
        }
        Action(std::string actionName, int actionCost, int actionTime, int actionArgumentsNo, std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<T>,std::vector<int>)> actionFunction,std::vector<std::function<bool(std::shared_ptr<game::Game>)>> actionGameRequirements) {
            name = actionName;
            cost = actionCost;
            time = actionTime;
            argumentsNo = actionArgumentsNo;
            function = actionFunction;
            gameRequirements = actionGameRequirements;
        }
        int execute(std::shared_ptr<screen::Screen> screen,std::shared_ptr<T> object,std::vector<int> arguments = {}) {
            if (arguments.size()<argumentsNo) {
                throw std::out_of_range("Not enough arguments.");
            }
            if (screen->getGame()->getMoney()>=cost || cost==0) {
                screen->getGame()->addMoney(-cost);
                screen->getGame()->addTime(time);
                function(screen, object, arguments);
                return 0;
            }
            throw std::out_of_range("Insufficient balance.");
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