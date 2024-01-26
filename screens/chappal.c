#include "chappal.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

// Creates a new chappal at a random location with a random rotation speed.
// Speed will increase with time.
Chappal* createChappal() {
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
    chappal->rotation = 0.0f;
    chappal->rotationSpeed = (float)GetRandomValue(-10, 10) / 10.0f;
    return chappal;
}

void updateChappal(Chappal* chappal, Vector2 target) {
    Vector2 direction = Vector2Subtract(target, chappal->position);
    direction = Vector2Normalize(direction);
    Vector2 velocity = Vector2Scale(direction, speed);
    chappal->position = Vector2Add(chappal->position, velocity);
};

void drawChappal(Chappal* chappal);
void destroyChappal(Chappal* chappal);