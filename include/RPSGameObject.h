#ifndef RPS_H
#define RPS_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"

enum RPSType { ROCK, PAPER, SCISSORS };
enum Direction { UP, DOWN, LEFT, RIGHT };
const int RPS_OBJECT_WIDTH = 1;
const int RPS_OBJECT_HEIGHT = 1;

class RPSGameObject : public GameObject, public ICollider {

public:
  bool isPlayer;

  RPSGameObject(RPSType,Direction,Position,bool);
  Icon setIcon(RPSType,bool);
  void update(Position) override;
  void onCollision(ICollider *) override;
  bool intersect(ICollider *) override;

  RPSType getType() const;
  void setType(RPSType type);
  void setDirection(Direction);

private:
  RPSType _type;
  Direction _dir;
};
#endif
