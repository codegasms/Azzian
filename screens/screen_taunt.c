#include "raygui.h"
#include "screens.h"
#include <math.h>
#include <raylib.h>

#include <stdio.h>

Texture2D tauntCharacter = {0};
Texture2D tauntScroll = {0};
Texture2D bigButton = {0};

int tauntCharacterWidth = 0;
int tauntCharacterHeight = 0;

int characterIdx = 0;
int tauntIdx = 0;

const static char *taunts[7][5] = {
	{  "Otosan 1",   "Otosan 2",   "Otosan 3",   "Otosan 4",   "Otosan 5"},
	{  "Sports 1",   "Sports 2",   "Sports 3",   "Sports 4",   "Sports 5"},
	{"Academic 1", "Academic 2", "Academic 3", "Academic 4", "Academic 5"},
	{   "Imoto 1",    "Imoto 2",    "Imoto 3",    "Imoto 4",    "Imoto 5"},
	{   "Oksan 1",    "Oksan 2",    "Oksan 3",    "Oksan 4",    "Oksan 5"},
	{  "Kanojo 1",   "Kanojo 2",   "Kanojo 3",   "Kanojo 4",   "Kanojo 5"},
	{    "Jiji 1",     "Jiji 2",     "Jiji 3",     "Jiji 4",     "Jiji 5"},
};

static int screenWidth = 0;
static int screenHeight = 0;

#define CHARACTER_SCALE 6

int deltaHealth(int characterIdx, int responseType);

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

bool DrawTauntScreen(void) {
	// int characterIdx = rng_u64(time(0)) % 7;
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

	DrawText(
		taunts[characterIdx][tauntIdx],
		screenWidth / 4 + 50,
		screenHeight / 2 - 50,
		30,
		BLACK);
	// DrawText(currTaunt, screenWidth / 4 + 50, screenHeight / 2 - 90, 30, BLACK);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
	if (GuiImageButtonExTint(
			(Rectangle){
				screenWidth / 2 - bigButton.width / 4 * 5,
				screenHeight / 4 - 52 + tauntScroll.height + 20,
				bigButton.width,
				bigButton.height},
			"Retaliate",
			bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height},
			WHITE)) {
		// printf("%d\n", deltaHealth(characterIdx, 1));
		healthChangeNPC(deltaHealth(characterIdx, 1));
		return true;
	}

	if (GuiImageButtonExTint(
			(Rectangle){
				screenWidth / 2 + bigButton.width / 4,
				screenHeight / 4 - 52 + tauntScroll.height + 20,
				bigButton.width,
				bigButton.height},
			"Ignore",
			bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height},
			WHITE)) {
		// printf("%d\n", deltaHealth(characterIdx, 2));
		healthChangeNPC(deltaHealth(characterIdx, 2));
		return true;
	}

	return false;
};

int deltaHealth(int characterIdx, int responseType) {
	// Response type 1 = Retaliate
	// Response type 2 = Ignore

	if (characterIdx == 5) {
		return 10;
	}
	int deltaHealth = 0;

	if (responseType == 1) {
		int gambleProb = GetRandomValue(0, 100);

		if (gambleProb < 30) {
			deltaHealth = GetRandomValue(1, 4);
		} else if (gambleProb < 40) {
			deltaHealth = 0;
		} else {
			deltaHealth = GetRandomValue(-4, -1);
		}
	}
	if (responseType == 2) {
		int safeProb = GetRandomValue(0, 100);

		if (safeProb < 20) {
			deltaHealth = 0;
		} else {
			deltaHealth = GetRandomValue(-3, -1);
		}
	}

	printf("%d\n", deltaHealth);
	return deltaHealth;
}

void UnloadTauntScreen(void) {
	UnloadTexture(bigButton);
	UnloadTexture(tauntCharacter);
	UnloadTexture(tauntScroll);
};

int FinishTauntScreen(void){
	// return finishScreen;
};