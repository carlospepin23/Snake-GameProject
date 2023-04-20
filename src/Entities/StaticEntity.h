#pragma once
#include "Entity.h"

class StaticEntity:public Entity{
    private:

    public:
        StaticEntity(string name, ofColor color, int entityX, int entityY, int cellSize);
        ~StaticEntity(){};
        void tick();
        void render();
        void update();
        void draw();

};