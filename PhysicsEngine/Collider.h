#pragma once

class Collider
{
public:
	Collider() {}
	virtual ~Collider() {}

	enum class ColliderType
	{
		Point,
		Line,
		Circle,
		Rectangle,
		Polygon
	};

protected:
	ColliderType type = ColliderType::Point;
};
