solution:
这题的意思是给你一根长为n(n <= 5*10^6) 的绳子，让你把它折成几个三角形，其中这些三角形是相似的。只要两个三角型序列不是数目相同
而且对应三角形都全等就算2种不同的三角形序列。

这题做法其实不难。

首先我们考虑一个简单的问题把一个绳子分成三段（长度a, b, c)，可以组成三角形，有多少种方案。这个可以做到O(1)处理。
首先可以想到三角形的形成条件是(a <= b <= c && a + b > c)。
所以可以得到 n / 3 <= c < n / 2。
对于每一个c，b可以的取值一定是[(n - b) / 2, c]。
令st = (n - b) / 2, ed = c, num = ed - st + 1;
那么显然得可以看到在c的可行区间那ed是等差数列，st 也满足等差性质（相邻2个相同），如此便可以求出这个答案。

然后就是考虑多个互相相似的三角形的问题。
我们可以由一个基三角形状(a, b, c) [gcd(a, b, c) == 1] , 去形成一个三角形序列
令sum = a + b + c; 所以共c(n-sum, 0) + c(n-sum, 1)+...c(n-sum,b-sum) = 2^(n-sum)种。
如果基三角形gcd(a, b, c) == g, 所以由它形成的序列一定可以由基三角形（a/g, b/g, c/g)形成。
但是a+b+c = sum, gcd(a, b, c) == 1的三角行数目直接求不好求，所以我们考虑容斥。容斥是考虑最大公因数是p的倍数。

所以最后的做法就是枚举因子加上容斥。由于因子数目不多，所以容斥很快。


code:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;
int n;

LL cal(LL N) {
	LL st, ed;
	if(N % 3 == 0) {
		st = N / 3;
	} else {
		st = N / 3 + 1;
	}
	if(N % 2 == 0) {
		ed = N / 2 - 1;
	} else {
		ed = N / 2;
	}
	//cout << st << " " << ed << endl;
	LL tot = (ed - st + 1);
	LL sum1 = (st + ed) * tot / 2;
	LL add = 0;
	st = N - st; ed = N - ed;
	if(st % 2 == 1) {
		add += (st / 2 + 1);
		st--;
	}
	if(ed % 2 == 0) {
		add += (ed / 2);
		ed++;
	}
	st = st / 2 ;
	ed = ed / 2 + 1;
	swap(st, ed);
	//cout << add << endl;
	//cout << st << "**" << ed << endl;
	LL sum2 = (st + ed) * (ed - st + 1);
	sum2 += add;
	LL ret = sum1 - sum2 + tot;
	//cout << sum1 << " " << sum2 << endl;
	//cout << tot << " " << ret << endl;
	return ret % MOD;
}

LL Pow(LL a, LL b) {
	LL ret = 1;
	while(b) {
		if(b & 1) {
			ret = (ret * a) % MOD;
		}
		a = (a * a) % MOD;
		b >>= 1;
	}
	return ret;
}

const int MAXN = 10010;
int flag[MAXN], prime[MAXN], t;

void pre() {
	t = 0;
	memset(flag, 0, sizeof(flag));
	for(int i = 2; i < MAXN; i++) {
		if(!flag[i]) {
			prime[t++] = i;
		}
		for(int j = 0; j < t && prime[j] * i < MAXN; j++) {
			flag[i * prime[j]] = 1;
			if(i % prime[j] == 0) {
				break;
			}
		}
	}
}

int tot;
LL p[30], k[30];

void dis(int n) {
	tot = 0;
	int now = n;
	for(int i = 0; i < t; i++) {
		if(now % prime[i] == 0) {
			int tmp = 1;
			now /= prime[i];
			while(now % prime[i] == 0) {
				now /= prime[i];
				tmp++;
			}
			tot++; p[tot] = prime[i]; k[tot] = tmp;
		}
	}
	if(now != 1) {
		tot++; p[tot] = now; k[tot] = 1;
	}
}

LL ans;

void dfs1(LL N, LL now, int num, int step) {
	if(step == tot + 1) {
		if(num % 2 == 1) {
			ans = (ans - cal(N / now)) % MOD;
			ans = (ans + MOD) % MOD;
		} else {
			ans = (ans + cal(N / now)) % MOD;
		}
		return;
	}
	dfs1(N, now * p[step], num + 1, step + 1);
	dfs1(N, now, num , step + 1);
}

LL fac[10010], num;

void dfs2(int step, LL now) {
	if(step == tot + 1) {
		fac[num++] = now;
		return;
	}
	dfs2(step + 1, now);
	for(int i = 1; i <= k[step]; i++) {
		now *= p[step];
		dfs2(step + 1, now);
	}
}

LL solve() {
	dis(n);
	num = 0;
	dfs2(1, 1);
	LL ret = 0;
	for(int i = 0; i < num; i++) {
		dis(fac[i]);
		ans = 0;
		dfs1(fac[i], 1, 0, 1);
		ans = (ans * Pow(2, n / fac[i] - 1)) % MOD;
		ret = (ret + ans) % MOD;
	}
	return ret;
}

int main() {
	//freopen("/home/lovezzt/桌面/input.txt", "r", stdin);
	int cas = 0;
	pre();
	while(~scanf("%d", &n)) {
		printf("Case %d: %I64d\n", ++cas, solve());
	}
	return 0;
}

