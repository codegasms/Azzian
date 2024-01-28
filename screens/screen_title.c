#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "screens.h"
#include <raylib.h>

extern GameScreen currentScreen;

Image menuBg = {0};

static Texture2D menuScreen = {0};
static Texture2D gameName = {0};
static Texture2D bigButton = {0};
static Texture2D bigButtonPressed = {0};
static Texture2D smallButton = {0};
static Texture2D smallButtonPressed = {0};
static Texture2D scrollPaper = {0};

static Music vboom = {0};
static Music haiya = {0};
static Music quack = {0};
static Music titleOST = {0};
static Music outro = {0};
// Chin Chen Han Ji
static Music cchj = {0};
static Music wrongBuzzer = {0};
static Music correctBuzzer = {0};
static Music click = {0};

static int menuButtonState = 0;

typedef enum {
	MENU_MAIN,
	MENU_DIFFICULTY,
	MENU_HELP,
	MENU_EXIT,
	MENU_LANG,
	MENU_CREDITS,
} MenuType;

MenuType menuType = MENU_MAIN;

static int finishScreen = 0;

unsigned int nextFrameDataOffset = 0;
int animFrames = 0;
int currentAnimFrame = 0;
int frameDelay = 8;
int frameCounter = 0;

static int asianHelp = 0;

void InitTitleScreen(void) {

	finishScreen = 0;

	GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0x1f3b4dff);

	menuBg = LoadImageAnim("resources/main_menu.gif", &animFrames);
	menuScreen = LoadTextureFromImage(menuBg);

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

	Image scroll = LoadImage("resources/scroll_wide.png");
	ImageResizeNN(&scroll, scroll.width * 0.6, scroll.height * 0.6);
	scrollPaper = LoadTextureFromImage(scroll);

	InitAudioDevice();

	quack = LoadMusicStream("resources/audio/quack.mp3");
	quack.looping = false;
	haiya = LoadMusicStream("resources/audio/haiya.mp3");
	haiya.looping = false;
	vboom = LoadMusicStream("resources/audio/vboom.mp3");
	SetMusicVolume(vboom, 0.5f);
	vboom.looping = false;
	wrongBuzzer = LoadMusicStream("resources/audio/wrong.mp3");
	SetMusicVolume(wrongBuzzer, 0.1f);
	wrongBuzzer.looping = false;
	correctBuzzer = LoadMusicStream("resources/audio/correct.mp3");
	correctBuzzer.looping = false;
	click = LoadMusicStream("resources/audio/click.mp3");
	click.looping = false;
	cchj = LoadMusicStream("resources/audio/chingchenghanji.mp3");
	outro = LoadMusicStream("resources/audio/outro.mp3");
	outro.looping = false;
	titleOST = LoadMusicStream("resources/audio/titleOST.mp3");

	PlayMusicStream(titleOST);

	UnloadImage(game);
	UnloadImage(big);
	UnloadImage(big2);
	UnloadImage(small);
	UnloadImage(small2);
	UnloadImage(scroll);
}

void UpdateTitleScreen(void) {
	UpdateMusicStream(quack);
	UpdateMusicStream(haiya);
	UpdateMusicStream(vboom);
	UpdateMusicStream(titleOST);
	UpdateMusicStream(outro);
	UpdateMusicStream(cchj);
	UpdateMusicStream(wrongBuzzer);
	UpdateMusicStream(correctBuzzer);
	UpdateMusicStream(click);

	frameCounter++;
	if (frameCounter >= frameDelay) {
		// Move to next frame
		// NOTE: If final frame is reached we return to first frame
		currentAnimFrame++;
		if (currentAnimFrame >= animFrames)
			currentAnimFrame = 0;

		// Get memory offset position for next frame data in image.data
		nextFrameDataOffset = menuBg.width * menuBg.height * 4 * currentAnimFrame;

		// Update GPU texture data with next frame image data
		// WARNING: Data size (frame size) and pixel format must match already created texture
		UpdateTexture(menuScreen, ((unsigned char *)menuBg.data) + nextFrameDataOffset);

		frameCounter = 0;
	}
};

