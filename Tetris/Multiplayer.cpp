#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "PlayerStats.h"
#include <thread>
#include "DisplayHelper.h"
#include "Leaderboards.h"
#include "DIsplay.h"

PlayerStats* currentPlayer = NULL;
PlayerStats* opponentPlayer = NULL;
Leaderboards* currLeaderboard = NULL;

int prevLineRm = 0;
int maxHeight = 14 + 5;
std::string path;
int currKDS[4] = { 0,0,0,0 };
int prevRand = 0;
int alloc = 0;

int Communicator = 0; // 0 Trans 1 Receive
int GameStateM = 0;

void printSplash() {
	system("CLS");
	std::cout << '\n';
	std::cout << "||=======================================================||\n";
	std::cout << "||                    __________     ";
	RenderColor(97, 104);
	std::cout << "MULTIPLAY"; 
	RenderColor(97, 101);
	std::cout << "ER BATTLES!";
	RenderColor();
	std::cout << "||\n";

	std::cout << "||                    |        |                         ||\n";
	std::cout << "||                    |        |                         ||\n";
	std::cout << "||           _________|________|________                 ||\n";
	std::cout << "||           |        |        |        |                ||\n";
	std::cout << "||           |        |        |        |                ||\n";
	std::cout << "||           ----------------------------                ||\n";
	std::cout << "||                   ";
	RenderColor(94, 103);
	std::cout << "TETRIS IN C++!";
	RenderColor();
	std::cout << "                      ||\n";
	std::cout << "||=======================================================||\n\n";
	
}

void printSplashWin() {
	system("CLS");
	int timeVal = 99999999;
	std::cout << '\n';
	RenderColor(97, 104);
	std::cout << "||=======================================================||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    __________     MULTIPLAYER BATTLES!||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    |        |                         ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    |        |                         ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           _________|________|________                 ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           |        |        |        |                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           |        |        |        |                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           ----------------------------                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                     YOU WON!                          ||\n";
	for (int i = 0; i < timeVal; i++) {}
	RenderColor();
	RenderColor(91);
	std::cout << "||        Congratulations " << currentPlayer->GetUserNameT() << "!\n";
	RenderColor(97, 104);
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||=======================================================||\n\n";
	for (int i = 0; i < timeVal*10; i++) {}
	RenderColor();

}

void printSplashLoss() {
	system("CLS");
	int timeVal = 99999999;
	std::cout << '\n';
	for (int i = 0; i < timeVal; i++) {}
	RenderColor(97, 101);
	std::cout << "||=======================================================||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    __________     MULTIPLAYER BATTLES!||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    |        |                         ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                    |        |                         ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           _________|________|________                 ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           |        |        |        |                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           |        |        |        |                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||           ----------------------------                ||\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||                     YOU LOST!                         ||\n";
	for (int i = 0; i < timeVal; i++) {}
	RenderColor();
	RenderColor(94);
	std::cout << "||        Congratulations " << opponentPlayer->GetUserNameT() << "!\n";
	RenderColor(97, 101);
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||=======================================================||\n\n";
	for (int i = 0; i < timeVal*10; i++) {}
	RenderColor();

}

void AddLayer(TetrisObj* multiplayergame, int prevLayer, int Layer) {
	for (int y = prevLayer; y >= Layer; y--) {
		for (int x = 0; x < 20; x++) {
			multiplayergame->gameMatrix[x][y] = 2;
		}
	}
}

