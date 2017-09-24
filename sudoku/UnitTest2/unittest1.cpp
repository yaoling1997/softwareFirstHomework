#include "stdafx.h"
//#include "../sudoku/solver.h"
#include "solver.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	void initVis(int vis[10]) {
		for (int i = 0; i < 10; i++)
			vis[i] = 0;
		vis[0] = 1;
	}
	bool checkLittleMatrix(int a[matrixLen][matrixLen], int x, int y, int vis[10]) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				if (vis[a[x + i][y + j]])
					return false;
				vis[a[x + i][y + j]] = 1;
			}
		return true;
	}
	bool checkMatrix(int a[matrixLen][matrixLen]) {
		int vis[10] = { 0 };
		for (int i = 0; i < matrixLen; i++) {
			initVis(vis);
			for (int j = 0; j < matrixLen; j++) {
				if (vis[a[i][j]])
					return false;
				vis[a[i][j]] = 1;
			}
		}
		for (int i = 0; i < matrixLen; i++) {
			initVis(vis);
			for (int j = 0; j < matrixLen; j++) {
				if (vis[a[j][i]])
					return false;
				vis[a[j][i]] = 1;
			}
		}
		for (int i = 0; i < matrixLen; i += 3)
			for (int j = 0; j < matrixLen; j += 3) {
				initVis(vis);
				if (!checkLittleMatrix(a, i, j, vis)) {
					return false;
				}
			}
		return true;
	}
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			SolveC solveC;
			int a[matrixLen];
			solveC.initPermutation(a);
			//Assert::AreEqual(a[matrixLen-1],firstNum);
		}

		TEST_METHOD(TestMethod2)
		{
			SolveC solveC;
			solveC.n = 2;
			solveC.rowChange(3);
			Assert::AreEqual(solveC.n, 0);
		}
		TEST_METHOD(TestMethod3)
		{
			SolveC solveC;
			solveC.n = 200;
			solveC.solve();
			Assert::AreEqual(solveC.n, 0);
			Assert::AreEqual(checkMatrix(solveC.newSeed), true);
		}
		TEST_METHOD(TestMethod4)
		{
			SolveC solveC;
			solveC.n = 2000;
			solveC.solve();
			Assert::AreEqual(solveC.n, 0);
			Assert::AreEqual(checkMatrix(solveC.newSeed), true);
		}
		TEST_METHOD(TestMethod5)
		{
			SolveC solveC;
			solveC.n = 10000;
			solveC.solve();
			Assert::AreEqual(solveC.n, 0);
			Assert::AreEqual(checkMatrix(solveC.newSeed), true);
		}
		TEST_METHOD(TestMethod6)
		{
			SolveS solveS;
			freopen("C:/Users/acer-pc/Desktop/git/softwareFirstHomework/sudoku/sudoku/1.in", "r", stdin);			
			solveS.solve();
			Assert::AreEqual(checkMatrix(solveS.matrix), true);
		}
		TEST_METHOD(TestMethod7)
		{
			SolveS solveS;
			freopen("C:/Users/acer-pc/Desktop/git/softwareFirstHomework/sudoku/sudoku/1.in", "r", stdin);
			solveS.solve();
			for (int i = 0; i < matrixLen; i++)
				for (int j = 1; j <= matrixLen; j++)
					Assert::AreEqual(solveS.rowVis[i][j]-1<=0, true);
		}
		TEST_METHOD(TestMethod8)
		{
			SolveS solveS;
			freopen("C:/Users/acer-pc/Desktop/git/softwareFirstHomework/sudoku/sudoku/2.in", "r", stdin);
			solveS.solve();
			for (int i = 0; i < matrixLen; i++)
				for (int j = 1; j <= matrixLen; j++)
					Assert::AreEqual(solveS.colVis[i][j] - 1 <= 0, true);
		}
		TEST_METHOD(TestMethod9)
		{
			SolveS solveS;
			freopen("C:/Users/acer-pc/Desktop/git/softwareFirstHomework/sudoku/sudoku/1.in", "r", stdin);
			solveS.solve();
			for (int i = 0; i < matrixLen/3; i++)
				for (int j= 0;j<matrixLen/3;j++)
				for (int k = 1; k <= matrixLen; k++)
					Assert::AreEqual(solveS.littleMatrixVis[i][j][k] - 1 <= 0, true);
		}
		TEST_METHOD(TestMethod10)
		{
			Assert::AreEqual(firstNum,1);
		}

	};
}