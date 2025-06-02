#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "unit.h"
#include "icon.h"

class GameObject{
	public:
		GameObject(Icon,Position);
    	Position getPosition() const;
  	 	Icon getIcon() const;
   	 	virtual void update(Position) = 0;
	protected:
    	Position _pos;
    	Icon _icon;
};
/*
class Player : public GameObject{
	public:
		Player(Position);
		void update(Position) override;
		void move(int);
};

class Wall : public GameObject{
	public:
		Wall(Position);
		void update(Position) override;
};
*/
#endif