void DrawTitleScreen(void) {
	ClearBackground(BLACK);

	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	int cellWidth = screenWidth / 2;
	int cellHeight = screenHeight / 6;
	int padding = cellHeight / 4;

	DrawTextureRec(
		menuScreen,
		(Rectangle){0, 0, screenWidth, screenHeight},
		(Vector2){0.0f, 0.0f},
		WHITE);

	if (menuType == MENU_MAIN) {
		DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 50});
	}

	DrawTexture(gameName, cellWidth - gameName.width / 2, padding, (Color){40, 40, 40, 255});

	GuiSetIconScale(4);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
	Rectangle boundBox = {
		screenWidth / 2 - bigButton.width / 2,
		cellHeight * 2,
		bigButton.width,
		cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 1");
	if (GuiImageButtonEx(
			boundBox,
			"Start",
			((menuButtonState >> 0) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(vboom);
		PlayMusicStream(vboom);
		menuButtonState = 0;
		menuButtonState |= 1 << 0;
		finishScreen = 1;
	}

	boundBox = (Rectangle){
		screenWidth / 2 - bigButton.width / 2,
		cellHeight * 3,
		bigButton.width,
		cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 2");
	GuiSetStyle(DEFAULT, TEXT_SIZE, 42);
	if (GuiImageButtonEx(
			boundBox,
			"Difficulty",
			((menuButtonState >> 1) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(vboom);
		PlayMusicStream(vboom);
		menuButtonState = 0;
		menuButtonState |= 1 << 1;
		menuType = MENU_DIFFICULTY;
	}
	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);

	boundBox = (Rectangle){
		screenWidth / 2 - bigButton.width / 2,
		cellHeight * 4,
		bigButton.width,
		cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 3");
	if (GuiImageButtonEx(
			boundBox,
			"Help",
			((menuButtonState >> 2) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(vboom);
		PlayMusicStream(vboom);
		menuButtonState = 0;
		menuButtonState |= 1 << 2;
		menuType = MENU_HELP;
	}

	boundBox = (Rectangle){
		screenWidth / 2 - bigButton.width / 2,
		cellHeight * 5,
		bigButton.width,
		cellHeight - padding};
	// GuiButton(boundBox, "Ur Mom 4");
	if (GuiImageButtonEx(
			boundBox,
			"Quit",
			((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
			(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(click);
		PlayMusicStream(click);
		PauseMusicStream(titleOST);
		PlayMusicStream(outro);
		menuButtonState = 0;
		menuButtonState |= 1 << 3;
		menuType = MENU_EXIT;
	}

	boundBox =
		(Rectangle){screenWidth / 16, cellHeight * 5, cellHeight - padding, cellHeight - padding};
	// GuiButton(boundBox, "C1");
	if (GuiImageButtonEx(
			boundBox,
			"#153#",
			((menuButtonState >> 4) & 1) == 1 ? smallButtonPressed : smallButton,
			(Rectangle){0, 0, smallButton.width, smallButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(haiya);
		PlayMusicStream(haiya);
		menuButtonState = 0;
		menuButtonState |= 1 << 4;
		menuType = MENU_LANG;
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
			(Rectangle){0, 0, smallButton.width, smallButton.height}) &&
	    menuType == MENU_MAIN) {
		StopMusicStream(click);
		PlayMusicStream(click);
		PauseMusicStream(titleOST);
		PlayMusicStream(cchj);
		menuButtonState = 0;
		menuButtonState |= 1 << 5;
		menuType = MENU_CREDITS;
	}

	if (menuType != MENU_MAIN) {
		DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 200});
	}

	if (!IsMusicStreamPlaying(outro) && menuType == MENU_EXIT) {
		finishScreen = 2;
	}

	if (((menuButtonState >> 1) & 1)) {
		GuiSetStyle(DEFAULT, TEXT_SIZE, 50);

		DrawTexture(
			scrollPaper,
			screenWidth / 2 - scrollPaper.width / 2,
			screenHeight / 2 - scrollPaper.height / 2,
			WHITE);
		DrawTextEx(
			GetFontDefault(),
			"DIFFICULTY",
			(Vector2){
				screenWidth / 2 - MeasureText("DIFFICULTY", 50) / 2 + 20,
				screenHeight / 2 - padding * 4},
			50,
			3,
			BLACK);

		Color difficultyFade = {200, 200, 200, 160};
		if (GuiImageButtonExTint(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 - bigButton.height / 2 - padding / 2,
					bigButton.width,
					bigButton.height},
				"Easy",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height},
				difficultyFade) &&
		    menuType == MENU_DIFFICULTY) {
			StopMusicStream(wrongBuzzer);
			PlayMusicStream(wrongBuzzer);
		}
		if (GuiImageButtonExTint(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 - bigButton.height / 2 - padding / 2,
					bigButton.width,
					bigButton.height},
				"Medium",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height},
				difficultyFade) &&
		    menuType == MENU_DIFFICULTY) {
			StopMusicStream(wrongBuzzer);
			PlayMusicStream(wrongBuzzer);
		}
		if (GuiImageButtonExTint(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"Hard",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height},
				difficultyFade) &&
		    menuType == MENU_DIFFICULTY) {
			StopMusicStream(wrongBuzzer);
			PlayMusicStream(wrongBuzzer);
		}
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"ASIAN",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_DIFFICULTY) {
			StopMusicStream(correctBuzzer);
			PlayMusicStream(correctBuzzer);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
	}

	if (((menuButtonState >> 2) & 1)) {

		GuiSetStyle(DEFAULT, TEXT_SIZE, 35);

		DrawTexture(
			scrollPaper,
			screenWidth / 2 - scrollPaper.width / 2,
			screenHeight / 2 - scrollPaper.height / 2,
			WHITE);
		DrawTextEx(
			GetFontDefault(),
			"        Don't You Know\n\n\n"
			"ASIANS DON'T NEED HELP",
			(Vector2){
				screenWidth / 2 - MeasureText("ASIANS DON'T NEED HELP", 50) / 2 + 20,
				screenHeight / 2 - padding * 3},
			50,
			3,
			BLACK);
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"Ok?",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_HELP) {
			StopMusicStream(click);
			PlayMusicStream(click);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				(asianHelp == 1) ? "Yes!!!" : "Really?",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_HELP) {
			StopMusicStream(vboom);
			PlayMusicStream(vboom);
			asianHelp += 1;

			if (asianHelp == 2) {
				StopMusicStream(vboom);
				PlayMusicStream(vboom);
				asianHelp = 0;
				menuButtonState = 0;
				menuType = MENU_MAIN;
			}
		}
	}

	if (((menuButtonState >> 3) & 1)) {

		GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
		// if (GuiMessageBox(
		// 		(Rectangle){screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
		// 		"Do You Want To Quit",
		// 		"If You Quit Ur GAY",
		// 		"Agree") == 0) {
		// }
		DrawTexture(
			scrollPaper,
			screenWidth / 2 - scrollPaper.width / 2,
			screenHeight / 2 - scrollPaper.height / 2,
			WHITE);
		DrawTextEx(
			GetFontDefault(),
			"Are You Sure You Want To Quit?",
			(Vector2){
				screenWidth / 2 - MeasureText("Are You Sure You Want To Quit?", 40) / 2 + 20,
				screenHeight / 2 - padding * 2},
			40,
			3,
			BLACK);
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"Yes",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_EXIT) {
			// QUIT GAME
			finishScreen = 2;
		}
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"No",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_EXIT) {
			StopMusicStream(click);
			PlayMusicStream(click);
			StopMusicStream(outro);
			ResumeMusicStream(titleOST);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
	}

	if (((menuButtonState >> 4) & 1)) {

		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		// GuiMessageBox(
		// 	(Rectangle){screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
		// 	"Change The Language?",
		// 	TextFormat("Learn English First & Come Play "),
		// 	"Agree");
		DrawTexture(
			scrollPaper,
			screenWidth / 2 - scrollPaper.width / 2,
			screenHeight / 2 - scrollPaper.height / 2,
			WHITE);
		DrawTextEx(
			GetFontDefault(),
			"WAIT WHAT!? YOU WANT TO CHANGE THE LANGUAGE?",
			(Vector2){
				screenWidth / 2 -
					MeasureText("WAIT WHAT!? YOU WANT TO CHANGE THE LANGUAGE?", 22) / 2 - 10,
				screenHeight / 2 - padding * 3},
			22,
			3,
			BLACK);
		DrawTextEx(
			GetFontDefault(),
			"How Would You Get Into Harvard If You Don't Know English?",
			(Vector2){
				screenWidth / 2 -
					MeasureText("How Would You Get Into Harvard If You Don't Know English?", 20) /
						2 -
					20,
				screenHeight / 2 - padding},
			20,
			3,
			BLACK);
		DrawTextEx(
			GetFontDefault(),
			"Go Learn English & Come Play This Game",
			(Vector2){
				screenWidth / 2 - MeasureText("Go Learn English & Come Play This Game", 20) / 2,
				screenHeight / 2},
			20,
			3,
			BLACK);
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"Ok, I'll Learn English",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_LANG) {
			// QUIT GAME
			finishScreen = 2;
		}
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 + bigButton.height / 2,
					bigButton.width,
					bigButton.height},
				"Wait, I Know English",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_LANG) {
			StopMusicStream(click);
			PlayMusicStream(click);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
	}

	if (((menuButtonState >> 5) & 1)) {

		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
		// GuiMessageBox(
		// 	(Rectangle){screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
		// 	"All Of Our Underpaid Labours",
		// 	"It's Illegal To Reveal Their Names",
		// 	"I Don't Give A F*ck");
		DrawTexture(
			scrollPaper,
			screenWidth / 2 - scrollPaper.width / 2,
			screenHeight / 2 - scrollPaper.height / 2,
			WHITE);
		DrawTextEx(
			GetFontDefault(),
			"THE CODEGASMS",
			(Vector2){
				screenWidth / 2 - MeasureText("THE CODEGASMS", 35) / 2,
				screenHeight / 2 - padding * 4},
			35.,
			3,
			BLACK);
		DrawTextEx(
			GetFontDefault(),
			"  Suvan Sarkar         (github.com/Suvansarkar)\n\n"
			"Bishwajeet Sahoo     (github.com/SahooBishwajeet)\n\n"
			"  Saurabh Pal               (github.com/virinci)\n\n"
			"  Aahnik Daw                (github.com/aahnik)\n\n"
			" Vinayak Anand         (github.com/Vinayak-Anand)",
			(Vector2){
				screenWidth / 2 -
					MeasureText("Bishwajeet Sahoo     (github.com/SahooBishwajeet)", 20) / 2,
				screenHeight / 2 - padding * 2},
			20,
			3,
			BLACK);
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 + bigButton.width / 2,
					screenHeight / 2 + bigButton.height,
					bigButton.width,
					bigButton.height},
				"I Don't Give A Duck",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_CREDITS) {
			StopMusicStream(quack);
			PlayMusicStream(quack);
			StopMusicStream(cchj);
			ResumeMusicStream(titleOST);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
		GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
		if (GuiImageButtonEx(
				(Rectangle){
					screenWidth / 2 - bigButton.width / 2 * 3,
					screenHeight / 2 + bigButton.height,
					bigButton.width,
					bigButton.height},
				"Appreciated!!!",
				((menuButtonState >> 3) & 1) == 1 ? bigButtonPressed : bigButton,
				(Rectangle){0, 0, bigButton.width, bigButton.height}) &&
		    menuType == MENU_CREDITS) {
			StopMusicStream(click);
			PlayMusicStream(click);
			StopMusicStream(cchj);
			ResumeMusicStream(titleOST);
			menuButtonState = 0;
			menuType = MENU_MAIN;
		}
	}
};

