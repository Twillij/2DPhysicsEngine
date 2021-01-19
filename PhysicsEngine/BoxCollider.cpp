#include "BoxCollider.h"
#include "CollisionDetection.h"

BoxCollider::BoxCollider()
{
	type = ColliderType::Box;
}

Collision BoxCollider::CheckCollision(LineCollider* line)
{
	return physics::Line2BoxCollision(line, this);
}

Collision BoxCollider::CheckCollision(BoxCollider* box)
{
	return physics::Box2BoxCollision(this, box);
}

vec2* BoxCollider::GetBoxCorners()
{
	vec2 corners[4];
	
	corners[0] = vec2(centre.x + extents.x, centre.y + extents.y);
	corners[1] = vec2(centre.x + extents.x, centre.y - extents.y);
	corners[2] = vec2(centre.x - extents.x, centre.y - extents.y);
	corners[3] = vec2(centre.x - extents.x, centre.y + extents.y);

	return &corners[0];
}
