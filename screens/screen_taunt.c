#include "raygui.h"
#include "screens.h"
#include <math.h>
#include <raylib.h>

Texture2D tauntCharacter = {0};
Texture2D tauntScroll = {0};
Texture2D bigButton = {0};

int tauntCharacterWidth = 0;
int tauntCharacterHeight = 0;

const static char *taunts[7][5] = {
	{				"Otosan 1",   "Otosan 2","Otosan 3",   "Otosan 4","Otosan 5"																		  },
	{				"Sports 1",   "Sports 2",   "Sports 3",   "Sports 4",   "Sports 5"},
	{			  "Academic 1", "Academic 2", "Academic 3", "Academic 4", "Academic 5"},
	{				 "Imoto 1",    "Imoto 2",    "Imoto 3",    "Imoto 4",    "Imoto 5"},
	{"I heard Google is jealous of your search history. They never thought someone could get so "
"many answers wrong.",    "Oksan 2",
     "Oksan 3",    "Oksan 4",
     "Oksan 5"																		 },
	{				"Kanojo 1",   "Kanojo 2",   "Kanojo 3",   "Kanojo 4",   "Kanojo 5"},
	{				  "Jiji 1",     "Jiji 2",     "Jiji 3",     "Jiji 4",     "Jiji 5"},
};

static int screenWidth = 0;
static int screenHeight = 0;

#define CHARACTER_SCALE 6

// static int menuButtonState = 0;

static int finishScreen = 0;

void InitTauntScreen(void) {

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	Image big = LoadImage("resources/Sprites/UI_Flat_Button_Medium_Press_02a1.png");
	ImageResizeNN(&big, big.width * 3, big.height * 2);
	bigButton = LoadTextureFromImage(big);
	UnloadImage(big);

	Image scrollImg = LoadImage("resources/scroll_taunt.png");
	ImageResizeNN(&scrollImg, scrollImg.width * 14, scrollImg.height * 12);
	tauntScroll = LoadTextureFromImage(scrollImg);
	UnloadImage(scrollImg);

	Image characterImage = LoadImage("resources/Character_Combined.png");
	ImageResizeNN(
		&characterImage,
		characterImage.width * CHARACTER_SCALE,
		characterImage.height * CHARACTER_SCALE);
	tauntCharacter = LoadTextureFromImage(characterImage);
	UnloadImage(characterImage);

	tauntCharacterWidth = tauntCharacter.width / 4;
	tauntCharacterHeight = tauntCharacter.height / 2;
}

void UpdateTauntScreen(void){

};

void DrawTauntScreen(void) {
	// int characterIdx = rng_u64(time(0)) % 7;
	int characterIdx = 0;

	DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6));

	DrawTextureRec(
		tauntScroll,
		(Rectangle){0, 0, tauntScroll.width, tauntScroll.height},
		(Vector2){screenWidth / 2 - tauntScroll.width / 2, screenHeight / 4 - 52},
		WHITE);

	DrawTextureRec(
		tauntCharacter,
		(Rectangle){
			characterIdx % 4 * 32 * CHARACTER_SCALE + CHARACTER_SCALE,
			characterIdx / 4 * 32 * CHARACTER_SCALE + CHARACTER_SCALE,
			30 * CHARACTER_SCALE,
			30 * CHARACTER_SCALE},
		(Vector2){screenWidth / 4 + 50, screenHeight / 4 - 30 * CHARACTER_SCALE + 30},
		WHITE);

	const char *currTaunt =
		"I heard Google is jealous of your \n\nsearch history. They never thought \n\n"
		"someone could get so many answers \n\nwrong.";

	// DrawText(taunts[characterIdx][2], screenWidth / 4 + 50, screenHeight / 2 - 50, 30, BLACK);
	DrawText(currTaunt, screenWidth / 4 + 50, screenHeight / 2 - 90, 30, BLACK);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
	GuiImageButtonExTint(
		(Rectangle){
			screenWidth / 2 - bigButton.width / 4 * 5,
			screenHeight / 4 - 52 + tauntScroll.height + 20,
			bigButton.width,
			bigButton.height},
		"Retaliate",
		bigButton,
		(Rectangle){0, 0, bigButton.width, bigButton.height},
		WHITE);

	GuiImageButtonExTint(
		(Rectangle){
			screenWidth / 2 + bigButton.width / 4,
			screenHeight / 4 - 52 + tauntScroll.height + 20,
			bigButton.width,
			bigButton.height},
		"Ignore",
		bigButton,
		(Rectangle){0, 0, bigButton.width, bigButton.height},
		WHITE);
};

void UnloadTauntScreen(void) {
	UnloadTexture(bigButton);
	UnloadTexture(tauntCharacter);
	UnloadTexture(tauntScroll);
};

int FinishTauntScreen(void) {
	return finishScreen;
};
