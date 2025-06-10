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

bool GameObject::intersect(ICollider *ogOther){
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

Player::Player(Position pos)
	:GameObject(iconFac.newIcon(RED,1,1),pos) {}

void Player::update(Position move){
	_pos.x() += move.x();
	_pos.y() += move.y();
}

void Player::onCollision(ICollider *ogOther){
	// The player can only collide with 3 types of objects:
	// (1) Boundaries - Walls & Floors
	// (2) Damage - Enemies & Traps
	// (3) Goal - The green door
    GameObject* other = dynamic_cast<GameObject*>(ogOther);
    /*if(other==Boundaries){
        // Block the player, do not let it go through walls or floors.
	} else if(other==Enemy || other==Trap){
		// Damage the player. Better if the player goes flying for a little.
	} else if(other==Goal){
		// End the game. The player wins.
	}*/
}

Wall::Wall(Position pos)
	:GameObject(iconFac.newIcon(CYAN,2,2),pos) {}

void Wall::update(Position move){}
