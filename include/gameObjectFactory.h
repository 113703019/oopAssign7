// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "gameObject.h"
#include "RPSGameObject.h"

class GameObjectFactory{
	public:
		static GameObjectFactory newFactory(){ return GameObjectFactory(); }
		/*
		Player* newPlayer(int,int);
		Wall* newWall(int,int);
		*/
		RPSGameObject* newRPS(RPSType,Direction,int,int,bool);
	private:
		GameObjectFactory();
};

#endif

