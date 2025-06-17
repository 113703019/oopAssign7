#ifndef COLLIDER_H
#define COLLIDER_H

class ICollider {

public:
  virtual ~ICollider() = default;
  virtual int intersect(ICollider *) = 0;
  virtual void onCollision(ICollider *) = 0;
};
#endif
