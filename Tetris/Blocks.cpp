#include <assert.h>
#include "Blocks.h"

void BlockInit(int** gameMatrix, int newX, int newY, int newrot, int val) {
	
	if (newX >= 0 && newY >= 0 && newrot == 0) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[1 + newX][1 + newY] = val;
		gameMatrix[2 + newX][1 + newY] = val;
		gameMatrix[3 + newX][1 + newY] = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 1) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[1 + newX][0 + newY] = val;
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[0 + newX][2 + newY] = val;
		gameMatrix[0 + newX][3 + newY] = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 2) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[1 + newX][0 + newY] = val;
		gameMatrix[2 + newX][0 + newY] = val;
		gameMatrix[3 + newX][0 + newY] = val;
		gameMatrix[3 + newX][1 + newY] = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 3) {
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[1 + newX][1 + newY] = val;
		gameMatrix[2 + newX][1 + newY] = val;
		gameMatrix[3 + newX][1 + newY] = val;
		gameMatrix[3 + newX][0 + newY] = val;
	}

}

int Block4x4(int** gameMatrix, int *DX, int *DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor) { // mode 0 clear blks, 1 add blks

	int DirX = *DX;
	int DirY = *DY;
	int rot = *RT;
	
	if (DirX >= 0 && DirY >= 0) {
		if (rot == 0) {
			if (DirX > 6) {
				*DX = 6;
				DirX = 6;
			}

			BlockInit(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[2 + DirX][1 + DirY] == 0 &&
				gameMatrix[3 + DirX][1 + DirY] == 0) {

				BlockInit(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				BlockInit(gameMatrix, prevX, prevY, prevrot, 1);

				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}



		if (rot == 1) {
			if (DirX > 8) {
				*DX = 8;
				DirX = 8;
			}

			BlockInit(gameMatrix, prevX, prevY, prevrot, 0);
			
			if (gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[0 + DirX][2 + DirY] == 0 &&
				gameMatrix[0 + DirX][3 + DirY] == 0) {

				BlockInit(gameMatrix, DirX, DirY, rot, 1);

				return 0;
			}

			else {

				BlockInit(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}


				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

		if (rot == 2) {
			if (DirX > 6) {
				*DX = 6;
				DirX = 6;
			}
			BlockInit(gameMatrix, prevX, prevY, prevrot, 0);
			
			if (gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[2 + DirX][0 + DirY] == 0 &&
				gameMatrix[3 + DirX][0 + DirY] == 0 &&
				gameMatrix[3 + DirX][1 + DirY] == 0) {

				BlockInit(gameMatrix, DirX, DirY, rot, 1);

				return 0;
			}

			else {

				BlockInit(gameMatrix, prevX, prevY, prevrot, 1);

				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

		if (rot == 3) {
			if (DirX > 6) {
				*DX = 6;
				DirX = 6;
			}
			
			BlockInit(gameMatrix, prevX, prevY, prevrot, 0);
			if (gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[2 + DirX][1 + DirY] == 0 &&
				gameMatrix[3 + DirX][1 + DirY] == 0 &&
				gameMatrix[3 + DirX][0 + DirY] == 0) {

				BlockInit(gameMatrix, DirX, DirY, rot, 1);

				return 0;
			}

			else {

				BlockInit(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

	}
	return 1;
}

void BlockInit4x1(int** gameMatrix, int newX, int newY, int newrot, int val) {

	if (newX >= 0 && newY >= 0 && newrot == 0) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[1 + newX][0 + newY] = val;
		gameMatrix[2 + newX][0 + newY] = val;
		gameMatrix[3 + newX][0 + newY] = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 1) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[0 + newX][2 + newY] = val;
		gameMatrix[0 + newX][3 + newY] = val;
	}

}

int Block4x1(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor) {

	if (*RT > 1) {
		*RT = 0;
		prevrot = 1;
	}

	int DirX = *DX;
	int DirY = *DY;
	int rot = *RT;

	if (DirX >= 0 && DirY >= 0) {
		
		if (rot == 0) {
			if (DirX > 6) {
				*DX = 6;
				DirX = 6;
			}
			BlockInit4x1(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[2 + DirX][0 + DirY] == 0 &&
				gameMatrix[3 + DirX][0 + DirY] == 0) {

				BlockInit4x1(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {

				BlockInit4x1(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
				
				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}


		if (rot == 1) {
			BlockInit4x1(gameMatrix, prevX, prevY, prevrot, 0);
			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[0 + DirX][2 + DirY] == 0 &&
				gameMatrix[0 + DirX][3 + DirY] == 0) {

				BlockInit4x1(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				
				BlockInit4x1(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

	}
	return 1;
}

int Block2x2(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* TimeFactor) {

	int DirX = *DX;
	int DirY = *DY;

	if (DirX >= 0 && DirY >= 0) {
		if (DirX > 8) {
			*DX = 8;
			DirX = 8;
		}

		if (prevX >= 0 && prevY >= 0) {
			gameMatrix[0 + prevX][0 + prevY] = 0;
			gameMatrix[0 + prevX][1 + prevY] = 0;
			gameMatrix[1 + prevX][0 + prevY] = 0;
			gameMatrix[1 + prevX][1 + prevY] = 0;
		}

		if (
			gameMatrix[0 + DirX][0 + DirY] == 0 &&
			gameMatrix[0 + DirX][1 + DirY] == 0 &&
			gameMatrix[1 + DirX][0 + DirY] == 0 &&
			gameMatrix[1 + DirX][1 + DirY] == 0) {

			gameMatrix[0 + DirX][0 + DirY] = 1;
			gameMatrix[0 + DirX][1 + DirY] = 1;
			gameMatrix[1 + DirX][0 + DirY] = 1;
			gameMatrix[1 + DirX][1 + DirY] = 1;
			return 0;
		}
		else {
			if (prevX >= 0 && prevY >= 0) {
				gameMatrix[0 + prevX][0 + prevY] = 1;
				gameMatrix[0 + prevX][1 + prevY] = 1;
				gameMatrix[1 + prevX][0 + prevY] = 1;
				gameMatrix[1 + prevX][1 + prevY] = 1;
			}

			if (prevX != DirX) {
				*DX = prevX;
				DirX = prevX;

				*DY = prevY;
				DirY = prevY;
				*TimeFactor = -1;
				return 0;
			}
		}
	}
	return 1;
}

void BlockS1Init(int** gameMatrix, int newX, int newY, int newrot, int val) {

	if (newX >= 0 && newY >= 0 && newrot == 0) {
		gameMatrix[0 + newX][1 + newY]  = val;
		gameMatrix[1 + newX][1 + newY]  = val;
		gameMatrix[1 + newX][0 + newY]  = val;
		gameMatrix[2 + newX][0 + newY]  = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 1) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[1 + newX][1 + newY] = val;
		gameMatrix[1 + newX][2 + newY] = val;
	}

}

int BlockS1(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor) {

	if (*RT > 1) {
		*RT = 0;
		prevrot = 1;
	}

	int DirX = *DX;
	int DirY = *DY;
	int rot = *RT;

	if (DirX >= 0 && DirY >= 0) {

		if (rot == 0) {
			if (DirX > 7) {
				*DX = 7;
				DirX = 7;
			}
			BlockS1Init(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[2 + DirX][0 + DirY] == 0) {

				gameMatrix[0 + DirX][1 + DirY] = 1;
				gameMatrix[1 + DirX][1 + DirY] = 1;
				gameMatrix[1 + DirX][0 + DirY] = 1;
				gameMatrix[2 + DirX][0 + DirY] = 1;
				return 0;
			}
			else {
				
				BlockS1Init(gameMatrix, prevX, prevY, prevrot, 1);

				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}


		if (rot == 1) { // <== 
			if (DirX > 8) {
				*DX = 8;
				DirX = 8;
			}
			BlockS1Init(gameMatrix, prevX, prevY, prevrot, 0);
			
			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][2 + DirY] == 0) {

				gameMatrix[0 + DirX][0 + DirY] = 1;
				gameMatrix[0 + DirX][1 + DirY] = 1;
				gameMatrix[1 + DirX][1 + DirY] = 1;
				gameMatrix[1 + DirX][2 + DirY] = 1;
				return 0;
			}
			else {
				BlockS1Init(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

	}
	return 1;
}

void BlockS2Init(int** gameMatrix, int newX, int newY, int newrot, int val) {

	if (newX >= 0 && newY >= 0 && newrot == 0) {
		gameMatrix[0 + newX][0 + newY] = val;
		gameMatrix[1 + newX][0 + newY] = val;
		gameMatrix[1 + newX][1 + newY] = val;
		gameMatrix[2 + newX][1 + newY] = val;
	}

	if (newX >= 0 && newY >= 0 && newrot == 1) {
		gameMatrix[1 + newX][0 + newY] = val;
		gameMatrix[0 + newX][1 + newY] = val;
		gameMatrix[1 + newX][1 + newY] = val;
		gameMatrix[0 + newX][2 + newY] = val;
	}

}

int BlockS2(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor) {

	if (*RT > 1) {
		*RT = 0;
		prevrot = 1;
	}

	int DirX = *DX;
	int DirY = *DY;
	int rot = *RT;

	if (DirX >= 0 && DirY >= 0) {

		if (rot == 0) {
			if (DirX > 7) {
				*DX = 7;
				DirX = 7;
			}
			BlockS2Init(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[2 + DirX][1 + DirY] == 0) {

				BlockS2Init(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {

				BlockS2Init(gameMatrix, prevX, prevY, prevrot, 1);

				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}


		if (rot == 1) {
			if (DirX > 8) {
				*DX = 8;
				DirX = 8;
			}
			BlockS2Init(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[0 + DirX][2 + DirY] == 0) {

				BlockS2Init(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				BlockS2Init(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

	}
	return 1;
}

void BlockTInit(int** gameMatrix, int DirX, int DirY, int Dirrot, int val) {

	if (DirX >= 0 && DirY >= 0 && Dirrot == 0) { // inv T
		gameMatrix[0 + DirX][1 + DirY] = val;
		gameMatrix[1 + DirX][0 + DirY] = val;
		gameMatrix[1 + DirX][1 + DirY] = val;
		gameMatrix[2 + DirX][1 + DirY] = val;
	}

	if (DirX >= 0 && DirY >= 0 && Dirrot == 1) { // T
		gameMatrix[0 + DirX][1 + DirY] = val;
		gameMatrix[1 + DirX][2 + DirY] = val;
		gameMatrix[1 + DirX][1 + DirY] = val;
		gameMatrix[2 + DirX][1 + DirY] = val;
	}

	if (DirX >= 0 && DirY >= 0 && Dirrot == 2) { // I-
		gameMatrix[0 + DirX][0 + DirY] = val;
		gameMatrix[0 + DirX][1 + DirY] = val;
		gameMatrix[0 + DirX][2 + DirY] = val;
		gameMatrix[1 + DirX][1 + DirY] = val;
	}
	
	if (DirX >= 0 && DirY >= 0 && Dirrot == 3) { //-I
		gameMatrix[0 + DirX][1 + DirY] = val;
		gameMatrix[1 + DirX][0 + DirY] = val;
		gameMatrix[1 + DirX][1 + DirY] = val;
		gameMatrix[1 + DirX][2 + DirY] = val;
	}
}

int BlocksT(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor) {

	int DirX = *DX;
	int DirY = *DY;
	int rot = *RT;

	if (DirX >= 0 && DirY >= 0) {

		if (rot == 0) {
			if (DirX > 7) {
				*DX = 7;
				DirX = 7;
			}
			BlockTInit(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[2 + DirX][1 + DirY] == 0) {

				BlockTInit(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {

				BlockTInit(gameMatrix, prevX, prevY, prevrot, 1);

				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}


		if (rot == 1) {
			if (DirX > 7) {
				*DX = 7;
				DirX = 7;
			}
			BlockTInit(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][2 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[2 + DirX][1 + DirY] == 0) {

				BlockTInit(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				BlockTInit(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

		if (rot == 2) {

			BlockTInit(gameMatrix, prevX, prevY, prevrot, 0);
			if (DirX > 8) {
				*DX = 8;
				DirX = 8;
			}
			if (
				gameMatrix[0 + DirX][0 + DirY] == 0 &&
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[0 + DirX][2 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0) {

				BlockTInit(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				BlockTInit(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

		if (rot == 3) {
			if (DirX > 8) {
				*DX = 8;
				DirX = 8;
			}
			BlockTInit(gameMatrix, prevX, prevY, prevrot, 0);

			if (
				gameMatrix[0 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][0 + DirY] == 0 &&
				gameMatrix[1 + DirX][1 + DirY] == 0 &&
				gameMatrix[1 + DirX][2 + DirY] == 0) {

				BlockTInit(gameMatrix, DirX, DirY, rot, 1);
				return 0;
			}
			else {
				BlockTInit(gameMatrix, prevX, prevY, prevrot, 1);
				if (prevX != DirX) {
					*DX = prevX;
					DirX = prevX;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}

				if (prevrot != rot) {
					*RT = prevrot;
					rot = prevrot;

					*DY = prevY;
					DirY = prevY;
					*TimeFactor = -1;
					return 0;
				}
			}
		}

	}

	return 1;
}