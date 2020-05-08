#pragma once
enum Blocks {
	EMPTY,
	Square,
	LSHAPE,
	RectangleT,
	S1,
	S2,
	TStar
};

int Block4x4(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor);
int Block2x2(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* TimeFactor);
int Block4x1(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor);
int BlockS1(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor);
int BlockS2(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor);
int BlocksT(int** gameMatrix, int* DX, int* DY, int prevX, int prevY, int* RT, int prevrot, int* TimeFactor);