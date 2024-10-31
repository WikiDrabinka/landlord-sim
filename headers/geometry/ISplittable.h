#pragma once
#include "point.h"
#include "../display/canvas.h"
#include "../display/color.h"
#include <memory>

namespace splittable {
    class ISplittable {
        public:
        virtual bool containsPoint(point::Point point) = 0;
        void merge(std::shared_ptr<ISplittable> newSplittable);
        std::shared_ptr<ISplittable> split();
        std::unique_ptr<canvas::Canvas> draw();
    };
}