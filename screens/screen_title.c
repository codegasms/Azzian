#define RAYGUI_IMPLEMENTATION

#include "screens.h"
#include "raygui.h"
#include <raylib.h>

static Rectangle r = {0};
bool testCheck = false;

static int finishScreen = 0;

void InitTitleScreen(void){
    r = (Rectangle){100.0f, 100.0f, 50, 50};
};

void UpdateTitleScreen(void){

};

void DrawTitleScreen(void){
    GuiCheckBox(r, "Ur Mom", &testCheck);
};

void UnloadTitleScreen(void){

};

int FinishTitleScreen(void){
    return finishScreen;
};
