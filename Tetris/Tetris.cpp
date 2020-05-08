// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <Windows.h>
#include <Mmsystem.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <conio.h>
#include "Blocks.h"
#include "Multiplayer.h"
#include "PlayerStats.h"
#include "DisplayHelper.h"
#include "Leaderboards.h"

PlayerStats* CurrentChar = new PlayerStats;
PlayerStats* LocalChar = new PlayerStats;
TetrisObj game;

int Score = 0;
int HighScore = 0;
int usingCheats = 0;

int GameState = 0; // 0 running 1 ended.
int start = 0;

int Level = 0;
int maxLevel = INT32_MAX;
Blocks prevBlock = EMPTY;
Blocks currentBlock = EMPTY;
int numBlocks = 6;
int Rotation = 0, prevRot = 0; // 0 normal 1
std::string userdatadir = getenv("appdata");
Leaderboards* lbdata = new Leaderboards;

char cmd[10]{};

void Startup(PlayerStats* newChar, int mode) {
	FILE* detectFile = fopen((userdatadir + "/userdata.bin").c_str(), "r");
	
	if (detectFile != NULL && mode == 0) {
		fread(newChar, sizeof(PlayerStats), 1, detectFile);

		HighScore = newChar->GetHighScore();

		FILE* readFile1 = fopen("leaderboards.dat", "r");

		if (readFile1 != NULL) {
			lbdata->LoadBinary("leaderboards.dat");
		}
		else {
			lbdata->InsertLeaderboardSrted(*newChar);
		}

		fclose(detectFile);
	}
	else {
		system("CLS");
		std::cout << '\n';
		std::cout << "||=======================================================||\n";
		std::cout << "||                    __________         BY ZHANGCODES620||\n";
		std::cout << "||                    |        |                         ||\n";
		std::cout << "||                    |        |                         ||\n";
		std::cout << "||           _________|________|________                 ||\n";
		std::cout << "||           |        |        |        |                ||\n";
		std::cout << "||           |        |        |        |                ||\n";
		std::cout << "||           ----------------------------                ||\n";
		std::cout << "||                   TETRIS IN C++!                      ||\n";
		std::cout << "||=======================================================||\n";
		std::cout << "Enter your name (Max 10 Chars): ";
		std::string username;
		std::getline(std::cin, username);
		if (username.length() < 10) {
			newChar->assignName(username.c_str());
			newChar->generateUID(); // Generates a new UID for each character to factilate searching.
			newChar->SetHighScore(0); // Sets the score to zero and resets the anti-tamper measures.
			newChar->Connector = -1;

			std::cout << "Username successfully registered. Welcome to TETRIS, " << newChar->GetUserNameT() << "!\n";
			std::cout << "UID: " << newChar->GetUID() << '\n';
			std::cout << "Current High Score: " << newChar->GetHighScore() << '\n';

			std::cout << "\nPress E on the keyboard to start playing Tetris!\n";
			char out = _getch();
		}
		else {
			std::cout << "Too long. Maximum 10 characters allowed. You entered: " << username.length() << " characters.\n";
			std::cout << "\nPress E on the keyboard to try again\n";
			char out = _getch();
			Startup(newChar, mode);
		}
	}
}