void Update(TetrisObj* multiplayergame) {
	int TimeOut = 0;
	while (GameStateM == 0 && TimeOut < 3000)  {
	//	for (int i = 0; i <= Time * 2; i++) { // 8 with full output
			FILE* progressFile;
			FILE* progressFile2;

			if (Communicator == 0) {
				progressFile = fopen("player2.bin", "r");
				progressFile2 = fopen("player1.bin", "w");
			}
			else {
				progressFile = fopen((path + "/player1.bin").c_str(), "r");
				progressFile2 = fopen((path + "/player2.bin").c_str(), "w");
			}

			if (progressFile != NULL) {
				fread(opponentPlayer, sizeof(PlayerStats), 1, progressFile);
				//	fclose(progressFile);
			}
			else {
				GameStateM = -1;
			}

			if (progressFile2 != NULL) {
				fwrite(currentPlayer, sizeof(PlayerStats), 1, progressFile2);
				//	fclose(progressFile2);
			}
			else {
				GameStateM = -1;
			}

			if (progressFile != NULL)
				fclose(progressFile);

			if (progressFile2 != NULL)
				fclose(progressFile2);

			currentPlayer->LinesRm = multiplayergame->Score;
			currentPlayer->Connector = rand();

			if (opponentPlayer->Connector != prevRand) {
				TimeOut = 0;
				prevRand = opponentPlayer->Connector;
			}
			else {
				TimeOut++;
			}

			multiplayergame->SignalStrength = 100 - TimeOut;

			if (opponentPlayer->getKD()[1] > currKDS[3]) {
				GameStateM = 1;

			}

			if (opponentPlayer->LinesRm > prevLineRm) {
				AddLayer(multiplayergame, maxHeight - prevLineRm, maxHeight - opponentPlayer->LinesRm);
				prevLineRm = opponentPlayer->LinesRm;
			}
		//}
	}
	if (TimeOut >= 3000) {
		GameStateM = -1;
	}
	multiplayergame->Stop();  // Stops the game
}

void BattleAnimation(TetrisObj* multiplayergame) {
	int timeVal = 99999999;
	PlaySound(TEXT("alt1.wav"), NULL, SND_LOOP | SND_ASYNC);
	system("CLS");
	std::cout << '\n';
	RenderColor(97, 104);
	std::cout << "||=======================================================||\n";
	RenderColor();
	for (int i = 0; i < timeVal; i++) {}
	RenderColor(94);
	std::cout << "||Player: " << currentPlayer->GetUserNameT() <<"\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||Score: " << currentPlayer->GetHighScore() << "\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||UID: " << currentPlayer->GetUID() << "\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||Wins/Losses: " << currentPlayer->getKD()[0] << "/" << currentPlayer->getKD()[1] << '\n';
	for (int i = 0; i < timeVal; i++) {}
	RenderColor();
	RenderColor(97, 104);
	std::cout << "||=============<V/S>=VERSUS=";
	RenderColor(97, 101);
	std::cout << "PLAYER=<V/S>=================||\n";
	RenderColor();
	RenderColor(91);
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||Player: " << opponentPlayer->GetUserNameT() << "\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||Score: " << opponentPlayer->GetHighScore() << "\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||UID: " << opponentPlayer->GetUID() << "\n";
	for (int i = 0; i < timeVal; i++) {}
	std::cout << "||Wins/Losses: " << opponentPlayer->getKD()[0] << "/" << opponentPlayer->getKD()[1] << '\n';
	for (int i = 0; i < timeVal; i++) {}
	RenderColor();
	RenderColor(97, 104);
	std::cout << "||=======================================================||\n";
	RenderColor();

	for (int i = 0; i < timeVal*10; i++) {}

	if (GameStateM != -1) {
		currentPlayer->Height = 14;
		system("CLS");
		multiplayergame->Run();
	}
	
	if (GameStateM == 0) {
		currentPlayer->AddLoss();
		printSplashLoss();
		GameStateM = 2;
		std::cout << "\nSaving... Do not exit the application.\n";
		std::cout << "Press any key to continue\n";
		int a = _getch();
	}
	else if (GameStateM == 1) {
		currentPlayer->AddWin();
		printSplashWin();
		std::cout << "\nSaving... Do not exit the application.\n";
		std::cout << "Press any key to continue\n";
		int a = _getch();
	}
	else if (GameStateM == -1) {
		RenderColor(91);
		std::cout << "\nCommunication error. Press any key to continue\n";
		RenderColor();
		int a = _getch();
	}

	std::string writePath = getenv("appdata");
	currLeaderboard->InsertLeaderboardSrted(*opponentPlayer);

	FILE* writeFile = fopen((writePath + "/userdata.bin").c_str(), "w");

	if (writeFile != NULL) {
		fwrite(currentPlayer, sizeof(PlayerStats), 1, writeFile);
		fclose(writeFile);
	}

	currLeaderboard->SavetoBinary("leaderboards.dat");

}
void BattleWrapper(TetrisObj* multiplayergame) {
	std::thread com(Update, multiplayergame);
	std::cout << "Communicating.. Please stand by.\n";
	currentPlayer->Height = 0;

	int Init = 0;
	int Time = 0;
	while (Init == 0 && Time < 1000000000) {
		if (currentPlayer->Height == 0 && opponentPlayer->Height == 0) {
			Init = 1;
		}
		Time++;
	}
	
	if (Time < 1000000000) {
		BattleAnimation(multiplayergame);
	}
	else {
		GameStateM = 1;
		RenderColor(91);
		std::cout << "Connection timed out. Press any key to continue\n";
		RenderColor();
		int a = _getch();
	}

	com.join();
}

