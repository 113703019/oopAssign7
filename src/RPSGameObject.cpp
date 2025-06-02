#include "iconFactory.h"
#include "RPSGameObject.h"
#include "unit.h"

IconFactory RPSIconFac = IconFactory::newFactory();

RPSGameObject::RPSGameObject(RPSType type,Direction dir,Position pos,bool player)
	:_type(type),_dir(dir),isPlayer(player),GameObject(RPSIconFac.newIcon(type,RPS_OBJECT_WIDTH,RPS_OBJECT_HEIGHT,player),pos) {}

void RPSGameObject::update(Position move){
	_pos.x() += move.x();
	_pos.y() += move.y();
}

void RPSGameObject::onCollision(ICollider *ogOther){
	RPSGameObject* other = dynamic_cast<RPSGameObject*>(ogOther);
	RPSType oType = other->getType();
	if(_type==ROCK && oType==PAPER){
		// If the player gets beaten by PAPER, thought you can play as PAPER?
	    // No! You die!
		_type = PAPER;
		if(isPlayer) isPlayer = false;
	} else if(_type==PAPER && oType==SCISSORS) _type = SCISSORS;
	else if(_type==SCISSORS && oType==ROCK) _type = ROCK;
	_icon = setIcon(_type,isPlayer);
}

Icon RPSGameObject::setIcon(RPSType type,bool player){
	_icon = RPSIconFac.newIcon(type,RPS_OBJECT_WIDTH,RPS_OBJECT_HEIGHT,player);
	return _icon;
}

bool RPSGameObject::intersect(ICollider *ogOther){
	RPSGameObject* other = dynamic_cast<RPSGameObject*>(ogOther);
	// Declare stuff
	struct Range{
		int start;
		int end;
	};
	struct Coverage{
		Range x;
		Range y;
	};
	Position oPos = other->getPosition();
	Coverage tCover = {{_pos.x(),_pos.x()+RPS_OBJECT_WIDTH},{_pos.y(),_pos.y()+RPS_OBJECT_HEIGHT}};
	Coverage oCover = {{oPos.x(),oPos.x()+RPS_OBJECT_WIDTH},{oPos.y(),oPos.y()+RPS_OBJECT_HEIGHT}};
	
	// I made it so that the collision works even if they simply collide (not intersect)
	int range = 1;

	// Check x intersection
	for(int i=tCover.x.start-range;i<tCover.x.end+range;i++){
		if(oCover.x.start==i || oCover.x.end-1==i){
			// Check y intersection
			for(int j=tCover.y.start-range;j<tCover.y.end+range;j++){
				if(oCover.y.start==j || oCover.y.end-1==j)
					return true;
			}
		}
	} return false;
}

RPSType RPSGameObject::getType() const{
	return _type;
}

void RPSGameObject::setType(RPSType type){
	_type = type;
}

void RPSGameObject::setDirection(Direction dir){
	_dir = dir;
}
