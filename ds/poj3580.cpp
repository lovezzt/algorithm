solution:
也是基本的splay，有了删除和添加操作，由于不多，不需要内存池，坑爹的是我把revolve操作理解错了，我晕。自己测数据没发现。唉
感觉在里面写个dubug函数还是挺方便的。

code:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 200010;

int n, m;
ll a[maxn];

struct Splay {
#define ls(x) key[x].next[0]
#define rs(x) key[x].next[1]
	struct Key {
		int next[2];
		int sz;
		ll add, ans, val;
		bool rev;

		Key() {
			next[0] = next[1] = 0;
			sz = add = val = 0;
			ans = (1ll << 62);
		}

		void reverse() {
			rev ^= 1;
			swap(next[0], next[1]);
		}

		void Add(ll D) {
			add += D;
			ans += D;
			val += D;
		}

		void up(Key &a, Key &b) {
			sz = a.sz + b.sz + 1;
			ans = val;
			ans = min(ans, a.ans);
			ans = min(ans, b.ans);
		}

		void down(Key &a, Key &b) {
			if(rev) {
				a.reverse();
				b.reverse();
				rev = 0;
			}
			if(add) {
				a.Add(add);
				b.Add(add);
				add = 0;
			}
		}
	} key[maxn];
	
	int pre[maxn], root;
	int tot, num;

	void up(int x) {
		key[x].up(key[ls(x)], key[rs(x)]);
	}

	void down(int x) {
		key[x].down(key[ls(x)], key[rs(x)]);
	}

	void rotate(int x, int kind) {
		int y = pre[x];
		int z = pre[y];
		key[y].next[!kind] = key[x].next[kind];
		pre[key[x].next[kind]] = y;
		key[z].next[key[z].next[1] == y] = x;
		pre[x] = z;
		key[x].next[kind] = y;
		pre[y] = x;
		up(y);
	}

	void splay(int x, int goal) {
		while(pre[x] != goal) {
			int kind1 = (ls(pre[x]) == x);
			if(pre[pre[x]] == goal) {
				rotate(x, kind1);
			} else {
				int kind2 = (ls(pre[pre[x]]) == pre[x]);
				if(kind1 == kind2) {
					rotate(pre[x], kind2);
					rotate(x, kind1);
				} else {
					rotate(x, kind1);
					rotate(x, kind2);
				}
			}
		}
		up(x);
		if(goal == 0) {
			root = x;
		}
	}

	void RotateTo(int k, int goal) {
		int x = root;
		down(x);
		while(1) {
			int sz = key[ls(x)].sz;
			if(sz + 1 == k) {
				break;
			} else if(k <= sz) {
				x = ls(x);
			} else {
				x = rs(x);
				k -= (sz + 1);
			}
			down(x);
		}
		splay(x, goal);
	}
	
	int build(int l, int r) {
		if(l > r) {
			return 0;
		}
		int x = (l + r) >> 1;
		key[x].sz = 1; key[x].val = a[x]; key[x].ans = a[x]; key[x].rev = 0; key[x].add = 0;
		ls(x) = rs(x) = 0;
		pre[x] = 0;
		if(l != r) {
			ls(x) = build(l, x - 1);
			rs(x) = build(x + 1, r);
			pre[ls(x)] = x;
			pre[rs(x)] = x;
			up(x);
		}
		return x;
	}

	void build(int n) {
		root = build(1, n);
		num = tot = n;
	}
	
	int new_node(ll val) {
		int id = ++tot;
		num++;
		key[id].ans = val; key[id].val = val; key[id].add = 0; key[id].rev = 0; key[id].sz = 1;
		key[id].next[0] = key[id].next[1] = 0;
		return id;
	}

	int make_range(int x, int y) {
		RotateTo(x - 1, 0);
		RotateTo(y + 1, root);
		return ls(rs(root));
	}

	void Add(int x, int y, ll D) {
		int id = make_range(x, y);
		key[id].Add(D);
	}

	void Reverse(int x, int y) {
		int id = make_range(x, y);
		key[id].reverse();
	}

	void Revolve(int x, int y, ll T) {
		int len = y - x + 1;
		T = ((T % len) + len) % len;
		if(T == 0) {
			return;
		}
		int id = make_range(x, y);
		key[id].reverse();
		id = make_range(x + T, y);
		key[id].reverse();
		id = make_range(x, x + T - 1);
		key[id].reverse();
	}

	void Insert(int x, ll P) {
		RotateTo(x, 0);
		RotateTo(x + 1, root);
		ls(rs(root)) = new_node(P);
		pre[ls(rs(root))] = rs(root);
		up(rs(root));
		up(root);
		splay(ls(rs(root)), 0);
	}

	void Delete(int x) {
		RotateTo(x, 0);
		pre[ls(root)] = pre[rs(root)] = 0;
		int Left = ls(root), Right = rs(root);
		ls(root) = rs(root) = 0;
		root = Right;
		RotateTo(1, 0);
		key[root].next[0] = Left;
		pre[Left] = root;
		up(root);
		num--;
	}

	void debug() {
		for(int i = 2; i <= num - 1; i++) {
			RotateTo(i, 0);
			cout << key[root].val << "*** ";
		}
		cout << "hehe" << endl;
	}

	void Min(int x, int y) {
		int id = make_range(x, y);
		printf("%lld\n", key[id].ans);
	}
} spt;

void sol() {
	while(~scanf("%d", &n)) {
		a[1] = a[n + 2] = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &a[i + 1]);
		}
		spt.build(n + 2);
		scanf("%d", &m);
		char s[10];
		for(int i = 1; i <= m; i++) {
			scanf("%s", s);
			if(strcmp(s, "ADD") == 0) {
				int x, y;
				ll D;
				scanf("%d%d%lld", &x, &y, &D);
				spt.Add(x + 1, y + 1, D);
			} else if(strcmp(s, "REVERSE") == 0) { 
				int x, y;
				scanf("%d%d", &x, &y);
				spt.Reverse(x + 1, y + 1);
			} else if(strcmp(s, "REVOLVE") == 0) {
				int x, y;
				ll T;
				scanf("%d%d%lld", &x, &y, &T);
				spt.Revolve(x + 1, y + 1, T);
			} else if(strcmp(s, "INSERT") == 0) {
				int x;
				ll P;
				scanf("%d%lld", &x, &P);
				spt.Insert(x + 1, P);
			} else if(strcmp(s, "DELETE") == 0) {
				int x;
				scanf("%d", &x);
				spt.Delete(x + 1);
			} else {
				int x, y;
				scanf("%d%d", &x, &y);
				spt.Min(x + 1, y + 1);
			}
//			spt.debug();
		}
	}
}

int main() {
	sol();
	return 0;
}
