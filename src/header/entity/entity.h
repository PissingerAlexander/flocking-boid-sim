#ifndef _ENTITY_H
#define _ENTITY_H

#include "../vector/vectors.h"
#include "../matrix/matrices.h"

class Entity {
	Vector2 position;
	Vector2 direction;
	float velocity;
	float acceleration;

	Entity(float x, float y) {
		position = Vector2(x, y);
		direction = Vector2(1.0f, 0.0f);
		velocity = 0.1f;
		acceleration = 0.0f;
	};

	void draw() {
		// what?
	};

	void update(float deltaTime) {
		position += (direction * velocity);
		velocity += deltaTime * acceleration;
	};
};

#endif
