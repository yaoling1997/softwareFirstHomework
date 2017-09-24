#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
using namespace std;
const int maxn= 5e5;
int n,ans,x;
int main()
{
#ifndef ONLINE_JUDGE	
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	while (scanf("%d",&x)>0){
		ans+= x;
	}
	printf("%d",ans);
	return 0;
}
