//
//  main.cpp
//  local minimum
//
//  Created by Валентина on 28/02/2019.
//  Поиск локального минимума методами деления отрезка пополам,
//  золотого сечения и с помощью чисел Фибоначчи + много отладочной печати
//

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

float f(float x)
{
    return 2*x*x*x+9*x*x - 6;    //Функция, локальный минимум которой мы ищем
}

float* fibonacci(int n)
{
    float *f = new float(n+1);
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i-1] + f[i-2];
    }
    return f;
}


void dichot(float (*f)(float), float a, float b) //Функци принимает функцию f и границы
{
    float x = 0;
    float dx;
    float eps = 0.2f;            //Погрешность метода
    while (b - a > eps)
    {
        dx = (b - a) / 2;
        x = a + dx;
        
        cout << "f(x) = " << f(x) << endl;
        cout << "f(a) = " << f(a) << endl;

        if (f(a) <= f(x))
        {
            b = x;
        } else
        {
            a = x;
        }
        
        cout << "промежуточный x = " << x << endl;
        cout << "промежуточный a = " << a << endl;
    }
    cout << "Result: " << f((x - a)/2) << endl;
}

void gMethod(float (*f)(float), float a, float b)
{
    float x1, x2, F;
    float eps = 0.2f;
    F = 1.618f;
    while (b - a > eps)
    {
        x1 = b - (b-a)/F;
        x2 = a + (b-a)/F;
        
        cout    << "x1 = " << x1 << endl
                << "x2 = " << x2 << endl
                << "f(x1) = " << f(x1) << endl
                << "f(x2) = " << f(x2) << endl;
        
        if (f(x1) >= f(x2))
        {
            a = x1;
        }
        else
        {
            b = x2;
        }
        cout << "a = " << a << endl;
        cout << "b = " << b << endl << endl;
        //cout << abs(b-a) << endl << endl;
    }
    cout << "\nLocal minimum is: \t" << f((a + b) / 2) << endl;
}

void fMethod(float (*f)(float), float a, float b, int n)
{
    float* F = fibonacci(n);
    float x1, x2;
    float f1, f2;
    while (n > 1)
    {
        cout << "F(n-2) = " << F[n-2] << "\tF(n-1) = " << F[n-1] << "\tF(n) = " << F[n] << endl;
        x1 = a + (F[n-2]/F[n]) * (b - a);
        x2 = a + (F[n-1]/F[n]) * (b - a);
        f1 = f(x1);
        f2 = f(x2);
        n--;

        cout    << "x1 = " << x1 << endl
                << "x2 = " << x2 << endl
                << "f(x1) = " << f1 << endl
                << "f(x2) = " << f2 << endl << endl;
        
        if (f1 <= f2)
        {
            b = x2;
        } else
        {
            a = x1;
        }
    }
    delete F;
    cout << "Local minimum is: " << f((b - a)/2) << endl;
}

int main()
{
    int c;
    int n = 1;
    float left, right;
    fibonacci(4);
    cout    << "Chose method:" << endl
            << "\t1.Dichotomy" << endl
            << "\t2.Golden-section search" << endl
            << "\t3.Fibonacci method" << endl;
    cin >> c;
    if (c == 3 || c == 2 || c == 1)        //Пропускаем ввод интервалов, если пользователь ввел недопустимое значение
    {
        cout << "Enter borders: ";
        cin >> left >> right;
        if (left > right)            //Меняем интервалы местами, если они введены неверно
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
        case 3:
            cout << "Enter number of fibonacci elements: ";
            cin >> n;
            fMethod(f, left, right, n);
            break;
        default:
            cout << "Incorrect input" << endl;
    }
    
    system("PAUSE");
    return 0;
}
