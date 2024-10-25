namespace splittable {
    class ISplittable {
        public:
        virtual bool containsPoint(int x, int y) = 0;
        void merge(ISplittable *newSplittable);
        ISplittable *split();
    };
}