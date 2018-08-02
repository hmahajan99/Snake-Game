#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

enum Directions{
	STOP,LEFT,RIGHT,UP,DOWN
};

Directions dir;

struct Tail {
	int x;
	int y;
};

bool gameOver;
int gameSpeed;
int totWidth;
int totHeight;
int score;
bool warp;
int x, y, fruitX, fruitY;
Tail snakeTail[100];

void Start() {
	gameOver = false;
	totWidth = 40;  // standard 40
	totHeight = 20;   // standard 20
	dir = STOP;
	x = totWidth / 2;
	y = totHeight / 2;
	srand(time(0));
	fruitX = rand() % (totWidth - 4) + 2;
	fruitY = rand() % (totHeight - 2) + 1;
	gameSpeed = 100;
	score = 0;
	warp = true; //Set to false if don't want snake to warp
}


bool inSnakeTail(int i, int j) {
	for (int k = 0; k < score; k++) {
		if (snakeTail[k].x == j&&snakeTail[k].y == i) {
			return true;
		}
	}
	return false;
}


void Draw() {

	system("cls");

	cout << "SCORE : " << score<<endl;

	for (int i = 0; i < totWidth; i++) {
		cout << "#";
	} cout << endl;

	for (int i = 1 ; i <= totHeight -2 ; i++)  // +Y
	{
		for (int j = 0; j < totWidth; j++)  // +X
		{
			if (j == 0 || j == totWidth - 1 || j == 1 || j == totWidth - 2) {
				cout << "#";
			}

			else if (i == fruitY&&j == fruitX) {
				cout << "F";
			}

			else if (i == y&&j == x) {
				cout << "O";
			}

			else if (inSnakeTail(i, j)) {
				cout << "o";
			}

			else {
				cout << " ";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < totWidth; i++) {
		cout << "#";
	} cout << endl;

	if (gameOver) {
		cout << "---------------------GAMEOVER---------------------";
	}

}

void UpdateSnakeTail() {
	if (score >= 1) {

		for (int i = score - 1; i >= 1; i--) {
			snakeTail[i].x = snakeTail[i - 1].x;
			snakeTail[i].y = snakeTail[i - 1].y;
		}

		snakeTail[0].x = x;
		snakeTail[0].y = y;
	}
}

void UpdateSnake() {

	UpdateSnakeTail();

	switch (dir) {
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	}

}

void Update() {

	//WARP
	if (warp) {
		if (x <= 1) {
			x = totWidth - 3;
		}
		if (x > totWidth - 3) {
			x = 2;
		}
		if (y <= 0) {
			y = totHeight - 2;
		}
		if (y > totHeight - 2) {
			y = 1;
		}
	}


	//GAMEOVER
	if (!warp) {
		if (x <= 1 || y <= 0 || x > totWidth - 3 || y > totHeight - 2) {
			gameOver = true;
		}
	}

	for (int k = 0; k < score; k++) {
		if (snakeTail[k].x == x&&snakeTail[k].y == y) {
			gameOver = true;
		}
	}


	// INPUT
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir= UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		}
	}

	UpdateSnake();

	//EAT
	if (x == fruitX&&y == fruitY) {
		score++;
		fruitX = rand() % (totWidth - 4) + 2;
		fruitY = rand() % (totHeight - 2) + 1;
	}

}

int main(){

	Start();

	while (!gameOver) {

		Update();
		Draw();
		Sleep(gameSpeed);
	}

	Draw();
	getch();
	getch();
	getch();
    return 0;
}
