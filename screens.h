#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen { TITLE = 0, GAMEPLAY } GameScreen;

extern GameScreen currentScreen;

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

//----------------------------------------------------------------------------------
// Game Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);
int FinishGameScreen(void);

#endif