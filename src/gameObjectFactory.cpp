// TODO implementation
#include "gameObject.h"
#include "gameObjectFactory.h"

GameObjectFactory::GameObjectFactory(){}

Player* GameObjectFactory::newPlayer(int pos_x,int pos_y){
	Player* player = new Player({pos_x,pos_y});
	return player;
}

Wall* GameObjectFactory::newWall(int pos_x,int pos_y,int extend_x,int extend_y){
	// extend.x(): Rightwards(>0) Leftwards(<0)
	// extend.y(): Downwards(>0) Upwards(<0)
	Wall* wall = new Wall({pos_x+(extend_x<0 ? extend_x : 0),pos_y+(extend_y<0 ? extend_y : 0)},{extend_x,extend_y});
	return wall;
}
