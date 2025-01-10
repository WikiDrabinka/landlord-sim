#include "../../headers/game/fileReader.h"
#include <fstream>
#include <algorithm>

namespace fileReader {
    FileReader::FileReader(){
        saves[0] = "resources/save1";
        saves[1] = "resources/save2";
        saves[2] = "resources/save3";
        saves[3] = "resources/save4";
        help = "resources/help";
        titlescreen = "resources/titlescreen";
    }
    std::shared_ptr<canvas::Canvas> FileReader::loadTitleScreeen() {
        std::fstream title(titlescreen);
        int sizeX,sizeY;
        title >> sizeX >> sizeY;
        std::shared_ptr<canvas::Canvas> titlescreen(new canvas::Canvas(sizeX,sizeY," "));
        int lines,x,y;
        title >> lines >> x >> y;
        color::ForegroundColor fcolor(50,0,50);
        for (int i=0;i<lines;++i){
            int crx,cry;
            title>>crx>>cry;
            color::BackgroundColor color(150-crx,30,150-cry);
            titlescreen->changeDrawing(crx+x,cry+y,color.getString()+fcolor.getString()+"┼"+color::Color::reset);
        }
        int elements;
        title >> elements;
        for (int el=0; el<elements; ++el) {
            title >> lines >> x >> y;
            for (int i = 0; i<=lines; ++i) {
                std::string line;
                getline(title,line);
                for (int j=0; j<line.length();++j) {
                    titlescreen->changeDrawing(x+i,y+j,line.substr(j,1));
                }
            }
        }
        int length;
        title >> lines >> length >> x >> y;
        std::vector<int> reds = {140,152,142,164,137,125,133,150,152,149,130,127};
        std::vector<int> greens = {30,41,35,37,23,28,40,24,34,41,22,19};
        std::vector<int> greys = {160,165,120,125,80,85};
        color::ForegroundColor grey(10,10,10);
        for (int i = 0; i<lines; ++i) {
            for (int j=0; j<length;++j) {
                std::string line;
                title >> line;
                color::ForegroundColor bricks(reds[(i+j)%reds.size()],greens[(i+j)%greens.size()],0);
                color::ForegroundColor kitty(greys[(i+j*(i+4))%greys.size()],greys[(i+j*(i+4))%greys.size()],greys[(i+j*(i+4))%greys.size()]);
                if (line!=".") {
                    if (i>5) {
                        titlescreen->changeDrawing(x+i,y+j,bricks.getString()+line+color::ForegroundColor::reset);
                    } else {
                        titlescreen->changeDrawing(x+i,y+j,kitty.getString()+line+color::ForegroundColor::reset);
                    }
                }
            }
        }
        title.close();
        return titlescreen;
    }
    std::vector<format::FormattedString> FileReader::loadHelp(std::string actionName) {  
        std::fstream fileHelp(help);
        std::string buffer;
        while (getline(fileHelp,buffer) && buffer!=actionName) {
            continue;
        }
        if (!getline(fileHelp,buffer)) {
            fileHelp.close();
            throw std::invalid_argument("Action not found");
        }
        std::vector<format::FormattedString> info;
        info.push_back(format::FormattedString(buffer,false,true));
        while (getline(fileHelp,buffer) && buffer!="---") {
            info.push_back(buffer);
        }
        fileHelp.close();
        return info;
    }
    void FileReader::saveGame(int idx, std::shared_ptr<game::Game> game) {
        std::fstream save;
        save.open(saves[idx],std::ios::out);
        save << game->getTime() << std::endl;
        save << game->getMoney() << std::endl;
        save << game->usedElectricity << " " << game->usedWater << " " << game->usedOther << " " << game->notIncluded << std::endl;
        
    
        // furniture
        save << game->getFurnitureStore().size() << std::endl;
        for (std::shared_ptr<furniture::Furniture> furn : game->getFurnitureStore()) {
            save << furn->getString() << std::endl;
        }
        save << game->getFurnitureStorage().size() << std::endl;
        for (std::shared_ptr<furniture::Furniture> furn : game->getFurnitureStorage()) {
            save << furn->getString() << std::endl;
        }

        // tenants
        std::vector<std::shared_ptr<tenant::Tenant>> tenants;
        save << game->getLeases().size() << std::endl;
        for (std::shared_ptr<lease::Lease> lease : game->getLeases()) {
            tenants.push_back(lease->getTenant());
            save << tenants.back()->getName() << std::endl;
            save << tenants.back()->getNickname() << std::endl;
            save << tenants.back()->getIncome() << " " << tenants.back()->getSavings() << " " << tenants.back()->getSpending() << " " << tenants.back()->owing << std::endl;
            save << tenants.back()->getPatience() << " " << tenants.back()->getHappiness() << std::endl;
        }

        // apartments
        save << game->getApartments().size() << std::endl;
        for (std::shared_ptr<apartment::Apartment> apt : game->getApartments()) {
            save << apt->getName() << std::endl;
            save << apt->marketPrice << " " << apt->tenantsNo << std::endl;
            save << apt->getRooms().size() << std::endl;
            for (std::shared_ptr<room::Room> room : apt->getRooms()) {
                save << room->getName()<< std::endl;
                save << (int) room->getState() << " ";
                if (room->getState()==livingSpace::claimed) {
                    save << std::distance(tenants.begin(),std::find(tenants.begin(),tenants.end(),room->getClaim())) << std::endl;
                } else {
                    save << -1 << std::endl;
                }
                save << room->getColor().red << " " << room->getColor().green << " " << room->getColor().blue << std::endl;
                save << room->getRectangles().size() << std::endl;
                for (std::shared_ptr<rectangle::Rectangle> rect : room->getRectangles()) {
                    save << rect->getPoint1().x << " " << rect->getPoint1().y << " " << rect->getPoint2().x << " " << rect->getPoint2().y << std::endl;
                }
                save << room->getFurniture().size() << std::endl;
                for (std::shared_ptr<furniture::Furniture> furn : room->getFurniture()) {
                    save << furn->getString() << std::endl;
                }
            }
        }
        
        // real estate
        save << game->getRealEstateMarket()->getAveragePrice() << std::endl;
        save << game->getRealEstateMarket()->getApartments().size() << std::endl;
        for (std::pair<std::shared_ptr<apartment::Apartment>,int> entry : game->getRealEstateMarket()->getApartments()) {
            save << std::distance(game->getApartments().begin(),std::find(game->getApartments().begin(),game->getApartments().end(),entry.first)) << " " << entry.second << std::endl;
        }
        // leases
        for (int i=0; i<game->getLeases().size(); ++i) {
            std::shared_ptr<lease::Lease> lease = game->getLeases()[i];
            save << lease->getRent() << " " << lease->getTime() << " " << lease->getUtilities() << std::endl;
            save << " " << std::distance(game->getApartments().begin(),std::find(game->getApartments().begin(),game->getApartments().end(),lease->getApartment())) << std::endl;
        }
        // messages
        save << game->getMessages().size() << std::endl;
        for (std::shared_ptr<messages::Conversation> convo : game->getMessages()) {
            save << convo->read << " " << convo->time << std::endl;
            if (std::find(tenants.begin(),tenants.end(),convo->getSender())!=tenants.end()) {
                save << std::distance(tenants.begin(),std::find(tenants.begin(),tenants.end(),convo->getSender())) << std::endl;
            } else {
                save << -1 << std::endl;
                save << convo->getSender()->getName() << std::endl;
                save << convo->getSender()->getNickname() << std::endl;
                save << convo->getSender()->getIncome() << " " << convo->getSender()->getSavings() << " " << convo->getSender()->getSpending() << " " << convo->getSender()->owing << std::endl;
                save << convo->getSender()->getPatience() << " " << convo->getSender()->getHappiness() << std::endl;
            }
            save << convo->getMessages().size() << std::endl;
            for (std::string message : convo->getMessages()) {
                save << message << std::endl;
            }
            save << convo->responses.size() << std::endl;
            for (int resp : convo->responses) {
                save << resp << " ";
            }
        }
        save.close();
    }
    std::shared_ptr<game::Game> FileReader::loadGame(int idx) {
        std::fstream save;
        save.open(saves[idx],std::ios::in);
        if (!save.is_open()) {
            throw std::runtime_error("Failed to open file: " + saves[idx]);
        }
        std::shared_ptr<game::Game> game(new game::Game(true));
        try {
            int time, money;
            save >> time;
            game->setTime(time);
            save >> money;
            game->setMoney(money);
            save >> game->usedElectricity >> game->usedWater >> game->usedOther >> game->notIncluded;
            int furnitureNum;
            save >> furnitureNum;
            std::string furnName;
            for (int i = 0; i<furnitureNum; ++i) {
                getline(save >> std::ws,furnName);
                int type;
                save >> type;
                switch (type)
                {
                case 1:
                {
                    int price, condition, sizeX, sizeY, posX, posY, comfortability, capacity;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> comfortability >> capacity;
                    game->getFurnitureStore().push_back(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable(
                        furnName, price, condition, sizeX, sizeY, comfortability, capacity
                    )));
                    break;
                }
                case 2:
                {
                    int price, condition, sizeX, sizeY, posX, posY, capacity, itemNum;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> capacity >> itemNum;
                    std::shared_ptr<furniture::Storage> storage(new furniture::Storage(
                        furnName, price, condition, sizeX, sizeX, capacity
                    ));
                    game->getFurnitureStore().push_back(storage);
                    for (int j = 0; j<itemNum; ++j) {
                        std::string itemName;
                        getline(save >> std::ws, itemName);
                        int size, value;
                        save >> size >> value;
                        storage->addItem(std::shared_ptr<item::Item>(new item::Item(itemName, size, value)));
                    }
                    break;
                }
                case 3:
                {
                    int price, condition, sizeX, sizeY, posX, posY, type, cost;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> type >> cost;
                    game->getFurnitureStore().push_back(std::shared_ptr<furniture::Utility>(new furniture::Utility(
                        furnName, price, condition, sizeX, sizeY, (furniture::utilityType) type, cost
                    )));
                    break;
                }
                default:
                    throw std::invalid_argument("Incorrect furniture type: "+std::to_string(type));
                }
            }
            save >> furnitureNum;
            for (int i = 0; i<furnitureNum; ++i) {
                getline(save >> std::ws,furnName);
                int type;
                save >> type;
                switch (type)
                {
                case 1:
                {
                    int price, condition, sizeX, sizeY, posX, posY, comfortability, capacity;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> comfortability >> capacity;
                    game->getFurnitureStorage().push_back(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable(
                        furnName, price, condition, sizeX, sizeY, comfortability, capacity
                    )));
                    break;
                }
                case 2:
                {
                    int price, condition, sizeX, sizeY, posX, posY, capacity, itemNum;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> capacity >> itemNum;
                    std::shared_ptr<furniture::Storage> storage(new furniture::Storage(
                        furnName, price, condition, sizeX, sizeX, capacity
                    ));
                    game->getFurnitureStorage().push_back(storage);
                    for (int j = 0; j<itemNum; ++j) {
                        std::string itemName;
                        getline(save >> std::ws, itemName);
                        int size, value;
                        save >> size >> value;
                        storage->addItem(std::shared_ptr<item::Item>(new item::Item(itemName, size, value)));
                    }
                    break;
                }
                case 3:
                {
                    int price, condition, sizeX, sizeY, posX, posY, type, cost;
                    save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> type >> cost;
                    game->getFurnitureStorage().push_back(std::shared_ptr<furniture::Utility>(new furniture::Utility(
                        furnName, price, condition, sizeX, sizeY, (furniture::utilityType) type, cost
                    )));
                    break;
                }
                default:
                    throw std::invalid_argument("Incorrect furniture type: "+std::to_string(type));
                }
            }
            // tenants
            int tenantsNum;
            save >> tenantsNum;
            std::vector<std::shared_ptr<tenant::Tenant>> tenants;
            for (int i = 0; i<tenantsNum; ++i) {
                std::string name, nickname;
                getline(save >> std::ws,name);
                getline(save >> std::ws,nickname);
                int income, savings, spending, owing, patience, happiness;
                save >> income >> savings >> spending >> owing >> patience >> happiness;
                tenants.push_back(std::shared_ptr<tenant::Tenant>(new tenant::Tenant(
                    name, income, savings, spending, patience, happiness
                )));
                tenants.back()->setNickname(nickname);
                tenants.back()->owing = owing;
            }
            // apartments
            int aptNum;
            save >> aptNum;
            for (int i = 0; i<aptNum; ++i) {
                std::string name;
                getline(save >> std::ws,name);
                std::shared_ptr<apartment::Apartment> apartment(new apartment::Apartment(name));
                save >> apartment->marketPrice >> apartment->tenantsNo;
                int roomNum;
                save >> roomNum;
                for (int j = 0; j<roomNum; ++j) {
                    std::string roomName;
                    getline(save >> std::ws,roomName);
                    int state, tenantIdx, r, g, b, rectNum, furnNum;
                    save >> state >> tenantIdx >> r >> g >> b >> rectNum;;
                    std::shared_ptr<room::Room> room(new room::Room(roomName,(livingSpace::state) state,color::BackgroundColor(r,g,b)));
                    if (room->getState()==livingSpace::claimed) {
                        room->setClaim(tenants[tenantIdx]);
                    }
                    for (int k = 0; k<rectNum; ++k) {
                        int x1, y1, x2, y2;
                        save >> x1 >> y1 >> x2 >> y2;
                        room->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(x1,y1),point::Point(x2,y2))));
                    }
                    save >> furnNum;
                    for (int k = 0; k<furnNum; ++k) {
                        getline(save >> std::ws,furnName);
                        int type;
                        save >> type;
                        switch (type)
                        {
                        case 1:
                        {
                            int price, condition, sizeX, sizeY, posX, posY, comfortability, capacity;
                            save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> comfortability >> capacity;
                            std::shared_ptr<furniture::Sleepable> sleepable(new furniture::Sleepable(
                                furnName, price, condition, sizeX, sizeY, comfortability, capacity
                            ));
                            room->addFurniture(sleepable,point::Point(posX,posY));
                            break;
                        }
                        case 2:
                        {
                            int price, condition, sizeX, sizeY, posX, posY, capacity, itemNum;
                            save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> capacity >> itemNum;
                            std::shared_ptr<furniture::Storage> storage(new furniture::Storage(
                                furnName, price, condition, sizeX, sizeY, capacity
                            ));
                            room->addFurniture(storage,point::Point(posX,posY));
                            for (int j = 0; j<itemNum; ++j) {
                                std::string itemName;
                                getline(save >> std::ws, itemName);
                                int size, value;
                                save >> size >> value;
                                storage->addItem(std::shared_ptr<item::Item>(new item::Item(itemName, size, value)));
                            }
                            break;
                        }
                        case 3:
                        {
                            int price, condition, sizeX, sizeY, posX, posY, type, cost;
                            save >> price >> condition >> sizeX >> sizeY >> posX >> posY >> type >> cost;
                            std::shared_ptr<furniture::Utility> utility(new furniture::Utility(
                                furnName, price, condition, sizeX, sizeY, (furniture::utilityType) type, cost
                            ));
                            room->addFurniture(utility,point::Point(posX,posY));
                            break;
                        }
                        default:
                            throw std::invalid_argument("Incorrect furniture type: "+std::to_string(type));
                        }
                    }
                    apartment->addRoom(room);
                }
                game->addApartment(apartment);
            }

            // real estate
            int price, entryNum;
            save >> price >> entryNum;
            std::shared_ptr<market::RealEstate> market(new market::RealEstate(price));
            for (int i = 0; i<entryNum; ++i) {
                int aptIdx, rent;
                save >> aptIdx >> rent;
                market->addApartment(game->getApartments()[aptIdx],rent);
            }
            game->setRealEstateMarket(market);

            // leases
            for (int i = 0; i<tenantsNum; ++i) {
                int rent, time, utilities, aptIdx;
                save >> rent >> time >> utilities >> aptIdx;
                game->addLease(std::shared_ptr<lease::Lease>(new lease::Lease(tenants[i],game->getApartments()[aptIdx],rent,time,(bool) utilities)));
            }

            // messages
            int convNum;
            save >> convNum;
            for (int i = 0; i<convNum; ++i) {
                int read, time, tenantIdx;
                save >> read >> time >> tenantIdx;
                std::shared_ptr<tenant::Tenant> tenant;
                if (tenantIdx!=-1) {
                    tenant = tenants[tenantIdx];
                } else {
                    std::string name, nickname;
                    getline(save >> std::ws,name);
                    getline(save >> std::ws,nickname);
                    int income, savings, spending, owing, patience, happiness;
                    save >> income >> savings >> spending >> owing >> patience >> happiness;
                    tenants.push_back(std::shared_ptr<tenant::Tenant>(new tenant::Tenant(
                        name, income, savings, spending, patience, happiness
                    )));
                    tenants.back()->setNickname(nickname);
                    tenants.back()->owing = owing;
                    tenant = tenants.back();
                }
                int messNum;
                save >> messNum;
                std::string message;
                getline(save >> std::ws,message);
                std::shared_ptr<messages::Conversation> conv(new messages::Conversation(tenant,message,time));
                for (int j = 0; j<messNum-1; ++j) {
                    getline(save >> std::ws,message);
                    conv->sendMessage(message,time);
                }
                conv->read = (bool) read;
                int respNum;
                save >> respNum;
                for (int j = 0; j<respNum; ++j) {
                    int idx;
                    save >> idx;
                    conv->responses.push_back(idx);
                }
                game->getMessages().push_back(conv);
            }

        } catch (std::invalid_argument e) {
            save.close();
            throw std::runtime_error("Corrupted save file: " + saves[idx] + " ("+e.what()+")");
        }
        save.close();
        return game;
    }
}