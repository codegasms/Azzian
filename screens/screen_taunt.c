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
	{											  "Old Man: You must be\n\na speed reader with all\n\nthose text messages and tweets.\n\nBack "
                                              "in my time, we\n\nhad to read entire books.","Old Man: Back in my\n\nday, we didn't have fancy\n\ngadgets. We had to calculate\n\nthe tip "
"using our brains,\n\nnot some fancy calculator app!",                                                     "Old Man: You complain about\n\ntraffic? Back in my day,\n\nwe didn't have cars. We\n\nrode "
                                                     "water buffaloes to get\n\naround!",                 "Old Man: You worry about\n\nmy age? My face has\n\nmore lines than a roadmap,\n\nand each "
                 "one tells a\n\ntale of surviving your mom's\n\ncooking experiments!",                                      "Old Man: You think your\n\njob is stressful? I once\n\nraised six kids without Google\n\n– "
                                      "now that's multitasking!"																								 },
	{																				 "Sports-Achiever: Hey , remember that\n\ntime you tried to out-sprint\n\nme? Yeah, me "
                                                                                 "neither.",                                                            "Sports-Achiever: You were doing great\n\nuntil I decided to join\n\nthe competition. Better "
                                                            "luck next\n\ntime",                                                           "Sports-Achiever: Props for trying, but\n\nI think you might need\n\na 'How to Win "
                                                           "Against\n\nYour Superior’",                                            "Sports-Achiever: I heard they're making\n\na movie about my sports\n\ntriumphs. Maybe you "
                                            "can audition\n\nfor the supporting role?",                          "Sports-Achiever: You're like my shadow\n\non the field – always\n\nbehind me. It's a "
                          "tough\n\nact to follow, I get\n\nit."},
	{									  "Over-Achiever Friend: Oh, you finished\n\nthat project? How cute. I\n\njust completed three "
                                      "and redesigned\n\nmy entire life in the\n\nprocess.", "Over-Achiever Friend: They say slow\n\nand steady people like you\n\nwin the race. Well, "
 "I\n\njust prefer fast and flawless,\n\nleaving everyone else in the\n\ndust.",                         "Over-Achiever Friend: Remember when we\n\nused to compete? I'm sorry,\n\nI got distracted by "
                         "achieving\n\nmy goals while you were\n\nstill deciding yours.",                          "Over-Achiever Friend: You know, the\n\nview from the top is\n\namazing. But don't bother, "
                          "you\n\nare not reaching there any\n\nway in this lifetime.", "Over-Achiever Friend: Oh it's nice\n\nto hear you are working\n\nhard. But you know "
 "I\n\nwill beat you at literally\n\nanything even in my sleep."},
	{"Sister: Your skills are like\n\nWi-Fi in a tunnel –\n\nbarely there and quite disappointing.",
     "Sister: I asked for your\n\nIT help, and now my\n\ncomputer has a new problem\n\n– it's "
     "caught your incompetence.",                                                                    "Sister: I guess the alphabet\n\nstarts with 'A,' but your\n\ngrades start with, 'Oh "
                                                                    "no,\n\nnot again!'",                                                      "Sister: They say everyone has\n\na talent. Yours might just\n\nbe turning a simple "
                                                      "drive\n\ninto an extreme sport",                                            "Sister: Your posts are so\n\ninteresting. Said no one, ever.\n\nMaybe try something other "
                                            "than\n\ncat memes?"																																				},
	{														  "Aunt: Oh dear, it looks\n\nlike your cousin outscored you\n\nin the exams! Maybe "
                                                          "next\n\ntime you should borrow some\n\nof his brainpower. Or maybe\n\nhe inherited all the "
                                                          "smart\n\ngenes from our family.",                                   "Aunt: I suppose not everyone\n\ncan appreciate the value of\n\nacademic success. It's "
                                   "fascinating how\n\nsome choose to revel in\n\nmediocrity. But hey, at least\n\nyou're "
                                   "consistent – consistently underachieving", "Aunt: Also I have noticed\n\nyou have become fat. Consistency\n\nis key, dear. Keep "
 "indulging\n\nin junk and you might\n\njust become the champion of\n\nthe obese world!",                                            "Aunt: People in the family\n\nsay you are just like\n\nyour father. Both of you\n\ndisappear "
                                            "at the time when\n\nit matters the most.",                                  "Aunt: If scientists could measure\n\nyour brain activity, they would\n\nrealize how smart "
                                  "the monkeys\n\nactually are."},
	{												  "Crush: You know, your smile\n\nhas this magnetic pull, like\n\nit's quietly inviting me "
                                                  "to\n\nbe a part of your\n\nhappy world.",                                         "Crush: Your energy is like\n\na cool breeze on a\n\nwarm day – refreshing and\n\nmaking me "
                                         "want to stick\n\naround for a while.",                                            "Crush: I've been thinking, your\n\nlaughter is like a melody\n\nin the background, making "
                                            "every\n\nmoment a little more interesting.", "Crush: There's something about the\n\nway you navigate through life\n\nthat has me curious. "
 "It's\n\nlike you've got this secret\n\nmap, and I'd love to\n\nexplore it with you.",           "Crush: I've noticed that every\n\ntime you're around, things just\n\nseem to brighten up "
           "a\n\nbit. Call it coincidence, but\n\nI'm enjoying."},
	{												"Father: Son, looks like your\n\ngrades are not exactly setting\n\nthe world on fire. "
                                                "Perhaps\n\nyou're majoring in mediocrity?",                      "Father: Well, it's good to\n\nknow you're exploring the bottom\n\nof the achievement barrel. "
                      "I\n\nguess not everyone inherits the\n\n'success gene.'",                                                                             "Father: When I was your\n\nage, I walked uphill both\n\nways to school. And I\n\nstill aced "
                                                                             "my exams!",                                                                     "Father: Are you sure you\n\ncan't solve this math problem?\n\nBack in my time, we\n\ndid it "
                                                                     "with an abacus!",                                         "Father: You want to be\n\ndoctor? Maybe start by diagnosing\n\nwhy you can't clean "
                                         "your\n\nstupid brain!"},
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
		screenWidth / 4 + 90,
		screenHeight / 2 - 65,
		23,
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
