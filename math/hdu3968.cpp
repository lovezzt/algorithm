solution:
水题一枚。
算一中物理题吧。告诉你抛体运动的起点坐标(x0, y0), 终点坐标（x1, y1), 并且告诉你运行时间t，然你求这条曲线长度。

只要求出抛物线方程就可以用曲线积分公式求出该值。这题直接求出符号解不好做，所以只要用数值积分即可。
尼码这题我因为模板不好挂了n次，然后居然把浮点除法写成了整数出法，挂了n发，跪烂。

code:
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-4;
const double g = 9.8;

double X0, Y0, X1, Y1, t;
double a, b, c, vx, vy;

void pre() {
	vx = (X1 - X0) / t;
	vy = ((Y1 - Y0) + 0.5 * g * t * t) / t;
	a = - g / (2 * vx * vx);
	b = (vx * vy + g * X0) / ( vx * vx);
	c = (- g * X0 * X0 - 2 * vx * vy * X0) / (2 * vx * vx);
}

double calc(double x) {
	return sqrt(1 + (2 * a * x + b) * (2 * a * x + b));
}

double rSimp(double l, double r, int n) {
	double h = (r - l) / n;
	double ans = calc(l) + calc(r);
	for(int i = 1; i < n; i += 2) ans += 4 * calc(l + i * h);
	for(int i = 2; i < n; i += 2) ans += 2 * calc(l + i * h);
	return ans * h / 3;
}

/*
double Simp(double l, double r) {
		double h = (r - l) / 2.0;
		return h * (calc(l) + 4 * calc((l + r) / 2.0) + calc(r)) / 3.0;
}

double rSimp(double l, double r) {
	double mid = (l + r) / 2.0;
	if(abs((Simp(l, r) - Simp(l, mid) - Simp(mid, r))) / 15 < eps) {
		return Simp(l, r);
	} else {
		return rSimp(l, mid) + rSimp(mid, r);
	}
}
*/

int main() {
	//freopen("/home/lovezzt/桌面/input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lf%lf%lf%lf%lf", &X0, &Y0, &X1, &Y1, &t);
		if(t == 0) {
			puts("Impossible.");
		} else {
			pre();
			if(X0 > X1) {
				swap(X0, X1);
			}
			double ans = rSimp(X0, X1, 10000);
			printf("%.3f\n", ans);
		}
	}
	return 0;
}
