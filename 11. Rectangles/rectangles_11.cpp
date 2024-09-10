#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>
#define endl '\n'
using namespace std;
typedef long long ll;

ifstream fin("rectangles.inp");
ofstream fout("rectangles.out");

struct stt {
	ll x;
	ll y;
};

vector <stt> v;

int gcd(int a, int b)
{
	int c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

bool cmp(stt& a, stt& b) {
	return a.x + a.y < b.x + b.y;
}

void ipt() {
	for (int m = 2; m < 1000; m++) {
		for (int n = 1; n < m; n++) {
			int x, y, z;
			if ((m + n) % 2 == 1) {
				if (gcd(m, n) == 1) {
					x = 2 * m * n;
					y = m * m - n * n;
					z = m * m + n * n;
					if (z * z == x * x + y * y) {
						stt st;
						st.x = x;
						st.y = y;
						v.push_back(st);
					}
				}
			}
		}
	}
}

int main() {
	ipt();
	sort(v.begin(), v.end(), cmp);

	int T;
	fin >> T;
	for (int i = 0; i < T; i++) {
		int lenght;
		fin >> lenght;

		int cnt = 0;
		while (lenght > 0) {
			for (int i = 0; i < v.size(); i++) {
				lenght -= (v[i].x + v[i].y) * 2;
				if (lenght >= 0) { cnt++; }
				else { break; }
			}
		}
		fout << cnt << endl;
	}

	return 0;
}