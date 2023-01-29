#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>

#define _WIN32_WINNT 0x0502
#define SCREEN_WIDTH 80
#define SCREEN_WIDTH_ 116
#define SCREEN_HEIGHT 26
#define SCREEN_HEIGHT_ 30
#define WIN_WIDTH 76
#define MENU_WIDTH 40
#define GAP_SIZE 7
#define Enemy_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[10];
int enemyX[10];
int enemyNext = 0;
bool enemyFlag[10];
int enemyType[10];
int bulletTime = 0;
bool bullet = 0;
float mnoznik = 1;
int labelCount = 0;
int piecPos = WIN_WIDTH / 2;
int score = 0;
int bullets[20][4];
int bulletsLife[20];
int bIndex = 0;

int label[18][2] = {
	0,18,0,20,0,20,0,20,0,20,0,20,0,18,0,16,0,14,0,12,0,12,0,12,0,12,0,12,0,12,0,12,0,12,0,12
};
char piec[5][8] = { ' ','<',' ',' ',' ','>',' ',
				   ' ', ' ','±',' ',' ',' ','±',' ',
					' ','/','±',' ',' ',' ','±',92,
					' ','±',' ','A','G','H',' ','±',
					' ',92,'±','_','_','_','±','/',
};

void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] < arr[j + 1])
				swap(arr[j], arr[j + 1]);
}
void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
void drawBorder_MENU() {
	for (int i = 0; i < SCREEN_WIDTH_; i++) {
		gotoxy(i, SCREEN_HEIGHT_ - 1); cout << (char)178 << (char)178 << (char)178 << (char)178;//dolna krawedz
	}
	for (int i = 0; i < SCREEN_HEIGHT_; i++) {
		gotoxy(0, i); cout << (char)178 << (char)178 << (char)178 << (char)178;//lewa krawedz
		gotoxy(SCREEN_WIDTH_, i); cout << (char)178 << (char)178 << (char)178 << (char)178;//prawa krawedz
	}
}
void drawBorder() {
	for (int i = 0; i <= SCREEN_WIDTH_; i++) {
		gotoxy(i, SCREEN_HEIGHT + 3); cout << (char)178 << (char)178 << (char)178 << (char)178;//dolna krawedz
	}

	for (int i = 0; i < SCREEN_HEIGHT + 3; i++) {
		gotoxy(0, i); cout << (char)178 << (char)178 << (char)178 << (char)178;//lewa krawedz
		gotoxy(SCREEN_WIDTH_, i); cout << (char)178 << (char)178 << (char)178 << (char)178;//prawa krawedz
		gotoxy(WIN_WIDTH, i); cout << (char)178 << (char)178 << (char)178 << (char)178;//krawedz menu boczne
	}
}
void drawWielkiPiec() {
	gotoxy(WIN_WIDTH + 4, 5); cout << "                                    ";
	gotoxy(WIN_WIDTH + 4, 6); cout << "           __________               ";
	gotoxy(WIN_WIDTH + 4, 7); cout << "        ||<__________>||            ";
	gotoxy(WIN_WIDTH + 4, 8); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 9); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 10); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 11); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 12); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 13); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 14); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 15); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 16); cout << "        ||            ||            ";
	gotoxy(WIN_WIDTH + 4, 17); cout << "       //              " << (char)92 << (char)92 << "           ";
	gotoxy(WIN_WIDTH + 4, 18); cout << "      //                " << (char)92 << (char)92 << "          ";
	gotoxy(WIN_WIDTH + 4, 19); cout << "     //                  " << (char)92 << (char)92 << "         ";
	gotoxy(WIN_WIDTH + 4, 20); cout << "    ||                    ||        ";
	gotoxy(WIN_WIDTH + 4, 21); cout << "    ||                    ||        ";
	gotoxy(WIN_WIDTH + 4, 22); cout << "    ||                    ||        ";
	gotoxy(WIN_WIDTH + 4, 23); cout << "    ||                    ||        ";
	gotoxy(WIN_WIDTH + 4, 24); cout << "    " << (char)92 << (char)92 << "                    //  O  _  ";
	gotoxy(WIN_WIDTH + 4, 25); cout << "     " << (char)92 << (char)92 << "                  //  <|--|  ";
	gotoxy(WIN_WIDTH + 4, 26); cout << "      " << (char)92 << (char)92 << "________________//    |  |  ";
	gotoxy(WIN_WIDTH + 4, 27); cout << "       " << (char)92 << "________________/    / " << (char)92 << " V  ";
	gotoxy(WIN_WIDTH + 4, 28); cout << "                                    ";
}
//najwa¿niejsza funkcja wizualna
int fillPiec(int type, int labels, int tab[18][2]) {
	for (int i = 0; i < 18; i++)
	{
		//dopasowuje siê do rozmiarów pieca
		gotoxy(WIN_WIDTH + (SCREEN_WIDTH_ - WIN_WIDTH) / 2 - tab[labels - 1][1] / 2, 26 - labels);
		for (int j = 0; j < tab[labels - 1][1]; j++)
		{
			if (type == 0)
			{
				cout << (char)176;
			}
			else {
				cout << (char)177;
			}
		}
	}
	return 0;
}
void genEnemy(int ind, bool bullet) {
	enemyY[ind] = 0;
	enemyX[ind] = 6 + rand() % (WIN_WIDTH - 10);
	int r = rand() % 100;
	if (!bullet)
	{
		if (r < 32)
		{
			enemyType[ind] = 0;
		}
		else if (r >= 32 && r < 65) {
			enemyType[ind] = 1;
		}
		else if (r >= 65 && r < 85)
		{
			enemyType[ind] = 2;
		}
		else
		{
			enemyType[ind] = 3;
		}
	}
	else
	{
		if (r < 20)
		{
			enemyType[ind] = 0;
		}
		else if (r >= 20 && r < 40) {
			enemyType[ind] = 1;
		}
		else if (r >= 40 && r < 90)
		{
			enemyType[ind] = 2;
		}
		else
		{
			enemyType[ind] = 3;
		}
	}
	enemyFlag[ind] = 1;
}
void drawEnemy() {
	for (int i = 0; i < 10; i++)
	{
		if (enemyFlag[i])
		{
			switch (enemyType[i]) {
			case 0://koks
				gotoxy(enemyX[i], enemyY[i]);
				cout << (char)218 << (char)191;
				gotoxy(enemyX[i], enemyY[i] + 1);
				cout << (char)192 << (char)217;
				break;
			case 1://zelazo
				gotoxy(enemyX[i], enemyY[i]);
				cout << (char)201 << (char)187;
				gotoxy(enemyX[i], enemyY[i] + 1);
				cout << (char)200 << (char)188;
				break;
			case 2://uj
				gotoxy(enemyX[i], enemyY[i]);
				cout << (char)85 << (char)74;
				gotoxy(enemyX[i], enemyY[i] + 1);
				cout << (char)158 << (char)158;
				break;
			case 3://bullet
				gotoxy(enemyX[i], enemyY[i] + 1);
				cout << (char)215 << (char)215;
				break;
			}
		}
	}
}
void eraseEnemy() {
	for (int i = 0; i < 10; i++)
	{
		if (enemyFlag[i])
		{
			gotoxy(enemyX[i], enemyY[i]);   cout << "  ";
			gotoxy(enemyX[i], enemyY[i] + 1);   cout << "  ";
			gotoxy(enemyX[i], enemyY[i] + 2);   cout << "  ";
			gotoxy(enemyX[i], enemyY[i] + 3);   cout << "  ";
		}
	}
}
void resetEnemy(int ind) {
	eraseEnemy();
	enemyFlag[ind] = 0;
	enemyY[ind] = 3;
}
void genBullet() {
	bullets[bIndex][0] = 22;
	bullets[bIndex][1] = piecPos + 1;
	bullets[bIndex][2] = 22;
	bullets[bIndex][3] = piecPos + 5;
	bIndex++;
	if (bIndex == 20)
		bIndex = 0;
}
void moveBullet() {
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] > 2)
			bullets[i][0]--;
		else
			bullets[i][0] = 0;

		if (bullets[i][2] > 2)
			bullets[i][2]--;
		else
			bullets[i][2] = 0;
	}
}
void drawBullets() {
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] > 1) {
			gotoxy(bullets[i][1], bullets[i][0]); cout << ".";
			gotoxy(bullets[i][3], bullets[i][2]); cout << ".";
		}
	}
}
void eraseBullets() {
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] >= 1) {
			gotoxy(bullets[i][1], bullets[i][0]); cout << " ";
			gotoxy(bullets[i][3], bullets[i][2]); cout << " ";
		}
	}
}
void eraseBullet(int i) {
	gotoxy(bullets[i][1], bullets[i][0]); cout << " ";
	gotoxy(bullets[i][3], bullets[i][2]); cout << " ";
}
void drawpiec() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			gotoxy(j + piecPos, i + 24); cout << piec[i][j];
		}
	}
}
void erasepiec() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			gotoxy(j + piecPos, i + 24); cout << " ";
		}
	}
}
int collision(int ind) {
	if (enemyX[ind] - piecPos >= 2 && enemyX[ind] - piecPos < 4) {
		return 1;
	}

	return 0;
}
int bulletHit() {
	for (int e = 0; e < 10; e++)
	{
		if (enemyFlag[e])
		{
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 4; j += 2) {
					if (bullets[i][j] != 0) {
						if (bullets[i][j] >= enemyY[e] && bullets[i][j] <= enemyY[e] + 1) {
							if (bullets[i][j + 1] >= enemyX[e] && bullets[i][j + 1] <= enemyX[e] + 4) {
								eraseBullet(i);
								bullets[i][j] = 0;
								if (enemyType[e] == 1 || enemyType[e] == 0)
								{
									score -= 10;
								}
								else if (enemyType[e] == 2) {
									score += 300;
								}
								resetEnemy(e);
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
int highscoreCount() {
	system("cls");
	fstream countOdczyt;
	countOdczyt.open("highscore.txt", ios::in);
	if (!countOdczyt.good())
	{
		cout << "Blad odczytu pliku" << endl;
	}
	int k = 0, l;
	while (countOdczyt.good())
	{
		countOdczyt >> l;
		k++;
	}
	const int K = k;
	countOdczyt.close();
	return K;
}
void highscore(int K) {
	int* scores = new int[K];
	fstream highOdczyt;
	highOdczyt.open("highscore.txt", ios::in);
	for (int i = 0; i < K; i++)
	{
		highOdczyt >> scores[i];
	}
	highOdczyt.close();
	bubbleSort(scores, K);
	cout << "Najlepsze wyniki:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (i < K)
		{
			cout << i + 1 << ".\t" << scores[i] << endl;
		}
	}
	delete[] scores;
	system("pause");
}
void gameover() {
	system("cls");
	fstream zapis;
	zapis.open("highscore.txt", ios::app);
	zapis << endl << score * mnoznik;
	zapis.close();
	cout << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------" << endl << endl;
	cout << "\t\t----- Zdobyte punkty -----" << endl;
	cout << "\t\t\t" << score * mnoznik << endl;
	cout << "\t\t--------------------------" << endl << endl;
	cout << "\t\t----- Jakosc surowki -----" << endl;
	cout << "\t\t\t" << mnoznik / 9.5 * 100 << "%" << endl;
	cout << "\t\tPress any key to go exit.";
	_getch();
	exit(1);
}
void updateScore() {
	gotoxy(WIN_WIDTH + 6, 1); cout << "Score: " << score << endl;
}
void updateBulletTime(int time) {
	for (int i = WIN_WIDTH + 4; i < SCREEN_WIDTH_; i++)
	{
		gotoxy(i, 3); cout << " ";
	}
	for (int i = 0; i < time / 2; i++)
	{
		gotoxy(WIN_WIDTH + 4 + i, 3); cout << (char)177;
	}
	if (time % 2)
	{
		gotoxy(WIN_WIDTH + time / 2 + 4, 3); cout << (char)176;
	}
}
void instructions() {
	system("cls");
	cout << "Instructions";
	cout << "\n----------------";
	cout << "\n [A] lewo, [D] prawo, [esc] wyjscie [spacja] strzelanie" << endl;
	cout << "\n " << (char)218 << (char)191 << "      " << (char)201 << (char)187 << "        " << (char)85 << (char)74 << "    ";
	cout << "\n " << (char)192 << (char)217 << " koks " << (char)200 << (char)188 << " zelazo " << (char)158 << (char)158 << " UJ " << (char)215 << (char)215 << " pociski" << endl;
	cout << "\n Koks i zelazo zbierane warstwami dadza najlepsza jakosc surowki zwiekszajac punkty";
	cout << "\n Zbierz pociski, zeby strzelac i zbierac punkty za zestrzelone UJoty";
	cout << "\n Gra konczy sie po wypelnieniu Wielkiego Pieca";
	cout << "\n\nPress any key to go back to menu " << endl;
	system("pause");
}

void play() {
	int timePlay = 0;
	piecPos = -1 + WIN_WIDTH / 2;
	for (int i = 0; i < 20; i++) {
		bullets[i][0] = bullets[i][1] = 0;
	}
	system("cls");
	drawBorder();
	updateScore();
	for (int i = WIN_WIDTH + 4; i < SCREEN_WIDTH_; i++)
	{
		gotoxy(i, 2); cout << (char)178;
	}
	for (int i = WIN_WIDTH + 4; i < SCREEN_WIDTH_; i++)
	{
		gotoxy(i, 0); cout << (char)178;
	}
	for (int i = WIN_WIDTH + 4; i < SCREEN_WIDTH_; i++)
	{
		gotoxy(i, 4); cout << (char)178;
	}
	drawWielkiPiec();
	gotoxy(10, 5); cout << "Press any key to start";
	_getch();
	gotoxy(10, 5); cout << "                      ";
	while (1) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'a' || ch == 'A') {
				if (piecPos > 5)
					piecPos -= 2;
			}
			if (ch == 'd' || ch == 'D') {
				if (piecPos < WIN_WIDTH - 9)
					piecPos += 2;
			}
			if (ch == 32 && bullet) {
				genBullet();
			}
			if (ch == 27) {
				system("cls");
				exit(1);
				break;
			}
		}
		if (timePlay % 5 == 0)
		{
			genEnemy(enemyNext, bullet);
			enemyNext++;
			if (enemyNext >= 10)
			{
				enemyNext = 0;
			}
		}
		if (bulletTime > 0)
		{
			updateBulletTime(bulletTime);
			bulletTime--;
		}
		else
		{
			bullet = 0;
		}
		drawpiec();
		drawEnemy();
		drawBullets();
		if (bulletHit() == 1) updateScore();
		Sleep(200);
		timePlay++;
		erasepiec();
		eraseEnemy();
		eraseBullets();
		moveBullet();
		for (int i = 0; i < 10; i++)
		{
			if (enemyFlag[i])
			{
				enemyY[i] += 1;
				if (enemyY[i] > SCREEN_HEIGHT - 2) {
					//najwiêkszy wp³yw na przebieg gry
					if (collision(i) == 1) {
						if (enemyType[i] == 3)//odblokowuje strzelanie
						{
							bullet = true;
							bulletTime += 30;
						}
						else if (enemyType[i] == 2) {
							score -= 100;
						}
						else
						{
							score += 50;
							label[labelCount][0] = enemyType[i];
							labelCount++;
							fillPiec(enemyType[i], labelCount, label);
							if (labelCount == 18)//warunek ukoñczenia gry/wype³nienie pieca
							{
								for (int i = 1; i < 18; i++)
								{
									if ((label[i - 1][0]) != label[i][0]) {//faktor zwiêkszaj¹cy iloœæ punktów
										mnoznik += 0.5;//lub zmniejszaj¹cy jak ktoœ na³apa³ punktów ujemnych
									}
								}
								gameover();
								break;
							}
						}
						updateScore();
					}
					resetEnemy(i);
				}
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		enemyFlag[i] = 0;
	}
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	//ciê¿ka praca Mateusza Mroza
	do {
		system("cls");
		drawBorder_MENU();
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 4); cout << "                   $  $               " << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 5); cout << " #     #    ___    $ $     ___   __  __" << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 6); cout << " #  #  # | |___ |  $$  O  |___|||__ {  " << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 7); cout << " #__#__# | |___ |__$ $ |  |    ||__ {__" << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 8); cout << "              THE  $  $  GAME         " << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 20, 9); cout << "                  " << endl;
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 10); cout << " _________________ ";
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 11); cout << "| 1. Start Game   |";
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 12); cout << "| 2. Instructions |";
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 13); cout << "| 3. Highscore    |";
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 14); cout << "| [esc] Quit      |";
		gotoxy(SCREEN_WIDTH_ / 2 - 10, 15); cout << "|_________________|";
		char op = _getche();
		if (op == '1') play();
		else if (op == '2') instructions();
		else if (op == '3') highscore(highscoreCount());
		else if (op == 27) {
			system("cls");
			exit(0);
		}
	} while (1);
	return 0;
}