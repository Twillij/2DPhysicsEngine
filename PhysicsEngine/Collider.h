#pragma once

class Collider
{
public:
	Collider() {}
	virtual ~Collider() {}

	enum class ColliderType
	{
		Plane,
		Circle,
		Box,
		Mesh
	};

	ColliderType type;
};