int MainMenu() {
	int Selection = 0;
	int prevSelection = -1;
	char input = 'N';
	while (input != 'e' && input != 'E') {
		if (prevSelection != Selection) {
			system("CLS");
			std::cout << '\n';
			std::cout << "||=======================================================||\n";
			std::cout << "||                    __________         BY ZHANGCODES620||\n";
			std::cout << "||                    |        |                         ||\n";
			std::cout << "||                    |        |                         ||\n";
			std::cout << "||           _________|________|________                 ||\n";
			std::cout << "||           |        |        |        |                ||\n";
			std::cout << "||           |        |        |        |                ||\n";
			std::cout << "||           ----------------------------                ||\n";
			std::cout << "||                   TETRIS IN C++!                      ||\n";
			std::cout << "||=======================================================||\n";
			std::cout << "\x1b[" << 94 << "m";
			std::cout << "||" << CurrentChar->GetUserNameT() << ": " << HighScore << "\n";
			std::cout << "\x1b[0m";
			std::cout << "||=======================================================||\n";

			if (Selection == 0) {
				std::cout << "         <PLAY TETRIS!>           EXIT TO TERMINAL          ";
				std::cout << "\n          MULTIPLAYER               LEADERBOARDS            \n\n";
			}
			else if (Selection == 1) {
				std::cout << "          PLAY TETRIS!           <EXIT TO TERMINAL>         ";
				std::cout << "\n          MULTIPLAYER               LEADERBOARDS            \n\n";
			}
			else if (Selection == 2) {
				std::cout << "          PLAY TETRIS!            EXIT TO TERMINAL          ";
				std::cout << "\n         <MULTIPLAYER>              LEADERBOARDS            \n\n";
			}
			else if (Selection == 3) {
				std::cout << "          PLAY TETRIS!            EXIT TO TERMINAL         ";
				std::cout << "\n          MULTIPLAYER              <LEADERBOARDS>           \n\n";
				
			}
			prevSelection = Selection;

			std::cout << "\x1b[" << 94 << "m";
			std::cout << "Controls: WASD\n(W to rotate Block, A and D to move left and right, and S to speed up descent of Block.\n\n";
			std::cout << "    [W] [E]\n";
			std::cout << "[A] [S] [D] [F]\n\n";
			std::cout << "For menus, E to go to option, F for filters (Leaderboards only).\n";
			std::cout << "\x1b[0m";
		}

		if (_kbhit()) {
			input = _getch();
			if (input == 'a' || input == 'A')
				if (Selection > 0)
					Selection--;

			if (input == 'd' || input == 'D')
				if (Selection < 3)
					Selection++;

			if (input == 'c') {
				std::cout << "Master Recognition Mode Enabled.\n";
				std::cout << "Enter your command: ";
				int num = 0;
				std::cin >> cmd;

				if (strcmp(cmd,"SetScore()") == 0) {
					std::cout << "\nParameters: ";
					std::cin >> game.Score;
					usingCheats++;
				}

				if (strcmp(cmd,"SetLevel()") == 0) {
					std::cout << "\nParameters: ";
					std::cin >> game.Level;
					usingCheats++;
				}

				if (strcmp(cmd, "SetSpeed()") == 0) {
					std::cout << "\nParameters: ";
					std::cin >> game.FixedTime;
					usingCheats++;
				}

				if (strcmp(cmd, "SetBlockBounds()") == 0) {
					std::cout << "\nParameters: ";
					std::cin >> game.numBlocks;
					usingCheats++;
				}

				if (strcmp(cmd, "SetTrack()") == 0) {
					std::cout << "\nParameters: ";
					std::cin >> num;

					if (num == 0)
						PlaySound(TEXT("main.wav"), NULL, SND_LOOP | SND_ASYNC);
					if (num == 1)
						PlaySound(TEXT("alt1.wav"), NULL, SND_LOOP | SND_ASYNC);
					if (num == 2)
						PlaySound(TEXT("alt2.wav"), NULL, SND_LOOP | SND_ASYNC);
					
					usingCheats++;
				}
			}
		}
	}

	return Selection;
}

int GameOver() {
	PlaySound(NULL, NULL, 0);
	int Selection = 0;
	char input = 'N';
	while (input != 'e' && input != 'E') {
		system("CLS");
		std::cout << '\n';
		std::cout << "||=======================================================||\n";
		std::cout << "||                    __________                 SCORE: " << Score <<"||\n";
		std::cout << "||                    | 88  88 |                         ||\n";
		std::cout << "||                    | 88  88 |                         ||\n";
		std::cout << "||           _________|________|________                 ||\n";
		std::cout << "||           |        | ====== |        |                ||\n";
		std::cout << "||           |        |-      -|        |                ||\n";
		std::cout << "||           ----------------------------                ||\n";
		std::cout << "\x1b[" << 91 << "m";
		std::cout << "||                     GAME OVER!                        ||\n";
		std::cout << "\x1b[0m";
		std::cout << "||=======================================================||\n";

		if (Selection == 0)
			std::cout << "         <TRY AGAIN!>             EXIT TO MENU              ";
		else
			std::cout << "          TRY AGAIN!             <EXIT TO MENU>             ";

		if (_kbhit()) {
			input = _getch();
			if (input == 'a' || input == 'A')
				if (Selection > 0)
					Selection--;

			if (input == 'd' || input == 'D')
				if (Selection < 1)
					Selection++;
		}
	}

	return Selection;
}

