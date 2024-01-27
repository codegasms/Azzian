#include "chappal.h"
#include "screens.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIVES 20

static Vector2 playerPosition = {0};
static Texture2D background = {0};
static Texture2D player = {0};
static Texture2D chappalTexture = {0};
static Texture2D heart = {0};
static Texture2D menuScreen = {0};
static Texture2D gamePaused = {0};
static Texture2D button1 = {0};
static Texture2D button2 = {0};
static Texture2D button3 = {0};
static Texture2D button4 = {0};
static Texture2D button5 = {0};
static Texture2D scoreBoard = {0};
static Texture2D button6 = {0};
static Texture2D button = {0};
static Camera2D camera = {0};
Texture2D grassland = {0};

Rectangle frameRec = {0};
Rectangle playerRec = {0};

Rectangle pauseBtn1Rec = {0};
Rectangle pauseBtn2Rec = {0};

int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 0;

int playerSpriteWidth = 0;
int playerSpriteHeight = 0;

static int WIDTH;
static int HEIGHT;

static int finishScreen = 0;
static int lives;

static int score;

static bool paused = false;
static bool pressed_1;
static bool pressed_2;
static int btnState_1;
static int btnState_2;

const bool debug = false;

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

// Function declarations
void UpdateTerrain(void);
void UpdateObstacles(void);
int CellIdx(int x, int size);
void SetCellsState(void);
int idx(int i, int j, int n);

