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
                    fs << rect->getPoint1().x << " " << rect->getPoint1().y << " " << rect->getPoint2().x << " " << rect->getPoint2().y << std::endl;
                }
                fs << room->getFurniture().size() << std::endl;
                // furniture
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
                // furniture
                rooms.push_back(newRoom);
            }
            newGame.addApartment(std::shared_ptr<apartment::Apartment>(new apartment::Apartment(apartmentName,rooms)));
            // tenants
        }
    }
}