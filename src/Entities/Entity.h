#pragma once
#include "ofMain.h"

class Entity {

protected:
    //Analizar Cuales propiedades puede conservar, cuales se pueden borrar y cuales puedes ser privadas 
    string name;
    ofColor color;
    int currentEntityX,currentEntityY;
    // bool crashed; //not implemented
    int cellSize; // Pixels

public:
    //(name,color,pos en eje x, pos en eje y, tamaño de entidad)
    Entity(string n, ofColor c, int entityX, int entityY, int cell_size){
        this->name=n;
        this->color=c;
        this->currentEntityX = entityX;
        this->currentEntityY = entityY;
        this->cellSize=cell_size;
    }
    virtual ~Entity(){}
    virtual void tick()=0;
    virtual void render()=0;
    virtual void update()=0;
    virtual void draw()=0;
    ofColor getColor(){return this->color;}
    int getCellsize(){return this->cellSize;}

    int getEntityX(){return this->currentEntityX;}
    int getEntityY(){return this->currentEntityY;}
    
};
