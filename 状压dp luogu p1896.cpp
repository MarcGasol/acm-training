/*
luogu p1896 
题目的描述与八皇后类似，在n*n的棋盘上放置k个国王，要求每两个国王之间不能互相攻击，问有多少种放置方法。（n<=9,k<=n*n)
首先注意到n的范围很小，但如果枚举每个格子放不放国王，2^(n*n)明显TLE。
考虑到2^9只有512，感觉可以状态压缩dp。
想法是：使用二进制位表示某个格子上放没放国王，利用位运算判断国王之间能不能相互攻击。（e.g. 101001=41 表示这一行第一、三、六列的位置摆放国王） 
我们可以创造这样一个数组：dp[i][j][k]表示已经考虑前i行，第i行的国王摆放情况是j，前i行（包括i）已经摆放了k个国王。
 
dp三大件：起始状态，状态转移，如何获取答案
起始状态：
与皇后不同，国王的攻击范围只有它周围的8格，也就是说，如果我们一行一行考虑，这一行的国王摆放只受相邻一行的限制。
所以可以初始化第一行的dp数组，然后一行一行计算下去：dp[1][i][count(i)] = 1(i:0->2^n, count(i)表示i状态有几个国王）

状态转移：
下文j1是当前考虑的行的国王摆放状态，j2是上一行的状态。 
首先，如何看上下两行国王能不能互相攻击呢？j1&j2 + j1&(j2<<1) + (j1<<1)&j2 == 0表示不能攻击，即不冲突。 
直接写方程：if j1与j2不冲突：dp[i][j1][k] = dp[i-1][j2][k-count(j1)]
其中，i j1 j2 k都是需要枚举的。复杂度在O（n^3*（2^2n))，测试之后通过70%数据。如何更快呢？
可以预处理每一行可能出现的状况：比如说，n==3时，110，011，111这三种状况是有冲突的，但是每次枚举都会找到。
预处理时可以去掉行内有冲突的状况：j&（j<<1）==0
然后就AC了 

如何获取答案：
dp数组构建好后，答案就是sigma(i:0--2^n-1)dp[n][i][k] 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long dp[10][520][90];// i line, situation j, already k
int situation[520],situation_num,king_num[520];
int n,K;
long long ans;
int count(int x){
	int cnt=0;
	while(x>0){
		x -= x&(-x);cnt++;
	}
	return cnt;
}
bool ok(int x,int y){
	return (x&y)+(x&(y<<1))+((x<<1)&y) == 0;
}
void init(){
	for(int i=0;i<(1<<n);i++)
	{
		if((i&(i<<1))==0 && (i&(i>>1))==0)situation[++situation_num]=i, king_num[i]=count(i);
	}
}
int main()
{
	cin>>n>>K;
	init();
	for(int i=1;i<=situation_num;i++)
	{
		dp[1][situation[i]][king_num[situation[i]]] = 1;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j1=1;j1<=situation_num;j1++)
		{
			for(int j2=1;j2<=situation_num;j2++)
			{
				for(int k=0;k<=K;k++)
				{
					if(k<king_num[situation[j2]])continue;
					if(ok(situation[j1], situation[j2]))
					{
						dp[i][situation[j2]][k] += dp[i-1][situation[j1]][k-king_num[situation[j2]]];
					}
				}
			}
		}
	}
	for(int i=1;i<=situation_num;i++)
	{
		ans+=dp[n][situation[i]][K];
	}
	cout<<ans;
	return 0;
}
