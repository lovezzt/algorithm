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
}

// euler 
void dfs(int u) {
	vst[u] = 1;
	for(int i = head[u]; ~i; i = E[i].nx) {
		int v = E[i].v, id = E[i].id;
		int type = E[i].type;
		if(E[i].flag) {
			continue;
		}
		E[i ^ 1].flag = E[i].flag = 1;
		result[id] = type;
		dfs(v);
	}
}

class PieOrDolphin {
        public:
        vector <int> Distribute(vector <int> choice1, vector <int> choice2) {
			init();
			int m = (int) choice1.size();
			for(int i = 0; i < m; i++) {
				int u = choice1[i], v = choice2[i];
				deg[u]++; deg[v]++;
				add(u, v, i, 1);
				add(v, u, i, 2);
			}
			int sum_odd = 0;
			for(int i = 0; i < 50; i++) {
				if(deg[i] & 1) {
					sum_odd++;	
				}
			}
			cout << "sum_odd: " << sum_odd << endl;
			for(int i = 0; i < 50; i++) if(deg[i] & 1) {
				for(int j = i + 1; j < 50; j++) if(deg[j] & 1) {
					deg[i]++; deg[j]++;
					add(i, j, m, 1);
					add(j, i, m, 2);
					break;
				}
			}
			for(int i = 0; i < 50; i++) if(!vst[i]) {
				dfs(i);
			}
			for(int i = 0; i < m; i++) {
				int u = choice1[i], v = choice2[i];
				if(result[i] == 1) {
					sum[u]++; sum[v]--;
				} else {
					sum[v]++; sum[u]--;
				}
			}
			int re = 0;
			for(int i = 0; i < 50; i++) {
				re += abs(sum[i]);
			}
			cout << re << "**********" << endl;
			vector<int> ret;
			for(int i = 0; i < m; i++) {
				ret.push_back(result[i]);
			}
			return ret;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {10, 20, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 30, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 1, 2, 3, 5, 6, 7, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 7, 6, 5, 3, 2, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2, 2, 2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {49, 0, 48, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {21,4,14,0,31,46,1,34,2,3,27,19,47,46,17,11,41,12,31,0,34,18,8,14,23,40,0,18,48,35,42,24,25,32,25,44,17,6,44,34,12,39,43,39,26,
34,10,6,13,2,40,15,16,32,32,29,1,23,8,10,49,22,10,15,40,20,0,30,1,43,33,42,28,39,28,4,38,11,5,1,47,12,0,22,20,33,33,34,18,8,23,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {25,5,39,20,44,47,11,49,42,17,25,15,23,11,32,17,24,4,11,47,27,41,40,0,49,27,5,28,6,11,18,0,17,1,0,32,45,28,17,5,13,40,40,25,33,
7,8,32,12,0,39,30,8,39,23,9,8,34,34,37,5,1,24,23,0,29,11,42,29,40,24,18,37,1,21,0,31,47,23,33,45,48,31,11,40,45,24,22,19,26,37,39}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, Distribute(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
        PieOrDolphin ___test;
        ___test.run_test(-1);
        return 0;
}
/
