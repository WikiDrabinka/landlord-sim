#include "../../../headers/objects/apartments/room.h"
#include <algorithm>
namespace room {
    Room::Room(std::string roomName, livingSpace::state roomState, color::BackgroundColor roomColor) {
        name = roomName;
        occupancyState = roomState;
        color = roomColor;
    }
    Room::Room(std::string roomName, livingSpace::state roomState, std::shared_ptr<rectangle::Rectangle> roomRectangle) {
        name = roomName;
        occupancyState = roomState;
        rectangles.push_back(roomRectangle);
        color = roomRectangle->getColor();
    }
    Room::Room(std::string roomName, livingSpace::state roomState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles, color::BackgroundColor roomColor) {
        name = roomName;
        occupancyState = roomState;
        color = roomColor;
        for (int i=0; i<roomRectangles.size(); ++i) {
            rectangles.push_back(roomRectangles[i]);
            roomRectangles[i]->setColor(roomColor);
        }
    }
    std::vector<std::shared_ptr<rectangle::Rectangle>> Room::getRectangles() { return rectangles; }
    std::vector<std::shared_ptr<furniture::Furniture>> Room::getFurniture() { return furniture; }
    color::BackgroundColor Room::getColor() { return color; }
    void Room::addRectangle(std::shared_ptr<rectangle::Rectangle> newRectangle) {
        rectangles.push_back(newRectangle);
        newRectangle->setColor(color);
    }
    std::vector<format::FormattedString> Room::getDisplay() {
        std::vector<format::FormattedString> display;
        display.push_back(format::FormattedString(name,std::nullopt,color,true,false,false,false));
        if (occupancyState==livingSpace::shared) {
            display.push_back(format::FormattedString("Shared"));
        } else if (occupancyState==livingSpace::unclaimed) {
            display.push_back(format::FormattedString("Unclaimed"));
        } else {
            display.push_back("Claimed by "+claim->getName());
        }
        return display;
    }
    std::shared_ptr<tenant::Tenant> Room::getClaim() { return claim; }
    bool Room::containsPoint(point::Point point) {
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            if (rectangle->containsPoint(point)) {
                return true;
            }
        }
        return false;
    }
    void Room::addFurniture(std::shared_ptr<furniture::Furniture> newFurniture, point::Point position) {
        if (!containsPoint(position) || !containsPoint(position+point::Point(newFurniture->getSizeX()-1,newFurniture->getSizeY()-1))) {
            std::cerr << "Invalid position. (" << position.x << "," << position.y << ")" << std::endl;
            return;
        }
        newFurniture.get()->setPosition(position);
        furniture.push_back(newFurniture);
    }
    void Room::merge(std::shared_ptr<Room> otherRoom) {
        for (std::shared_ptr<rectangle::Rectangle> rect: otherRoom->getRectangles()) {
            rect->setColor(color);
            rectangles.push_back(rect);
        }
    }
    void Room::setClaim(std::shared_ptr<tenant::Tenant> newTenant) {
        if (newTenant==nullptr) {
            claim = nullptr;
            occupancyState = livingSpace::unclaimed;
        } else {
            claim = newTenant;
            occupancyState = livingSpace::claimed;
        }
    }
    std::shared_ptr<Room> Room::split(std::string newName, std::set<int> rectIndices) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> newRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        for (int i=0; i<rectangles.size(); ++i) {
            if (rectIndices.count(i)>0) {
                splitRectangles.push_back(rectangles[i]);
            } else {
                newRectangles.push_back(rectangles[i]);
            }
        }
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,splitRectangles,color));
        rectangles = newRectangles;
        return newRoom;
    }
    std::shared_ptr<Room> Room::splitVertically(std::string newName, int y, std::vector<std::shared_ptr<furniture::Furniture>> &storage) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> rightRectangles;
        std::copy_if(rectangles.begin(),rectangles.end(),std::back_inserter(rightRectangles),[y](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().y>y;});
        std::copy_if(rectangles.begin(),rectangles.end(),std::back_inserter(splitRectangles),[y](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().y<=y && rect->getPoint2().y>y;});
        rectangles.erase(std::remove_if(rectangles.begin(),rectangles.end(),[y](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().y>y;}),rectangles.end());
        for (std::shared_ptr<rectangle::Rectangle> rect: splitRectangles) {
            rightRectangles.push_back(rect->splitVertically(y));
        }

        std::vector<std::shared_ptr<furniture::Furniture>> rightFurniture;
        std::copy_if(furniture.begin(),furniture.end(),std::back_inserter(rightFurniture),[y](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().y>y;});
        std::copy_if(furniture.begin(),furniture.end(),std::back_inserter(storage),[y](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().y<=y && furn->getPosition().y+furn->getSizeY()-1>y;});
        furniture.erase(std::remove_if(furniture.begin(),furniture.end(),[y](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().y+furn->getSizeY()-1>y;}),furniture.end());
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,rightRectangles,color));
        for (std::shared_ptr<furniture::Furniture> furn: rightFurniture) {
            newRoom->addFurniture(furn,furn->getPosition());
        }
        return newRoom;
    }
    std::shared_ptr<Room> Room::splitHorizontally(std::string newName, int x, std::vector<std::shared_ptr<furniture::Furniture>>& storage) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> bottomRectangles;
        std::copy_if(rectangles.begin(),rectangles.end(),std::back_inserter(bottomRectangles),[x](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().x>x;});
        std::copy_if(rectangles.begin(),rectangles.end(),std::back_inserter(splitRectangles),[x](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().x<=x && rect->getPoint2().x>x;});
        rectangles.erase(std::remove_if(rectangles.begin(),rectangles.end(),[x](std::shared_ptr<rectangle::Rectangle> rect) {return rect->getPoint1().x>x;}),rectangles.end());
        for (std::shared_ptr<rectangle::Rectangle> rect: splitRectangles) {
            bottomRectangles.push_back(rect->splitHorizontally(x));
        }

        std::vector<std::shared_ptr<furniture::Furniture>> bottomFurniture;
        std::copy_if(furniture.begin(),furniture.end(),std::back_inserter(bottomFurniture),[x](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().x>x;});
        std::copy_if(furniture.begin(),furniture.end(),std::back_inserter(storage),[x](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().x<=x && furn->getPosition().x+furn->getSizeX()-1>x;});
        furniture.erase(std::remove_if(furniture.begin(),furniture.end(),[x](std::shared_ptr<furniture::Furniture> furn) {return furn->getPosition().x+furn->getSizeX()-1>x;}),furniture.end());
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,bottomRectangles,color));
        for (std::shared_ptr<furniture::Furniture> furn: bottomFurniture) {
            newRoom->addFurniture(furn,furn->getPosition());
        }
        return newRoom;
    }
    int Room::maxX() {
        int maxX = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxX = std::max(maxX,rectangle->getPoint2().x);
        }
        return maxX;
    }
    int Room::minX() {
        int minX = INT16_MAX;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            minX = std::min(minX,rectangle->getPoint1().x);
        }
        return minX;
    }
    int Room::maxY() {
        int maxY = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxY = std::max(maxY,rectangle->getPoint2().y);
        }
        return maxY;
    }
    int Room::minY() {
        int minY = INT16_MAX;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            minY = std::min(minY,rectangle->getPoint1().y);
        }
        return minY;
    }
    int Room::area() {
        // to change once I have an idea
        int sum = 0;
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            sum += rect->area();
        }
        return sum;
    }
    
    void Room::draw(std::shared_ptr<canvas::Canvas> drawing) {
        for (std::shared_ptr<furniture::Furniture> furn : furniture) {
            if (furn->getSizeX()==1 && furn->getSizeY()==1) {
                drawing->changeDrawing(furn->getPosition(),furn->getColor().getString()+"╠╣");
            } else if (furn->getSizeX()==1) {
                drawing->changeDrawing(furn->getPosition(),furn->getColor().getString()+"╠═");
                for (int i = 1; i<furn->getSizeY()-1; ++i) {
                    drawing->changeDrawing(furn->getPosition()+point::Point(0,i),furn->getColor().getString()+"══");
                }
                drawing->changeDrawing(furn->getPosition()+point::Point(0,furn->getSizeY()-1),furn->getColor().getString()+"═╣");
            } else if (furn->getSizeY()==1) {
                drawing->changeDrawing(furn->getPosition(),furn->getColor().getString()+" ╦");
                for (int i = 1; i<furn->getSizeX()-1; ++i) {
                    drawing->changeDrawing(furn->getPosition()+point::Point(i,0),furn->getColor().getString()+" ║");
                }
                drawing->changeDrawing(furn->getPosition()+point::Point(furn->getSizeX()-1,0),furn->getColor().getString()+" ╩");
            } else {
                drawing->changeDrawing(furn->getPosition(),furn->getColor().getString()+"╔═");
                drawing->changeDrawing(furn->getPosition()+point::Point(0,furn->getSizeY()-1),furn->getColor().getString()+"═╗");
                drawing->changeDrawing(furn->getPosition()+point::Point(furn->getSizeX()-1,0),furn->getColor().getString()+"╚═");
                drawing->changeDrawing(furn->getPosition()+point::Point(furn->getSizeX()-1,furn->getSizeY()-1),furn->getColor().getString()+"═╝");
                for (int i = 1; i<furn->getSizeX()-1; ++i) {
                    drawing->changeDrawing(furn->getPosition()+point::Point(i,0),furn->getColor().getString()+"║ ");
                    drawing->changeDrawing(furn->getPosition()+point::Point(i,furn->getSizeY()-1),furn->getColor().getString()+" ║");
                }
                for (int i = 1; i<furn->getSizeY()-1; ++i) {
                    drawing->changeDrawing(furn->getPosition()+point::Point(0,i),furn->getColor().getString()+"══");
                    drawing->changeDrawing(furn->getPosition()+point::Point(furn->getSizeX()-1,i),furn->getColor().getString()+"══");
                }
            }
        }
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            rect->draw(drawing);
        }
    }
    std::ostream& operator<<(std::ostream& os, Room room) {
        os << *room.draw();
        return os;
    }
    std::shared_ptr<canvas::Canvas> Room::draw() {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(maxX()+1,maxY()+1,"  "));
        draw(drawing);
        return drawing;
    }
}
