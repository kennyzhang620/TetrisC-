#include <iostream>
#include <Windows.h>
#include <Mmsystem.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <conio.h>
#include "Blocks.h"
#include "DIsplay.h"

class TetrisObj {
public:
	int maxX = 31;
	int maxY = 31;
	int** gameMatrix = new int* [maxX];

	int Score = 0;
	int HighScore = 0;
	int TotalTimeElapsed = 0;
	int FixedTime = 350;
	int TimeFactor = 350;

	int GameState = 0; // 0 running 1 ended.

	int Level = 0;
	int maxLevel = INT32_MAX;
	Blocks prevBlock = EMPTY;
	Blocks currentBlock = EMPTY;
	int numBlocks = 6;
	int currX, prevX, prevY = 0;
	int currY = -2;
	int Rotation = 0, prevRot = 0; // 0 normal 1

	int SignalStrength = -1;
	int prevSignal = -1;
	// ANSI Enhanced Features
	int fg = 91;
	int bg = 101;

	void cls()
	{
			COORD cursorPosition;	
			cursorPosition.X = 0;	
			cursorPosition.Y = 0;	
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	}

	void RandomizeColor(int* color, int* color2) {
		uint8_t selection = rand() % 2;

			*color = rand() % 7;
			*color2 = *color + 10;
		
		if (*color != 0) {
			if (selection == 0) {
				*color += 30;
					*color2 += 30;
			}
			else {
				*color += 90;
				*color2 += 90;
			}
		}
		else {
			RandomizeColor(color, color2);
		}
	}

	void flushMatrix() {
		for (int y = 0; y < maxY; y++) {
			for (int x = 0; x < maxX; x++) {
				gameMatrix[x][y] = 0; // Represent a empty block.
			}
		}
	}

	void initMatrix() {
		for (int i = 0; i < maxY; i++) {
			gameMatrix[i] = new int[maxY];
		}

		for (int y = 0; y < maxY; y++) {
			for (int x = 0; x < maxX; x++) {
				gameMatrix[x][y] = 0; // Represent a empty block.


				if (x == 10)
					gameMatrix[x][y] = 2;

				if (y >= 9 + 10)
					gameMatrix[x][y] = 2; // Represents out of bounds.
			}
		}
	}

	void freeMatrix() {
		for (int i = 0; i < maxY; i++) {
			if (gameMatrix[i] != NULL)
				delete gameMatrix[i];
		}

		if (gameMatrix != NULL)
			delete gameMatrix;
	}

	TetrisObj() {
		initMatrix();
	}

	~TetrisObj() {
		freeMatrix();
	}

	void DropfromPoint(int yLevel) {
		for (int y = yLevel; y >= 0; y--) {
			for (int x = 0; x < 10; x++) {
				if (gameMatrix[x][y] == 1) {
					gameMatrix[x][y] = 0; // Represent a empty block.

					if (y + 1 < 9 + 10)
						gameMatrix[x][y + 1] = 1;
				}
			}
		}
	}

