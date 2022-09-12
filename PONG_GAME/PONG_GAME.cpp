﻿#include<iostream>
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
	void changeDirection(eDir d) {
		direction = d;
	}
	//Рандомное направление
	void randomDirection() {

		direction = (eDir)((rand() % 6) + 1);
	
	}
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
	friend ostream& operator <<(ostream& o, cBall c)
	{
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
	friend ostream& operator <<(ostream& o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};
//Main
int main() {
	cPaddle p1(0, 0);
	cPaddle p2(10, 0);
	cout << p1 << endl;
	cout << p2 << endl;
	p1.moveUp();
	p2.moveDown();
	cout << p1 << endl;
	cout << p2 << endl;


	return 0;
}