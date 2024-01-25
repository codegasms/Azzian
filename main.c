#include "screens.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

GameScreen currentScreen = GAMEPLAY;

void UpdateDrawFrame(void);
Vector2 GetCenterTileLocation();

int main() {
  InitWindow(1280, 720, "Test Game");

  InitGameScreen();

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }

  switch (currentScreen) {
  case GAMEPLAY:
    UnloadGameScreen();
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
    break;
  default:
    break;
  }

  BeginDrawing();

  switch (currentScreen) {
  case GAMEPLAY:
    DrawGameScreen();
    break;
  default:
    break;
  }

  EndDrawing();
}
