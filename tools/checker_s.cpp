#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<cmath>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
using namespace std;
const int maxn= 5e5,matrixLen= 9;
int a[matrixLen][matrixLen];
int x,n;
void initVis(int vis[10]){
	for (int i= 0;i<10;i++)
		vis[i]= 0;
	vis[0]= 1;
}
bool checkLittleMatrix(int x,int y,int vis[10]){
	for (int i= 0;i<3;i++)
		for (int j= 0;j<3;j++){
			if (vis[a[x+i][y+j]])
				return false;
			vis[a[x+i][y+j]]= 1;
		}
	return true;
}
bool checkMatrix(){
	int vis[10]= {0};
	for (int i= 0;i<matrixLen;i++){
		initVis(vis);
		for (int j= 0;j<matrixLen;j++){
			if (vis[a[i][j]])
				return false;
			vis[a[i][j]]= 1;
		}
	}
	for (int i= 0;i<matrixLen;i++){
		initVis(vis);
		for (int j= 0;j<matrixLen;j++){
			if (vis[a[j][i]])
				return false;
			vis[a[j][i]]= 1;
		}
	}
	for (int i= 0;i<matrixLen;i+= 3)
		for (int j= 0;j<matrixLen;j+= 3){
			initVis(vis);
			if (!checkLittleMatrix(i,j,vis)){
				return false;
			}
		}
	return true;
}
bool check(){
	while (scanf("%d",&x)>0){
		n++;
		string s= "";
		for (int i= 0;i<matrixLen;i++)
			for (int j= 0;j<matrixLen;j++){
				if (i==0&&j==0){
					a[i][j]= x;
				}else {
					scanf("%d",&a[i][j]);
				}
				s.push_back((char)(a[i][j]+'0'));
			}
		if (!checkMatrix())
			return false;
	}
	return true;
}
int main()
{
#ifndef ONLINE_JUDGE	
	freopen("sudoku.txt","r",stdin);
	freopen("check_s.out","w",stdout);
#endif
	if (check()){
		printf("%d\n",n);
		printf("ok");
	}else {
		printf("shit!");
	}
	return 0;
}
