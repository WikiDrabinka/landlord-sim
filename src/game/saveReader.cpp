#include "../../headers/game/game.h"
#include <fstream>
namespace saveReader {
    void saveGame(std::string filePath, game::Game &newGame) {
        std::fstream fs;
        fs.open(filePath, std::fstream::out);
        fs << newGame.getMoney() << std::endl;
        fs << newGame.getTime() << std::endl;
        fs << newGame.getApartments().size() << std::endl;
        for (std::shared_ptr<apartment::Apartment> apartment: newGame.getApartments()) {
            fs << apartment->getName() << std::endl;
            fs << apartment->getRooms().size() << std::endl;
            for (std::shared_ptr<room::Room> room: apartment->getRooms()) {
                fs << room->getName() <<std::endl;
                fs << room->getColor().red << " " << room->getColor().green << " " << room->getColor().blue << std::endl;
                fs << room->getState() << std::endl;
                fs << room->getRectangles().size() << std::endl;
                for (std::shared_ptr<rectangle::Rectangle> rect: room->getRectangles()) {
                    fs << rect->getPoint1().getString() << " " << rect->getPoint2().getString() << std::endl;
                }
                fs << room->getFurniture().size() << std::endl;
                for (std::shared_ptr<furniture::Furniture> furn: room->getFurniture()) {
                    fs << furn->getString() << std::endl;
                }
            }
            // tenants
        }
        fs.close();
    }
    void loadGame(std::string filePath, game::Game &newGame) {
        std::fstream fs(filePath,std::fstream::in);
        std::string line;
        getline(fs,line);
        newGame.setMoney(stoi(line));
        getline(fs,line);
        newGame.setTime(stoi(line));
        getline(fs,line);
        int apartmentNo = stoi(line);
        for (int i = 0; i<apartmentNo; ++i) {
            std::string apartmentName;
            getline(fs,apartmentName);
            getline(fs,line);
            int roomNo = stoi(line);
            std::vector<std::shared_ptr<room::Room>> rooms;
            for (int j = 0; j<roomNo; ++j) {
                std::string roomName;
                getline(fs,roomName);
                getline(fs,line,' ');
                int red = stoi(line);
                getline(fs,line,' ');
                int green = stoi(line);
                getline(fs,line);
                int blue = stoi(line);
                color::BackgroundColor roomColor = color::BackgroundColor(red,green,blue);
                getline(fs,line);
                int state = stoi(line);
                getline(fs,line);
                int rectNo = stoi(line);
                std::vector<std::shared_ptr<rectangle::Rectangle>> rects;
                for (int k = 0; k<rectNo; ++k) {
                    getline(fs,line,' ');
                    int x1 = stoi(line);
                    getline(fs,line,' ');
                    int y1 = stoi(line);
                    getline(fs,line,' ');
                    int x2 = stoi(line);
                    getline(fs,line);
                    int y2 = stoi(line);
                    std::shared_ptr<rectangle::Rectangle> newRect(new rectangle::Rectangle(point::Point(x1,y1),point::Point(x2,y2),roomColor));
                    rects.push_back(newRect);
                }
                std::shared_ptr<room::Room> newRoom(new room::Room(roomName,(livingSpace::state) state,rects,roomColor));
                getline(fs,line);
                int furnitureNo = stoi(line);
                for (int k = 0; k<furnitureNo; ++k) {
                    getline(fs,line,' ');
                    int type = stoi(line);
                    std::string furnitureName;
                    getline(fs, furnitureName,'\'');
                    getline(fs, furnitureName,'\'');
                    getline(fs,line,' ');
                    getline(fs,line,' ');
                    int price = stoi(line);
                    getline(fs,line,' ');
                    int condition = stoi(line);
                    getline(fs,line,' ');
                    int sizeX = stoi(line);
                    getline(fs,line,' ');
                    int sizeY = stoi(line);
                    getline(fs,line,' ');
                    int posX = stoi(line);
                    getline(fs,line,' ');
                    int posY = stoi(line);
                    switch (type) {
                    case 1:
                    {
                        getline(fs,line,' ');
                        int comfortability = stoi(line);
                        getline(fs,line);
                        int capacity = stoi(line);
                        newRoom->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable(furnitureName,price,condition,sizeX,sizeY,comfortability,capacity)),point::Point(posX,posY));
                        break;
                    }
                    case 2:
                    {
                        getline(fs,line,' ');
                        int capacity = stoi(line);
                        getline(fs,line);
                        std::shared_ptr<furniture::Storage> newStorage(new furniture::Storage(furnitureName,price,condition,sizeX,sizeY,capacity));
                        int itemNo = stoi(line);
                        for (int l = 0; l<itemNo; ++l) {
                            std::string itemName;
                            getline(fs,itemName,'\'');
                            getline(fs,itemName,'\'');
                            getline(fs,line,' ');
                            getline(fs,line,' ');
                            int size = stoi(line);
                            getline(fs,line);
                            int value = stoi(line);
                            newStorage->addItem(std::shared_ptr<item::Item>(new item::Item(itemName,size,value)));
                        }
                        newRoom->addFurniture(newStorage,point::Point(posX,posY));
                        break;
                    }
                    case 3:
                    {
                        getline(fs,line);
                        furniture::utilityType type = (furniture::utilityType) stoi(line);
                        newRoom->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility(furnitureName,price,condition,sizeX,sizeY,type)),point::Point(posX,posY));
                        break;
                    }
                    default:
                        break;
                    }
                }
                rooms.push_back(newRoom);
            }
            newGame.addApartment(std::shared_ptr<apartment::Apartment>(new apartment::Apartment(apartmentName,rooms)));
            // tenants
        }
    }
}