#pragma once
#pragma warning (disable : 4996)
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<ctime>
#include<set>
using namespace std;
const int firstNum = (9 + 9) % 9 + 1;//1
const int matrixLen = 9;//矩阵宽和高长度
int outputNum = 0;
void output(int matrix[matrixLen][matrixLen]) {
	outputNum++;

	char s[300];
	int index = 0;

	if (outputNum != 1)//不是第一次输出要空行
		//putchar('\n');
		s[index++] = '\n';

	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++) {
			//putchar(matrix[i][j] + '0');
			s[index++] = matrix[i][j] + '0';
			if (j < matrixLen - 1)
				//putchar(' ');
				s[index++] = ' ';
			else
				//putchar('\n');
				s[index++] = '\n';
		}
	s[index] = 0;
	fputs(s, stdout);
}
struct SolveC {
	int n = 0;
	const int seed[matrixLen][matrixLen] = {
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
		{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
		{ 2, 1, 4, 3, 6, 5, 8, 9, 7 },
		{ 3, 6, 5, 8, 9, 7, 2, 1, 4 },
		{ 8, 9, 7, 2, 1, 4, 3, 6, 5 },
		{ 5, 3, 1, 6, 4, 2, 9, 7, 8 },
		{ 6, 4, 2, 9, 7, 8, 5, 3, 1 },
		{ 9, 7, 8, 5, 3, 1, 6, 4, 2 }
	};
	int newSeed[matrixLen][matrixLen];
	void initPermutation(int a[matrixLen]) {
		int cnt = 0;
		for (int i = 1; i <= matrixLen; i++) {
			if (i == firstNum)
				continue;
			a[cnt++] = i;
		}
		a[matrixLen - 1] = firstNum;
	}
	void rowChange(int row) {
		if (row >= matrixLen) {
			output(newSeed);
			n--;
			return;
		}
		int per[3];
		for (int i = 0; i < 3; i++)
			per[i] = row + i;
		do {
			int temp[3][matrixLen];
			for (int i = row; i < row + 3; i++) {
				memcpy(temp[i % 3], newSeed[per[i % 3]], sizeof(temp[0]));
			}
			for (int i = row; i < row + 3; i++) {
				swap(temp[i % 3], newSeed[i]);
			}
			rowChange(row + 3);
			if (!n)
				return;
			for (int i = row; i < row + 3; i++) {
				swap(temp[i % 3], newSeed[i]);
			}
		} while (next_permutation(per, per + 3));
	}
	void solve() {
		//fix the firstNum
		int origin[matrixLen] = { 0 };
		int trans[matrixLen] = { 0 };
		int numToPos[matrixLen + 1] = { 0 };
		initPermutation(origin);
		initPermutation(trans);
		for (int i = 0; i < matrixLen; i++) {
			numToPos[origin[i]] = i;
		}
		while (n > 0) {
			for (int i = 0; i < matrixLen; i++)
				for (int j = 0; j < matrixLen; j++) {
					newSeed[i][j] = trans[numToPos[seed[i][j]]];
				}
			rowChange(3);
			if (!n)
				break;
			swap(newSeed[1], newSeed[2]);
			rowChange(3);
			next_permutation(trans, trans + matrixLen - 1);
		}
	}
};
typedef pair<int, int> Node;
struct SolveS {
	int matrix[matrixLen][matrixLen];
	set<int> S[matrixLen][matrixLen];
	int rowVis[matrixLen][matrixLen + 1];
	int colVis[matrixLen][matrixLen + 1];
	int littleMatrixVis[3][3][matrixLen + 1];
	void init() {
		for (int i = 0; i < matrixLen; i++)
			for (int j = 0; j < matrixLen; j++)
				S[i][j].clear();
		memset(rowVis, 0, sizeof(rowVis));
		memset(colVis, 0, sizeof(colVis));
		memset(littleMatrixVis, 0, sizeof(littleMatrixVis));
	}
	void initSetOfThisEmptyPos(int x, int y) {
		for (int i = 1; i <= matrixLen; i++) {
			if (rowVis[x][i] || colVis[y][i] || littleMatrixVis[x / 3][y / 3][i])
				continue;
			S[x][y].insert(i);
		}
	}
	int removeItem(int x, int y, int xx, int yy) {
		//use (x,y) to update (xx,yy)'s set
		//1 remove success,other fail
		int v = matrix[x][y];
		if (x == xx || y == yy || (x / 3 == xx / 3 && y / 3 == yy / 3))
			if (S[xx][yy].count(v) != 0) {
				S[xx][yy].erase(v);
				return 1;
			}
		return 0;
	}
	bool dfsSolve(vector<Node> emptyPos) {
		if (emptyPos.size() == 0) {
			output(matrix);
			return true;
		}
		Node c = emptyPos[0];//choice
		int cPos = 0;
		for (int i = 1; i < (int)emptyPos.size(); i++)
			if (S[c.first][c.second].size() > S[emptyPos[i].first][emptyPos[i].second].size()) {
				c = emptyPos[i];
				cPos = i;
			}
		emptyPos.erase(emptyPos.begin() + cPos, emptyPos.begin() + cPos + 1);
		for (set<int>::iterator it = S[c.first][c.second].begin(); it != S[c.first][c.second].end(); it++) {
			int x = *it;
			matrix[c.first][c.second] = x;
			vector<int> isRemoved;
			for (int i = 0; i < (int)emptyPos.size(); i++) {
				int re = removeItem(c.first, c.second, emptyPos[i].first, emptyPos[i].second);
				isRemoved.push_back(re);
			}
			if (dfsSolve(emptyPos))
				return true;
			for (int i = 0; i < (int)emptyPos.size(); i++)
				if (isRemoved[i] == 1)
					S[emptyPos[i].first][emptyPos[i].second].insert(x);
			matrix[c.first][c.second] = 0;
		}
		return false;
	}
	void solve() {
		int x;
		while (scanf("%d", &x) > 0) {//get first num in matrix
			vector<Node> emptyPos;
			init();
			for (int i = 0; i < matrixLen; i++)
				for (int j = 0; j < matrixLen; j++) {
					if (i != 0 || j != 0)
						//not first num in matrix
						scanf("%d", &x);
					matrix[i][j] = x;
					if (x != 0) {
						rowVis[i][x] = 1;
						colVis[j][x] = 1;
						littleMatrixVis[i / 3][j / 3][x] = 1;
					}
				}
			for (int i = 0; i < matrixLen; i++)
				for (int j = 0; j < matrixLen; j++)
					if (matrix[i][j] == 0) {
						emptyPos.push_back(make_pair(i, j));
						initSetOfThisEmptyPos(i, j);
					}
			if (!dfsSolve(emptyPos)) {
				printf("No solution!\n");
			}
		}
	}
};