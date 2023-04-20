#include "StaticEntity.h"

StaticEntity::StaticEntity(string n, ofColor c, int entityX, int entityY, int cellSize):Entity(n, c, entityX,entityY, cellSize){}

void StaticEntity::tick(){

};
void StaticEntity::render(){

};
void StaticEntity::update(){

};
void StaticEntity::draw(){
    ofSetColor(this->getColor());
    ofDrawRectangle(currentEntityX*getCellsize(), currentEntityY*getCellsize(), getCellsize(), getCellsize());
        
};