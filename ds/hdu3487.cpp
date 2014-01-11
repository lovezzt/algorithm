solution:
splay 裸题，没有插入，删除，但有取区间的操作，注意splay是以自身为轴旋转的，一定要主要维护pre数组。

code:
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 300010;

int ans[maxn], cnt = 0;

struct Splay {
#define ls(x) key[x].next[0]
#define rs(x) key[x].next[1]
	struct Key {
		int next[2];
		int val, sz;
		bool rev;

		void reverse() {
			rev ^= 1;
			swap(next[0], next[1]);
		}
		
		void up(Key &a, Key &b) {
			sz = a.sz + b.sz + 1;
		}

		void down(Key &a, Key &b) {
			if(rev) {
				a.reverse();
				b.reverse();
				rev = 0;
			}
		}
	} key[maxn];
	int pre[maxn], root; // default 0

	void up(int x) {
		key[x].up(key[ls(x)], key[rs(x)]);
	}
		
	void down(int x) {
		key[x].down(key[ls(x)], key[rs(x)]);
	}

// only when there are some insert operations
	Key new_node(int val) {
		Key ret;
		ret.val = val; ret.sz = 1; ret.next[0] = ret.next[1] = 0; ret.rev = 0;
		return ret;
	}
// rotate on node x own
	void rotate(int x, int kind) {
		int y = pre[x];
		int z = pre[y];
		key[y].next[!kind] = key[x].next[kind];
		pre[key[x].next[kind]] = y;
		key[z].next[rs(z) == y] = x;
		pre[x] = z;
		key[x].next[kind] = y;
		pre[y] = x;
		up(y);
	}
// splay node x under node goal
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
// rotate kth node under node goal (the only interface) 
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

// depend on the problem
	int build(int l, int r) {
		if(l > r) {
			return 0;
		}
		int x = (l + r) >> 1;
		key[x] = new_node(x);
		pre[x] = 0;
		if(l != r) {
			ls(x) = build(l, x - 1);
			rs(x) = build(x + 1, r);
			if(ls(x) != 0) {
				pre[ls(x)] = x;
			}
			if(rs(x) != 0) {
				pre[rs(x)] = x;
			}
			up(x);
		}
		return x;
	}

	void build(int n) {
		root = build(1, n);
	}

	void cut(int a, int b, int c) {
		// cut
		RotateTo(a - 1, 0);
		RotateTo(b + 1, root); 
		int part = ls(rs(root));
		key[root].sz -= key[part].sz;
		key[rs(root)].sz -= key[part].sz;
		ls(rs(root)) = 0;
		pre[part] = 0;
		// add
		RotateTo(c + 1, 0);
		RotateTo(c, root);
		rs(ls(root)) = part;
		pre[part] = ls(root);
		key[root].sz += key[part].sz;
		key[ls(root)].sz += key[part].sz;
	}

	void flip(int a, int b) {
		// [a. b]
		RotateTo(a - 1, 0);
		RotateTo(b + 1, root);
		key[ls(rs(root))].reverse();
	}

	void dfs(int x) { 
		if(x == 0) {
			return;
		}
		down(x);
		dfs(ls(x));
		ans[++cnt] = key[x].val;
		dfs(rs(x));
	}

	void output() {
		cnt = 0;
		dfs(root);
	}
}spt;

int n, m;

void sol() {
// add two nodes in the front and at the end
	spt.build(n + 2);
	char s[10];
	int a, b, c;
	for(int i = 1; i <= m; i++) {
		scanf("%s", s);
		if(s[0] == 'C') {
			scanf("%d%d%d", &a, &b, &c);
			spt.cut(a + 1, b + 1, c + 1);
		} else {
			scanf("%d%d", &a, &b);
			spt.flip(a + 1, b + 1);
		}
	}
	spt.output();
	for(int i = 2; i <= n + 1; i++) {
		printf("%d%c", ans[i] - 1, (i == n + 1) ? '\n' : ' ');
	}
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		if(n < 0 && m < 0 ) {
			break;
		}
		sol();	
	}
	return 0;
}
