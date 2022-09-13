#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>

using namespace std;
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};
//Класс мяча
class cBall {
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	//Позиция мяча
	cBall(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}
	//Сброс
	void Reset() {
		x = originalX; y = originalY;
		direction = STOP;
	}
	//Изменение направления 
	void changeDirection(eDir d) {direction = d;}
	//Рандомное направление
	void randomDirection() { direction = (eDir)((rand() % 6) + 1);}
	//Функция для перемещения
	void Move() {
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}
	//Получение текущих координат
	inline int getX() { return x; }
	inline int getY() { return y; }
	//Получение текущего направления
	inline eDir getDirection() { return direction; }
	//Вывод обьекта через cout
	friend ostream& operator <<(ostream& o, cBall c){
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};
//Класс плитки
class cPaddle{
	int x, y;
	int originalX, originalY;
public:
	cPaddle() { x = y = 0; } //Текущее положение равно нулю
	cPaddle(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	//Сброс положения
	inline void Reset() { x = originalX; y = originalY; }
	//Получить координаты
	inline int getX() { return x; }
	inline int getY() { return y; }
	//Передвижение плитки
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	//Вывод обьекта через cout
	friend ostream& operator <<(ostream& o, cPaddle c){
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};
//Менеджер
class cGameManager {
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall* ball;
	cPaddle* player1;
	cPaddle* player2;
public:
	cGameManager(int w,int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		//Создание игроков и мяча
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}
	~cGameManager() { delete ball, player1, player2; }
	void ScoreUp(cPaddle* player) {
		if (player == player1) score1++;
		else if (player == player2) score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw(){
		system("cls");
		for (int i = 0; i < width + 2; i++)cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0) cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O"; //Мяч
				else if (player1x == j && player1y == i)
					cout << "\xDB"; //игрок 1
				else if (player2x == j && player2y == i)
					cout << "\xDB"; //игрок 2
				//игрок 1 рисование плитки
				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; 
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; 
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; 
				//игрок 2 рисование плитки
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB"; 
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB"; 
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB"; 
				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;
		cout << "Score 1: " << score1 << "\t\t" << "Score 2: " << score2 << endl;
	}

	void Input(){
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit()){
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		//Левая плитка
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		//Правая плитка
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//Нижняя стена
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		
		//Верхняя стена
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		
		//Правая стена
		if (ballx == width - 1)
			ScoreUp(player1);
		
		//Левая стена
		if (ballx == 0)
			ScoreUp(player2);
	}
	void Run(){
		while (!quit){
			Draw();
			Input();
			Logic();
			Sleep(60);
		}
	}
};
//Main
int main() {
	
	cGameManager c(40, 20);
	c.Run();
	return 0;
}