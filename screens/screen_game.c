#include "screens.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>

static Vector2 playerPosition = {0};
static Vector2 centerTile = {0, 0};
static Texture2D background = {0};
static Texture2D player = {0};
static Camera2D camera = {0};
Texture2D grassland = {0};

Rectangle frameRec = {0};
int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 0;

int playerSpriteWidth = 0;
int playerSpriteHeight = 0;

static int WIDTH;
static int HEIGHT;

static int finishScreen = 0;

int face = 0;

enum {
	FACE_IDLE,
	FACE_RIGHT,
	FACE_DOWN,
	FACE_LEFT,
	FACE_UP,
};

void InitGameScreen(void) {
	// Initialize the center tile location. This is used for mapping the 9
	// background tiles.
	centerTile.x = 0;
	centerTile.y = 0;

	// Loading Textures
	background = LoadTexture("resources/background.png");

	Image image = LoadImage("resources/char.png");
	ImageResizeNN(&image, image.width * 4, image.height * 4);
	player = LoadTextureFromImage(image);

	Image grasslandImage = LoadImage("resources/grassland.png");
	ImageResizeNN(&grasslandImage, grasslandImage.width * 4, grasslandImage.height * 4);
	grassland = LoadTextureFromImage(grasslandImage);

	playerSpriteWidth = player.width / 10;
	playerSpriteHeight = player.height / 20;
	assert(playerSpriteWidth == 16 * 4 && playerSpriteHeight == 16 * 4);

	// Initialize player position
	// playerPosition.x = -playerSpriteWidth / 2.0f;
	// playerPosition.y = -playerSpriteHeight / 2.0f;
	playerPosition.x = 0.0f;
	playerPosition.y = 0.0f;

	// Getting width and height
	WIDTH = GetScreenWidth();
	HEIGHT = GetScreenHeight();

	frameRec = (Rectangle){
		(float)player.width / 10,
		17.0 * (float)player.height / 20,
		(float)player.width / 10,
		(float)player.height / 20};

	currentFrame = 0;
	framesCounter = 0;
	framesSpeed = 8;

	// Initializing the camera
	camera.zoom = 1.0f;
};

Vector2 GetCenterTileLocation();

