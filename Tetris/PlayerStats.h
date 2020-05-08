#pragma once
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class PlayerStats
{
private:
	string UserName;
	int UID = 1;
	int HighScore = 0;
	int Wins = 0;
	int Losses = 0;

	int storemc = 0; // Reduces tampering.
public:
	int Height = 14;
	int LinesRm = 0;

	int Connector = -1;
	void assignName(const char* name) {
		UserName = name;
	}

	void generateUID() {
		srand(time(NULL));
		int gen = rand();
		if (gen == 0)
			generateUID();
		else
			UID = gen;
	}
	
	void SetHighScore(int hscore) {
		HighScore = hscore;
		storemc = (HighScore * UID);
		storemc += (Wins + Losses);
	}

	int GetHighScore() {
		int testscore = HighScore;
		HighScore = (storemc - (Wins + Losses));
		HighScore = HighScore / UID;
		if (HighScore == testscore)
			return HighScore;
		else
			return -1;
	}

	std::string GetUserNameT() {
		return UserName;
	}
	
	int GetUID() {
		return UID;
	}
	
	int* getKD() {
		int KD[2];
		KD[0] = Wins;
		KD[1] = Losses;
		return KD;
	}

	void AddWin() {
		Wins++;
		Height = 14;
		LinesRm = 0;
	}

	void AddLoss() {
		Losses++;
		Height = 14;
		LinesRm = 0;
	}
	
	PlayerStats() {
		assignName("Username0X5");
		generateUID();
	}

	PlayerStats(const char* UserName) {
		assignName(UserName);
		generateUID();
	}
	
};