	int Display() {  /////////////////////////////////////////////////////////

		if (((SignalStrength <= prevSignal - 20 || SignalStrength >= prevSignal + 20) && SignalStrength >= 0) || SignalStrength <= 0 && prevSignal != -1) {
			system("CLS");

			if (SignalStrength <= 0)
				prevSignal = -1;
		}
		if (SignalStrength >= 0 && SignalStrength < 20) {
			RenderColor(91);
			std::cout << "[     ]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}
		else if (SignalStrength >= 20 && SignalStrength < 40) {
			RenderColor(91);
			std::cout << "[#    ]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}
		else if (SignalStrength >= 40 && SignalStrength < 60) {
			RenderColor(91);
			std::cout << "[##   ]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}
		else if (SignalStrength >= 60 && SignalStrength < 80) {
			RenderColor(93);
			std::cout << "[###  ]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}
		else if (SignalStrength >= 80 && SignalStrength < 100) {
			RenderColor(92);
			std::cout << "[#### ]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}
		else if (SignalStrength >= 100) {
			RenderColor(92);
			std::cout << "[#####]\n";
			RenderColor();
			prevSignal = SignalStrength;
		}

		RenderColor(93, 102);
		std::cout << "\n=======================TETRIS C++!========================"  << '\n';
		RenderColor();

		for (int y = 0 + 5; y < 20; y++) {
			int blocksXRow = 0;
			//if (y < 10 + 5)
				//std::cout << y << " ";
			for (int x = 0; x < 20; x++) {
				if (x < 10 && y < 10 + 10) {
					if (gameMatrix[x][y] == 0) {
						RenderColor(30, 40);
						std::cout << "[ ]";
						RenderColor();
					}// Represent a empty block.
					else if (gameMatrix[x][y] == 1) { // Render a X at location. Set blocksXRows++ for that particular row and if >= 10 append to score.
						RenderColor(fg, bg);
						std::cout << "[X]";
						RenderColor();
						blocksXRow++;

						if (blocksXRow >= 10 && (currY >= 9 + 10 || currY == 1)) {
							Score++;

							if (HighScore < Score)
								HighScore = Score;

							if (Score % 5 == 0) {
								Level++;
								FixedTime -= 10;
							}

							blocksXRow = 0;

							for (int fx = 0; fx < 10; fx++) {
								gameMatrix[fx][y] = 0;
							}

							DropfromPoint(y);
						}

					}
					else if (gameMatrix[x][y] == 2) {
						RenderColor(37, 107);
						std::cout << "[O]";
						RenderColor();
					}
				}

				if (y == 0 + 5 && x == 11) {
					std::cout << " CURRENT LEVEL: " << Level;
				}

				if (y == 1 + 5 && x == 11) {
					std::cout << " SCORE: " << Score;
				}
				if (y == 2 + 5 && x == 11) {
					std::cout << " HIGHSCORE: " << HighScore;
				}
			}
			std::cout << "\n";
		}
		RenderColor(93, 102);
		std::cout << "==========================================================";
		RenderColor();

		return 0;
	}

	void refreshDisplay() {
		cls();
		Display();
	}

	void Timer(int Time) { // in ms
		int Elapsed = 0;
		srand(time(NULL));
		while (TotalTimeElapsed != Time && GameState != 2) {
			for (int i = 0; i <= Time * 2; i++) { // 8 with full output

			}
			if (GameState <= 2) {
				TotalTimeElapsed++;
				refreshDisplay();
			}
			else if (SignalStrength < 0) {
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
				std::cout << "||                    GAME PAUSED                        ||\n";
				std::cout << "||                   PRESS E TO EXIT                     ||\n";
				std::cout << "||=======================================================||\n";
			}

			if (currY >= 9 + 10 || currY == -2) {
				if (prevY == 1 && currY == 19)
					GameState++;

				currY = 1;
				// Randomly select another block.
				prevBlock = currentBlock;

				int randVal = rand() % 6;

				if (randVal == 0 && currX < 6)
					currentBlock = LSHAPE;
				if (randVal == 1)
					currentBlock = RectangleT;
				if (randVal == 2)
					currentBlock = Square;
				if (randVal == 3)
					currentBlock = S1;
				if (randVal == 4)
					currentBlock = S2;
				if (randVal == 5)
					currentBlock = TStar;

				RandomizeColor(&fg, &bg);

			}
			else {

				char input = 'N';

				if (_kbhit()) {
					input = _getch();
				}

				prevY = currY;
				prevX = currX;
				prevRot = Rotation;

				if (input == 27) {
					system("CLS");
					if (GameState == 5)
						GameState = 0;
					else
						GameState = 5;
				}

				if ((input == 'e' || input == 'E') && GameState == 5) {
					GameState = 2;
				}

				if (input == 'a' || input == 'A')
					if (currX > 0)
						currX--;

				if (input == 'd' || input == 'D')
					if (currX < 10)
						currX++;

				if (input == 'w' || input == 'W')
					if (Rotation < 3)
						Rotation++;
					else
						Rotation = 0;

				if (input == 's' || input == 'S')
					TimeFactor = 20;
				else
					TimeFactor = FixedTime;

				if (TotalTimeElapsed % (TimeFactor / 20) == 0) {
					currY += 1;
					if (GameState > 0 && (prevY != 1 && prevY != 19))
						if (GameState > 0)
							GameState--;
						else
							GameState = 0;
				}

				if (currentBlock == LSHAPE) {
					if (Block4x4(gameMatrix, &currX, &currY, prevX, prevY, &Rotation, prevRot, &TimeFactor) != 0)
						currY = 19;
				}

				if (currentBlock == Square) {
					if (Block2x2(gameMatrix, &currX, &currY, prevX, prevY, &TimeFactor) != 0) {
						currY = 19;
					}
				}

				if (currentBlock == RectangleT) {
					if (Block4x1(gameMatrix, &currX, &currY, prevX, prevY, &Rotation, prevRot, &TimeFactor) != 0)
						currY = 19;
				}

				if (currentBlock == S1) {
					if (BlockS1(gameMatrix, &currX, &currY, prevX, prevY, &Rotation, prevRot, &TimeFactor) != 0)
						currY = 19;
				}

				if (currentBlock == S2) {
					if (BlockS2(gameMatrix, &currX, &currY, prevX, prevY, &Rotation, prevRot, &TimeFactor) != 0)
						currY = 19;
				}

				if (currentBlock == TStar) {
					if (BlocksT(gameMatrix, &currX, &currY, prevX, prevY, &Rotation, prevRot, &TimeFactor) != 0)
						currY = 19;
				}

				TimeFactor = FixedTime;

			}
		}
	}

	void Run() {
		system("CLS");
		GameState = 0;
		Score = 0;
		currY = -2;
		Timer(3600000);
	}

	void Stop() {
		GameState = 2;
	}

	void Reset() {
		flushMatrix();
		Score = 0;
		HighScore = 0;
		TotalTimeElapsed = 0;
		if (GetColorMode()) {
			FixedTime = 350;
			TimeFactor = 350;
		}
		else {
			FixedTime = 350*2;
			TimeFactor = 350*2;
		}

		GameState = 0; // 0 running 1 ended.

		Level = 0;
		maxLevel = INT32_MAX;
		prevBlock = EMPTY;
		currentBlock = EMPTY;
		numBlocks = 6;
		currX, prevX, prevY = 0;
		currY = -2;
		Rotation = 0, prevRot = 0; // 0 normal 1

		for (int y = 0; y < maxY; y++) {
			for (int x = 0; x < maxX; x++) {
				gameMatrix[x][y] = 0; // Represent a empty block.


				if (x == 10)
					gameMatrix[x][y] = 2;

				if (y >= 9 + 10)
					gameMatrix[x][y] = 2; // Represents out of bounds.
			}
		}

	}
};