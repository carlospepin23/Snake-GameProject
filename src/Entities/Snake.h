#pragma once
#include <vector>

enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

class Snake {

private:
    std::vector<std::vector<int>> body;
    Direction direction;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    bool crashed;
    bool inmortal=false;

public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();

    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    bool isCrashed() {return this->crashed;}
    bool isInmortal() {return this->inmortal;}
    void ignoreCrash();
    void setCrashed(bool b){this->crashed=b;}
    void setInmortal(bool i){this->inmortal=i;}
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    }

    void removeSegment(){
        body.pop_back();
    }
};
