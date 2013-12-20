solution:
这题是给你一个n * m的01矩阵，问你至少改变多少个位置的值可以保证至少rowCount个行和columnCount个列是回文串。

首先我们可以非常自然得想到通过枚举行列，然后计算这种情况的最优值。
但是这样应该会超时，所以我们考虑枚举列，然后对行去dp。
我们可以发现(i, n - 1 - i)之间的矩形和x <= i && y >= n - 1 - i 的矩形无关，所以我们可以dp[i][j], 表示考虑到了第i行，加入了j列。转移的时候和暴力枚举情况一样。

还是若爆了，这么简单一个dp，写挂好久。呜呜。

code:
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef long long LL;

#define SZ(x) (int(x.size()))

int n, m, cc, rc;
int ans;
bool ok[30];
int dp[20][20], mp[20][20];

int process1(int r) {
	int ret = 0;
	for(int i = 0; i < m / 2; i++) {
		int a = i, b = m - 1 - i, tmp = 0;
		if(!ok[a] && !ok[b]) {
			tmp = mp[r][a] + mp[r][b];
			tmp = min(tmp, 2 - tmp);
		} else {
			if(!ok[a]) {
				tmp = mp[r][a] + mp[r][b] + mp[n - 1 - r][b];
				tmp = min(tmp, 3 - tmp) - (mp[n - 1 - r][b] != mp[r][b]);
			} else if(!ok[b]) {
				tmp = mp[r][a] + mp[n - 1 - r][a] + mp[r][b];	
				tmp = min(tmp, 3 - tmp) - (mp[n - 1 - r][a] != mp[r][a]);
			} else {
				tmp = mp[r][a] + mp[r][b] + mp[n - 1 - r][a] + mp[n - 1 - r] [b];
				tmp = min(tmp, 4 - tmp) - (mp[n - 1 - r][a] != mp[r][a]) - (mp[n - 1 - r][b] != mp[r][b]);
/*				if(m == 4 && ok[0] && !ok[1] && !ok[2] && ok[3]) {
					cout << tmp << "caocaocao" << endl;
				}
*/			}
		}
		ret += tmp;	
	}
	return ret;
}

int process2(int r) {
	int ret = 0;
	for(int i = 0; i < m / 2; i++) {
		int a = i, b = m - 1 - i, tmp = 0;
		if(!ok[a] && !ok[b]) {
			int tmp1 = mp[r][a] + mp[r][b];
			tmp1 = min(tmp1, 2 - tmp1);
			int tmp2 = mp[n - 1 - r][a] + mp[n - 1 - r][b];
			tmp2 = min(tmp2, 2 - tmp2);
			tmp = tmp1 + tmp2;
		} else {
			tmp = mp[r][a] + mp[r][b] + mp[n - 1 - r][a] + mp[n - 1 - r][b];
			tmp = min(tmp, 4 - tmp);
			if(ok[a]) {
				tmp -= (mp[r][a] != mp[n - 1 - r][a]);
			}
			if(ok[b]) {
				tmp -= (mp[r][b] != mp[n - 1 - r][b]);
			}
		}
		ret += tmp;
	}
	return ret;
}

int cal() {
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	dp[0][1] = min(process1(0), process1(n - 1));
	dp[0][2] = process2(0);
/*	if(m == 4 && ok[0] && !ok[1] && !ok[2] && ok[3]) {
		cout << dp[0][2] << "fuck" << endl;
	}
*/	int ed = (n % 2) ? n / 2 : n / 2 - 1;
	for(int i = 1; i < n / 2; i++) {
		for(int j = 0; j <= rc; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j - 1 >= 0 && dp[i - 1][j - 1] != -1) {
				int tmp = min(process1(i), process1(n - 1 - i)) + dp[i - 1][j - 1];
				if(dp[i][j] == -1) {
					dp[i][j] = tmp;
				} else {
					dp[i][j] = min(dp[i][j], tmp);
				}
			}
			if(j - 2 >= 0 && dp[i - 1][j - 2] != -1) {
				int tmp = process2(i) + dp[i - 1][j - 2];
				if(dp[i][j] == -1) {
					dp[i][j] = tmp;
				} else {
					dp[i][j] = min(dp[i][j], tmp);
				}
			}
		}
	}
/*	if(m == 4 && ok[0] && !ok[1] && !ok[2] && ok[3]) {
		cout << dp[1][3] << "fuck" << endl;
	}
*/	if(n % 2 && n != 1) {
		for(int i = 0; i <= rc; i++) {
			int sum = 0;
			dp[n / 2][i] = dp[n / 2 - 1][i];
			for(int j = 0; j < m / 2; j++) {
				int a = j, b = m - 1 - j;
				int tmp = (mp[n / 2][a] == mp[n / 2][b]) ? 0 : 1;
				sum += tmp;
			}
			if(i - 1 >= 0 && dp[n / 2][i - 1] != -1) {
				int tt = dp[n / 2][i - 1] + sum;
				if(dp[n / 2][i] == -1) {
					dp[n / 2][i] = tt;
				} else {
					dp[n / 2][i] = min(dp[n / 2][i], tt);
				}
			}
		}
	}
	return dp[ed][rc];
}

int pre() {
	int ret = 0;
	for(int i = 0; i < m; i++) {
		if(ok[i]) {
			for(int j = 0; j < n / 2; j++) {
				ret += (mp[j][i] == mp[n - 1 - j][i]) ? 0 : 1;
			}
		}
	}
	return ret ;
}

void dfs(int loc, int tot) {
	if(loc == m) {
		if(tot >= cc) {
/*			if(m == 4 && ok[0] && !ok[2] && ok[3] && !ok[1]) {
				cout << pre() <<  "&&" << endl;
			}
*/			int tmp = pre();
			ans = min(ans, tmp + cal());
		}
		return;
	}
	ok[loc] = 1;
	dfs(loc + 1, tot + 1);
	ok[loc] = 0;
	dfs(loc + 1, tot);
}
 
class PalindromeMatrix {
public:
    int minChange(vector <string> A, int rowCount, int columnCount)  {
		n = (int) A.size(), m = (int) A[0].size();
		rc = rowCount, cc = columnCount;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				mp[i][j] = A[i][j] - '0';
			}
		}
        ans = 1 << 30;
		memset(ok, 0, sizeof(ok));
		dfs(0, 0);
        return ans;
     }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0000"
,"1000"
,"1100"
,"1110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 1; verify_case(0, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0000"
,"1000"
,"1100"
,"1110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; int Arg3 = 3; verify_case(1, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"01"
,"10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(2, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"1110"
,"0001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; verify_case(3, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 8; verify_case(4, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"000000000000"
,"011101110111"
,"010001010101"
,"010001010101"
,"011101010101"
,"010101010101"
,"010101010101"
,"011101110111"
,"000000000000"
,"000000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 9; int Arg3 = 14; verify_case(5, Arg3, minChange(Arg0, Arg1, Arg2)); }
	void test_case_6() { string Arr0[] = {"11111101001110"
,"11000111111111"
,"00010101111001"
,"10110000111111"
,"10000011010010"
,"10001101101101"
,"00101010000001"
,"10111010100100"
,"11010011110111"
,"11100010110110"
,"00100101010100"
,"01001011001000"
,"01010001111010"
,"10100000010011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 8; int Arg3 = 31; verify_case(6, Arg3, minChange(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
        PalindromeMatrix ___test;
        ___test.run_test(-1);
        return 0;
}
/