void UnloadTitleScreen(void) {
	UnloadTexture(menuScreen);
	UnloadTexture(gameName);
	UnloadTexture(bigButton);
	UnloadTexture(bigButtonPressed);
	UnloadTexture(smallButton);
	UnloadTexture(smallButtonPressed);
	UnloadTexture(scrollPaper);
	UnloadMusicStream(quack);
	UnloadMusicStream(haiya);
	UnloadMusicStream(vboom);
	UnloadMusicStream(titleOST);
	UnloadMusicStream(outro);
	UnloadMusicStream(cchj);
	UnloadMusicStream(wrongBuzzer);
	UnloadMusicStream(correctBuzzer);
	UnloadMusicStream(click);
	CloseAudioDevice();
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
bool GuiImageButtonExTint(
	Rectangle bounds,
	const char *text,
	Texture2D texture,
	Rectangle texSource,
	Color tint) {
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
			tint);
	// Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))), guiAlpha));

	GuiDrawText(
		text,
		GetTextBounds(BUTTON, bounds),
		GuiGetStyle(BUTTON, TEXT_ALIGNMENT),
		Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))), guiAlpha));
	//------------------------------------------------------------------

	return clicked;
}

// Image button control, returns true when clicked
bool GuiImageButtonEx(Rectangle bounds, const char *text, Texture2D texture, Rectangle texSource) {
	return GuiImageButtonExTint(bounds, text, texture, texSource, WHITE);
}
