/*
luogu p3092
状压dp：https://www.luogu.com.cn/training/215#problems 
========================================================================================================= 
题目：约翰要**依次**买n件商品，每件价格为ci。他有k枚硬币 （n<=100000, k<=16) 
在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，
支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。
不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1 
========================================================================================================= 
看到这个难度的题，k的范围那么小，说实话就想到状压dp了www
最多剩下多少钱《==》最少花多少钱 
注意到的点是，商品只能依次买。 
一开始的想法是，dp[i]表示选择i这些硬币最多能买到第几个商品，sum[i]表示这些硬币一共多少钱。
转移的时候是按照i：0--> 1<<n的顺序， dp[i]=max（dp[i except coinj]+coinj能在dp[i except coinj]之后买到的商品数量， dp[i]）
很明显i和j都是需要遍历的,并且要找“ coinj能在dp[i except coinj]之后买到的商品数量”是O（n） 
每当dp【i】到达n的时候，sum[i]与ans取min，就是最少花的钱了。O（2^k*kn) ，TLE20%

正当我在想如何加速的时候，我突然注意到了“商品只能依次买”，这样就可以前缀和二分找 “ coinj能在dp[i except coinj]之后买到的商品数量”
AC了。 
*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
//#define _MATH_DEFINES_DEFINED
using namespace std;
int n,k;
int coin[20],a[100001],dp[66000],sum[66000];
int ans=2147483647;
int bisearch(int x,int start)
{
	int l = start, r = n, mid;
	while(l<=r)
	{
		mid = (l+r)>>1;
		if(a[mid]-a[start-1]==x)return mid;
		if(a[mid]-a[start-1]<x)l = mid + 1;
		else r = mid-1;
	}
	return r;
}
int main()
{
	cin>>k>>n; for(int i=1;i<=k;i++)cin>>coin[i];
	for(int i=1;i<=n;i++)
	{
		int temp;cin>>temp;a[i]=a[i-1]+temp; 
	}
	for(int i=0;i<(1<<k);i++)
	{
		for(int j=0;j<k;j++)
		{
			if(i & (1<<j))
			{
				int situation = i^(1<<j);
				int after=bisearch(coin[j+1], dp[situation]+1);
				if(after>dp[i])
				{
					dp[i] = after; sum[i] = sum[situation]+coin[j+1];
				}
				if(dp[i]==n)ans = min(ans, sum[i]);
			}
		}
	}
	if(ans==2147483647)
	{
		cout<<"-1";return 0;
	}
	for(int i=1;i<=k;i++)
	{
		ans-=coin[i];
	}
	cout<<-ans;
	return 0;
}

