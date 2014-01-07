solution:
题目意思是给你2个字符串A、B, 满足A、B的长度均为n，A、B均由前k个小写字母组成，并且满足存在一个字符串C，满足A + C = C + B。
给你n <= 10^9 , k <= 26, 问你满足条件的对数有多少。
首先A + C = C + B, 可以得出 B 循环同构于 A， 所以题目就转化了对于每个A， 求出循环同构与A的字符串的数目，求和即可。
然后我们可以知道循环同构的话，由A出发第一个重复遇到的元素一定是A，然后就可以dp了。
然后画一下，可以知道最小循环节是A’，A = (A') ^ k。
dp[k]表示长度为k，最小循环节长度 < k 的字符串个数， 转移的话枚举因子即可(注意1的特例，这里我还挂了), 晕。
写题一定要想得很清楚再去写才对。

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

typedef long long ll;

const ll mod = 1000000007ll;

map<int, ll> dp;

ll Pow(ll a, ll b) {
	ll ret = 1;
	while(b) {
		if(b & 1) {
			ret = (ret * a) % mod;	
		}
		b >>= 1;
		a = (a * a) % mod;
	}
	return ret;
}

ll dfs(int x, int k) {
	if(dp.find(x) != dp.end()) {
		return dp[x];
	}
	if(x == 1) {
		dp[x] = 0;
		return 0;
	}
	ll ret = 0;
	for(int i = 1; (ll) i * i <= x; i++) {
		int a, b;
		if(x % i != 0) {
			continue;
		}
		a = i; b = x / i;
		ret += (((Pow(k, a) - dfs(a, k)) % mod) + mod) % mod;;
		if(b != a && b != x) {
			ret += (((Pow(k, b) - dfs(b, k)) % mod) + mod) % mod;
		}
	}
	dp[x] = ret;
	return dp[x];
}
 
class PairsOfStrings {
public:
    int getNumber(int n, int k)  {
		dp.clear();
		ll num1 = dfs(n, k);
		ll num2 = (Pow(k, n) - num1 + mod) % mod;
		ll ret = (num2 * n) % mod;
		if(n != 1) {
			for(int i = 1; (ll) i * i <= n; i++) {
				int a, b;
				if(n % i != 0) {
					continue;
				}
				a = i; b = n / i;
				ll tmp1 = (((Pow(k, a) - dp[a]) % mod) + mod) % mod;
				ret = ((tmp1 * a) % mod + ret) % mod;
				if(b != a && b != n) {
					ll tmp2 = (((Pow(k, b) - dp[b]) % mod) + mod) % mod;
					ret = ((tmp2 * b) % mod + ret) % mod;
				}
			}
		}
        return (int) ret;
     }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 6; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 20; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 184; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 2; int Arg2 = 348; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = 26; int Arg2 = 46519912; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
        PairsOfStrings ___test;
        ___test.run_test(-1);
        return 0;
}
/
