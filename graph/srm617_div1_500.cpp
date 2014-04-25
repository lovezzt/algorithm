题意：
题意就是有50个人，进行了n次抽奖（n <= 1000），每次抽出2个人，一个人给个dolphin，另一个人给个pie。抽奖结束后，让每个人pie和dolphin的差的绝对值的和最小。让你构造一种方案。

解法：这题如果一开始久一个劲去钻那个绝对值之差就坑爹了，那个东西优化实在比较困难。所以我们要把问题转化。其实可以这样想，第一种分配方案，分到dolphin的人加1，分到pie的人减1，这样我们我们的目标就是让每个人最后的值绝对值最小。
这样就可以转化为一个图论，问题，我们要做的就是选择边的方向。
我们可以知道，度数为奇数的点最后入度和出度差是不会为0的，所以答案最少为cnt（cnt为度数为奇数的点的个数）。
然后我们可以知道，只要有一个度数为奇数的点，就一定存在另一个，因为总的度数和为偶数，这样我们可以通过加边的方式，把图转化为点的度数全部是偶数的图。所有点都为偶点的图是存在欧拉回路的，所以对于该图我们知道答案为0，然后我们把添上的边，去掉，答案就为cnt。于是我们只要按着求欧拉回路套圈法的方式找答案即可。呜呜，欧拉回路好久没写，写挂n久。

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
