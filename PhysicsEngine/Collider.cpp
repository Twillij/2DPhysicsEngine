#include "Collider.h"
#include "Collision.h"

Collision Collider::CheckCollision(Collider* other)
{
    return Collision(this, other);
}
