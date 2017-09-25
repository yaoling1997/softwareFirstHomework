#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<sys/timeb.h>
using namespace std;
const int maxn= 100,matrixLen= 9,T= 10000;
int a[matrixLen][matrixLen];
int n,m,i,j,x,y,z;
int random(int o){
	return rand()%o;
}
int main()
{
	freopen("seed1000000.txt","r",stdin);
	freopen("1.in","w",stdout);
	struct timeb t;ftime(&t);
	srand(t.time*1000+t.millitm);
	for (int tt= 1;tt<=T;tt++){
		for (int i= 0;i<matrixLen;i++)
			for (int j= 0;j<matrixLen;j++){
				int x;
				scanf("%d",&x);
				if (random(2)==0)
					x= 0;
				printf("%d%c",x,j<matrixLen-1?' ':'\n');
			}
		printf("\n");
	}			
	return 0;
}
