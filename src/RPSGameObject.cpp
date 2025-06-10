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

Icon RPSGameObject::setIcon(RPSType type,bool player){
	_icon = RPSIconFac.newIcon(type,RPS_OBJECT_WIDTH,RPS_OBJECT_HEIGHT,player);
	return _icon;
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
