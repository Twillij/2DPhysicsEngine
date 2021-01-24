#include "Box.h"
#include "BoxCollider.h"
#include <Gizmos.h>

Box::Box(vec2 centre, vec2 extents)
{
	position = centre;
	this->extents = extents;

	// set collider
	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->centre = position;
	boxCollider->extents = extents;
	collider = boxCollider;
}

void Box::Draw(Renderer2D* renderer)
{
	Gizmos::add2DAABB(position, extents, vec4(1, 1, 1, 0));
}
