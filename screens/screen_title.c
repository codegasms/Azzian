#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include "screens.h"
#include <raylib.h>

extern GameScreen currentScreen;

static bool
GuiImageButtonEx(Rectangle bounds, const char *text, Texture2D texture, Rectangle texSource);

static Texture2D gameName = {0};
static Texture2D bigButton = {0};
static Texture2D bigButtonPressed = {0};
static Texture2D smallButton = {0};
static Texture2D smallButtonPressed = {0};

static int menuButtonState = 0;

static int finishScreen = 0;

void InitTitleScreen(void) {
	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);

	Image game = LoadImage("resources/azzian.png");
	ImageResizeNN(&game, game.width * 1.2, game.height * 1.2);
	gameName = LoadTextureFromImage(game);

	Image big = LoadImage("resources/Sprites/UI_Flat_Button_Medium_Press_02a1.png");
	ImageResizeNN(&big, big.width * 3, big.height * 3);
	bigButton = LoadTextureFromImage(big);
	Image big2 = LoadImage("resources/Sprites/UI_Flat_Button_Medium_Press_02a2.png");
	ImageResizeNN(&big2, big2.width * 3, big2.height * 3);
	bigButtonPressed = LoadTextureFromImage(big2);

	Image small = LoadImage("resources/Sprites/UI_Flat_Button_Small_Lock_02a1.png");
	ImageResizeNN(&small, small.width * 3, small.height * 3);
	smallButton = LoadTextureFromImage(small);
	Image small2 = LoadImage("resources/Sprites/UI_Flat_Button_Small_Lock_02a2.png");
	ImageResizeNN(&small2, small2.width * 3, small2.height * 3);
	smallButtonPressed = LoadTextureFromImage(small2);
}

void UpdateTitleScreen(void){

};

void DrawTitleScreen(void) {
	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	int cellWidth = screenWidth / 2;
	int cellHeight = screenHeight / 6;
	int padding = cellHeight / 4;

	DrawTexture(gameName, cellWidth - gameName.width / 2, padding, WHITE);

	GuiSetIconScale(4);

	Rectangle boundBox = {cellWidth / 2, cellHeight * 2, cellWidth, cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 1");
	if (GuiImageButtonEx(
			boundBox,
			"Start",
			((menuButtonState >> 0) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 0;
		finishScreen = 1;
	}

	boundBox = (Rectangle){cellWidth / 2, cellHeight * 3, cellWidth, cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 2");
	if (GuiImageButtonEx(
			boundBox,
			"Options",
			((menuButtonState >> 1) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 1;
	}

	boundBox = (Rectangle){cellWidth / 2, cellHeight * 4, cellWidth, cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 3");
	if (GuiImageButtonEx(
			boundBox,
			"Help",
			((menuButtonState >> 2) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 2;
	}

	boundBox = (Rectangle){cellWidth / 2, cellHeight * 5, cellWidth, cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 4");
	if (GuiImageButtonEx(
			boundBox,
			"Quit",
			((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 3;
	}

	boundBox =
		(Rectangle){screenWidth / 16, cellHeight * 5, cellHeight - padding, cellHeight - padding};
	// GuiButton(boundBox, "C1");
	if (GuiImageButtonEx(
			boundBox,
			"#153#",
			((menuButtonState >> 4) & 1) == 1 ? smallButtonPressed : smallButton,
			(Rectangle){0, 0, smallButton.width, smallButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 4;
	}

	boundBox = (Rectangle){
		screenWidth / 16 * 15 - (cellHeight - padding),
		cellHeight * 5,
		cellHeight - padding,
		cellHeight - padding};
	// GuiButton(boundBox, "C2");
	if (GuiImageButtonEx(
			boundBox,
			"#186#",
			((menuButtonState >> 5) & 1) == 1 ? smallButtonPressed : smallButton,
			(Rectangle){0, 0, smallButton.width, smallButton.height})) {
		menuButtonState = 0;
		menuButtonState |= 1 << 5;
	}
};

void UnloadTitleScreen(void){

};

int FinishTitleScreen(void) {
	return finishScreen;
};

// // Image button control, returns true when clicked
// bool GuiImageButton(Rectangle bounds, const char *text, Texture2D texture) {
// 	return GuiImageButtonEx(
// 		bounds,
// 		text,
// 		texture,
// 		RAYGUI_CLITERAL(Rectangle){0, 0, (float)texture.width, (float)texture.height});
// }

// Image button control, returns true when clicked
bool GuiImageButtonEx(Rectangle bounds, const char *text, Texture2D texture, Rectangle texSource) {
	GuiState state = guiState;
	bool clicked = false;

	// Update control
	//--------------------------------------------------------------------
	if ((state != STATE_DISABLED) && !guiLocked) {
		Vector2 mousePoint = GetMousePosition();

		// Check button state
		if (CheckCollisionPointRec(mousePoint, bounds)) {
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				state = STATE_PRESSED;
			else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				clicked = true;
			else
				state = STATE_FOCUSED;
		}
	}
	//--------------------------------------------------------------------

	// Draw control
	//--------------------------------------------------------------------
	// GuiDrawRectangle(
	// 	bounds,
	// 	GuiGetStyle(BUTTON, BORDER_WIDTH),
	// 	Fade(GetColor(GuiGetStyle(BUTTON, BORDER + (state * 3))), guiAlpha),
	// 	Fade(GetColor(GuiGetStyle(BUTTON, BASE + (state * 3))), guiAlpha));
	if (texture.id > 0)
		DrawTextureRec(
			texture,
			texSource,
			RAYGUI_CLITERAL(Vector2){
				bounds.x + bounds.width / 2 - texSource.width / 2,
				bounds.y + bounds.height / 2 - texSource.height / 2 + texSource.height / 16},
			WHITE);
	// Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))), guiAlpha));

	GuiDrawText(
		text,
		GetTextBounds(BUTTON, bounds),
		GuiGetStyle(BUTTON, TEXT_ALIGNMENT),
		Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))), guiAlpha));
	//------------------------------------------------------------------

	return clicked;
}