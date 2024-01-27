#include "chappal.h"
#include "screens.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <raymath.h>
#include <stdlib.h>

#define SPAWN_DELAY 0.75f

static Vector2 playerPosition = {0};
static Vector2 centerTile = {0, 0};
static Texture2D background = {0};
static Texture2D player = {0};
Texture2D chappalTexture = {0};
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
const bool debug = true;

int face = 0;

enum {
	FACE_IDLE,
	FACE_RIGHT,
	FACE_DOWN,
	FACE_LEFT,
	FACE_UP,
};

typedef struct Node {
	Chappal* chappal;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct ChappalList {
	Node* head;
} ChappalList;

static ChappalList* chappalList;

void InitGameScreen(void) {
	// Initialize player position
	playerPosition.x = 0.0f;
	playerPosition.y = 0.0f;

	// Testing
	chappalTexture = LoadTexture("resources/book.png");
	chappalList = (ChappalList*)malloc(sizeof(ChappalList));
	chappalList->head = NULL;
	// chappal = CreateChappal(chappalTexture, playerPosition);
	// End Testing

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

Node* createNode(Chappal* chappal) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->chappal = chappal;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void SpawnChappal() {
	Chappal* chappal = CreateChappal(chappalTexture, playerPosition);
	Node* node = createNode(chappal);
	if (chappalList->head == NULL) {
		chappalList->head = node;
	} else {
		Node* temp = chappalList->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
		node->prev = temp;
	}
}

void DeleteChappal(Node* node) {
	if (node->prev == NULL) {
		chappalList->head = node->next;
	} else {
		node->prev->next = node->next;
	}
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	DestroyChappal(node->chappal);
	free(node);
}

Vector2 GetCenterTileLocation();

void UpdateGameScreen(void) {

	framesCounter++;

	if (framesCounter >= (60 / framesSpeed)) {
		SpawnChappal();
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 1)
			currentFrame = 0;

		if (face == FACE_LEFT || face == FACE_RIGHT) {
			frameRec.x = currentFrame * player.width / 10.0f + player.width / 10.0f * 8;
		} else if (face == FACE_UP) {
			frameRec.x = currentFrame * player.width / 10.0f + player.width / 10.0f * 6;
		} else if (face == FACE_DOWN) {
			frameRec.x = currentFrame * player.width / 10.0f + player.width / 10.0f * 4;
		}
	}

	face = FACE_IDLE;

	int deltaX = 0, deltaY = 0;
	static const int moveSize = 10;

	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
		deltaX -= 1;
		face = FACE_LEFT;
	}
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
		deltaX += 1;
		face = FACE_RIGHT;
	}
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
		deltaY -= 1;
		face = FACE_UP;
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
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

	camera.target = (Vector2){
		.x = playerPosition.x + playerSpriteWidth / 2.0f,
		.y = playerPosition.y + playerSpriteHeight / 2.0f};

	// Draw chappals
	Node* node = chappalList->head;
	while (node != NULL) {
		UpdateChappal(node->chappal);
		if (node->chappal->position.x < playerPosition.x - (WIDTH / 2) - SPAWN_OFFSET ||
		    node->chappal->position.x > playerPosition.x + (WIDTH / 2) + SPAWN_OFFSET ||
		    node->chappal->position.y < playerPosition.y - (HEIGHT / 2) - SPAWN_OFFSET ||
		    node->chappal->position.y > playerPosition.y + (HEIGHT / 2) + SPAWN_OFFSET) {
			Node* temp = node;
			node = node->next;
			DeleteChappal(temp);
		} else {
			node = node->next;
		}
	}
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

int gTerrain[100 * 100];
int gObstacles[100 * 100];

int idx(int i, int j, int n) {
	return i * n + j;
}

void DrawTerrain(void) {
	int playerX = CellIdx(playerPosition.x, playerSpriteWidth);
	int playerY = CellIdx(playerPosition.y, playerSpriteHeight);

	int rows = 4 + HEIGHT / playerSpriteHeight;
	int cols = 4 + WIDTH / playerSpriteWidth;

	int x1 = playerX - cols / 2;
	int y1 = playerY - rows / 2;

	Image noiseImage = GenImagePerlinNoise(cols, rows, x1, y1, 20.0f);
	Color* colors = LoadImageColors(noiseImage);
	UnloadImage(noiseImage);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			Color color = colors[i * cols + j];
			assert(color.r == color.g && color.r == color.b && color.a == 255);
			int intensity = color.r;

			int y = y1 + i;
			int x = x1 + j;
			int si = 0, sj = 0;

			// clang-format off
			if (intensity < 50) {
				si = 10;
				sj = 5;
				gTerrain[idx(i, j, cols)] = 0;
			} else if (intensity < 150) {
				si = 6;
				sj = 2;
				gTerrain[idx(i, j, cols)] = 1;
			} else if (intensity < 200) {
				si = 7;
				sj = 3;
				gTerrain[idx(i, j, cols)] = 2;
			} else {
				si = 6;
				sj = 3;
				gTerrain[idx(i, j, cols)] = 3;
			}
			// clang-format on

			Rectangle terrainRect =
				{.x = 16 * 4 * sj, .y = 16 * 4 * si, .width = 16 * 4, .height = 16 * 4};
			DrawTextureRec(
				grassland,
				terrainRect,
				(Vector2){x * playerSpriteWidth, y * playerSpriteHeight},
				WHITE);
		}
	}

	UnloadImageColors(colors);
}

