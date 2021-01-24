#include "Box.h"
#include "BoxCollider.h"

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
	renderer->drawBox(position.x, position.y, extents.x * 2, extents.y * 2);
}
