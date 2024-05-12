#include "chappal.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdlib.h>

// Speed will increase with time.
static float speed = 6.0f;

// Creates a new chappal at a random location with a random rotation speed.
Chappal* CreateChappal(Texture2D textures[], Vector2 target) {
	Chappal* chappal = malloc(sizeof(Chappal));

	int x = 0;
	int y = 0;

	const int halfWidth = GetScreenWidth() / 2;
	const int halfHeight = GetScreenHeight() / 2;

	if (GetRandomValue(0, 1)) {
		x = GetRandomValue(
			target.x - halfWidth - SPAWN_OFFSET,
			target.x + halfWidth + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			y = target.y + halfHeight + SPAWN_OFFSET;
		} else {
			y = target.y - halfHeight - SPAWN_OFFSET;
		}
	} else {
		y = GetRandomValue(
			target.y - halfHeight - SPAWN_OFFSET,
			target.y + halfHeight + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			x = target.x + halfWidth + SPAWN_OFFSET;
		} else {
			x = target.x - halfWidth - SPAWN_OFFSET;
		}
	}

	Vector2 position = {x, y};
	chappal->position = position;
	Vector2 direction = Vector2Subtract(target, chappal->position);
	direction = Vector2Normalize(direction);
	chappal->rotation = 0.0f;
	chappal->rotationSpeed = (float)GetRandomValue(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX) / 10.0f;
	chappal->direction = direction;

	// Choose a weapon randomly.
	int weaponChoice = GetRandomValue(1, 100);

	if (weaponChoice < 5)
		chappal->type = KHANA;
	else if (weaponChoice < 20)
		chappal->type = DANDA;
	else if (weaponChoice < 40)
		chappal->type = JUTA;
	else
		chappal->type = CHAPPAL;

	// Set weapon texture.
	chappal->texture = textures[chappal->type];

	return chappal;
}

void UpdateChappal(Chappal* chappal) {
	Vector2 velocity = Vector2Scale(chappal->direction, speed);
	chappal->position = Vector2Add(chappal->position, velocity);
	chappal->rotation += chappal->rotationSpeed;
}

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
}

void IncreaseSpeed() {
	speed += 4.0f;
}

void SetSpeed(float newSpeed) {
	speed = newSpeed;
}

void DestroyChappal(Chappal* chappal) {
	free(chappal);
}
