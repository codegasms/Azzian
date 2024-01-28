#ifndef SCREENS_H
#define SCREENS_H

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum GameScreen {
	TITLE = 0,
	GAMEPLAY
} GameScreen;

extern GameScreen currentScreen;

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

//----------------------------------------------------------------------------------
// Game Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);
int FinishGameScreen(void);

//----------------------------------------------------------------------------------
// Taunt Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTauntScreen(void);
void UpdateTauntScreen(void);
void DrawTauntScreen(void);
void UnloadTauntScreen(void);
int FinishTauntScreen(void);

bool GuiImageButtonEx(Rectangle bounds, const char *text, Texture2D texture, Rectangle texSource);
bool GuiImageButtonExTint(
	Rectangle bounds,
	const char *text,
	Texture2D texture,
	Rectangle texSource,
	Color tint);

/// Generate a random uint64_t based on the given seed using the WyHash algorithm.
uint64_t rng_u64(uint64_t seed);

/// Generate a random double in range [0, 1].
double rng_f64(uint64_t seed);
#endif