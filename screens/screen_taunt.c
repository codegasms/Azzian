#include "screens.h"
#include <math.h>
#include <raylib.h>

Texture2D backgroundTexture = {0};
Texture2D tauntCharacter = {0};

#define MAX_OPTIONS 4

typedef struct {
	Rectangle rect;
	const char *text;
} TauntElement;

typedef struct {
	Rectangle rect;
	const char *name;
} Taunter;

static int menuButtonState = 0;

static int finishScreen = 0;

// Define padding and margin values
const int paddingX = 10;
const int paddingY = 10;
const int marginX = 30;
const int marginY = 30;

const int overlayMarginX = 140;
const int overlayMarginY = 120;

// Define the question and options
TauntElement question = {0};
Taunter taunter = {0};
TauntElement options[MAX_OPTIONS] = {0};
const char *optionsText[MAX_OPTIONS] = {"Option 1", "Option 2", "Option 3", "Option 4"};

void InitTauntScreen(void) {

	const int screenWidth = GetScreenWidth();

	// Load your background texture
	// Texture2D backgroundTexture = LoadTexture("/home/aahnik/Downloads/transpa.jpg");
	Image characterImage = LoadImage("/path/to/character.jpg");
	ImageResizeNN(&characterImage, 1, 1);
	Texture2D tauntCharacter = LoadTextureFromImage(characterImage);
	// Define the question text
	question.text = "What is the question?";

	// Define the options text

	// Calculate positions for question and options dynamically
	int currentY = overlayMarginY + marginY;

	taunter.rect.x = 2 * marginX + overlayMarginX;
	taunter.rect.y = currentY;
	taunter.rect.width = 300;
	taunter.rect.height = 400;

	// Calculate position for the question
	question.rect.x = 16 * marginX + overlayMarginX;
	question.rect.y = currentY + 10;
	question.rect.width = screenWidth - 5 * (marginX + overlayMarginX);
	question.rect.height = 180;

	// Update currentY for options
	currentY += question.rect.height + 2 * marginY;

	// Calculate positions for options
	int optionsBase = 15 * marginX + overlayMarginX;
	for (int i = 0; i < MAX_OPTIONS; i++) {
		options[i].rect.x =
			optionsBase + (i % 2) * ((screenWidth - 3 * marginX) / 4 + 2 * paddingX);
		options[i].rect.y = currentY + (i / 2) * (options[i].rect.height + paddingY);
		options[i].rect.width = (screenWidth - 3 * (marginX + overlayMarginX)) / 4;
		options[i].rect.height = 50;
		currentY += (i % 2) * (options[i].rect.height + marginY);

		options[i].text = optionsText[i];
	}
}

void UpdateTauntScreen(void){

};

void DrawTauntScreen(void) {

	// Draw background texture
	// DrawTexture(backgroundTexture, 0, 0, tint);
	DrawRectangle(
		overlayMarginX,
		overlayMarginY,
		GetScreenWidth() - 2 * overlayMarginX,
		GetScreenHeight() - 2 * overlayMarginY,
		Fade(BLACK, 0.7));

	// Draw taunter character
	DrawRectangleRec(taunter.rect, DARKGRAY);
	DrawText(taunter.name, taunter.rect.x + paddingX, taunter.rect.y + paddingY, 20, WHITE);
	// Draw question rectangle and text
	DrawRectangleRec(question.rect, DARKGRAY);
	DrawText(question.text, question.rect.x + paddingX, question.rect.y + paddingY, 20, WHITE);

	// Draw option rectangles and text
	for (int i = 0; i < MAX_OPTIONS; i++) {
		DrawRectangleRec(options[i].rect, LIGHTGRAY);
		DrawText(options[i].text, options[i].rect.x, options[i].rect.y, 20, BLACK);
	}
};

void UnloadTauntScreen(void) {
	UnloadTexture(backgroundTexture);
};

int FinishTauntScreen(void) {
	return finishScreen;
};
