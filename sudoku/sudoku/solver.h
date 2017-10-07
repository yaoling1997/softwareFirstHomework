/*
# Copyright 2017 YiJun Li
*/
#pragma once
#pragma warning(disable : 4996)
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<ctime>
#include<set>
#include<utility>
using std::next_permutation;
using std::swap;
const int firstNum = (9 + 9) % 9 + 1;  // 1
const int matrixLen = 9;  // 矩阵的宽度和高度
int outputNum = 0;
void output(int matrix[matrixLen][matrixLen]) {
    outputNum++;

    char s[300];
    int index = 0;

    if (outputNum != 1)  // 不是第一次输出要空行
        s[index++] = '\n';

    for (int i = 0; i < matrixLen; i++)
        for (int j = 0; j < matrixLen; j++) {
            s[index++] = matrix[i][j] + '0';
            if (j < matrixLen - 1)
                s[index++] = ' ';
            else
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
                int o = i % 3;
                for (int j = 0; j < matrixLen; j++) {
                    int t = temp[o][j];
                    temp[o][j] = newSeed[i][j];
                    newSeed[i][j] = t;
                }
            }
            rowChange(row + 3);
            if (!n)
                return;
            for (int i = row; i < row + 3; i++) {
                int o = i % 3;
                for (int j = 0; j < matrixLen; j++) {
                    int t = temp[o][j];
                    temp[o][j] = newSeed[i][j];
                    newSeed[i][j] = t;
                }
            }
        } while (next_permutation(per, per + 3));
    }
    void solve() {
        // fix the firstNum
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


// 行代表决策,(r,c,v)表示r行c列放v
// 列代表需要满足的条件，有一下四种条件
// slot(a,b),a行b列要数字
// row(a,b),a行缺b
// col(a,b),a列缺b
// sub(a,b),第a个小矩形缺b
// 一共9*9*9+1=729+1行(包括虚拟节点所占行)
// 一共9*9*4=324列(不包括头节点)
// 总共不超过9*9*9*4+324+1=3241个节点
const int maxn = 1000;
const int maxnode = 5000;
const int maxr = 1000;
struct DLX {
    int n, sz;  // 列数，节点总数
    int S[maxn];  // 各列节点数(不包括虚拟节点)
    int row[maxnode], col[maxnode];  // 各节点行列编号
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode];  // 十字链表
    int ansd, ans[maxr];  // 解
    void init(int n) {
        this->n = n;
        // 虚拟节点,0号为链表头
        for (int i = 0; i <= n; i++) {
            U[i] = i;
            D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[n] = 0; L[0] = n;
        sz = n + 1;
        memset(S, 0, sizeof(S));
    }
    void addRow(int r, int columns[], int cnt) {
        // r 行号,columns存放这一行的哪些列为1
        int first = sz;  // sz 当前新建节点标号
        for (int i = 0; i < cnt; i++) {
            int c = columns[i];
            L[sz] = sz - 1;
            R[sz] = sz + 1;
            D[sz] = c;
            U[sz] = U[c];
            D[U[c]] = sz;
            U[c] = sz;
            row[sz] = r;
            col[sz] = c;
            S[c]++;
            sz++;
        }
        R[sz - 1] = first;
        L[first] = sz - 1;
    }

    // 顺着链表A,遍历除s外的其它元素
#define FOR(i, A, s) for (int i= A[s]; i != s; i=A[i])
    void remove(int c) {
        // 移除标号为c所在的列
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i, D, c)
            FOR(j, R, i) {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            --S[col[j]];
        }
    }
    void restore(int c) {
        // 恢复标号c所在的列
        FOR(i, U, c)
            FOR(j, L, i) {
            ++S[col[j]];
            U[D[j]] = j;
            D[U[j]] = j;
        }
        L[R[c]] = c;
        R[L[c]] = c;
    }
    // d为递归深度
    bool dfs(int d) {
        if (R[0] == 0) {
            // 表示列的虚拟节点都删完了
            ansd = d;  // 找到解
            return true;  // 记录解的长度
        }
        // 找S最小的列c
        int c = R[0];  // 第一个未删除列
        FOR(i, R, 0)
            if (S[i] < S[c])
                c = i;
        remove(c);  // 删除第c列
        FOR(i, D, c) {  // 用节点i所在行覆盖第c列
            ans[d] = row[i];
            FOR(j, R, i)
                remove(col[j]);  // 删除节点i所在行能覆盖的其它所有列
            if (dfs(d + 1))
                return true;
            FOR(j, L, i)
                restore(col[j]);  // 恢复节点i所在行能覆盖的其它所有列
        }
        restore(c);  // 恢复第c列
        return false;
    }
     bool solve(int ansre[], int *anssize) {
        if (!dfs(0))
            return false;
        for (int i = 0; i < ansd; i++)
            ansre[i] = ans[i];
        *anssize = ansd;
        return true;
    }
};
const int SLOT = 0;
const int ROW = 1;
const int COL = 2;
const int SUB = 3;
struct SolveS_DLX {
    int matrix[matrixLen][matrixLen];
    DLX solver;
    int encode(int a, int b, int c) {
        return (a * matrixLen + b) * matrixLen + c + 1;
    }
    void decode(int code, int *a, int *b, int *c) {
        code--;
        *c = code%matrixLen;
        code /= matrixLen;
        *b = code %matrixLen;
        code /= matrixLen;
        *a = code;
    }
    void solve() {
        int x;
        while (scanf("%d", &x) > 0) {  // get first num in matrix
            for (int i = 0; i < matrixLen; i++)
                for (int j = 0; j < matrixLen; j++) {
                    if (i != 0 || j != 0)
                        // not first num in matrix
                        scanf("%d", &x);
                    matrix[i][j] = x;
                }
            solver.init(matrixLen*matrixLen * 4);
            for (int r = 0; r < matrixLen; r++)
                for (int c = 0; c < matrixLen; c++)
                    for (int v = 0; v < matrixLen; v++) {
                        if (matrix[r][c] == 0 || matrix[r][c] == v + 1) {
                            // vector<int> columns;
                            int columns[10];
                            int cnt = 0;
                            // 列号从1开始
                            columns[cnt++] = encode(SLOT, r, c);
                            columns[cnt++] = encode(ROW, r, v);
                            columns[cnt++] = encode(COL, c, v);
                            columns[cnt++] = encode(SUB, r / 3 * 3 + c / 3, v);
                            solver.addRow(encode(r, c, v), columns, cnt);
                        }
                    }
            int ans[1000];
            int ansSize = 0;
            if (solver.solve(ans, &ansSize)) {
                for (int i = 0; i < ansSize; i++) {
                    int r, c, v;
                    decode(ans[i], &r, &c, &v);
                    matrix[r][c] = v + 1;
                }
                output(matrix);
            } else {
                printf("No solution!\n");
            }
        }
    }
};
