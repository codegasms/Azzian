#include "screens.h"
#include <raylib.h>
#include <raymath.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

GameScreen currentScreen = TITLE;

void UpdateDrawFrame(void);

static bool quitGame = false;

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void) {
#ifdef NDEBUG
	SetTraceLogLevel(LOG_NONE);
#endif

	InitWindow(screenWidth, screenHeight, "Azzian - DEBUG");
	InitAudioDevice();

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

	SetExitKey(KEY_NULL);

#if defined(PLATFORM_WEB)
	const int fps =
		60; // Looks like you are rendering without using requestAnimationFrame for the main loop.
	        // You should use 0 for the frame rate in emscripten_set_main_loop in order to use
	        // requestAnimationFrame, as that can greatly improve your frame rates!
	emscripten_set_main_loop(UpdateDrawFrame, fps, 1);
#else
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		UpdateDrawFrame();
		if (quitGame) {
			break;
		}
	}
#endif

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

	CloseAudioDevice();
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
	ClearBackground(RAYWHITE);

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
