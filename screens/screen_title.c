#define RAYGUI_IMPLEMENTATION

#include "screens.h"
#include "raygui.h"
#include <raylib.h>

static Texture2D player = {0};

static int finishScreen = 0;

void InitTitleScreen(void)
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 50);

    Image image = LoadImage("resources/azzian.png");
    ImageResizeNN(&image, image.width * 1.2, image.height * 1.2);
    player = LoadTextureFromImage(image);
}

void UpdateTitleScreen(void){

};

void DrawTitleScreen(void)
{
    ClearBackground(BLACK);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int cellWidth = screenWidth / 2;
    int cellHeight = screenHeight / 6;
    int padding = cellHeight / 4;

    DrawTexture(player, cellWidth - player.width / 2, padding , WHITE);

    Rectangle boundBox = {cellWidth / 2, cellHeight * 2, cellWidth, cellHeight - padding};
    GuiButton(boundBox, "Ur Mom 1");

    boundBox = (Rectangle){cellWidth / 2, cellHeight * 3, cellWidth, cellHeight - padding};
    GuiButton(boundBox, "Ur Mom 2");

    boundBox = (Rectangle){cellWidth / 2, cellHeight * 4, cellWidth, cellHeight - padding};
    GuiButton(boundBox, "Ur Mom 3");

    boundBox = (Rectangle){cellWidth / 2, cellHeight * 5, cellWidth, cellHeight - padding};
    GuiButton(boundBox, "Ur Mom 4");

    boundBox = (Rectangle){screenWidth / 16, cellHeight * 5, cellHeight - padding, cellHeight - padding};
    GuiButton(boundBox, "C1");

    boundBox = (Rectangle){screenWidth / 16 * 15 - (cellHeight - padding), cellHeight * 5, cellHeight - padding, cellHeight - padding};
    GuiButton(boundBox, "C2");
};

void UnloadTitleScreen(void){

};

int FinishTitleScreen(void)
{
    return finishScreen;
};
