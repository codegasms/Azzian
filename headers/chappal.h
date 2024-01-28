#ifndef CHAPPAL_H
#define CHAPPAL_H

#include <raylib.h>

#define SPAWN_OFFSET 100
#define ROTATION_SPEED_MIN -10.0f
#define ROTATION_SPEED_MAX 10.0f

#define MAX_CHAPPAL_TYPES 4

// TODO: add resource links
const static char *chappalSources[MAX_CHAPPAL_TYPES] = {
	// "resources/Square Buttons/Colored Square Buttons/Audio col_Square Button.png",
	// "resources/Square Buttons/Colored Square Buttons/Back col_Square Button.png",
	"resources/burger.png",
	"resources/chappal_1.png",
	"resources/chappal_2.png",
	"resources/chappal_1.png"};

typedef enum {
	KHANA = 0,
	DANDA,
	JUTA,
	CHAPPAL
} ChappalType;

typedef struct Chappal {
	ChappalType type;
	Texture2D texture;
	Vector2 position;
	Vector2 direction;
	float rotation;
	float rotationSpeed;
} Chappal;

Chappal *CreateChappal(Texture2D textures[], Vector2 target);
void UpdateChappal(Chappal *chappal);
void DrawChappal(Chappal *chappal);
void IncreaseSpeed();
void SetSpeed(float newSpeed);
void DestroyChappal(Chappal *chappal);

#endif