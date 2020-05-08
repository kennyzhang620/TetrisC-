#pragma once
#include "PlayerStats.h"
#include <vector>
#include "Tree.h"
#include <unordered_map>
#include <map>
#include <conio.h>
#include <fstream>
#include <iterator>

class Leaderboards
{
public: 
	std::vector<PlayerStats> LeaderboardScores;
	Tree LeaderboardNames;
	std::unordered_map<int, PlayerStats> Leaderboardsmap;

	void InsertLeaderboardSrted(PlayerStats newPlayer) {
		int first = 0;
		int last = LeaderboardScores.size();

		for (int x = first; x < last; x++) {
			int mid = (first + (last)) / 2;
			if (LeaderboardScores[mid].GetHighScore() > newPlayer.GetHighScore()) {
				last = mid;
			}
			if (LeaderboardScores[mid].GetHighScore() <= newPlayer.GetHighScore()) {
				first = mid;
			}
		}

		if (LeaderboardScores.size() <= 0 || LeaderboardScores[first].GetHighScore() >= newPlayer.GetHighScore())
			LeaderboardScores.insert(LeaderboardScores.begin() + first, newPlayer);
		else if (LeaderboardScores[first].GetHighScore() < newPlayer.GetHighScore())
			LeaderboardScores.insert(LeaderboardScores.begin() + first + 1, newPlayer);

		std::pair<int, PlayerStats> insertChar(newPlayer.GetUID(), newPlayer);
		LeaderboardNames.AppendBinTree(newPlayer);
		Leaderboardsmap.insert(insertChar);
	}

	void LocateUID(int UID) {
		std::unordered_map<int, PlayerStats>::iterator data = Leaderboardsmap.find(UID);
		
		if (data == Leaderboardsmap.end()) {
			std::cout << "User with UID: " << UID << " not found.\n";
		}
		else {
			std::cout << "||=======================================================||\n";
			std::cout << "                       PLAYER FOUND!						 \n";
			std::cout << "||=======================================================||\n";
			std::cout << "||Player: " << data->second.GetUserNameT() << "\n";
			std::cout << "||Score: " << data->second.GetHighScore() << "\n";
			std::cout << "||UID: " << data->second.GetUID() << "\n";
			std::cout << "||Wins/Losses: " << data->second.getKD()[0] << "/" << data->second.getKD()[1] << '\n';
			std::cout << "||=======================================================||\n\n";


		}
		std::cout <<     "         Press any key to return to the Leaderboards.		 \n";
		_getch();
	}

	void Search(const char* search) {
		vector<PlayerStats> storeddata;
		PlayerStats searchdata(search);

		int offset = 0;
		int cursor = 0;

		Tree* result = LeaderboardNames.SearchBinTree(searchdata, &storeddata);

		char inputD = 'N';
		while (inputD != 27) {
			system("CLS");
			std::cout << "||======================RESULTS==========================||\n";
			std::cout << "||Name:            |UID:             |Score:             ||\n";
			std::cout << "||-------------------------------------------------------||\n";

			int sizeD = storeddata.size();

			for (int i = 0; i < 9; i++) {
				if (i == cursor)
					std::cout << ">>";
				else
					std::cout << "||";

				int point = i + offset;
				if (point < sizeD)
					std::cout << storeddata[point].GetUserNameT() << "  |  " << storeddata[point].GetUID() << "  |  " << storeddata[point].GetHighScore() << '\n';
				else
					std::cout << "\n";
			}
			std::cout << "||=======================================================||\n";

			int pointerD = (cursor + offset);
			if (pointerD < storeddata.size()) {
				std::cout << "||=======================================================||\n";
				std::cout << "||Player: " << storeddata[pointerD].GetUserNameT() << "\n";
				std::cout << "||Score: " << storeddata[pointerD].GetHighScore() << "\n";
				std::cout << "||UID: " << storeddata[pointerD].GetUID() << "\n";
				std::cout << "||Wins/Losses: " << storeddata[pointerD].getKD()[0] << "/" << storeddata[pointerD].getKD()[1] << '\n';
				std::cout << "||=======================================================||\n";
			}

			if (_kbhit()) {

				inputD = _getch();

				if (inputD == 'w' || inputD == 'W')
					if (cursor > 0)
						cursor--;
					else
						if (offset > 0)
							offset--;

				if (inputD == 's' || inputD == 'S')
					if (cursor < 8)
						cursor++;
					else
						if (offset < 1)
							offset++;
			}
		}
	}

	void SavetoBinary(const char* filename) {
		FILE* savebin = fopen(filename, "w");

		if (savebin != NULL) {
			fwrite(&LeaderboardScores[0], sizeof(PlayerStats), LeaderboardScores.size(), savebin);
			fclose(savebin);
		}
	}
	
	void PopulateBST(int first, int last) {
		if (last <= first)
			return;
		else {
			int mid = (first + last) / 2;
			LeaderboardNames.AppendBinTree(LeaderboardScores[mid]);

			PopulateBST(first, mid);
			PopulateBST(mid+1, last);
		}
	}
	
	void LoadBinary(const char* filename) {
		// open the file:
		FILE* loadbin = fopen(filename, "r");

		if (loadbin != NULL) {
			fseek(loadbin, 0L, SEEK_END);
			size_t filesize = ftell(loadbin)/ sizeof(PlayerStats);
			rewind(loadbin);

			PlayerStats* temp = new PlayerStats[filesize];
			
			fread(temp, sizeof(PlayerStats), filesize, loadbin);

			for (int i = 0; i < filesize; i++) {
				LeaderboardScores.push_back(temp[i]);

				// Populate the hash table.
				std::pair<int, PlayerStats> insertChar(temp[i].GetUID(), temp[i]);
				Leaderboardsmap.insert(insertChar);
			}

			delete[] temp;
			temp = NULL;

			// Populate and autobalance BST using recursion.
			PopulateBST(0, filesize);

			fclose(loadbin);
		}
	}

};

void RenderLeaderBoards(Leaderboards collection);

