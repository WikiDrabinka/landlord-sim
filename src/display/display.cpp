#include "../../headers/display/display.h"
namespace display {
    Display::Display(std::string displayName, int displayWidth, int displayHeight, displayType displayType, std::shared_ptr<game::Game> displayGame): width(displayWidth), height(displayHeight) {
        name = format::FormattedString(displayName,true,false,true,false);
        name.center(displayWidth);
        type = displayType;
        game = displayGame;
        displayStart = 0;
        idx = {};
        switch (type) {
        case furniture:
        {
            idx.push_back(0);
            idx.push_back(0);
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getRooms()[idx[1]]->getName());
            name.text[2].backgroundColor = game->getApartments()[idx[0]]->getRooms()[idx[1]]->getColor();
            name += ")";
            break;
        }
        case rooms:
        {
            idx.push_back(0);
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getName());
            name += ")";
            break;
        }
        case apartment:
        {
            idx.push_back(0);
            break;
        }
        case conversation:
        {
            idx.push_back(0);
            break;
        }
        }
        name.center(width);
        text.clear();
        updateDisplay();
    }
    void Display::updateDisplay(std::string newText) {
        text.clear();
        switch (type) {
        case furniture:
        {
            int i = 1;
            for (std::shared_ptr<furniture::Furniture> furn: game->getApartments()[idx[0]]->getRooms()[idx[1]]->getFurniture()){
                bool n = true;
                for (format::FormattedString line: furn->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(width);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
            break;
        }
        case rooms:
        {
            int i = 1;
            for (std::shared_ptr<room::Room> room: game->getApartments()[idx[0]]->getRooms()){
                bool n = true;
                for (format::FormattedString line: room->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(width);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
            break;
        }
        case tenants:
        {
            int i = 1;
            for (std::shared_ptr<lease::Lease> lease: game->getLeases()){
                bool n = true;
                for (format::FormattedString line: lease->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(width);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
            break;
        }
        case apartments:
        {
            int i = 1;
            for (std::shared_ptr<apartment::Apartment> apartment: game->getApartments()){
                bool n = true;
                for (format::FormattedString line: apartment->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(width);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
            break;
        }
        case apartment:
        {
            for (std::vector<std::string> str: game->getApartments()[idx[0]]->draw()->getDrawing()) {
                format::FormattedString line;
                for (int i=0;i<(width-(game->getApartments()[idx[0]]->maxY()*2-1))/2-1;++i) {
                    line += " ";
                }
                for (std::string c: str) {
                    line += c;
                }
                for (int i=0;i<(width-(game->getApartments()[idx[0]]->maxY()*2-1))/2-2;++i) {
                    line += " ";
                }
                if (width%2==0) {
                    line+=" ";
                }
                text.push_back(line);
            }
            format::FormattedString rent;
            rent += "Total rent: " + std::to_string(game->totalRent(game->getApartments()[idx[0]]));
            rent.left(width);
            text.push_back(rent);
            format::FormattedString happiness;
            happiness += "Average happiness: " + std::to_string(game->averageHapiness(game->getApartments()[idx[0]]));
            happiness.left(width);
            text.push_back(happiness);
            format::FormattedString rooms;
            rooms += "Rooms: " + std::to_string(game->getApartments()[idx[0]]->getRooms().size());
            rooms.left(width);
            text.push_back(rooms);
            break;
        }
        case store:
        {
            std::vector<std::shared_ptr<furniture::Furniture>> furnitureStore = game->getFurnitureStore();
            for (int i = 0; i<furnitureStore.size(); i=i+2) {
                format::FormattedString line;
                if (i==furnitureStore.size()-1) {
                    line = furnitureStore[i]->getDisplay()[0];
                    line = std::to_string(i+1)+") "+line;
                    line.left(width);
                    text.push_back(line);
                    for (int j = 1; j<furnitureStore[i]->getDisplay().size();++j) {
                        line = furnitureStore[i]->getDisplay()[j];
                        line.left(width);
                        text.push_back(line);
                    }
                } else {
                    format::FormattedString lineLeft = furnitureStore[i]->getDisplay()[0];
                    lineLeft = std::to_string(i+1)+") "+lineLeft;
                    lineLeft.left(width/2);
                    format::FormattedString lineRight = furnitureStore[i+1]->getDisplay()[0];
                    lineRight = std::to_string(i+2)+") "+lineRight;
                    if (width%2==0) {
                        lineRight.left(width/2);
                    } else {
                        lineRight.left(width/2+1);
                    }
                    line = lineLeft.getDisplay() + lineRight.getDisplay();
                    text.push_back(line);
                    for (int j = 1; j<furnitureStore[i]->getDisplay().size();++j) {
                        lineLeft = furnitureStore[i]->getDisplay()[j];
                        lineLeft.left(width/2);
                        lineRight = furnitureStore[i+1]->getDisplay()[j];
                        if (width%2==0) {
                            lineRight.left(width/2);
                        } else {
                            lineRight.left(width/2+1);
                        }
                        line = lineLeft.getDisplay() + lineRight.getDisplay();
                        text.push_back(line);
                    }
                }
            }
            break;
        }
        case storage:
        {
            std::vector<std::shared_ptr<furniture::Furniture>> furnitureStorage = game->getFurnitureStorage();
            for (int i = 0; i<furnitureStorage.size(); i=i+2) {
                format::FormattedString line;
                if (i==furnitureStorage.size()-1) {
                    line = furnitureStorage[i]->getDisplay()[0];
                    line = std::to_string(i+1)+") "+line;
                    line.left(width);
                    text.push_back(line);
                    for (int j = 1; j<furnitureStorage[i]->getDisplay().size();++j) {
                        line = furnitureStorage[i]->getDisplay()[j];
                        line.left(width);
                        text.push_back(line);
                    }
                } else {
                    format::FormattedString lineLeft = furnitureStorage[i]->getDisplay()[0];
                    lineLeft = std::to_string(i+1)+") "+lineLeft;
                    lineLeft.left(width/2);
                    format::FormattedString lineRight = furnitureStorage[i+1]->getDisplay()[0];
                    lineRight = std::to_string(i+2)+") "+lineRight;
                    if (width%2==0) {
                        lineRight.left(width/2);
                    } else {
                        lineRight.left(width/2+1);
                    }
                    line = lineLeft.getDisplay() + lineRight.getDisplay();
                    text.push_back(line);
                    for (int j = 1; j<furnitureStorage[i]->getDisplay().size();++j) {
                        lineLeft = furnitureStorage[i]->getDisplay()[j];
                        lineLeft.left(width/2);
                        lineRight = furnitureStorage[i+1]->getDisplay()[j];
                        if (width%2==0) {
                            lineRight.left(width/2);
                        } else {
                            lineRight.left(width/2+1);
                        }
                        line = lineLeft.getDisplay() + lineRight.getDisplay();
                        text.push_back(line);
                    }
                }
            }
            break;
        }
        case messages:
        {
            for (std::shared_ptr<messages::Conversation> conversation: game->getMessages()) {
                format::FormattedString line("",!conversation->read);
                line += conversation->getSender()->getName() + ": ";
                line += conversation->getMessages().back();
                if (line.textLength()>width) {
                    line.text.resize(width-4);
                    line += "...";
                }
                line.left(width);
                text.push_back(line);
            }
        }
        default:
        {
            text.push_back(newText);
            text[text.size()-1].left(width);
            break;
        }
        }
    }
    std::vector<std::string> Display::getDisplay() {
        updateDisplay();
        std::vector<std::string> display;
        display.push_back(name.getDisplay());
        if (displayStart>0) {
            format::FormattedString line("...",true,false,false,false);
            line.right(width);
            display.push_back(line.getDisplay());
        } else if (text.size()!=0) {
            display.push_back(text[0].getDisplay());
        }
        for (int i=displayStart+1; i<std::min(displayStart+height-2,(int) text.size()-1);++i) {
            display.push_back(text[i].getDisplay());
        }
        if (displayStart+height-1<text.size()) {
            format::FormattedString line("...",true,false,false,false);
            line.right(width);
            display.push_back(line.getDisplay());
        } else if (displayStart+height-1==text.size()) {
            display.push_back(text.back().getDisplay());
        } else {
            if (text.size()>1) {
                display.push_back(text.back().getDisplay());
            }
            for (int i = 0; i<displayStart+height-text.size();++i) {
                format::FormattedString line("");
                line.left(width);
                display.push_back(line.getDisplay());
            }
        }
        return display;
    }
    void Display::scrollUp(int i) {
        displayStart = std::max(0,displayStart-i);
    }
    void Display::scrollDown(int i) {
        displayStart = std::max(std::min(displayStart+i,(int) text.size()-height),0);
    }
    void Display::changeDisplay(displayType newType, std::string newName) {
        type=newType;
        name=format::FormattedString(newName,true,false,true,false);
        name.center(width);
        updateDisplay();
    }
    void Display::changeDisplay(std::vector<int> newIdx) {
        idx = newIdx;
        if (type==furniture) {
            name = name.text[0];
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getRooms()[idx[1]]->getName());
            name.text[2].backgroundColor = game->getApartments()[idx[0]]->getRooms()[idx[1]]->getColor();
            name += ")";
        }
        if (type==rooms) {
            name = name.text[0];
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getName());
            name += ")";
        }
        if (type==apartment) {
            name = format::MultiFormattedString(format::FormattedString(game->getApartments()[idx[0]]->getName(),true,false,true,false));
        }
        name.center(width);
        updateDisplay();
    }
}