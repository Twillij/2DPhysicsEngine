#include "Box.h"
#include "BoxCollider.h"

Box::Box()
{
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->object = this;
	boxCollider->centre = position;
	boxCollider->extents = extents;
	collider = boxCollider;
}

void Box::Draw(Renderer2D* renderer)
{
	renderer->drawBox(position.x, position.y, extents.x * 2, extents.y * 2);
}
