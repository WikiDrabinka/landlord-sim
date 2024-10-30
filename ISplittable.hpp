#include <memory>
namespace splittable {
    class ISplittable {
        public:
        virtual bool containsPoint(int x, int y) = 0;
        void merge(std::shared_ptr<ISplittable> newSplittable);
        std::shared_ptr<ISplittable> split();
    };
}