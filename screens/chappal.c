#include "chappal.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdlib.h>

// Creates a new chappal at a random location with a random rotation speed.
// Speed will increase with time.

static float speed = 6.0f;

Chappal* CreateChappal(Texture2D textures[], Vector2 target) {
	// Texture2D textures
	Chappal* chappal = malloc(sizeof(Chappal));
	int x = 0;
	int y = 0;
	const int WIDTH = GetScreenWidth();
	const int HEIGHT = GetScreenHeight();
	if (GetRandomValue(0, 1)) {
		x = GetRandomValue(
			target.x - (WIDTH / 2) - SPAWN_OFFSET,
			target.x + (WIDTH / 2) + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			y = target.y + (HEIGHT / 2) + SPAWN_OFFSET;
		} else {
			y = target.y - (HEIGHT / 2) - SPAWN_OFFSET;
		}
	} else {
		y = GetRandomValue(
			target.y - (HEIGHT / 2) - SPAWN_OFFSET,
			target.y + (HEIGHT / 2) + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			x = target.x + (WIDTH / 2) + SPAWN_OFFSET;
		} else {
			x = target.x - (WIDTH / 2) - SPAWN_OFFSET;
		}
	}
	Vector2 position = {x, y};
	chappal->position = position;
	Vector2 direction = Vector2Subtract(target, chappal->position);
	direction = Vector2Normalize(direction);
	chappal->rotation = 0.0f;
	chappal->rotationSpeed = (float)GetRandomValue(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX) / 10.0f;
	chappal->direction = direction;
	// chappal->texture = texture;
	// chappal->type = random type between 1 to n

	// int randNum = rng_u64(rng_u64(time(NULL))) % 100;

	int randNum = GetRandomValue(1, 100);

	if (randNum < 5)
		chappal->type = KHANA;
	else if (randNum < 20)
		chappal->type = DANDA;
	else if (randNum < 40)
		chappal->type = JUTA;
	else
		chappal->type = CHAPPAL;
	chappal->texture = textures[chappal->type];
	return chappal;
}

void UpdateChappal(Chappal* chappal) {
	Vector2 velocity = Vector2Scale(chappal->direction, speed);
	chappal->position = Vector2Add(chappal->position, velocity);
	chappal->rotation += chappal->rotationSpeed;
};

void DrawChappal(Chappal* chappal) {
	DrawTexturePro(
		chappal->texture,
		(Rectangle){0.0f, 0.0f, (float)chappal->texture.width, (float)chappal->texture.height},
		(Rectangle){
			(chappal->position.x),
			(chappal->position.y),
			(float)chappal->texture.width,
			(float)chappal->texture.height},
		(Vector2){(float)chappal->texture.width / 2, (float)chappal->texture.height / 2},
		chappal->rotation,
		WHITE);
};

void IncreaseSpeed() {
	speed += 4.0f;
};

void SetSpeed(float newSpeed) {
	speed = newSpeed;
};

void DestroyChappal(Chappal* chappal) {
	free(chappal);
};
