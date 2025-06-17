#include <iostream> //debug
#include <cmath>
#include "environment.h"
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

// Current problem: Some parts of the wall icon doesns't seem to be in the collide hitbox range

int GameObject::intersect(ICollider *ogOther){
    GameObject* other = dynamic_cast<GameObject*>(ogOther);
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
    Coverage tCover = {{_pos.x(),_pos.x()+int(icon_width(this->getIcon()))},
					   {_pos.y(),_pos.y()+int(icon_height(this->getIcon()))}};
    Coverage oCover = {{oPos.x(),oPos.x()+int(icon_width(other->getIcon()))},
					   {oPos.y(),oPos.y()+int(icon_height(other->getIcon()))}};

    // I made it so that the collision works even if they simply collide (not intersect)
    int range = 1;

    // Check x intersection
    for(int i=tCover.x.start-range;i<tCover.x.end+range;i++){
	if(oCover.x.start==i || oCover.x.end-1==i){
		// x strict intersection
		if(i>=tCover.x.start && i<=tCover.x.end){
			// y strict intersection
			for(int j=tCover.y.start;j<tCover.y.end;j++){
				if(oCover.y.start==j || oCover.y.end-1==j)
					return 2;
			}
		}
		// x lenient intersection
		// y lenient intersection
		for(int j=tCover.y.start-range;j<tCover.y.end+range;j++){
			if(oCover.y.start==j || oCover.y.end-1==j)
				return 1;
		}
	}
    } return 0;
}

Player::Player(Position pos)
	:_hp(3),GameObject(iconFac.newIcon(YELLOW,1,1),pos) {}

int Player::getHP(){
	return _hp;
}

void Player::update(Position move){
	_pos.x() += move.x();
	_pos.y() += move.y();
}

void Player::onCollision(ICollider *ogOther){
	// The player can only collide with 2 types of objects:
	// (1) Damage - Enemies & Traps
	// (2) Goal - The green door
	GameObject* other = dynamic_cast<GameObject*>(ogOther);
	if(dynamic_cast<Enemy*>(ogOther)){
		// Damage the player.
		_hp--;
	}/* else if(dynamic_cast<Goal*>(ogOther)){
		// End the game. The player wins.
	}*/
}

Wall::Wall(Position pos,Position extend)
	:GameObject(iconFac.newIcon(/*color*/CYAN,
		     		    /*width*/1+abs(extend.x()),
				    /*height*/1+abs(extend.y())),pos) {}

void Wall::update(Position move){}

void Wall::onCollision(ICollider *ogOther) {}

Enemy::Enemy(Position pos)
	:GameObject(iconFac.newIcon(RED,1,1),pos) {}

void Enemy::update(Position move){
	_pos.x() += move.x();
	_pos.y() += move.y();
}

void Enemy::onCollision(ICollider *ogOther){}

Goal::Goal(Position pos)
	:GameObject(iconFac.newIcon(GREEN,1,2),pos) {}

void Goal::update(Position move) {}

void Goal::onCollision(ICollider *ogOther){
	GameObject* other = dynamic_cast<GameObject*>(ogOther);
	if(dynamic_cast<Player*>(ogOther))
		trigger = true;
}