void GameStarter(PlayerStats* newChar, int mode) {
	if (usingCheats == 0)
		PlaySound(TEXT("main.wav"), NULL, SND_LOOP | SND_ASYNC);
	
	game.Reset();
	game.HighScore = newChar->GetHighScore();
	game.Run();

	if (mode == 0) {
		FILE* writeFile = fopen((userdatadir + "/userdata.bin").c_str(), "w");

		if (writeFile != NULL) {
			fwrite(newChar, sizeof(PlayerStats), 1, writeFile);
			fclose(writeFile);
		}
	}


	if (newChar->GetHighScore() < game.HighScore) {
		newChar->SetHighScore(game.HighScore);
		lbdata->InsertLeaderboardSrted(*newChar);
	}

	Score = game.Score;

	lbdata->SavetoBinary("leaderboards.dat");

	if (GameOver() == 0) {
		GameStarter(newChar, mode);
	}

	//exit(0);
}


void LocalMPOptions() {
	int Selection = 0;
	int prevSelection = -1;
	char input = 'N';
	while (input != 'e' && input != 'E' && input != 27) {
		if (prevSelection != Selection) {
			system("CLS");
			std::cout << '\n';
			std::cout << "||=======================================================||\n";
			std::cout << "||                    __________         BY ZHANGCODES620||\n";
			std::cout << "||                    |        |                         ||\n";
			std::cout << "||                    |        |                         ||\n";
			std::cout << "||           _________|________|________                 ||\n";
			std::cout << "||           |        |        |        |                ||\n";
			std::cout << "||           |        |        |        |                ||\n";
			std::cout << "||           ----------------------------                ||\n";
			std::cout << "||                   TETRIS IN C++!                      ||\n";
			std::cout << "||=======================================================||\n";
			std::cout << "\x1b[" << 94 << "m";
			std::cout << "||" << CurrentChar->GetUserNameT() << ": " << HighScore << "\n";
			std::cout << "\x1b[0m";
			std::cout << "||=======================================================||\n";

			if (Selection == 0) {
				std::cout << "         <NEW PLAYER>           CONTINUE AS ";
				std::cout << "\x1b[" << 94 << "m" << CurrentChar->GetUserNameT() << "\x1b[0m" << "\n";
			}
			else if (Selection == 1) {
				std::cout << "          NEW PLAYER           <CONTINUE AS ";
				std::cout << "\x1b[" << 94 << "m" << CurrentChar->GetUserNameT() << "\x1b[0m" << ">\n";
			}
			prevSelection = Selection;
		}

		if (_kbhit()) {
			input = _getch();

			if (input == 27)
				Selection = -1;

			if (input == 'a' || input == 'A')
				if (Selection > 0)
					Selection--;

			if (input == 'd' || input == 'D')
				if (Selection < 1)
					Selection++;

		}
	}

	if (Selection == 1) {
		GameStarter(CurrentChar, 0);
	}
	else if (Selection == 0) {
		Startup(LocalChar, 1);
		GameStarter(LocalChar, 1);
	}
}


int main()
{
	SetConsoleTitle(TEXT("Tetris in C++ by ZHANGCODES620! Now with limited multiplayer!"));
	remove("player1.bin");
	remove("player2.bin");

	if (start == 0) {
		Startup(CurrentChar, 0);
		start = 1;
	}
	int option = MainMenu();
	if (option == 0) {
		LocalMPOptions();
		main();
	}
	else if (option == 2) {
		MultiplayerConnect(CurrentChar,lbdata);
		main();
	}
	else if (option == 3) {
		RenderLeaderBoards(*lbdata);
		main();
	}
	else {
		exit(0);
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
