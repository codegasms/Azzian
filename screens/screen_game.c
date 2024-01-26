#include "screens.h"
#include <raylib.h>

static Vector2 playerPosition = {0};
static Vector2 centerTile = {0, 0};
static Texture2D background = {0};
static Texture2D player = {0};
static Camera2D camera = {0};

Rectangle frameRec = {0};
int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 0;

static int width;
static int height;

static int finishScreen = 0;

bool face_right = false;
bool face_left = false;
bool face_top = false;
bool face_bot = false;

void InitGameScreen(void)
{
  // Initialize player position
  playerPosition.x = 0.0f;
  playerPosition.y = 0.0f;

  // Initialize the center tile location. This is used for mapping the 9
  // background tiles.
  centerTile.x = 0;
  centerTile.y = 0;

  // Loading Textures
  background = LoadTexture("resources/background.png");

  Image image = LoadImage("resources/char.png");
  ImageResizeNN(&image, image.width * 4, image.height * 4);
  player = LoadTextureFromImage(image);

  // Getting width and height
  width = GetScreenWidth();
  height = GetScreenHeight();

  frameRec = (Rectangle){(float)player.width / 10, 17.0 * (float)player.height / 20, (float)player.width / 10, (float)player.height / 20};

  currentFrame = 0;
  framesCounter = 0;
  framesSpeed = 8;

  // Initializing the camera
  camera.offset = (Vector2){0, 0};
  camera.target = (Vector2){.x = playerPosition.x - width / 2 + player.width / 20,
                            .y = playerPosition.y - GetScreenHeight() / 2 + player.height / 40};
  camera.rotation = 0;
  camera.zoom = 1.0f;
};

Vector2 GetCenterTileLocation();

void UpdateGameScreen(void)
{
  framesCounter++;

  if (framesCounter >= (60 / framesSpeed))
  {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > 1)
      currentFrame = 0;

    if (face_left == true || face_right == true)
      frameRec.x = (float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 8;
    if (face_top == true)
      frameRec.x = (float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 6;
    if (face_bot == true)
      frameRec.x = (float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 4;
  }

  if (IsKeyDown(KEY_UP))
  {
    playerPosition.y -= 10;
    face_top = true;
    face_bot = false;
    face_right = false;
    face_left = false;
  }
  else if (IsKeyDown(KEY_DOWN))
  {
    playerPosition.y += 10;
    face_bot = true;
    face_top = false;
    face_right = false;
    face_left = false;
  }
  else if (IsKeyDown(KEY_RIGHT))
  {
    playerPosition.x += 10;
    face_right = true;
    face_left = false;
    face_top = false;
    face_bot = false;
  }
  else if (IsKeyDown(KEY_LEFT))
  {
    playerPosition.x -= 10;
    face_left = true;
    face_right = false;
    face_top = false;
    face_bot = false;
  }

  // Update the center tile
  centerTile = GetCenterTileLocation();
  // Update the camera
  camera.target = (Vector2){.x = playerPosition.x - width / 2 + player.width / 20,
                            .y = playerPosition.y - height / 2 + player.height / 40};
};

void DrawGameScreen(void)
{
  BeginMode2D(camera);
  // Draw 9 background tiles from the center tile.
  for (int i = -1; i < 2; i++)
  {
    for (int j = -1; j < 2; j++)
    {
      DrawTexture(background,
                  (centerTile.x * width - (width / 2)) + (width * i),
                  (centerTile.y * height - (height / 2)) + (height * j), WHITE);
    }
  }

  if (face_left)
  {
    // frameRec.width = -frameRec.width;
    DrawTextureRec(player, (Rectangle){frameRec.x, frameRec.y, -frameRec.width, frameRec.height}, playerPosition, WHITE); // Draw part of the texture
  }
  else if (face_top || face_bot || face_right)
  {
    DrawTextureRec(player, frameRec, playerPosition, WHITE); // Draw part of the texture
  }
  else
  {
    DrawTextureRec(player, (Rectangle){0.0f, frameRec.y, frameRec.width, frameRec.height}, playerPosition, WHITE); // Draw part of the texture
  }

  EndMode2D();
};

// Unloads the textures. I mean what else did you expect from the name?
void UnloadGameScreen(void)
{
  UnloadTexture(background);
  UnloadTexture(player);
};

// This function returns whether the game should end or not. No logic
// implemented as of yet.
int FinishGameScreen(void) { return finishScreen; };

// Returns relative tile location from the center of the screen.
// The center tile is 0,0 and the tile left of it is -1, 0 (Assuming that the
// background is the same size as the screen).
Vector2 GetCenterTileLocation()
{
  float x = (playerPosition.x + width / 2) / width;
  float y = (playerPosition.y + height / 2) / height;
  return (Vector2){x < 0 ? (int)(x - 1) : (int)(x),
                   y < 0 ? (int)(y - 1) : (int)(y)};
}