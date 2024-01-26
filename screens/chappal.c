#include "chappal.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdio.h>
#include <stdlib.h>

// Creates a new chappal at a random location with a random rotation speed.
// Speed will increase with time.

static float speed = 3.0f;

Chappal* CreateChappal(Texture2D texture, Vector2 target) {
	Chappal* chappal = malloc(sizeof(Chappal));
	int x = 0;
	int y = 0;
	if (GetRandomValue(0, 1)) {
		x = GetRandomValue(-SPAWN_OFFSET, GetScreenWidth() + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			y = GetScreenHeight() + SPAWN_OFFSET;
		} else {
			y = -SPAWN_OFFSET;
		}
	} else {
		y = GetRandomValue(-SPAWN_OFFSET, GetScreenHeight() + SPAWN_OFFSET);
		if (GetRandomValue(0, 1)) {
			x = GetScreenWidth() + SPAWN_OFFSET;
		} else {
			x = -SPAWN_OFFSET;
		}
	}
	Vector2 position = {x, y};
	chappal->position = position;
	Vector2 direction = Vector2Subtract(target, chappal->position);
	direction = Vector2Normalize(direction);
	chappal->rotation = 0.0f;
	chappal->rotationSpeed = (float)GetRandomValue(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX) / 10.0f;
	chappal->direction = direction;
	chappal->texture = texture;
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

void DestroyChappal(Chappal* chappal) {
	free(chappal);
};