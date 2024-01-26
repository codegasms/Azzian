#ifndef CHAPPAL_H
#define CHAPPAL_H

#include <raylib.h>

#define SPAWN_OFFSET 100

static float speed = 1.0f;

typedef struct Chappal {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
} Chappal;

Chappal* createChappal();
void updateChappal(Chappal* chappal, Vector2 target);
void drawChappal(Chappal* chappal);
void destroyChappal(Chappal* chappal);

#endif