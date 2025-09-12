#include "headers/boid.h"

Boid::Boid(unsigned int id): id(id) {
	position.x = (rand() % WIDTH ) - (WIDTH / 2);
	position.y = (rand() % HEIGHT) - (HEIGHT / 2);
	float rotation = (float)(rand() % 360) * PI / 180;
	velocity.x = std::cos(rotation);
	velocity.y = std::sin(rotation);
	float speed = (float)(rand() % MAX_VELOCITY) + 1;
	velocity *= speed;
}

Boid::~Boid() {};

void Boid::update(const float delta, const std::vector<Boid>& boids) {
	for (Boid boid : boids) {
		if (boid.id == id) continue;
	}
	position += velocity * delta;

	if (position.x < -(WIDTH/2)) position.x = WIDTH/2;
	else if (position.x > WIDTH/2) position.x = -(WIDTH/2);
	if (position.y < -(HEIGHT/2)) position.y = HEIGHT/2;
	else if (position.y > HEIGHT/2) position.y = -(HEIGHT/2);
}

