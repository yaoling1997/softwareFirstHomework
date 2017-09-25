// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solver.h"
using namespace std;
int option = -1;
bool stringEqual(char *a, char *b)
{
	if (strlen(a) != strlen(b))
		return false;
	int len = (int)strlen(a);
	for (int i = 0; i < len; i++)
		if (a[i] != b[i])
			return false;
	return true;
}
int stringToNum(char *s)
{
	//-1 invalid
	//1~1000000
	const int MaxNum = 1000000;
	int re = 0, len = (int)strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (s[i]<'0' || s[i]>'9')
			return -1;
		re = re * 10 + s[i] - '0';
		if (re > MaxNum)
			return -1;
	}
	if (re < 1)
		return -1;
	return re;
}
int checkParameter(int argc, char *argv[])
{
	//re==-1 invalid
	//re==1 -c
	//re==2 -s
	if (argc != 3)
	{
		return -1;
	}
	if (stringEqual(argv[1], "-c"))
	{
		int x = stringToNum(argv[2]);
		if (x > 0)
			return 1;
	}
	else if (stringEqual(argv[1], "-s")) {
		FILE *fp = NULL;
		fp = fopen(argv[2], "r");
		if (fp == NULL) {
			printf("file not exist\n");
			return -1;
		}
		else {
			return 2;
		}
	}
	return -1;
}


SolveC solveC;
//SolveS solveS;
SolveS_DLX solveS_DLX;


int main(int argc, char *argv[])
{
	double beginTime = clock();
	freopen("sudoku.txt", "w", stdout);
	option = checkParameter(argc, argv);
	if (option == 1) {//-c
		solveC.n = stringToNum(argv[2]);
		solveC.solve();
	}
	else if (option == 2) {//-s
		freopen(argv[2], "r", stdin);
		//solveS.solve();
		solveS_DLX.solve();
	}
	else {
		printf("invalid parameters\n");
	}
	double endTime = clock();
	fclose(stdout);

	//freopen("2.out", "w", stdout);
	//printf("time cost:%.3f", (endTime - beginTime) / CLOCKS_PER_SEC);
	return 0;
}