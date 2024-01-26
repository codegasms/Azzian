#ifndef CHAPPAL_H
#define CHAPPAL_H

#include <raylib.h>

#define SPAWN_OFFSET 100
#define ROTATION_SPEED_MIN -10.0f
#define ROTATION_SPEED_MAX 10.0f

typedef struct Chappal {
	Texture2D texture;
	Vector2 position;
	Vector2 direction;
	float rotation;
	float rotationSpeed;
} Chappal;

Chappal* CreateChappal(Texture2D texture, Vector2 target);
void UpdateChappal(Chappal* chappal);
void DrawChappal(Chappal* chappal);
void DestroyChappal(Chappal* chappal);

#endif