#include "screens.h"
#include <raylib.h>

static Vector2 playerPosition = {0};
static Vector2 centerTile = {0, 0};
static Texture2D background = {0};
static Texture2D player = {0};
static Camera2D camera = {0};

static int width;
static int height;

static int finishScreen = 0;

void InitGameScreen(void) {
  // Initialize player position
  playerPosition.x = 0.0f;
  playerPosition.y = 0.0f;
  // Initialize the center tile location. This is used for mapping the 9
  // background tiles.
  centerTile.x = 0;
  centerTile.y = 0;
  // Loading Textures
  background = LoadTexture("resources/background.png");
  player = LoadTexture("resources/book.png");
  // Getting width and height
  width = GetScreenWidth();
  height = GetScreenHeight();
  // Initializing the camera
  camera.offset = (Vector2){0, 0};
  camera.target = (Vector2){.x = playerPosition.x - width / 2,
                            .y = playerPosition.y - GetScreenHeight() / 2};
  camera.rotation = 0;
  camera.zoom = 1.0f;
};

Vector2 GetCenterTileLocation();

void UpdateGameScreen(void) {
  // Player movement
  if (IsKeyDown(KEY_UP)) {
    playerPosition.y -= 10;
  }
  if (IsKeyDown(KEY_DOWN)) {
    playerPosition.y += 10;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    playerPosition.x += 10;
  }
  if (IsKeyDown(KEY_LEFT)) {
    playerPosition.x -= 10;
  }

  // Update the center tile
  centerTile = GetCenterTileLocation();
  // Update the camera
  camera.target = (Vector2){.x = playerPosition.x - width / 2,
                            .y = playerPosition.y - height / 2};
};

void DrawGameScreen(void) {
  BeginMode2D(camera);
  // Draw 9 background tiles from the center tile.
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      DrawTexture(background,
                  (centerTile.x * width - (width / 2)) + (width * i),
                  (centerTile.y * height - (height / 2)) + (height * j), WHITE);
    }
  }
  DrawTextureEx(player, playerPosition, 0, 1, WHITE); // Draw the player
  ClearBackground(RAYWHITE);
  EndMode2D();
};

// Unloads the textures. I mean what else did you expect from the name?
void UnloadGameScreen(void) {
  UnloadTexture(background);
  UnloadTexture(player);
};

// This function returns whether the game should end or not. No logic
// implemented as of yet.
int FinishGameScreen(void) { return finishScreen; };

// Returns relative tile location from the center of the screen.
// The center tile is 0,0 and the tile left of it is -1, 0 (Assuming that the
// background is the same size as the screen).
Vector2 GetCenterTileLocation() {
  float x = (playerPosition.x + width / 2) / width;
  float y = (playerPosition.y + height / 2) / height;
  return (Vector2){x < 0 ? (int)(x - 1) : (int)(x),
                   y < 0 ? (int)(y - 1) : (int)(y)};
}