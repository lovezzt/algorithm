���⣺
���������50���ˣ�������n�γ齱��n <= 1000����ÿ�γ��2���ˣ�һ���˸���dolphin����һ���˸���pie���齱��������ÿ����pie��dolphin�Ĳ�ľ���ֵ�ĺ���С�����㹹��һ�ַ�����

�ⷨ���������һ��ʼ��һ����ȥ���Ǹ�����ֵ֮��Ϳӵ��ˣ��Ǹ������Ż�ʵ�ڱȽ����ѡ���������Ҫ������ת������ʵ���������룬��һ�ַ��䷽�����ֵ�dolphin���˼�1���ֵ�pie���˼�1�������������ǵ�Ŀ�������ÿ��������ֵ����ֵ��С��
�����Ϳ���ת��Ϊһ��ͼ�ۣ����⣬����Ҫ���ľ���ѡ��ߵķ���
���ǿ���֪��������Ϊ�����ĵ������Ⱥͳ��Ȳ��ǲ���Ϊ0�ģ����Դ�����Ϊcnt��cntΪ����Ϊ�����ĵ�ĸ�������
Ȼ�����ǿ���֪����ֻҪ��һ������Ϊ�����ĵ㣬��һ��������һ������Ϊ�ܵĶ�����Ϊż�����������ǿ���ͨ���ӱߵķ�ʽ����ͼת��Ϊ��Ķ���ȫ����ż����ͼ�����е㶼Ϊż���ͼ�Ǵ���ŷ����·�ģ����Զ��ڸ�ͼ����֪����Ϊ0��Ȼ�����ǰ����ϵıߣ�ȥ�����𰸾�Ϊcnt����������ֻҪ������ŷ����·��Ȧ���ķ�ʽ�Ҵ𰸼��ɡ����أ�ŷ����·�þ�ûд��д��n�á�

code:
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
using namespace std;

typedef long long ll;
#define clr(x,a) memset(x,a,sizeof(x))
#define sz(x) (int)x.size()
#define see(x) cerr<<#x<<" "<<x<<endl
#define se(x) cerr<<" "<<x 
#define pb push_back
#define mp make_pair

struct Edge {
	int id, v, type, flag, nx;
} E[100010];
int head[60], cnt;
int result[100010];
int vst[60];
int deg[60];
int sum[60];

void add(int u, int v, int id, int type) {
	E[cnt].nx = head[u];
	E[cnt].v = v;
	E[cnt].id = id;
	E[cnt].type = type;
	E[cnt].flag = 0;
	head[u] = cnt++;
}

void init() {
	memset(head, -1, sizeof(head));
	cnt = 0;
	memset(vst, 0, sizeof(vst));
	memset(deg, 0, sizeof(deg));
	memset(result, 0, sizeof(result));
	memset(sum, 0, sizeof(sum));
