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
SolveS solveS;

//行代表决策,(r,c,v)表示r行c列放v
//列代表需要满足的条件，有一下四种条件
//slot(a,b),a行b列要数字
//row(a,b),a行缺b
//col(a,b),a列缺b
//sub(a,b),第a个小矩形缺b
//一共9*9*9+1=729+1行(包括虚拟节点所占行)
//一共9*9*4=324列(不包括头节点)
//总共不超过9*9*9*4+324+1=3241个节点
//const int maxn = 1000;
//const int maxnode = 5000;
//const int maxr = 1000;
//struct DLX {
//	int n, sz;//列数，节点总数
//	int S[maxn];//各列节点数(不包括虚拟节点)
//	int row[maxnode], col[maxnode];//各节点行列编号
//	int L[maxnode], R[maxnode], U[maxnode], D[maxnode];//十字链表
//	int ansd, ans[maxr];//解
//	void init(int n) {
//		this->n = n;
//		//虚拟节点,0号为链表头
//		for (int i = 0; i <= n; i++) {
//			U[i] = i;
//			D[i] = i;
//			L[i] = i - 1;
//			R[i] = i + 1;
//		}
//		R[n] = 0; L[0] = n;
//		sz = n + 1;
//		memset(S, 0, sizeof(S));
//	}
//	void addRow(int r, vector<int> columns) {
//		//r 行号,columns存放这一行的哪些列为1
//		int first = sz;//sz 当前新建节点标号
//		for (int i = 0; i < (int)columns.size(); i++) {
//			int c = columns[i];
//			L[sz] = sz - 1;
//			R[sz] = sz + 1;
//			D[sz] = c;
//			U[sz] = U[c];
//			D[U[c]] = sz;
//			U[c] = sz;
//			row[sz] = r;
//			col[sz] = c;
//			S[c]++;
//			sz++;
//		}
//		R[sz - 1] = first;
//		L[first] = sz - 1;
//	}
//
//	//顺着链表A,遍历除s外的其它元素
//#define FOR(i,A,s) for(int i= A[s];i!=s;i=A[i])
//	void remove(int c) {
//		//移除标号为c所在的列
//		L[R[c]] = L[c];
//		R[L[c]] = R[c];
//		FOR(i, D, c)
//			FOR(j, R, i) {
//			U[D[j]] = U[j];
//			D[U[j]] = D[j];
//			--S[col[j]];
//		}
//	}
//	void restore(int c) {
//		//恢复标号c所在的列
//		FOR(i, U, c)
//			FOR(j, L, i) {
//			++S[col[j]];
//			U[D[j]] = j;
//			D[U[j]] = j;
//		}
//		L[R[c]] = c;
//		R[L[c]] = c;
//	}
//	//d为递归深度
//	bool dfs(int d) {
//		if (R[0] == 0) {
//			//表示列的虚拟节点都删完了
//			ansd = d;//找到解
//			return true;//记录解的长度
//		}
//		//找S最小的列c
//		int c = R[0];//第一个未删除列
//		FOR(i, R, 0)
//			if (S[i] < S[c])
//				c = i;
//		remove(c);//删除第c列
//		FOR(i, D, c) {//用节点i所在行覆盖第c列
//			ans[d] = row[i];
//			FOR(j, R, i)
//				remove(col[j]);//删除节点i所在行能覆盖的其它所有列
//			if (dfs(d + 1))
//				return true;
//			FOR(j, L, i)
//				restore(col[j]);//恢复节点i所在行能覆盖的其它所有列
//		}
//		restore(c);//恢复第c列
//		return false;
//	}
//	bool solve(vector<int> &v) {
//		v.clear();
//		if (!dfs(0))
//			return false;
//		for (int i = 0; i < ansd; i++)
//			v.push_back(ans[i]);
//		return true;
//	}
//};
//const int SLOT = 0;
//const int ROW = 1;
//const int COL = 2;
//const int SUB = 3;
//struct SolveS_DLX {
//	int matrix[matrixLen][matrixLen];
//	DLX solver;
//	int encode(int a, int b, int c) {
//		return (a * matrixLen + b) * matrixLen + c + 1;
//	}
//	void decode(int code, int &a, int &b, int &c) {
//		code--;
//		c = code%matrixLen;
//		code /= matrixLen;
//		b = code %matrixLen;
//		code /= matrixLen;
//		a = code;
//	}
//	void solve() {
//		int x;
//		while (scanf("%d", &x) > 0) {//get first num in matrix
//			for (int i = 0; i < matrixLen; i++)
//				for (int j = 0; j < matrixLen; j++) {
//					if (i != 0 || j != 0)
//						//not first num in matrix
//						scanf("%d", &x);
//					matrix[i][j] = x;
//				}
//			solver.init(matrixLen*matrixLen * 4);
//			for (int r = 0; r < matrixLen; r++)
//				for (int c = 0; c < matrixLen; c++)
//					for (int v = 0; v < matrixLen; v++) {
//						if (matrix[r][c] == 0 || matrix[r][c] == v + 1) {
//							vector<int> columns;
//							//列号从1开始
//							columns.push_back(encode(SLOT, r, c));
//							columns.push_back(encode(ROW, r, v));
//							columns.push_back(encode(COL, c, v));
//							columns.push_back(encode(SUB, r / 3 * 3 + c / 3, v));
//							solver.addRow(encode(r, c, v), columns);
//						}
//					}
//			vector<int> ans;
//			if (solver.solve(ans)) {
//				for (int i = 0; i < (int)ans.size(); i++) {
//					int r, c, v;
//					decode(ans[i], r, c, v);
//					matrix[r][c] = v + 1;
//				}
//				output(matrix);
//			}
//			else {
//				printf("No solution!\n");
//			}
//		}
//	}
//}solveS_DLX;
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
		solveS.solve();
		//solveS_DLX.solve();
	}
	else {
		printf("invalid parameters\n");
	}
	double endTime = clock();
	fclose(stdout);

	freopen("2.out", "w", stdout);
	printf("time cost:%.3f", (endTime - beginTime) / CLOCKS_PER_SEC);
	return 0;
}