void InitGameScreen(void) {
	finishScreen = 0;
	score = 0;
	pressed_1 = false;
	pressed_2 = false;
	btnState_1 = 0;
	btnState_1 = 0;
	lives = MAX_LIVES;

	// Initialize player position
	playerPosition.x = 0.0f;
	playerPosition.y = 0.0f;

	playerRec = (Rectangle){
		playerPosition.x,
		playerPosition.y,
		(float)player.width / 10,
		(float)player.height / 20};

	// Testing
	chappalTexture = LoadTexture("resources/book.png");
	chappalList = (ChappalList*)malloc(sizeof(ChappalList));
	chappalList->head = NULL;
	// chappal = CreateChappal(chappalTexture, playerPosition);
	// End Testing

	// Loading Textures
	background = LoadTexture("resources/background.png");

	Image menuImage = LoadImage("resources/Sprites/UI_Flat_Frame_01_Standard.png");
	ImageResizeNN(&menuImage, menuImage.width * 8, menuImage.height * 6);
	menuScreen = LoadTextureFromImage(menuImage);
	UnloadImage(menuImage);

	gamePaused = LoadTexture("resources/game_paused.png");

	Image buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a1.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	button = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a1.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Resume", 55, 15, 20, BLACK);
	button1 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a2.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Resume", 55, 20, 20, BLACK);
	button2 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a3.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Resume", 55, 25, 20, BLACK);
	button3 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a1.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Title", 70, 15, 20, BLACK);
	button4 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a2.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Title", 70, 20, 20, BLACK);
	button5 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	buttonImage = LoadImage("resources/Sprites/UI_Flat_Button_Large_Lock_01a3.png");
	ImageResizeNN(&buttonImage, buttonImage.width * 2, buttonImage.height * 2);
	ImageDrawText(&buttonImage, "Title", 70, 25, 20, BLACK);
	button6 = LoadTextureFromImage(buttonImage);
	UnloadImage(buttonImage);

	Image scoreImage = LoadImage("resources/Sprites/UI_Flat_Banner_02_Downward.png");
	ImageResizeNN(&scoreImage, scoreImage.width * 2.5, scoreImage.height * 2.5);
	scoreBoard = LoadTextureFromImage(scoreImage);
	UnloadImage(scoreImage);

	Image heart_image = LoadImage("resources/life.png");
	ImageResizeNN(&heart_image, heart_image.width * 2, heart_image.height * 2);
	heart = LoadTextureFromImage(heart_image);
	UnloadImage(heart_image);

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

	// Dummy code
	pauseBtn1Rec = (Rectangle){playerPosition.x, playerPosition.y, button.width, button.height};
	pauseBtn2Rec =
		(Rectangle){playerPosition.x, playerPosition.y + 50, button.width, button.height};

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
	Chappal* chappal = CreateChappal(
		chappalTexture,
		(Vector2){
			playerPosition.x + playerSpriteWidth / 2.0f,
			playerPosition.y + playerSpriteHeight / 2.0f});
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

void DeleteChappalNode(Node* node) {
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

void SimulateUpdate() {}

int gStartX = 0, gStartY = 0;
int gRows = 0, gCols = 0;
int gTerrain[100 * 100];
int gObstacles[100 * 100];

void UpdateGameScreen(void) {
	if (IsKeyPressed(KEY_SPACE)) {
		paused = !paused;
		pauseBtn1Rec = (Rectangle){
			playerPosition.x + (playerSpriteWidth / 2.0f) - 3 * button.width / 2,
			playerPosition.y + (playerSpriteHeight / 2.0f) - (button.height / 2.0f) + 150,
			button.width,
			button.height};
		pauseBtn2Rec = (Rectangle){
			playerPosition.x + (playerSpriteWidth / 2.0f) + button.width / 2,
			playerPosition.y + (playerSpriteHeight / 2.0f) - (button.height / 2.0f) + 150,
			button.width,
			button.height};
	}

	if (paused) {
		Vector2 mousePoint = GetMousePosition();

		if (debug) {
			printf("x: %f; y:%f\n", mousePoint.x, mousePoint.y);
		}

		if (mousePoint.x >= 355 && mousePoint.x <= 540 && mousePoint.y >= 480 &&
		    mousePoint.y <= 540) {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				btnState_1 = 2;
			} else {
				btnState_1 = 1;
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				pressed_1 = true;
			}
		} else {
			btnState_1 = 0;
		}

		if (mousePoint.x >= 740 && mousePoint.x <= 925 && mousePoint.y >= 480 &&
		    mousePoint.y <= 540) {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				btnState_2 = 2;
			} else {
				btnState_2 = 1;
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				pressed_2 = true;
			}
		} else {
			btnState_2 = 0;
		}

		if (pressed_1) {
			paused = false;
			pressed_1 = false;
		} else if (pressed_2) {
			finishScreen = 1;
			paused = false;
			pressed_2 = false;
		}
	} else {
		framesCounter++;

		if (framesCounter >= (60 / framesSpeed)) {
			SpawnChappal();
			framesCounter = 0;
			score++;
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

		int moveX = 0, moveY = 0;

		if (deltaX != 0 && deltaY != 0) {
			const int diagMoveSize = sqrt((moveSize * moveSize) / 2.0);
			moveX = deltaX * diagMoveSize;
			moveY = deltaY * diagMoveSize;
		} else {
			moveX = deltaX * moveSize;
			moveY = deltaY * moveSize;
		}

		SetCellsState();
		UpdateTerrain();
		UpdateObstacles();

		{
			int cx = playerPosition.x + playerSpriteWidth / 2.0f;
			int cy = playerPosition.y + playerSpriteHeight / 2.0f;

			bool collision = false;
			for (int i = 4; i >= 1; --i) {
				int nx = CellIdx(cx + (float)moveX / i, playerSpriteWidth);
				int ny = CellIdx(cy + (float)moveY / i, playerSpriteHeight);

				if (gObstacles[idx(ny - gStartY, nx - gStartX, gCols)] != -1) {
					collision = true;
					break;
				}
			}

			if (!collision) {
				playerPosition.x += moveX;
				playerPosition.y += moveY;
			}
		}

		// Update the camera
		camera.offset = (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f};
		camera.target = (Vector2){
			.x = playerPosition.x + playerSpriteWidth / 2.0f,
			.y = playerPosition.y + playerSpriteHeight / 2.0f};

		playerRec = (Rectangle){
			playerPosition.x,
			playerPosition.y,
			(float)player.width / 10,
			(float)player.height / 20};

		// Draw chappals
		Node* node = chappalList->head;
		while (node != NULL) {
			UpdateChappal(node->chappal);
			Rectangle chappalRec =
				(Rectangle){node->chappal->position.x - 10, node->chappal->position.y - 10, 20, 20};
			if (CheckCollisionRecs(playerRec, chappalRec)) {
				lives--;
				Node* temp = node;
				node = node->next;
				DeleteChappalNode(temp);
				if (lives == 0) {
					finishScreen = 1;
				}
			}
			if (node->chappal->position.x < playerPosition.x - (WIDTH / 2) - (SPAWN_OFFSET + 100) ||
			    node->chappal->position.x > playerPosition.x + (WIDTH / 2) + (SPAWN_OFFSET + 100) ||
			    node->chappal->position.y <
			        playerPosition.y - (HEIGHT / 2) - (SPAWN_OFFSET + 100) ||
			    node->chappal->position.y >
			        playerPosition.y + (HEIGHT / 2) + (SPAWN_OFFSET + 100)) {
				Node* temp = node;
				node = node->next;
				DeleteChappalNode(temp);
			} else {
				node = node->next;
			}
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

int idx(int i, int j, int n) {
	return i * n + j;
}

void SetCellsState(void) {
	int playerX = CellIdx(playerPosition.x, playerSpriteWidth);
	int playerY = CellIdx(playerPosition.y, playerSpriteHeight);

	int rows = 10 + HEIGHT / playerSpriteHeight;
	int cols = 10 + WIDTH / playerSpriteWidth;

	gStartX = playerX - cols / 2;
	gStartY = playerY - rows / 2;
	gRows = rows;
	gCols = cols;
}

void UpdateTerrain(void) {
	int rows = gRows, cols = gCols;
	int x1 = gStartX, y1 = gStartY;

	Image noiseImage = GenImagePerlinNoise(cols, rows, x1, y1, 20.0f);
	Color* colors = LoadImageColors(noiseImage);
	UnloadImage(noiseImage);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			Color color = colors[i * cols + j];
			assert(color.r == color.g && color.r == color.b && color.a == 255);
			int intensity = color.r;

			if (intensity < 50) {
				gTerrain[idx(i, j, cols)] = 0;
			} else if (intensity < 150) {
				gTerrain[idx(i, j, cols)] = 1;
			} else if (intensity < 200) {
				gTerrain[idx(i, j, cols)] = 2;
			} else {
				gTerrain[idx(i, j, cols)] = 3;
			}
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

void UpdateObstacles(void) {
	int rows = gRows, cols = gCols;
	int x1 = gStartX, y1 = gStartY;

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

			assert(terrainType >= 0 && terrainType < 4);
			gObstacles[idx(i, j, cols)] = obstacleType;
		}
	}
}

void DrawTerrain(void) {
	int rows = gRows, cols = gCols;
	int x1 = gStartX, y1 = gStartY;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int y = y1 + i;
			int x = x1 + j;
			int si = 0, sj = 0;

			// clang-format off
			switch(gTerrain[idx(i, j, cols)]) {
				case 0: si = 10; sj =  5; break;
				case 1: si =  6; sj =  2; break;
				case 2: si =  7; sj =  3; break;
				case 3: si =  6; sj =  3; break;
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
}

void DrawObstacles(void) {
	int rows = gRows, cols = gCols;
	int x1 = gStartX, y1 = gStartY;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int x = x1 + j;
			int y = y1 + i;

			int obstacleType = gObstacles[idx(i, j, cols)];
			if (obstacleType < 0) {
				continue;
			}

			int terrainType = gTerrain[idx(i, j, cols)];
			int oi = 0, oj = 0;

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

	// _Static_assert(MAX_LIVES % 4 == 0, "MAX_LIVES must be a multiple of 4");
	const int HEARTS = (MAX_LIVES + 3) / 4;
	for (int i = 0; i < HEARTS; ++i) {
		int rem = lives - i * 4;
		if (rem < 0) {
			rem = 0;
		}

		if (rem > 4)
			rem = 4;
		DrawTextureRec(
			heart,
			(Rectangle){17 * 2 * (4 - rem), 0, 17 * 2, 17 * 2},
			(Vector2){playerPosition.x - 600 + (17 * 2 * i), playerPosition.y - 300},
			WHITE);
	}
	DrawTexture(scoreBoard, playerPosition.x - 625, playerPosition.y - 255, WHITE);
	DrawText(
		TextFormat("Score: %d", score),
		playerPosition.x - 550,
		playerPosition.y - 225,
		20,
		BLACK);
	DrawFPS(playerPosition.x - WIDTH / 2.0f + 40, playerPosition.y - HEIGHT / 2.0f + 40);

	if (paused) {
		// Draw fade background.
		DrawRectangle(
			playerPosition.x - (WIDTH / 2.0f) + (playerSpriteWidth / 2.0f),
			playerPosition.y - (HEIGHT / 2.0f) + (playerSpriteHeight / 2.0f),
			WIDTH,
			HEIGHT,
			ColorAlpha(BLACK, 0.3));
		// Draw blue board
		DrawTexture(
			menuScreen,
			playerPosition.x + (playerSpriteWidth / 2.0f) - (menuScreen.width / 2),
			playerPosition.y + (playerSpriteHeight / 2.0f) - (menuScreen.height / 2),
			WHITE);
		// Draw game paused text
		DrawTexture(
			gamePaused,
			playerPosition.x + (playerSpriteWidth / 2.0f) - (gamePaused.width / 2),
			playerPosition.y + (playerSpriteHeight / 2.0f) - (gamePaused.height / 2) - 200,
			WHITE);

		if (btnState_1 == 0) {
			DrawTexture(button1, pauseBtn1Rec.x, pauseBtn1Rec.y, WHITE);
		} else if (btnState_1 == 1) {
			DrawTexture(button2, pauseBtn1Rec.x, pauseBtn1Rec.y, WHITE);
		} else if (btnState_1 == 2) {
			DrawTexture(button3, pauseBtn1Rec.x, pauseBtn1Rec.y, WHITE);
		}
		// DrawRectangleRec(pauseBtn1Rec, RED);
		if (btnState_2 == 0) {
			DrawTexture(button4, pauseBtn2Rec.x, pauseBtn2Rec.y, WHITE);
		} else if (btnState_2 == 1) {
			DrawTexture(button5, pauseBtn2Rec.x, pauseBtn2Rec.y, WHITE);
		} else if (btnState_2 == 2) {
			DrawTexture(button6, pauseBtn2Rec.x, pauseBtn2Rec.y, WHITE);
		}
	}

	// Testing
	if (debug) {
		DrawRectangleRec(playerRec, RED);
		DrawText(
			TextFormat("Lives: %d", lives),
			playerPosition.x - 600,
			playerPosition.y,
			20,
			BLACK);
		DrawText(
			TextFormat("Chappals: %d", counter),
			playerPosition.x - 600,
			playerPosition.y + 30,
			20,
			BLACK);
		DrawText(
			TextFormat("Score: %d", score),
			playerPosition.x - 600,
			playerPosition.y + 60,
			20,
			BLACK);
	}
	// End Testing

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
		DeleteChappalNode(temp);
	}
	UnloadTexture(heart);
	UnloadTexture(menuScreen);
	UnloadTexture(gamePaused);
	UnloadTexture(background);
	UnloadTexture(button1);
	UnloadTexture(button2);
	UnloadTexture(button3);
	UnloadTexture(button4);
	UnloadTexture(button5);
	UnloadTexture(button6);
	UnloadTexture(button);
	UnloadTexture(player);
};

// This function returns whether the game should end or not.
// No logic implemented as of yet.
int FinishGameScreen(void) {
	return finishScreen;
};
