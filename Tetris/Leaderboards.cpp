#include "Leaderboards.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
PlayerStats* CurrentPlayer = NULL;


void SearchLB(Leaderboards collection) {
	system("CLS");
	std::cout << "Search for: ";

	std::string search;
	std::getline(std::cin, search);
	collection.Search(search.c_str());

}

void LocateUIDLB(Leaderboards collection) {
	system("CLS");
	std::cout << "Enter the player's UID here: ";

	int uid;
	string uidStr;
	std::getline(std::cin, uidStr);

	bool isDig = true;
	for (unsigned int i = 0; i < uidStr.size(); i++) {
		if (!isdigit(uidStr[i]))
			isDig = false;

	}
	
	std::stringstream uidStream;
	uidStream << uidStr;
	uidStream >> uid;

	collection.LocateUID(uid);
}

void RenderLeaderBoards(Leaderboards collection) {

	int offset = 0;
	int Selection = 0;
	int cursor = 0;
	int prevCursor = -1;
	int displaymode = 0;
	
	int NOTrender = -1;
	char input = 'N';
	
	while (input != 27) {
		if (prevCursor != cursor) {
			system("CLS");
			RenderColor(94);
			std::cout << "||=====================LEADERBOARDS======================||\n";
			RenderColor();
			std::cout << "||Name:            |UID:             |Score:             ||\n";
			std::cout << "||-------------------------------------------------------||\n";
			int size = collection.LeaderboardScores.size() - 1;
			NOTrender = -1;

			for (int i = 0; i < 9; i++) {
				if (i == cursor)
					std::cout << ">>";
				else
					std::cout << "||";

				int index = i + offset;

				if (index < collection.LeaderboardScores.size()) {
					if (collection.LeaderboardScores[size - index].Connector == -1 && displaymode == 2)
						std::cout << collection.LeaderboardScores[size - index].GetUserNameT() << "  |  " << collection.LeaderboardScores[size - index].GetUID() << "  |  " << collection.LeaderboardScores[size - index].GetHighScore() << '\n';

					else if (collection.LeaderboardScores[size - index].Connector >= 0 && displaymode == 1)
						std::cout << collection.LeaderboardScores[size - index].GetUserNameT() << "  |  " << collection.LeaderboardScores[size - index].GetUID() << "  |  " << collection.LeaderboardScores[size - index].GetHighScore() << '\n';

					else if (displaymode == 0)
						std::cout << collection.LeaderboardScores[size - index].GetUserNameT() << "  |  " << collection.LeaderboardScores[size - index].GetUID() << "  |  " << collection.LeaderboardScores[size - index].GetHighScore() << '\n';

					else {
						std::cout << "\n";
						if (i == cursor)
							NOTrender = cursor;
					}
				}
				else
					std::cout << "\n";
			}
			RenderColor(94);
			std::cout << "||=======================================================||\n\n";
			RenderColor();

			int pointer = (cursor + offset);
			if (pointer < collection.LeaderboardScores.size() && cursor != NOTrender) {
				RenderColor(93);
				std::cout << "||=======================================================||\n";
				RenderColor();
				std::cout << "||Player: " << collection.LeaderboardScores[size - (cursor + offset)].GetUserNameT() << "\n";
				std::cout << "||Score: " << collection.LeaderboardScores[size - (cursor + offset)].GetHighScore() << "\n";
				std::cout << "||UID: " << collection.LeaderboardScores[size - (cursor + offset)].GetUID() << "\n";
				std::cout << "||Wins/Losses: " << collection.LeaderboardScores[size - (cursor + offset)].getKD()[0] << "/" << collection.LeaderboardScores[size - (cursor + offset)].getKD()[1] << '\n';
				RenderColor(93);
				std::cout << "||=======================================================||\n";
				RenderColor();
			}


			prevCursor = cursor;

			if (Selection == 0) {
				std::cout << " [Locate by name]         Locate by UID";

				if (displaymode == 0) {
					std::cout << "          <MODE: ALL> ";
				}
				if (displaymode == 1) {
					std::cout << "          <MODE: REMOTE> ";
				}
				if (displaymode == 2) {
					std::cout << "          <MODE: LOCAL> ";
				}

				if (input == 'e') {
					SearchLB(collection);
					input = 'N';

					prevCursor = -1;
				}
			}
			if (Selection == 1) {
				std::cout << "  Locate by name         [Locate by UID]";

				if (displaymode == 0) {
					std::cout << "          <MODE: ALL> ";
				}
				if (displaymode == 1) {
					std::cout << "          <MODE: REMOTE> ";
				}
				if (displaymode == 2) {
					std::cout << "          <MODE: LOCAL> ";
				}

				if (input == 'e') {
					LocateUIDLB(collection);
					input = 'N';

					prevCursor = -1;
				}
			}

		}

		if (_kbhit()) {

			input = _getch();
			if (input == 'a' || input == 'A')
				if (Selection > 0)
					Selection--;

			if (input == 'd' || input == 'D')
				if (Selection < 1)
					Selection++;

			if (input == 'w' || input == 'W')
				if (cursor > 0)
					cursor--;
				else
					if (offset > 0) {
						offset--;
					}

			if (input == 's' || input == 'S')
				if (cursor < 8)
					cursor++;
				else
					offset++;

			if (input == 'f' || input == 'F')
				if (displaymode < 2)
					displaymode++;
				else
					displaymode = 0;


			prevCursor = -1;
		}
	}
}