#pragma once
#include "point.h"
#include "../display/format.h"
#include "../display/color.h"
#include <memory>

namespace splittable {
    class ISplittable {
        public:
        virtual bool containsPoint(point::Point point) = 0;
        void merge(std::shared_ptr<ISplittable> otherSplittable);
        std::shared_ptr<ISplittable> splitVertically(int y);
        std::shared_ptr<ISplittable> splitHorizontally(int x);
        std::vector<format::MultiFormattedString> draw();
        int area();
    };
}