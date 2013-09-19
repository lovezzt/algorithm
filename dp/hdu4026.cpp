solution: 这题难度不大，预处理完以后就是一个装压dp问题， 关键是状态比较稀疏，所以直接记忆化搜索比较好；而如果状态比较多，则直接for循环处理比较好。
唉，姿势不对，肯定就要各种T。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const int MAXN = 30;
const int MAXE = 60050;

int head[MAXN], cnt, mp[30][30];
struct Edge {
	int v, w, nx;
}E[MAXE];

int gcd(int a, int b) {
	if(b == 0) {
		return a;
	} else {
		return gcd(b, a % b);
	}
}

void add(int u, int v, int w) {
	E[cnt].v = v; E[cnt].w = w; E[cnt].nx = head[u];
	head[u] = cnt++;
	mp[u][v] = w;
	swap(u, v);
	E[cnt].v = v; E[cnt].w = w; E[cnt].nx = head[u];
	head[u] = cnt++;
	mp[u][v] = w;
}

int a[30][30], n, m;
int id[30][30], tot;

void  build() {
	tot = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 0) {
				id[i][j] = tot++;
			}
		}
	}

	memset(head, -1, sizeof(head));
	cnt = 0;
	memset(mp, -1, sizeof(mp));

	//cout << tot << "fuck" << endl;

	for(int i1 = 1; i1 <= n; i1++) {
		for(int j1 = 1; j1 <= m; j1++) {
			// 横着
			int i2 = i1;
			for(int j2 = j1 + 1; j2 <= m; j2++) {
				if(a[i1][j1] != 0 || a[i2][j2] != 0) {
					continue;
				}
				int w = 0;
				bool flag = 0;
				for(int k = j1 + 1; k < j2; k++) {
					if(a[i1][k] == 0) {
						int tt = id[i1][k];
						w |= (1 << tt);
					} else if(a[i1][k] == 1) {
						flag = 1;
						break;
					}
				}
				if(!flag) {
					int id1 = id[i1][j1], id2 = id[i2][j2];
					add(id1, id2, w);
					//cout << id1 << " " << id2 << " " << w << endl;
				}
			}

			// 竖着
			int j2 = j1;
			for(int i2 = i1 + 1; i2 <= n; i2++) {
				if(a[i1][j1] != 0 || a[i2][j2] != 0) {
					continue;
				}
				int w = 0;
				bool flag = 0;
				for(int k = i1 + 1; k < i2; k++) {
					if(a[k][j1] == 0) {
						int tt = id[k][j1];
						w |= (1 << tt);
					} else if(a[k][j1] == 1) {
						flag = 1;
						break;
					}
				}
				if(!flag) {
					int id1 = id[i1][j1], id2 = id[i2][j2];
					add(id1, id2, w);
			//		cout << id1 << " " << id2 << " " << w << endl;
				}
			 }

			// 斜下着
			for(int i2 = i1 + 1; i2 <= n; i2++) {
				for(int j2 = 1; j2 <= m; j2++) {
					if(i1 == i2 || j1 == j2) {
						continue;
					}
					if(a[i1][j1] == 0 && a[i2][j2] == 0) {
						int id1 = id[i1][j1], id2 = id[i2][j2];
						int w = 0;
						bool flag = 0;
						int dx = i2 - i1, dy = j2 - j1;
						int g = gcd(abs(dx), abs(dy));
						dx /= g; dy /= g;
						int x = i2 - dx, y = j2 - dy;
						while(x != i1 && y != j1) {
							if(a[x][y] == 0) {
								int tt = id[x][y];
								w |= (1 << tt);
							} else if(a[x][y] == 1) {
								flag = 1;
								break;
							}
							x -= dx; y -= dy;
						}
						if(!flag) {
							add(id1, id2, w);
							//cout << id1 << " " << id2 << " " << w << endl;
						}
					}
				}
			}
		}
	}
}

vector<int> cn[1 << 17];

void pre() {
	for(int i = 0; i < (1 << 16); i++) {
		for(int j = 0; j < 16; j++) {
			if( ((1 << j) & i) > 0)  {
				cn[i].push_back(j);
			}
		}
	}
}

LL dp[1 << 17][20];

LL solve2(int st) {
	for(int i = 0; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
			dp[i][j] = 0;
		}
	}
	dp[1 << st][st] = 1;
//	cout << endl;
//	cout << dp[1][0] << "&&" << endl;
	for(int i = 1; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
			if((i & (1 << j)) == 0) {
				continue;
			}
			if(cn[i].size() == 1) {
				continue;
			}
			for(int k = 0; k < (int) cn[i].size(); k++) {
				int v = cn[i][k];
				//cout << v << "^^" << i << endl;
				if(v == j) {
					continue;
				}
				if(mp[v][j] == -1) {
					continue;
				}
				int w = mp[v][j];
				int pre = i - (1 << j);


				if((pre & w) == w) {
	//				cout << "**" << endl;
/*					if(pre == 1 && v == 0) {
							cout << i << "fuckfuck " << j << endl;
					}
	*/				dp[i][j] += dp[pre][v];
				}
			}
		}
	}
	LL ret = 0;

	for(int i = 0; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
	//	cout << i << " " << j << ":" << dp[i][j] << endl;
		}
	}
	for(int i = 0; i < tot; i++) {
		ret += dp[(1 << tot) - 1][i];
	}
	return ret;
}

LL solve(int st) {
	for(int i = 0; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
			dp[i][j] = 0;
		}
	}
	dp[1 << st][st] = 1;
	for(int i = 1; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
			if(dp[i][j] == 0) {
				continue;
			}
			int u = j;
			for(int k = head[u]; ~k; k = E[k].nx) {
				int v = E[k].v, w = E[k].w;
				if((i & (1 << v)) > 0) {
					continue;
				}
				int st = (i | (1 << v));
				if( (i & w) == w) {
					dp[st][v] += dp[i][j];
				}
			}
		}
	}
	LL ret = 0;

/*	for(int i = 0; i < (1 << tot); i++) {
		for(int j = 0; j < tot; j++) {
			cout << i << " " << j << ":" << dp[i][j] << endl;
		}
	}
*/	for(int i = 0; i < tot; i++) {
		ret += dp[(1 << tot) - 1][i];
	}
	return ret;
}

LL dfs(int st, int pos) {
	if(dp[st][pos] != -1) {
		return dp[st][pos];
	}
	if(st == (1 << pos)) {
		dp[st][pos] = 1;
	} else {
		dp[st][pos] = 0;
		for(int k = 0; k < (int) cn[st].size(); k++) {
			int v = cn[st][k];
			if(v == pos) {
				continue;
			}
			if(mp[v][pos] == -1) {
				continue;
			}
			int w = mp[v][pos];
			int pre = st - (1 << pos);
			if((pre & w) == w) {
				dp[st][pos] += dfs(pre, v);
			}
		}
	}
	return dp[st][pos];
}

int main() {
	pre();
	while(~scanf("%d%d", &n, &m)) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d", &a[i][j]);
			}
		}

		build();

		LL ans = 0;

		memset(dp, -1, sizeof(dp));
		for(int i = 0; i < tot; i++) {
			ans += dfs((1 << tot) -1 , i);
		}
/*		LL ans = 0;
		for(int i = 0; i < tot; i++) {
//			cout << ans << "**" << endl;
			ans += solve2(i);
		}

	*/	printf("%I64d\n", ans);
	}
	return 0;
}

