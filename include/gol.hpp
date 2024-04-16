#define GOL_HEIGHT 64
#define GOL_WIDTH 128


class GameOfLife{
    public:
        GameOfLife();
        void step();
        bool* getState();
};