/// Returns a non-negative int on obstacle, and -1 for no obstacle.
int ObstacleAt(int x, int y) {
	static const double OBSTACLE_PROBABILITY = 0.02;
	uint64_t seed = ((uint64_t)x << 31) * (x ^ ~y);

	if (rng_f64(seed) >= OBSTACLE_PROBABILITY) {
		return -1;
	}

	seed = ((uint64_t)~x << 31) * (~x ^ ~y);
	int obstacleType = rng_u64(seed) % 4;
	return obstacleType;
}

void DrawObstacles(void) {
	int playerX = CellIdx(playerPosition.x, playerSpriteWidth);
	int playerY = CellIdx(playerPosition.y, playerSpriteHeight);

	int rows = 4 + HEIGHT / playerSpriteHeight;
	int cols = 4 + WIDTH / playerSpriteWidth;

	int x1 = playerX - cols / 2;
	int y1 = playerY - rows / 2;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int x = x1 + j;
			int y = y1 + i;

			int terrainType = gTerrain[idx(i, j, cols)];
			int obstacleType = ObstacleAt(x, y);

			if (terrainType == 0 || obstacleType < 0) {
				gObstacles[idx(i, j, cols)] = -1;
				continue;
			}

			int oi = 0, oj = 0;
			assert(terrainType >= 0 && terrainType < 4);

			gObstacles[idx(i, j, cols)] = terrainType * 4 + obstacleType;

			// clang-format off
			switch (terrainType) {
				default:
				case 1: {
					switch (obstacleType) {
						default:
						case 0: oi = 12; oj =  6; break;
						case 1: oi = 12; oj = 15; break;
						case 2: oi = 11; oj = 12; break;
						case 3: oi = 11; oj = 13; break;
					}
					break;
				}
				case 2:
					switch (obstacleType) {
						default:
						case 0: oi = 12; oj = 10; break;
						case 1: oi = 12; oj = 11; break;
						case 2: oi = 12; oj = 12; break;
						case 3: oi = 13; oj = 24; break;
					}
					break;
				case 3: {
					switch (obstacleType) {
						default:
						case 0: oi = 13; oj = 2; break;
						case 1: oi = 13; oj = 3; break;
						case 2: oi = 13; oj = 5; break;
						case 3: oi = 13; oj = 6; break;
					}
					break;
				}
			}
			// clang-format on

			Rectangle obstacleRect =
				{.x = 16 * 4 * oj, .y = 16 * 4 * oi, .width = 16 * 4, .height = 16 * 4};
			DrawTextureRec(
				grassland,
				obstacleRect,
				(Vector2){x * playerSpriteWidth, y * playerSpriteHeight},
				WHITE);
		}
	}
}

void DrawGameScreen(void) {
	BeginMode2D(camera);

	DrawTerrain();
	DrawObstacles();

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
	// Draw chappals
	Node* node = chappalList->head;
	int counter = 0;
	while (node != NULL) {
		DrawChappal(node->chappal);
		node = node->next;
		counter++;
	}
	// Testing
	if (debug) {
		DrawText(
			TextFormat("Chappals: %d", counter),
			playerPosition.x - 600,
			playerPosition.y - 300,
			20,
			BLACK);
	}
	// End Testing

	DrawFPS(playerPosition.x - WIDTH / 2.0f + 40, playerPosition.y - HEIGHT / 2.0f + 40);
	EndMode2D();
};

// Unloads the textures. I mean what else did you expect from the name?
void UnloadGameScreen(void) {
	// Delete chappals
	UnloadTexture(chappalTexture);
	Node* node = chappalList->head;
	while (node != NULL) {
		Node* temp = node;
		node = node->next;
		DeleteChappal(temp);
	}
	UnloadTexture(background);
	UnloadTexture(player);
};

// This function returns whether the game should end or not.
// No logic implemented as of yet.
int FinishGameScreen(void) {
	return finishScreen;
};

// Returns relative tile location from the center of the screen.
// The center tile is 0,0 and the tile left of it is -1, 0
// (Assuming that the background is the same size as the screen).
Vector2 GetCenterTileLocation() {
	float x = (playerPosition.x + WIDTH / 2.0f) / WIDTH;
	float y = (playerPosition.y + HEIGHT / 2.0f) / HEIGHT;
	return (Vector2){x < 0 ? (int)(x - 1) : (int)(x), y < 0 ? (int)(y - 1) : (int)(y)};
}