void UpdateGameScreen(void) {
	framesCounter++;

	if (framesCounter >= (60 / framesSpeed)) {
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 1)
			currentFrame = 0;

		if (face == FACE_LEFT || face == FACE_RIGHT) {
			frameRec.x =
				(float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 8;
		} else if (face == FACE_UP) {
			frameRec.x =
				(float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 6;
		} else if (face == FACE_DOWN) {
			frameRec.x =
				(float)currentFrame * (float)player.width / 10 + (float)player.width / 10 * 4;
		}
	}

	face = FACE_IDLE;

	int deltaX = 0, deltaY = 0;
	static const int moveSize = 10;

	if (IsKeyDown(KEY_LEFT)) {
		deltaX -= 1;
		face = FACE_LEFT;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		deltaX += 1;
		face = FACE_RIGHT;
	}
	if (IsKeyDown(KEY_UP)) {
		deltaY -= 1;
		face = FACE_UP;
	}
	if (IsKeyDown(KEY_DOWN)) {
		deltaY += 1;
		face = FACE_DOWN;
	}

	if (deltaX != 0 && deltaY != 0) {
		const int diagMoveSize = sqrt((moveSize * moveSize) / 2.0);
		playerPosition.x += deltaX * diagMoveSize;
		playerPosition.y += deltaY * diagMoveSize;
	} else {
		playerPosition.x += deltaX * moveSize;
		playerPosition.y += deltaY * moveSize;
	}

	// Update the center tile
	centerTile = GetCenterTileLocation();
	// Update the camera
	camera.offset = (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f};

	camera.target =
		(Vector2){// .x = playerPosition.x - (float)WIDTH / 2 + (float)player.width / 20 */ ,
	              // .y = playerPosition.y - (float)HEIGHT / 2 + (float)player.height / 40 */};
	              .x = playerPosition.x + playerSpriteWidth / 2.0f,
	              .y = playerPosition.y + playerSpriteHeight / 2.0f};
}

int CellIdx(int x, int size) {
	return (x - (x % size + size) % size) / size;
}

/// Generate a random uint64_t based on the given seed using the WyHash algorithm.
uint64_t rng_u64(uint64_t seed) {
	typedef unsigned __int128 u128;
	seed += (uint64_t)0x60bee2bee120fc15ULL;
	u128 tmp = (u128)seed * (u128)0xa3b195354a39b70dULL;
	uint64_t m1 = (uint64_t)(tmp >> 64 ^ tmp);
	tmp = (u128)m1 * (u128)0x1b03738712fad5c9ULL;
	uint64_t m2 = (uint64_t)(tmp >> 64 ^ tmp);
	return m2;
}

/// Generate a random double in range [0, 1].
double rng_f64(uint64_t seed) {
	static const double uint64_t_max = (double)0xffffffffffffffffULL;
	const uint64_t gen = rng_u64(seed);
	return (double)gen / uint64_t_max;
}

void SpawnObstacles(void) {
	int playerX = CellIdx(playerPosition.x, playerSpriteWidth);
	int playerY = CellIdx(playerPosition.y, playerSpriteHeight);

	int rows = 4 + HEIGHT / playerSpriteHeight;
	int cols = 4 + WIDTH / playerSpriteWidth;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			/*
			int x = playerPosition.x, y = playerPosition.y;

			x = x - (x % playerSpriteWidth)  + (j - cols / 2.0f) * playerSpriteWidth;
			y = y - (y % playerSpriteHeight) + (i - rows / 2.0f) * playerSpriteHeight;
			*/
			int x = (playerX + j - cols / 2);
			int y = (playerY + i - rows / 2);

			Rectangle grassRect =
				{.x = 16 * 4 * 0, .y = 16 * 4 * 0, .width = 16 * 4, .height = 16 * 4};
			DrawTextureRec(
				grassland,
				grassRect,
				(Vector2){x * playerSpriteWidth, y * playerSpriteHeight},
				WHITE);

			uint64_t seed = ((uint64_t)x << 31) * (x ^ ~y);
			if (rng_f64(seed) <= 0.02) {
				uint64_t seed = ((uint64_t)~x << 31) * (~x ^ ~y);
				int type = rng_u64(rng_u64(seed)) % 7;
				// Rectangle trunkRect = {.x = 16 * 4 * 11, .y = 16 * 4 * 12, .width = 16 * 4,
				// .height = 16 * 4};
				Rectangle trunkRect =
					{.x = 16 * 4 * (7 + type), .y = 16 * 4 * 12, .width = 16 * 4, .height = 16 * 4};
				DrawTextureRec(
					grassland,
					trunkRect,
					(Vector2){x * playerSpriteWidth, y * playerSpriteHeight},
					WHITE);
			}
		}
	}

	/*

	Image noiseImage = GenImagePerlinNoise(50, 50, 0, 0, 5.0f);
	Texture2D noiseTexture = LoadTextureFromImage(noiseImage);
	DrawTexture(noiseTexture, 0, 0, WHITE);
	*/
}

void DrawGameScreen(void) {
	BeginMode2D(camera);

	/*
	// Draw 9 background tiles from the center tile.
	for (int i = -1; i < 2; i++) {
	    for (int j = -1; j < 2; j++) {
	        DrawTexture(
	            background,
	            (centerTile.x * WIDTH - (WIDTH / 2.0f)) + (WIDTH * i),
	            (centerTile.y * HEIGHT - (HEIGHT / 2.0f)) + (HEIGHT * j),
	            WHITE);
	    }
	}
	*/

	SpawnObstacles();

	if (face == FACE_LEFT) {
		// frameRec.width = -frameRec.width;
		DrawTextureRec(
			player,
			(Rectangle){frameRec.x, frameRec.y, -frameRec.width, frameRec.height},
			playerPosition,
			WHITE);
	} else if (face != FACE_IDLE) {
		DrawTextureRec(player, frameRec, playerPosition, WHITE);
	} else {
		DrawTextureRec(
			player,
			(Rectangle){0.0f, frameRec.y, frameRec.width, frameRec.height},
			playerPosition,
			WHITE);
	}

	DrawFPS(playerPosition.x - WIDTH / 2.0f + 40, playerPosition.y - HEIGHT / 2.0f + 40);
	EndMode2D();
};

// Unloads the textures. I mean what else did you expect from the name?
void UnloadGameScreen(void) {
	UnloadTexture(background);
	UnloadTexture(player);
};

// This function returns whether the game should end or not. No logic
// implemented as of yet.
int FinishGameScreen(void) {
	return finishScreen;
};

// Returns relative tile location from the center of the screen.
// The center tile is 0,0 and the tile left of it is -1, 0 (Assuming that the
// background is the same size as the screen).
Vector2 GetCenterTileLocation() {
	float x = (playerPosition.x + WIDTH / 2.0f) / WIDTH;
	float y = (playerPosition.y + HEIGHT / 2.0f) / HEIGHT;
	return (Vector2){x < 0 ? (int)(x - 1) : (int)(x), y < 0 ? (int)(y - 1) : (int)(y)};
}