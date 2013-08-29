solution:
多校第二场的A题，比赛时候我跪成狗了，其实不难。
题意是让你求sigma(abs(x % A - x % B)) (0 < x < 1000000000, 1 <= A <= 1000000, 1 <= B <= 1000000)。
首先就是模一定有个循环，这个一定要意识到，这个表达式的循环节就是lcm（A， B）。
每次只要算循环节里面的。对于循环结里面的，他一定是分成一段一段的，每段里面答案相同，所以只要模拟一下即可。
复杂么，可以这么想，当lcm大的时候循环节里面间隔也大，所以总的复杂度不会很高，精确分析暂时不会。
code:
/*
Author:lovezzt
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <complex>
#include <cassert>
using namespace std;

typedef long long LL;

const int MAXN = 2000010;
int p[MAXN]; 
int n, A, B, tot;

LL lcm(int a, int b) {
	return (LL) a * b / __gcd(a, b);
}

inline int up(int st, int x) {
	return (st / x + 1) * x;
}

LL cal(int st, int ed) {
	tot = 0;
	p[tot++] = st;
//	cout << up(st, A) << "%%" << endl;
	for(int i = up(st, A); i <= ed; i += A) {
		p[tot++] = i;
	}
	for(int i = up(st, B); i <= ed; i += B) {
		p[tot++] = i;
	}
	sort(p, p + tot);
//	for(int i = 0; i < tot; i++) {
//		cout << i << "  " << p[i] << endl;
//	}
	LL ans = 0;
	for(int i = 0; i < tot; i++) {
		int aa = p[i], bb = (i == tot-1) ? ed + 1 : p[i+1];
		int p = abs(aa % A - aa % B);
		ans += (LL) p * (bb - aa);
	}
	return ans;
}

LL work() {
	LL LCM = lcm(A, B);
//	cout << LCM << "&&" << endl;
	LL ret;
	if(LCM >= n) {
		ret = cal(0, n-1);
	}else {
		LL tt = cal(0, LCM - 1);
//		cout << tt << "^^" << endl;
		LL dd = (LL) n / LCM;
		LL re = (LL) n % LCM; 
//		cout << re << "^^" << endl;
		ret = tt * dd;
//		cout << ret << "**" << endl;
		if(re != 0) {
			ret += cal(dd * LCM, n-1);
		}
	}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("1.in", "r", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &A, &B);
		printf("%I64d\n", work());
	}
	return 0;
}

