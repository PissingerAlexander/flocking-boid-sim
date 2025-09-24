#include "headers/boid.h"

Boid::Boid(unsigned int id): id(id) {
	position.x = (rand() % WIDTH ) - (WIDTH / 2);
	position.y = (rand() % HEIGHT) - (HEIGHT / 2);
	float rotation = (float)(rand() % 360) * PI / 180;
	velocity.x = std::cos(rotation);
	velocity.y = std::sin(rotation);
	float speed = (float)(rand() % (MAX_SPEED - MIN_SPEED + 1)) + MIN_SPEED;
	velocity *= speed;
}

Boid::Boid(unsigned int id, float x, float y): id(id), position(x, y) {
	velocity.x = 2.0f;
	velocity.y = 0.0f;
	velocity;

};

Boid::~Boid() {};

void Boid::update(const float delta, const std::vector<Boid>& boids) {
	applySteer(boids);

	if (velocity.magnitude() > MAX_SPEED) velocity = velocity.normalized() * MAX_SPEED;
	if (velocity.magnitude() < MIN_SPEED) velocity = velocity.normalized() * MIN_SPEED;
	position += velocity * delta;
	velocity *= FRICTION;

	if (position.x < -(WIDTH/2)) position.x = WIDTH/2;
	else if (position.x > WIDTH/2) position.x = -(WIDTH/2);
	if (position.y < -(HEIGHT/2)) position.y = HEIGHT/2;
	else if (position.y > HEIGHT/2) position.y = -(HEIGHT/2);
}

void Boid::applySteer(const std::vector<Boid>& boids) {
	// TODO: possibly account amount of neibours
	unsigned int neighbours = 0;
	Vector2 separation = Vector2(0, 0);
	Vector2 alignment = Vector2(0, 0);
	Vector2 cohesion = Vector2(0, 0);
	for (Boid boid : boids) {
		if (boid.id == id) continue;

		Vector2 distance = position - boid.position;
		float distanceMagnitude = distance.magnitude();
		if (distanceMagnitude > INFLUENCE_RANGE) continue;
		neighbours++;

		// SEPARATION
		if (distanceMagnitude < SEPARATION_RANGE) {
			float weight = (distanceMagnitude * distanceMagnitude) / 100;

			separation += distance.normalized() * weight;
			// separation += distance.normalized();
			// separation += distance * (1/(distance.magnitude()*distance.magnitude()));
		}

		// ALIGNMENT
		alignment += boid.velocity.normalized();

		// COHESION
		cohesion += boid.position;
	}
	Vector2 randomNoise = Vector2(
		(float)(rand() % 200 - 100) / 100.0f,
		(float)(rand() % 200 - 100) / 100.0f
	);
	randomNoise = randomNoise.normalized() * NOISE;
	if (neighbours == 0) {
		velocity += randomNoise;
		return;
	}

	separation *= SEPARATION;

	if (alignment.magnitude() > 0) {
		alignment = alignment.normalized() * ALIGNMENT;
	}
	
	if (cohesion.magnitude() > 0) {
		cohesion /= neighbours;
		cohesion = cohesion - position;
		cohesion = cohesion.normalized() * COHESION;
	}


	Vector2 steer = separation + alignment + cohesion + randomNoise;
	velocity += steer;
}
