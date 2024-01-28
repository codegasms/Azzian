#include "screens.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

GameScreen currentScreen = TITLE;

void UpdateDrawFrame(void);

static bool quitGame = false;

int main() {
	InitWindow(1280, 720, "Test Game");

	// Change it later to Title screen. Player should not go directly to the game screen.
	switch (currentScreen) {
	case GAMEPLAY:
		InitGameScreen();
		InitTauntScreen();
		break;
	case TITLE:
		InitTitleScreen();
		break;
	default:
		break;
	}

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		ClearBackground(RAYWHITE);
		UpdateDrawFrame();
		if (quitGame) {
			break;
		}
	}

	switch (currentScreen) {
	case GAMEPLAY:
		UnloadGameScreen();
		UnloadTauntScreen();
		break;
	case TITLE:
		UnloadTitleScreen();
		break;
	default:
		break;
	}

	CloseWindow();
	return 0;
}

void UpdateDrawFrame(void) {
	switch (currentScreen) {
	case GAMEPLAY:
		UpdateGameScreen();
		if (FinishGameScreen() == 1) {
			currentScreen = TITLE;
			UnloadGameScreen();
			UnloadTauntScreen();
			InitTitleScreen();
		}
		break;
	case TITLE:
		UpdateTitleScreen();
		if (FinishTitleScreen() == 1) {
			currentScreen = GAMEPLAY;
			UnloadTitleScreen();
			InitGameScreen();
			InitTauntScreen();
		} else if (FinishTitleScreen() == 2) {
			quitGame = true;
		}
		break;
	default:
		break;
	}

	BeginDrawing();

	switch (currentScreen) {
	case GAMEPLAY:
		DrawGameScreen();
		break;
	case TITLE:
		DrawTitleScreen();
		break;
	default:
		break;
	}

	EndDrawing();
}
