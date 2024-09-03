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

ifstream fin("parallelogram.inp");
ofstream fout("parallelogram.out");

struct vertex {
	ll x;
	ll y;
};

vector <vertex> v;

bool check_angle() {
	double a1, a2, b1, b2;
	a1 = double((v[0].y - v[1].y)) / double((v[0].x - v[1].x));
	a2 = double((v[3].y - v[2].y)) / double((v[3].x - v[2].x));
	b1 = double((v[1].y - v[2].y)) / double((v[1].x - v[2].x));
	b2 = double((v[0].y - v[3].y)) / double((v[0].x - v[3].x));
	if (a1 == a2 && b1 == b2) { return true; }
	else { return false; }
}

ll cmp(vertex& v1, vertex v2) {
	if (v1.y == v2.y) { return v1.x < v2.x; }
	else { return v1.y < v2.y; }
}

ll ccw(vertex& a, vertex& b, vertex& c) {
	ll sum = a.x * b.y + b.x * c.y + c.x * a.y;
	ll sub = b.x * a.y + c.x * b.y + a.x * c.y;
	return sum - sub;
}

bool cmpccw(vertex& v1, vertex& v2) {
	ll temp = ccw(v[0], v1, v2);
	if (temp != 0) {
		if (temp) { return temp > 0; }
		else { return cmp(v1, v2); }
	}
	else if (temp == 0) {
		if (v1.x == v2.x) { return v1.y < v1.y; }
		else { return v1.x < v2.x; }
	}
}


int main() {
	vertex vt;
	while (true) {
		bool bk = true;
		for (int i = 0; i < 4; i++) {
			fin >> vt.x >> vt.y;
			v.push_back(vt);
		}

		for (int i = 0; i < 4; i++) {
			int t1, t2;
			t1 = v[i].x;
			t2 = v[i].y;
			if (t1 != 0 || t2 != 0) { bk = false; }
		}

		if (bk) { break; }
		sort(v.begin(), v.end(), cmp);
		sort(v.begin() + 1, v.end(), cmpccw);

		bool angle = check_angle();
		if (angle == true) { fout << 1 << endl; }
		else { fout << 0 << endl; }
		v.clear();
	}

	return 0;
}