#include "wall.h"
#include <vector>
#include <algorithm>
#include <iostream>
namespace wall {
    Wall::Wall(int wallStartX, int wallStartY, int wallEndX, int wallEndY) {
        startX = wallStartX;
        startY = wallStartY;
        endX = wallEndX;
        endY = wallEndY;
    }
    bool Wall::containsPoint(int pointX, int pointY) {
        if (startX==endX) {
            return (pointX==startX && ((pointY<=startY && pointY>=endY) || (pointY>=startY && pointY<=endY)));
        }
        if (startY==endY) {
            return (pointY==startY && ((pointX<=startX && pointX>=endX) || (pointX>=startX && pointX<=endX)));
        }
        return false;
    }
    void Wall::merge(std::shared_ptr<Wall> wall) {
        if (startX==endX && wall->startX==wall->endX && startX==wall->startX) {
            std::vector<int> points1;
            std::vector<int> points2;
            for (int i=std::min(startY,endY); i<=std::max(startY,endY); ++i ) {
                points1.push_back(i);
            }
            for (int i=std::min(wall->startY,wall->endY); i<=std::max(wall->startY,wall->endY); ++i ) {
                points2.push_back(i);
            }
            std::vector<int> intersection;
            std::set_intersection(points1.begin(),points1.end(),points2.begin(),points2.end(),std::back_inserter(intersection));
            if (intersection.size()==0) {
                std::cerr << "Cannot merge incompatible walls." << std::endl;
                return;
            }
            std::vector<int> newPoints;
            std::set_union(points1.begin(),points1.end(),points2.begin(),points2.end(),std::back_inserter(newPoints));
            startY = *std::min_element(newPoints.begin(),newPoints.end());
            endY = *std::max_element(newPoints.begin(),newPoints.end());
        } else if (startY==endY && wall->startY==wall->endY && startY==wall->startY){
            std::vector<int> points1;
            std::vector<int> points2;
            for (int i=std::min(startX,endX); i<=std::max(startX,endX); ++i ) {
                points1.push_back(i);
            }
            for (int i=std::min(wall->startX,wall->endX); i<=std::max(wall->startX,wall->endX); ++i ) {
                points2.push_back(i);
            }
            std::vector<int> intersection;
            std::set_intersection(points1.begin(),points1.end(),points2.begin(),points2.end(),std::back_inserter(intersection));
            if (intersection.size()==0) {
                std::cerr << "Cannot merge incompatible walls." << std::endl;
                return;
            }
            std::vector<int> newPoints;
            std::set_union(points1.begin(),points1.end(),points2.begin(),points2.end(),std::back_inserter(newPoints));
            startX = *std::min_element(newPoints.begin(),newPoints.end());
            endX = *std::max_element(newPoints.begin(),newPoints.end());
        } else {
            std::cerr << "Cannot merge incompatible walls." << std::endl;
        }
    }
    std::shared_ptr<Wall> Wall::split(int newEndX, int newEndY) {
        if (!Wall::containsPoint(newEndX, newEndY)) {
              std::cerr << "Cannot split wall at a point not contained in it." << std::endl;
            return nullptr;
        }
        std::shared_ptr<Wall> newWall = std::shared_ptr<Wall>(new Wall(newEndX, newEndY, endX, endY));
        endX = newEndX;
        endY = newEndY;
        return newWall;
    }

    int Wall::getStartX() { return startX; }
    int Wall::getStartY() { return startY; }
    int Wall::getEndX() { return endX; }
    int Wall::getEndY() { return endY; }
    bool Wall::operator==(Wall &otherWall) {
        return ((startX==otherWall.startX && startY==otherWall.startY && endX==otherWall.endX && endY==otherWall.endY) || (startX==otherWall.startY && startY==otherWall.startX && endX==otherWall.endY && endY==otherWall.endX));
    }

    Door::Door(int doorX, int doorY) {
        X = doorX;
        Y = doorY;
    }
    int Door::getX() { return X; }
    int Door::getY() { return Y; }

}