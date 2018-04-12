#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

float f(float x)	
{
	return x*x*x-2*x;	//Функция, локальный минимум которой мы ищем
}

void dichot(float (*f)(float), float a, float b) //Функци принимает функцию f и границы
{
	float x, dx;
	float eps = 0.0005f;			//Погрешность метода
	while (b - a > eps)
	{
		dx = (b - a) /2;
		x = a + dx;
		if (f(a) <= f(x))
		{
			b = x;
		} else
		{
			a = x;
		}
	}
	cout << "Result: " << x << endl;
}

void gMethod(float (*f)(float), float left, float right)
{
	float x1, x2, F, a, b;
	float eps = 0.0005f;
	F = 1.618f;
	a = left;
	b = right;
	while (true)
	{
		x1 = b - (b-a)/F;
		x2 = a + (b-a)/F;
		if (f(x1) >= f(x2))
		{
			a = x1;
		}
		else
		{
			b = x2;
		}
		if (abs(b-a) < eps)
		{
			break;
		}
	}
	cout << "\nLocal minimum is: \t" << (a + b) / 2;
}

int _tmain()
{
	int c;
	float left, right;
	cout << "Chose method:" << endl
		 << "\t1.Dichotomy" << endl
		 << "\t2.Golden-section search" << endl;
	cin >> c;
	if (c == 2 || c == 1)		//Пропускаем ввод интервалов, если пользователь ввел недопустимое значение
	{
		cout << "Enter borders: ";
		cin >> left >> right;
		if (left > right)			//Меняем интервалы местами, если они введены неверно
		{
			float tmp = left;
			left = right;
			right = tmp;
		}
	}
	
	switch (c)
	{
	case 1:
		dichot(f, left, right);
		break;
	case 2:
		gMethod(f, left, right);
		break;
	default:
		cout << "Incorrect input" << endl;	
	}
	system("PAUSE");
}


