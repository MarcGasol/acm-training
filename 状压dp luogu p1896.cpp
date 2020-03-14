/*
luogu p1896 
��Ŀ��������˻ʺ����ƣ���n*n�������Ϸ���k��������Ҫ��ÿ��������֮�䲻�ܻ��๥�������ж����ַ��÷�������n<=9,k<=n*n)
����ע�⵽n�ķ�Χ��С�������ö��ÿ�����ӷŲ��Ź�����2^(n*n)����TLE��
���ǵ�2^9ֻ��512���о�����״̬ѹ��dp��
�뷨�ǣ�ʹ�ö�����λ��ʾĳ�������Ϸ�û�Ź���������λ�����жϹ���֮���ܲ����໥��������e.g. 101001=41 ��ʾ��һ�е�һ���������е�λ�ðڷŹ����� 
���ǿ��Դ�������һ�����飺dp[i][j][k]��ʾ�Ѿ�����ǰi�У���i�еĹ����ڷ������j��ǰi�У�����i���Ѿ��ڷ���k��������
 
dp���������ʼ״̬��״̬ת�ƣ���λ�ȡ��
��ʼ״̬��
��ʺ�ͬ�������Ĺ�����Χֻ������Χ��8��Ҳ����˵���������һ��һ�п��ǣ���һ�еĹ����ڷ�ֻ������һ�е����ơ�
���Կ��Գ�ʼ����һ�е�dp���飬Ȼ��һ��һ�м�����ȥ��dp[1][i][count(i)] = 1(i:0->2^n, count(i)��ʾi״̬�м���������

״̬ת�ƣ�
����j1�ǵ�ǰ���ǵ��еĹ����ڷ�״̬��j2����һ�е�״̬�� 
���ȣ���ο��������й����ܲ��ܻ��๥���أ�j1&j2 + j1&(j2<<1) + (j1<<1)&j2 == 0��ʾ���ܹ�����������ͻ�� 
ֱ��д���̣�if j1��j2����ͻ��dp[i][j1][k] = dp[i-1][j2][k-count(j1)]
���У�i j1 j2 k������Ҫö�ٵġ����Ӷ���O��n^3*��2^2n))������֮��ͨ��70%���ݡ���θ����أ�
����Ԥ����ÿһ�п��ܳ��ֵ�״��������˵��n==3ʱ��110��011��111������״�����г�ͻ�ģ�����ÿ��ö�ٶ����ҵ���
Ԥ����ʱ����ȥ�������г�ͻ��״����j&��j<<1��==0
Ȼ���AC�� 

��λ�ȡ�𰸣�
dp���鹹���ú󣬴𰸾���sigma(i:0--2^n-1)dp[n][i][k] 
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
