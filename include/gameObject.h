#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "unit.h"
#include "icon.h"
#include "collider.h"

class GameObject : public ICollider{
	public:
		GameObject(Icon,Position);
    	Position getPosition() const;
  	 	Icon getIcon() const;

   	 	virtual void update(Position) = 0;
		bool intersect(ICollider *) override;
	protected:
    	Position _pos;
    	Icon _icon;
};

class Player : public GameObject{
	public:
		Player(Position);
		void update(Position) override;
		void move(int);
		void onCollision(ICollider *) override;
};

class Wall : public GameObject{
	public:
		Wall(Position,Position);
	    void update(Position) override;
		void onCollision(ICollider *) override;
};

class Enemy : public GameObject{
	public:
		Enemy(Position);
		void update(Position) override;
		void onCollision(ICollider *) override;
};

class Goal : public GameObject{
	public:
		Goal(Position);
		void update(Position) override;
		void onCollision(ICollider *) override;
};

#endif
