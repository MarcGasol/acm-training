/*
luogu p3092
״ѹdp��https://www.luogu.com.cn/training/215#problems 
========================================================================================================= 
��Ŀ��Լ��Ҫ**����**��n����Ʒ��ÿ���۸�Ϊci������köӲ�� ��n<=100000, k<=16) 
�����ν��еĹ���N����Ʒ�Ĺ����У�Լ��������ʱͣ�������ÿ�θ���ֻ��һ��Ӳ�ң�
֧������������Ǵ���һ��֧����ʼ�����ڵ���Щ������Ʒ��ǰ���Ǹ�Ӳ������֧����Щ��Ʒ�ķ��ã���
���ҵ��ǣ��̳������������ˣ����Լ��֧����Ӳ����ֵ��������ķ��ã�������õ��κ����㡣

�������ڹ�����N����Ʒ��Լ�����ʣ�¶���Ǯ������޷���ɹ������-1 
========================================================================================================= 
��������Ѷȵ��⣬k�ķ�Χ��ôС��˵ʵ�����뵽״ѹdp��www
���ʣ�¶���Ǯ��==�����ٻ�����Ǯ 
ע�⵽�ĵ��ǣ���Ʒֻ�������� 
һ��ʼ���뷨�ǣ�dp[i]��ʾѡ��i��ЩӲ��������򵽵ڼ�����Ʒ��sum[i]��ʾ��ЩӲ��һ������Ǯ��
ת�Ƶ�ʱ���ǰ���i��0--> 1<<n��˳�� dp[i]=max��dp[i except coinj]+coinj����dp[i except coinj]֮���򵽵���Ʒ������ dp[i]��
������i��j������Ҫ������,����Ҫ�ҡ� coinj����dp[i except coinj]֮���򵽵���Ʒ��������O��n�� 
ÿ��dp��i������n��ʱ��sum[i]��ansȡmin���������ٻ���Ǯ�ˡ�O��2^k*kn) ��TLE20%

������������μ��ٵ�ʱ����ͻȻע�⵽�ˡ���Ʒֻ�������򡱣������Ϳ���ǰ׺�Ͷ����� �� coinj����dp[i except coinj]֮���򵽵���Ʒ������
AC�ˡ� 
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

