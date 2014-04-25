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
