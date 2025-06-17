// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "gameObject.h"

class GameObjectFactory{
	public:
		static GameObjectFactory newFactory(){ return GameObjectFactory(); }
		Player* newPlayer(int,int);
		Wall* newWall(int,int,int,int);
		Enemy* newEnemy(int,int);
		Goal* newGoal(int,int);
	private:
		GameObjectFactory();
};

#endif

