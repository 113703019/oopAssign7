// TODO implementation
#include "iconFactory.h"
#include "gameObject.h"

IconFactory iconFac = IconFactory::newFactory();

GameObject::GameObject(Icon icon,Position pos)
	:_icon(icon),_pos(pos){}

Icon GameObject::getIcon() const {
	return _icon;
}

Position GameObject::getPosition() const {
	return _pos;
}
/*
Player::Player(Position pos)
	:GameObject(iconFac.newIcon(RED,1,1),pos) {}

void Player::update(Position move){
	_pos.x() += move.x();
	_pos.y() += move.y();
}

Wall::Wall(Position pos)
	:GameObject(iconFac.newIcon(CYAN,2,2),pos) {}

void Wall::update(Position move){}
*/
