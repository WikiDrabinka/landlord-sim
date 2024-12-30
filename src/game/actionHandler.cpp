#include "../../headers/game/actionHandler.h"
#include <algorithm>
#include <sstream>
#include <random>

namespace action {
    int ActionHandler::execute(std::string input, std::shared_ptr<screen::Screen> screen) {
        std::string actionName;
        std::stringstream s(input);
        getline(s,actionName,' ');
        std::vector<int> arguments;
        std::string arg;
        while (getline(s,arg,' ')) {
            try {
                arguments.push_back(stoi(arg));
            } catch (std::invalid_argument) {
                // incorrect user input
                return 4;
            }
        }
        auto displayIt = std::find_if(displayActions.begin(),displayActions.end(),[actionName](Action<display::Display>& action){return action.name==actionName;});
        if (displayIt!=displayActions.end()) {
            Action<display::Display> action = displayActions[std::distance(displayActions.begin(),displayIt)];
            if (arguments.size()>action.argumentsNo) {
                std::shared_ptr<display::Display> display = screen->displays[arguments[0]];
                arguments.erase(arguments.begin());
                if (action.checkRequirements(screen, display)) {
                    try {
                        return action.execute(screen, display, arguments);
                    } catch (std::out_of_range e) {
                        screen->addLog(e.what());
                        return 4;
                    }
                }
                return 2;
            }
            for (std::shared_ptr<display::Display> display : screen->displays) {
                if (action.checkRequirements(screen, display)) {
                    try {
                        return action.execute(screen, display, arguments);
                    } catch (std::out_of_range e) {
                        screen->addLog(e.what());
                        return 4;
                    }
                }
            }
            // requirements not met
            return 2;
        }
        auto apartmentIt = std::find_if(apartmentActions.begin(),apartmentActions.end(),[actionName](Action<apartment::Apartment>& action){return action.name==actionName;});
        if (apartmentIt!=apartmentActions.end()) {
            Action<apartment::Apartment> action = apartmentActions[std::distance(apartmentActions.begin(),apartmentIt)];
            if (arguments.size() == 0) {
                screen->addLog("Not enough arguments.");
                return 4;
            }
            if (screen->getGame()->getApartments().size() <= arguments[0]-1) {
                screen->addLog("Incorrect apartment index.");
                return 4;
            }
            std::shared_ptr<apartment::Apartment> apartment = screen->getGame()->getApartments()[arguments[0]-1];
            arguments.erase(arguments.begin());
            if (action.checkRequirements(screen, apartment)) {
                try {
                    return action.execute(screen, apartment, arguments);
                } catch (std::out_of_range e) {
                    screen->addLog(e.what());
                    return 4;
                }
            }
            // requirements not met
            return 2;
        }
        auto furnitureIt = std::find_if(furnitureActions.begin(),furnitureActions.end(),[actionName](Action<furniture::Furniture>& action){return action.name==actionName;});
        if (furnitureIt!=furnitureActions.end()) {
            Action<furniture::Furniture> action = furnitureActions[std::distance(furnitureActions.begin(),furnitureIt)];
            if (arguments.size() == 0) {
                screen->addLog("Not enough arguments.");
                return 4;
            }
            if (screen->getGame()->getFurnitureStorage().size() <= arguments[0]-1) {
                screen->addLog("Incorrect furniture index.");
                return 4;
            }
            std::shared_ptr<furniture::Furniture> furniture = screen->getGame()->getFurnitureStorage()[arguments[0]-1];
            arguments.erase(arguments.begin());
            if (action.checkRequirements(screen, furniture)) {
                try {
                    return action.execute(screen, furniture, arguments);
                } catch (std::out_of_range e) {
                    screen->addLog(e.what());
                    return 4;
                }
            }
            // requirements not met
            return 2;
        }
        furnitureIt = std::find_if(storeActions.begin(),storeActions.end(),[actionName](Action<furniture::Furniture>& action){return action.name==actionName;});
        if (furnitureIt!=storeActions.end()) {
            Action<furniture::Furniture> action = storeActions[std::distance(storeActions.begin(),furnitureIt)];
            if (arguments.size() == 0) {
                screen->addLog("Not enough arguments.");
                return 4;
            }
            if (screen->getGame()->getFurnitureStore().size() <= arguments[0]-1) {
                screen->addLog("Incorrect furniture index.");
                return 4;
            }
            std::shared_ptr<furniture::Furniture> furniture = screen->getGame()->getFurnitureStore()[arguments[0]-1];
            arguments.erase(arguments.begin());
            if (action.checkRequirements(screen, furniture)) {
                try {
                    return action.execute(screen, furniture, arguments);
                } catch (std::out_of_range e) {
                    screen->addLog(e.what());
                    return 4;
                }
            }
            // requirements not met
            return 2;
        }
        auto leaseIt = std::find_if(leaseActions.begin(),leaseActions.end(),[actionName](Action<lease::Lease>& action){return action.name==actionName;});
        if (leaseIt!=leaseActions.end()) {
            Action<lease::Lease> action = leaseActions[std::distance(leaseActions.begin(),leaseIt)];
            if (arguments.size() == 0) {
                screen->addLog("Not enough arguments.");
                return 4;
            }
            if (screen->getGame()->getApartments().size() <= arguments[0]-1) {
                screen->addLog("Incorrect lease index.");
                return 4;
            }
            std::shared_ptr<lease::Lease> lease = screen->getGame()->getLeases()[arguments[0]-1];
            arguments.erase(arguments.begin());
            if (action.checkRequirements(screen, lease)) {
                try {
                    return action.execute(screen, lease, arguments);
                } catch (std::out_of_range e) {
                    screen->addLog(e.what());
                    return 4;
                }
            }
            // requirements not met
            return 2;
        }
        // action not found
        return 3;
    }
    ActionHandler::ActionHandler() {
        displayActions.push_back(Action<display::Display>("SwitchStorage",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display, std::vector<int> arguments){
            if (display->getType()==display::storage) {
                display->changeDisplay(display::store,"Store");
            } else {
                display->changeDisplay(display::storage,"Storage");
            }
            display->updateDisplay();
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::store || display->getType()==display::storage);
        })}));

        displayActions.push_back(Action<display::Display>("OpenMessage",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display,std::vector<int> arguments = {0}){
            int messageIdx = arguments[0]-1;
            if (messageIdx<0 || messageIdx>=screen->getGame()->getMessages().size()) {
                throw std::out_of_range("Incorrect message index.");
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

        displayActions.push_back(Action<display::Display>("CloseMessage",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display,std::vector<int> arguments){
            display->changeDisplay(display::messages,"Messages");
            display->updateDisplay();
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::conversation);
        })}));

        displayActions.push_back(Action<display::Display>("ScrollUp",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display,std::vector<int> arguments){
            display->scrollUp();
        })));

        displayActions.push_back(Action<display::Display>("ScrollDown",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display,std::vector<int> arguments){
            display->scrollDown();
        })));

        displayActions.push_back(Action<display::Display>("ShowFurniture",0,0,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display, std::vector<int> arguments){
            int aptIdx = arguments[0]-1;
            int roomIdx = arguments[1]-1;
            if (screen->getGame()->getApartments().size()<=aptIdx) {
                throw std::out_of_range("Incorrect apartment index.");
            }
            if (screen->getGame()->getApartments()[aptIdx]->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            display->changeDisplay({aptIdx,roomIdx});
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::furniture);
        })}));

        displayActions.push_back(Action<display::Display>("ShowRooms",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display, std::vector<int> arguments){
            int aptIdx = arguments[0]-1;
            if (screen->getGame()->getApartments().size()<=aptIdx) {
                throw std::out_of_range("Incorrect apartment index.");
            }
            display->changeDisplay({aptIdx});
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::rooms);
        })}));

        displayActions.push_back(Action<display::Display>("ShowApartment",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<display::Display>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<display::Display> display, std::vector<int> arguments){
            int aptIdx = arguments[0]-1;
            if (screen->getGame()->getApartments().size()<=aptIdx) {
                throw std::out_of_range("Incorrect apartment index.");
            }
            display->changeDisplay({aptIdx});
        }),{std::function<bool(std::shared_ptr<display::Display>)>([](std::shared_ptr<display::Display> display){
            return (display->getType()==display::apartment);
        })}));


        apartmentActions.push_back(Action<apartment::Apartment>("SplitRoomVertically",50,20,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int y = arguments[1];
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            screen->addLog("Enter the name of the new room.");
            std::string newName;
            getline(std::cin, newName);
            std::cout<<"\033[1A\033[2K";
            apartment->addRoom(apartment->getRooms()[roomIdx]->splitVertically(newName,y,screen->getGame()->getFurnitureStorage()));
            if (apartment->getRooms().back()->getRectangles().size()==0) {
                apartment->getRooms().pop_back();
                screen->getGame()->addMoney(50);
                screen->getGame()->addTime(-20);
                throw std::out_of_range("Incorrect coordinate.");
            }
            if (apartment->getRooms()[roomIdx]->getRectangles().size()==0) {
                apartment->getRooms().erase(apartment->getRooms().begin()+roomIdx);
                screen->getGame()->addMoney(50);
                screen->getGame()->addTime(-20);
                throw std::out_of_range("Incorrect coordinate.");
            }
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("SplitRoomHorizontally",50,20,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int x = arguments[1];
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            screen->addLog("Enter the name of the new room.");
            std::string newName;
            getline(std::cin, newName);
            std::cout<<"\033[1A\033[2K";
            apartment->addRoom(apartment->getRooms()[roomIdx]->splitHorizontally(newName,x,screen->getGame()->getFurnitureStorage()));
            if (apartment->getRooms().back()->getRectangles().size()==0) {
                apartment->getRooms().pop_back();
                screen->getGame()->addMoney(50);
                screen->getGame()->addTime(-20);
                throw std::out_of_range("Incorrect coordinate.");
            }
            if (apartment->getRooms()[roomIdx]->getRectangles().size()==0) {
                apartment->getRooms().erase(apartment->getRooms().begin()+roomIdx);
                screen->getGame()->addMoney(50);
                screen->getGame()->addTime(-20);
                throw std::out_of_range("Incorrect coordinate.");
            }
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("MergeRooms",50,20,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int room1Idx = arguments[0]-1;
            int room2Idx = arguments[1]-1;
            if (apartment->getRooms().size()<=room1Idx || apartment->getRooms().size()<=room2Idx) {
                throw std::out_of_range("Incorrect room index.");
            }
            apartment->getRooms()[room1Idx]->merge(apartment->getRooms()[room2Idx]);
            apartment->getRooms().erase(apartment->getRooms().begin()+room2Idx);
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("PlaceFurniture",0,10,4,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int furnIdx = arguments[1]-1;
            int positionX = arguments[2];
            int positionY = arguments[3];
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            if (screen->getGame()->getFurnitureStorage().size()<=furnIdx) {
                throw std::out_of_range("Incorrect furniture index.");
            }
            try {
                apartment->getRooms()[roomIdx]->addFurniture(screen->getGame()->getFurnitureStorage()[furnIdx],point::Point(positionX,positionY));
                screen->getGame()->getFurnitureStorage().erase(screen->getGame()->getFurnitureStorage().begin()+furnIdx);
            } catch (std::invalid_argument e) {
                throw std::out_of_range(e.what());
            }
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("RemoveFurniture",0,10,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int furnIdx = arguments[1]-1;
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            if (apartment->getRooms()[roomIdx]->getFurniture().size()<=furnIdx) {
                throw std::out_of_range("Incorrect furniture index.");
            }
            std::shared_ptr<furniture::Furniture> furniture = apartment->getRooms()[roomIdx]->getFurniture()[furnIdx];
            screen->getGame()->getFurnitureStorage().push_back(furniture);
            apartment->getRooms()[roomIdx]->getFurniture().erase(apartment->getRooms()[roomIdx]->getFurniture().begin()+furnIdx);
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("RepairFurniture",0,30,2,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int furnIdx = arguments[1]-1;
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            if (apartment->getRooms()[roomIdx]->getFurniture().size()<=furnIdx) {
                throw std::out_of_range("Incorrect furniture index.");
            }
            std::shared_ptr<furniture::Furniture> furniture = apartment->getRooms()[roomIdx]->getFurniture()[furnIdx];
            int price = furniture->repairPrice();
            if (screen->getGame()->getMoney()<price) {
                screen->getGame()->addTime(-5);
                throw std::out_of_range("Insufficient balance.");
            }
            furniture->setCondition(100);
            screen->getGame()->addMoney(-price);
            screen->addLog("Repaired "+furniture->getName()+" for "+std::to_string(price)+".");
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("ChangeRoomColor",0,0,4,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            int r = arguments[1];
            int g = arguments[2];
            int b = arguments[3];
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            apartment->getRooms()[roomIdx]->setColor(color::BackgroundColor(r,g,b));
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("ChangeRoomName",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int roomIdx = arguments[0]-1;
            if (apartment->getRooms().size()<=roomIdx) {
                throw std::out_of_range("Incorrect room index.");
            }
            screen->addLog("Enter the new name of the room.");
            std::string newName;
            getline(std::cin, newName);
            std::cout<<"\033[1A\033[2K";
            apartment->getRooms()[roomIdx]->setName(newName);
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("SplitVertically",100,60,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int y = arguments[0];
            if (y>=apartment->maxY()) {
                screen->getGame()->addMoney(100);
                screen->getGame()->addTime(60);
                throw std::out_of_range("Incorrect coordinate.");
            }
            screen->addLog("Enter the name of the new apartment.");
            std::string newName;
            getline(std::cin, newName);
            std::cout<<"\033[1A\033[2K";
            screen->getGame()->addApartment(apartment->splitVertically(newName,y,screen->getGame()->getFurnitureStorage()));
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("SplitHorizontally",100,60,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int x = arguments[0];
            if (x>=apartment->maxX()) {
                screen->getGame()->addMoney(100);
                screen->getGame()->addTime(60);
                throw std::out_of_range("Incorrect coordinate.");
            }
            screen->addLog("Enter the name of the new apartment.");
            std::string newName;
            getline(std::cin, newName);
            std::cout<<"\033[1A\033[2K";
            screen->getGame()->addApartment(apartment->splitHorizontally(newName,x,screen->getGame()->getFurnitureStorage()));
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("Merge",100,60,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int aptIdx = arguments[0]-1;
            if (apartment->getRooms().size()<=aptIdx) {
                throw std::out_of_range("Incorrect apartment index.");
            }
            for (std::shared_ptr<lease::Lease> lease : screen->getGame()->getLeases()) {
                if (lease->getApartment() == screen->getGame()->getApartments()[aptIdx]) {
                    lease->setApartment(apartment);
                }
            }
            apartment->merge(screen->getGame()->getApartments()[aptIdx]);
            screen->getGame()->getApartments().erase(screen->getGame()->getApartments().begin()+aptIdx);
            screen->displays[0]->changeDisplay({0});
            screen->displays[4]->changeDisplay({0});
            screen->displays[5]->changeDisplay({0,0});
        })));

        apartmentActions.push_back(Action<apartment::Apartment>("Market",5,10,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<apartment::Apartment>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<apartment::Apartment> apartment,std::vector<int> arguments){
            int rent = arguments[0];
            if (apartment->marketPrice == 0) {
                screen->getGame()->getRealEstateMarket()->addApartment(apartment,rent);
            } else {
                screen->getGame()->getRealEstateMarket()->changeRent(apartment,rent);
            }
            apartment->marketPrice = rent;
        })));

        //offer lease


        leaseActions.push_back(Action<lease::Lease>("ChangeRent",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<lease::Lease>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<lease::Lease> lease,std::vector<int> arguments){
            int newRent = arguments[0];
            int perMeter = newRent*lease->getApartment()->tenantsNo/lease->getApartment()->area();
            if (perMeter==0) {
                perMeter = 1;
            }
            int happinessDiff = (lease->getRent()-newRent)*100/lease->getRent();
            if (happinessDiff>0 && (screen->getGame()->getRealEstateMarket()->getAveragePrice()/perMeter)>0) {
                happinessDiff*=(screen->getGame()->getRealEstateMarket()->getAveragePrice()/perMeter);
            } else if (((perMeter)/screen->getGame()->getRealEstateMarket()->getAveragePrice()) > 0){
                happinessDiff*=((perMeter)/screen->getGame()->getRealEstateMarket()->getAveragePrice());
            }
            lease->setRent(newRent);
            lease->getTenant()->addHappiness(happinessDiff);
        })));

        leaseActions.push_back(Action<lease::Lease>("Renew",0,0,1,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<lease::Lease>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<lease::Lease> lease,std::vector<int> arguments){
            int time = arguments[0];
            std::random_device dev;
            std::mt19937 gen(dev());
            std::uniform_int_distribution<> renewalDistr(0,100);
            if (renewalDistr(gen)*0.75<lease->getTenant()->getHappiness()) {
                lease->addTime(time);
            } else {
                auto conversation = std::find_if(screen->getGame()->getMessages().begin(),screen->getGame()->getMessages().end(),[lease](std::shared_ptr<messages::Conversation> message){ return message->getSender()==lease->getTenant(); });
                if (conversation!=screen->getGame()->getMessages().end()) {
                    conversation[0]->sendMessage("No thanks, bye.",screen->getGame()->getTime());
                } else {
                    screen->getGame()->getMessages().push_back(std::shared_ptr<messages::Conversation>(new messages::Conversation(lease->getTenant(),"No thanks, bye.",screen->getGame()->getTime())));
                }
                std::sort(screen->getGame()->getMessages().begin(),screen->getGame()->getMessages().end(),[](std::shared_ptr<messages::Conversation> &lhs, std::shared_ptr<messages::Conversation> &rhs) {return lhs->time>rhs->time;});
            }
        })));


        furnitureActions.push_back(Action<furniture::Furniture>("RotateFurniture",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<furniture::Furniture>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<furniture::Furniture> furniture,std::vector<int> arguments){
            furniture->rotate();
        })));

        furnitureActions.push_back(Action<furniture::Furniture>("SellFurniture",0,5,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<furniture::Furniture>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<furniture::Furniture> furniture,std::vector<int> arguments){
            std::random_device dev;
            std::mt19937 gen(dev());
            std::normal_distribution<> priceDistr(furniture->getPriceMean(),furniture->getPriceSD());
            int newPrice = priceDistr(gen);
            while (newPrice < 0) {
                newPrice = priceDistr(gen);
            }
            furniture->setPrice(newPrice);
            screen->getGame()->addMoney(furniture->getPrice());
            screen->getGame()->getFurnitureStore().push_back(furniture);
            screen->getGame()->getFurnitureStorage().erase(std::find(screen->getGame()->getFurnitureStorage().begin(),screen->getGame()->getFurnitureStorage().end(),furniture));
            screen->addLog("Sold "+furniture->getName()+" for "+std::to_string(furniture->getPrice())+".");
        })));


        storeActions.push_back(Action<furniture::Furniture>("BuyFurniture",0,0,0,std::function<void(std::shared_ptr<screen::Screen>,std::shared_ptr<furniture::Furniture>,std::vector<int>)>([](std::shared_ptr<screen::Screen> screen,std::shared_ptr<furniture::Furniture> furniture,std::vector<int> arguments){
            if (screen->getGame()->getMoney()<furniture->getPrice()) {
                throw std::out_of_range("Insufficient balance.");
            }
            screen->getGame()->addMoney(-furniture->getPrice());
            screen->getGame()->getFurnitureStorage().push_back(furniture);
            screen->getGame()->getFurnitureStore().erase(std::find(screen->getGame()->getFurnitureStore().begin(),screen->getGame()->getFurnitureStore().end(),furniture));
        })));
    }

}