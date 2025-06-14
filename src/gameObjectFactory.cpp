// TODO implementation
#include "gameObject.h"
#include "gameObjectFactory.h"

GameObjectFactory::GameObjectFactory(){}

Player* GameObjectFactory::newPlayer(int pos_x,int pos_y){
	Player* player = new Player({pos_x,pos_y});
	return player;
}

Wall* GameObjectFactory::newWall(int pos_x,int pos_y){
	Wall* wall = new Wall({pos_x,pos_y});
	return wall;
}
