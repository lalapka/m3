#define _CRT_SECURE_NO_WARNINGS
# include <iostream>
# include <fstream>
# include <iomanip>
# include <fstream>
# include <string>
# include <thread>
# include <map>
# include <functional>
# include <stdio.h>
# include <windows.h>
# include <chrono>
# include <dos.h>
# include <conio.h>
using namespace std;

void cypher(long V[], long n, long k[], long r[], long t[]);

int main()
{
	setlocale(LC_ALL, "RUS");

	std::string mes;
	std::ifstream F;
	F.open("text.txt", ios::in, ios::binary);

	if (F.is_open())
	{
		int i = 0;
		getline(F, mes);
	}
	F.close();
	cout << "1 - шифр" << endl << "2 - дешифр" << endl;
	int len = mes.size();
	char* abc = new char[len];
	char* out = new char[len];
	strcpy(abc, mes.c_str());
	long* V = new long[len];
	long n, k[4], r[6], t[256];
	n = -4;
	for (int i = 0; i < 4; i++)
	{
		r[i] = rand() % 10;
	}
	for (int count = 0; count < 4; count++)
	{
		k[count] = rand() % 512;
	}
	for (int count_t = 0; count_t < 256; count_t++)
	{
		t[count_t] = rand() % 255;
	}
	while (true)
	{
		if (_kbhit()) // слушатель нажатия на клавиатуру
		{
			switch (_getch()) // ждёт нажатия на клавишу
			{
			case 49: // выбрано шифр
			{
				cout << endl << "начато шифр" << endl;
				ofstream f;
				f.open("code.txt", ios::out, ios::binary);
				for (int i = 1; i < len; i++)
				{
					V[i] = abc[i];
					cypher(V, len, k, r, t);
					out[i] = V[i];
					//cout << out[i];
					f << out[i];
				}
				f.close();
				cout << "текст зашифр" << endl;
			}
			break;

			case 50: // выбрано дешифр
			{
				cout << endl << "начато дешифр" << endl;
				ofstream f;
				f.open("decode.txt", ios::out, ios::binary);
				for (int i = 1; i < len; i++)
				{
					V[i] = abc[i];
					cypher(V, n, k, r, t);
					out[i] = V[i];
					//cout << out[i];
					f << out[i];
				}
				f.close();
				cout << "текст дешифр" << endl;
			}
			break;
			}
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

void cypher(long V[], long n, long k[], long r[], long t[])
{
	long r1, r2, r3, r4, r5, r6, d, * e, m = 0x00ffffff;
	r3 = k[0];
	r4 = k[1];
	r5 = k[2];
	r6 = k[3];
	if (n < 0)
	{
		d = -1;
	}
	else
	{
		d = 1;
	}
	e = V + n;
	while (V - e)
	{
		r1 = *V;
		r2 = r1 ^ r6;
		*V = r2;
		V += d;
		r3 = r3 + r2;
		r3 = (r3 >> 8 & m) ^ t[r3 & 255];
		r4 = r4 + r3;
		r4 = (r4 >> 8 & m) ^ t[r4 & 255];
		r5 = r5 + r4;
		r5 = (r5 >> 8 & m) ^ t[r5 & 255];
		r6 = r6 + r5;
		r6 = (r6 >> 8 & m) ^ t[r6 & 255];
	}
	r[0] = r3;
	r[1] = r4;
	r[2] = r5;
	r[3] = r6;
}
