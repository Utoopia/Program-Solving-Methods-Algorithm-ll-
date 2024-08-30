#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#define endl '\n'
using namespace std;
typedef long long ll;

ifstream fin("hull.inp");
ofstream fout("hull.out");

struct vertex {
	ll x;
	ll y;
};

vector <vertex> v;
vector <vertex> st;


bool cmp(vertex& v1, vertex& v2) {
	if (v1.x == v2.x) { return v1.y < v2.y; }
	return v1.x < v2.x;
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
	int N;
	fin >> N;

	vertex vt;
	for (int i = 0; i < N; i++) {
		ll tempx, tempy;
		fin >> tempx >> tempy;
		vt.x = tempx;
		vt.y = tempy;
		v.push_back(vt);
	}

	sort(v.begin(), v.end(), cmp);
	st.push_back(v[0]);
	sort(v.begin() + 1, v.end(), cmpccw);
	st.push_back(v[1]);

	for (int i = 2; i < N; i++) {
		while (st.size() >= 2) {
			vertex first = st.back();
			st.pop_back();
			vertex second = st.back();

			double temp = ccw(second, first, v[i]);
			if (temp > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(v[i]);
	}

	fout << st.size() << endl;
	for (auto i = st.begin(); i < st.end(); i++) {
		fout << i->x << ' ' << i->y << endl;
	}

	return 0;
}