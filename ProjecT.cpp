#include <iostream>
#include <math.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNIRGS
#pragma warning(disable : 4996)
#define L 0.1
#define X 100.
#define A 1.*pow(10.,-4)
#define T 30.
#define TIME 10
#define W 0.5
#define dt  0.0001

double** Memory_alloc(int ts)
{
	double** pt = NULL;
	pt = (double**)malloc((int(ts))*sizeof(double*)  );
	for (int i = 0; i <int(ts); i++)
		pt[i] = (double*)malloc(int(X)*sizeof(double));
	return pt;
}

double Temp(double time)
{
	double temp = T * pow(cos(W * time), 2);
	return temp;
}

double** FirstCondition(double** pt, int ts)
{
	double time = 0;
	for (int j = 0; j < ts; j++)
	{
		pt[j][0] = Temp(time);  //подводимая температура по краям стержня
		pt[j][int(X)-1 ] = Temp(time);
		time +=dt;
	}
	for (int i = 1; i <= X - 2; i++)// начальная температура стержня, кроме краевых точек
		pt[0][i] = 20;
	return pt;
}

double** Decision(double** pt, int ts)
{
	pt = FirstCondition( pt, ts); // начальные условия
	double k = (A * dt) / pow((L/X), 2);
	for (int i = 0; i < ts-1 ; i++)
		for (int j = 1; j < X -1; j++)
			pt[i+1][j] = k * pt[i][j-1] + (1 - 2 * k) * pt[i][j] + k * pt[i][j+1 ];// расчет температуры в каждой точки методом сеток
	return pt;
}

void OutPut(FILE* fp, double** temp, int ts)
{
	double time = 0;
	double length = 0;
	fprintf(fp, "%s %s %s\n", "temperature ", "N: ", "t: ");
	for (int i = 0; i < ts; i++)
	{
		for (int j = 0; j < X; j++)
		{
			fprintf(fp, "%f\n", temp[i][j]);
			length += (L / X);
		}
		time += dt;
	}
	for (int i = 0; i < ts; i++)   // очищение памяти
		free(temp[i]);   
	free(temp);
}
int main()
{
	FILE* fp;
	if ((fp = fopen("output.txt", "w")) == NULL)
		printf("Ошибка при открытии файла.\n");
	int ts =  int(TIME /  dt);  // количество шагов по времени
	double** pt = Memory_alloc(ts); // выделение памяти для  динамического 2d массива
	pt = Decision(pt, ts);// решенеие
	OutPut(fp, pt, ts);// выовод
	fclose(fp);
	return 0;
}
