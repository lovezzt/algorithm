solution:
这题是问你[A, B]之内的f(n, K)和，其中f(n, k) 定义为 n 的划分数目使得n = (ab)。(a + b) % K = 0。
这题不难，用类似数位dp的思想，我们先枚举共有几位，对于共有tot位的情况，我们枚举第一个数有x位，然后第二个数有tot - x位，
然后枚举第一个数模K余i，那么第二个数模K余（K-i）%K，然后统计各有几个数相乘即可。

code:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long LL;

LL A, B, K;
int tot, digit[20], tmp[20];

LL Pow(LL a, LL b) {
	LL ret = 1;
	while(b--) {
		ret *= a;
	}
	return ret;
}

bool in(LL r1, LL r2, LL r) {
	if(r1 <= r2) {
		return r >= r1 && r <= r2;
	} else {
		return r >= r1 || r <= r2;
	}
}

LL pre(LL st, LL ed, LL r) {
	LL r1 = st % K, r2 = ed % K;
	LL cnt = (ed - st) / K;
	if(in(r1, r2, r)) {
		cnt++;
	}
	return cnt;
}

LL init(int st, int ed) {
	LL num = 0;
	for(int i = st; i <= ed; i++) {
		num = num * 10 + digit[i];
	}
	return num;
}

LL gao(int loc) {
	LL ret = 0, st1, ed1, st2, ed2, r1, r2;
	if(loc == tot + 1) {
		if(K == 1) {
			LL ed = init(0, tot);
			return (ed - Pow(10, loc - 1) + 1) * (loc - 1);
		}
		for(int i = 1; i < loc; i++) {
			int num1 = i, num2 = loc - i;
			st1 = Pow(10, num1 - 1);
			ed1 = init(0, i - 1) - 1;

			st2 = 0;
			ed2 = Pow(10, num2) - 1;

			if(ed1 >= st1) {
				for(int j = 0; j < K; j++) {
					r1 = j, r2 = (K - j) % K;
					LL tot1 = pre(st1, ed1, r1);
					LL tot2 = pre(st2, ed2, r2);
					ret += tot1 * tot2;
				}
			}

			st1 = ed1 = init(0, i - 1);

			st2 = 0;
			ed2 = init(i, tot);

			for(int j = 0; j < K; j++) {
				r1 = j, r2 = (K - j) % K;
				LL tot1 = pre(st1, ed1, r1);
				LL tot2 = pre(st2, ed2, r2);
				ret += tot1 * tot2;
			}
		}
	} else {
		LL st1, ed1, st2, ed2, r1, r2;
		if(K == 1) {
			return (Pow(10, loc) - Pow(10, loc - 1)) * (loc - 1);
		}
		for(int i = 1; i < loc; i++) {
			int num1 = i, num2 = loc - i;
			st1 =  Pow(10, (num1 - 1));
			ed1 = Pow(10, num1) - 1;

			st2 = 0;
			ed2 = Pow(10, num2) - 1;

			for(int j = 0; j < K; j++) {
				r1 = j, r2 = (K - j) % K;
				LL tot1 = pre(st1, ed1, r1);
				LL tot2 = pre(st2, ed2, r2);
				ret += tot1 * tot2;
			}
		}
	}
	return ret;
}

LL cal(LL x) {
	if(x <= 9) {
		return 0;
	}
	tot = 0;
	while(x) {
		tmp[tot++] = x % 10;
		x /= 10;
	}
	for(int i = 0; i < tot; i++) {
		digit[i] = tmp[tot - 1 - i];
	}
	tot--;
	LL ans = 0;
	for(int i = 2; i <= tot + 1; i++) {
		ans += gao(i);
	}
	return ans;
}

int main() {
	while(~scanf("%I64d%I64d%I64d", &A, &B, &K)) {
		LL Sum1 = cal(B);
		Sum1 -= cal(A - 1);
		printf("%I64d\n", Sum1);
	}
	return 0;
}

