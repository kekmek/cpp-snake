#ifndef GAME
#define GAME

class Game{
 public:
 

 private:

};

class Snake{
 public:
    //Snake();
    void CheckAlive();
    void SetDirection(char dir);
    //~Snake();

 private:

    bool is_alive;
    size_t size;
    struct Direction{
        bool UP    = false;
        bool DOWN  = false;
        bool RIGHT = false;
        bool LEGT  = false;
    } Dir;

};

#endif //GAME