void Setup(TetrisObj* multiplayergame) {
	char input = 'N';
	int Selection = 0;
	currKDS[0] = currentPlayer->getKD()[0];
	currKDS[1] = currentPlayer->getKD()[1];

	currKDS[2] = opponentPlayer->getKD()[0];
	currKDS[3] = opponentPlayer->getKD()[1];

	while (input != 'e'&& input != 'E') {
		printSplash();
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring ws(buffer);
		std::string str(ws.begin(), ws.end());

		if (Communicator == 0) {
			RenderColor(91);
			std::cout << "====================PLAYER 2 FOUND!======================||\n";
			RenderColor();
		}
		else {
			RenderColor(94);
			std::cout << "====================PLAYER 1 FOUND!======================||\n";
			RenderColor();
		}
		std::cout << "Name: " << opponentPlayer->GetUserNameT() << '\n';
		std::cout << "HighScore: " << opponentPlayer->GetHighScore() << '\n';
		std::cout << "UID: " << opponentPlayer->GetUID() << '\n';
		std::cout << "Wins: " << opponentPlayer->getKD()[0] << " Losses: " << opponentPlayer->getKD()[1] << '\n';
		std::cout << "\n";

		if (Selection == 0) {
			std::cout << "\n                    <START BATTLE>                       \n";
			std::cout << "                    Starts the battle.                     \n";
		}
		if (Selection == 1) {
			std::cout << "\n                    <BACK TO MENU>                       \n";
			std::cout << "                Returns to the main menu.               \n";
		}

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

	if (Selection == 0) {
		BattleWrapper(multiplayergame);
		input = 'e';
	}
	else {
		input = 'e';
	}
	
}

void Transmitter(TetrisObj* multiplayergame) {
	char input = 'N';
	FILE* detectFile = fopen("player1.bin", "w");
	if (detectFile != NULL) {
		fwrite(currentPlayer, sizeof(PlayerStats), 1, detectFile);
		fclose(detectFile);
	}
	else {
		std::cout << "<FATAL ERROR> Transmitter Error. Please try again later.\n";
		_getch();
	}
	
	while (input != 'e') {
		printSplash();
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring ws(buffer);
		std::string str(ws.begin(), ws.end());

		std::cout << "============AWAITING RESPONSE FROM PLAYER 2...===========||\n";
		std::cout << "For Player 2, input the URL: \n";
		std::cout << str << "\n";
		std::cout << "to connect to this machine.\n";
		std::cout << "\n";
		std::cout << "\n                    <BACK TO MENU>                      \n";
		std::cout << "                Returns to the main menu.               \n";

		FILE* detectFile2 = fopen("player2.bin", "r");
		if (detectFile2 != NULL) {
			input = 'e';
			fread(opponentPlayer, sizeof(PlayerStats), 1, detectFile2);
			fclose(detectFile2);
			Setup(multiplayergame);
		}
		
		if (_kbhit()) {
			input = _getch();
		}
	}
}

void Receiver(TetrisObj* multiplayergame) {
	char input = 'N';

	while (input != 'e') {
		printSplash();
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring ws(buffer);
		std::string str(ws.begin(), ws.end());

		std::cout << "============AWAITING RESPONSE FROM PLAYER 1...===========||\n";
		std::cout << "Input the URL that Player 1 has given you.\n";
		std::cout << "URL to connect to: ";
		std::cin >> path;
		std::cout << "\n";
		std::cout << "             Communicating... Please stand by.             \n";

		FILE* detectFile2 = fopen((path + "/player1.bin").c_str(), "r");
		if (detectFile2 != NULL) {
			input = 'e';
			fread(opponentPlayer, sizeof(PlayerStats), 1, detectFile2);
			fclose(detectFile2);


			FILE* detectFile = fopen((path + "/player2.bin").c_str(), "w");
			if (detectFile != NULL) {
				fwrite(currentPlayer, sizeof(PlayerStats), 1, detectFile);
				fclose(detectFile);
			}

			Setup(multiplayergame);
		}
		else {
			std::cout << "        Connection timed out or does not exist.         \n";
			std::cout << "        Press any key to continue or E to exit.         \n";
			input = _getch();
		}
	}
}

void MultiplayerConnect(PlayerStats* currentChar, Leaderboards* currentLeaderboard, TetrisObj* multiplayergame) {
	currentPlayer = currentChar;
	currLeaderboard = currentLeaderboard;
	currentPlayer->LinesRm = 0;
	currentPlayer->Height = 14;
	
	multiplayergame->Reset();

	if (opponentPlayer != NULL) {
		delete opponentPlayer;
	}

	opponentPlayer = new PlayerStats;
	

	remove("player1.bin");
	remove("player2.bin");
	prevLineRm = 0;
	prevRand = 0;

	Communicator = 0; // 0 Trans 1 Receive
	GameStateM = 0;


	int Selection = 0;
	int prevSelection = -1;
	char input = 'N';
	while (input != 'e' && input != 'E' && input != 27) {
		if (prevSelection != Selection) {
			printSplash();
			std::cout << "||==================CHOOSE A OPTION======================||\n";
			if (Selection == 0) {
				std::cout << "        <TRANSMITTER>            RECEIVER                ";
				std::cout << "\n                     BACK TO MENU                      \n";
				std::cout << "  Choose this option to start the battle as the leader.\n";
				std::cout << "        The recipient must choose RECEIVER.            \n";
			}
			else if (Selection == 1) {
				std::cout << "         TRANSMITTER             <RECEIVER>              ";
				std::cout << "\n                     BACK TO MENU                      \n";
				std::cout << "    Choose this to connect to the leader through a URL.\n";
			}
			else if (Selection == 2) {
				std::cout << "         TRANSMITTER              RECEIVER                ";
				std::cout << "\n                    <BACK TO MENU>                      \n";
				std::cout << "                Returns to the main menu.               \n";
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
				if (Selection < 2)
					Selection++;
		}
	}

	if (Selection == 0) {
		Communicator = 0;
		Transmitter(multiplayergame);
		PlaySound(NULL, NULL, 0);
		MultiplayerConnect(currentChar, currentLeaderboard, multiplayergame);
	}
	if (Selection == 1) {
		Communicator = 1;
		Receiver(multiplayergame);
		PlaySound(NULL, NULL, 0);
		MultiplayerConnect(currentChar, currentLeaderboard, multiplayergame);
	}

	
	if (opponentPlayer != NULL && GameStateM != 0)
		delete opponentPlayer;
	
}