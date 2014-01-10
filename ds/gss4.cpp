solution:
这题是给你个序列，长度10 ^ 5，2种操作，一种是把一段区间的数字变成原来的平方根，还有一种是对某一段区间求和。
首先，对一段内每个数开根号，不可能O(1)时间内完成，所以我们要想办法转化。一种办法是我们可以对每个数字求对数，
然后开根号求变成了全部乘以0.5，可以在o(1)时间内完成，但是可惜的是这样会挂精度。
然后我们可以发现，开方是一种衰减的很快的运算，我们可以利用这个性质。
一开是我的做法是，我在线段树每个结点维护一个add[6], add[i]表示对这个序列中的每一个元素开i次方，减掉的个数。不过这样的话是
严格6 o(n * log n)。
其实还有一种非常巧妙的做法，在知道每个点被操作次数不超过k时候，我们可以直接暴力每个区间，也就是一直递归到底，这样的话总复杂度
不超过k * o(n * log n)。而且往往会小于这个上界。
所以第二种做法过了，第一种做法果断TLE了。spoj真是慢。
其实第二种写法好写多了。

code:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 100010;

int n;
ll a[maxn];

struct SegTree {
	struct Key {
		int l, r;
		ll ans;

		void up(Key &a, Key &b) {
			ans = a.ans + b.ans;
		}
	} key[maxn << 2];

	void up(int rt) {
		key[rt].up(key[rt << 1], key[rt << 1 | 1]);
	}

	void build(int l, int r, int rt) {
		key[rt].l = l; key[rt].r = r;
		if(l == r) {
			key[rt].ans = a[l];
			return;
		}
		int m = (l + r) >> 1;
		build(l, m, rt << 1);
		build(m + 1, r, rt << 1 | 1);
		up(rt);
	}

	void update(int l, int r, int rt) {
		if(key[rt].r - key[rt].l + 1 == key[rt].ans) {
				return;
		}
		if(key[rt].l == key[rt].r) {
			key[rt].ans = (ll) sqrt(1.0 * key[rt].ans);
			return;
		}
		int m = (key[rt].l + key[rt].r) >> 1;
		if(l <= m) {
			update(l, r, rt << 1);	
		}
		if(r > m) {
			update(l, r, rt << 1 | 1);
		}
		up(rt);
	}

	ll query(int l, int r, int rt) {
		if(key[rt].l >= l && key[rt].r <= r) {
			return key[rt].ans;
		}
		int m = (key[rt].l + key[rt].r) >> 1;
		ll ans = 0;
		if(l <= m) {
			ans += query(l, r, rt << 1);	
		}
		if(r > m) {
			ans += query(l, r, rt << 1 | 1);
		}
		return ans;
	}
} sgt;

int main() {
	int cas = 0;
	while(~scanf("%d", &n)) {
		printf("Case #%d:\n", ++cas);
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
		}
		sgt.build(1, n, 1);
		int m, op, x, y;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			scanf("%d%d%d", &op, &x, &y);
			if(x > y) {
				swap(x, y);
			}
			if(op == 0) {
				sgt.update(x, y, 1);
			} else {
				printf("%lld\n", sgt.query(x, y, 1));	
			}
		}
		puts("");
	}
	return 0;
}
