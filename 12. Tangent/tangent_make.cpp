#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
#define endl '\n'
using namespace std;
typedef long long ll;

ifstream fin("tangent.inp");
ofstream fout("tangent.out");

struct vertex {
	ll x;
	ll y;
	int div;
	int num;
};

vector <vertex> a;
vector <vertex> b;
vector <vertex> all;
vector <vertex> st;
vector <vertex> tag;
vector <vertex> complete1;
vector <vertex> complete2;
long double a1, a2;

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
	ll temp = ccw(all[0], v1, v2);
	if (temp != 0) {
		if (temp) { return temp > 0; }
		else { return cmp(v1, v2); }
	}
	else if (temp == 0) {
		if (v1.x == v2.x) { return v1.y < v1.y; }
		else { return v1.x < v2.x; }
	}
}

bool new_cmp(vertex& c, vertex& a, vertex& b) {
	long long dx1 = a.x - c.x;
	long long dy1 = a.y - c.y;
	long long dx2 = b.x - c.x;
	long long dy2 = b.y - c.y;

	long long det1 = dx1 * dy1;
	long long det2 = dx2 * dy2;

	if (dy1 * dx2 == dx1 * dy2) {
		if (dx1 == dx2)
			return dy1 > dy2;
		return dx1 < dx2;
	}
	return dy1 * dx2 < dx1 * dy2;
}

void check_line() {
	for (int i = 0; i < st.size() - 1; i++) {
		auto cur = st[i];
		auto next = st[i + 1];
		if (cur.div != next.div) {
			tag.push_back(cur);
			tag.push_back(next);
		}
	}
	if (tag.size() == 2) {
		tag.push_back(st[st.size() - 1]);
		tag.push_back(st[0]);
	}
}

void make_complete() {
	if (tag[0].div == 1) {
		if (tag[0].num < tag[3].num) {
			for (int i = tag[0].num; i <= tag[3].num; i++) {
				complete1.push_back(a[i]);
			}
		}

		else {
			for (int i = tag[0].num; i < a.size(); i++) {
				complete1.push_back(a[i]);
			}
			for (int i = 0; i <= tag[3].num; i++) {
				complete1.push_back(a[i]);
			}
		}

		if (tag[2].num < tag[1].num) {
			for (int i = tag[2].num; i <= tag[1].num; i++) {
				complete1.push_back(b[i]);
			}
		}

		else {
			for (int i = tag[2].num; i < b.size(); i++) {
				complete1.push_back(b[i]);
			}
			for (int i = 0; i <= tag[1].num; i++) {
				complete1.push_back(b[i]);
			}
		}
	}

	else {
		if (tag[0].num < tag[3].num) {
			for (int i = tag[0].num; i <= tag[3].num; i++) {
				complete1.push_back(b[i]);
			}
		}

		else {
			for (int i = tag[0].num; i < b.size(); i++) {
				complete1.push_back(b[i]);
			}
			for (int i = 0; i <= tag[3].num; i++) {
				complete1.push_back(b[i]);
			}
		}

		if (tag[2].num < tag[1].num) {
			for (int i = tag[2].num; i <= tag[1].num; i++) {
				complete1.push_back(a[i]);
			}
		}

		else {
			for (int i = tag[2].num; i < a.size(); i++) {
				complete1.push_back(a[i]);
			}
			for (int i = 0; i <= tag[1].num; i++) {
				complete1.push_back(a[i]);
			}
		}
	}

	if (tag[3].div == 1) {
		if (tag[3].num < tag[0].num) {
			for (int i = tag[3].num; i <= tag[0].num; i++) {
				complete2.push_back(a[i]);
			}
		}

		else {
			for (int i = tag[3].num; i < a.size(); i++) {
				complete2.push_back(a[i]);
			}
			for (int i = 0; i <= tag[0].num; i++) {
				complete2.push_back(a[i]);
			}
		}

		if (tag[1].num < tag[2].num) {
			for (int i = tag[1].num; i <= tag[2].num; i++) {
				complete2.push_back(b[i]);
			}
		}

		else {
			for (int i = tag[1].num; i < b.size(); i++) {
				complete2.push_back(b[i]);
			}
			for (int i = 0; i <= tag[2].num; i++) {
				complete2.push_back(b[i]);
			}
		}
	}

	else {
		if (tag[3].num < tag[0].num) {
			for (int i = tag[3].num; i <= tag[0].num; i++) {
				complete2.push_back(b[i]);
			}
		}

		else {
			for (int i = tag[3].num; i < b.size(); i++) {
				complete2.push_back(b[i]);
			}
			for (int i = 0; i <= tag[0].num; i++) {
				complete2.push_back(b[i]);
			}
		}

		if (tag[1].num < tag[2].num) {
			for (int i = tag[1].num; i <= tag[2].num; i++) {
				complete2.push_back(a[i]);
			}
		}

		else {
			for (int i = tag[1].num; i < a.size(); i++) {
				complete2.push_back(a[i]);
			}
			for (int i = 0; i <= tag[2].num; i++) {
				complete2.push_back(a[i]);
			}
		}
	}
}

void get_area() {
	long double temp1 = 0, temp2 = 0;
	for (int i = 0; i < complete1.size() - 1; i++) {
		temp1 += complete1[i].x * complete1[i + 1].y - complete1[i].y * complete1[i + 1].x;
	}
	temp1 += complete1[complete1.size() - 1].x * complete1[0].y - complete1[complete1.size() - 1].y * complete1[0].x;
	a1 = abs(temp1) / 2;

	for (int i = 0; i < complete2.size() - 1; i++) {
		temp2 += complete2[i].x * complete2[i + 1].y - complete2[i].y * complete2[i + 1].x;
	}
	temp2 += complete2[complete2.size() - 1].x * complete2[0].y - complete2[complete2.size() - 1].y * complete2[0].x;
	a2 = abs(temp2) / 2;
}

int main() {
	vertex vt;
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;
		for (int i = 0; i < N; i++) {
			ll tempx, tempy;
			cin >> tempx >> tempy;
			vt.div = 1;
			vt.num = i;
			vt.x = tempx;
			vt.y = tempy;
			a.push_back(vt);
			all.push_back(vt);
		}

		cin >> N;
		for (int i = 0; i < N; i++) {
			ll tempx, tempy;
			cin >> tempx >> tempy;
			vt.div = 2;
			vt.num = i;
			vt.x = tempx;
			vt.y = tempy;
			b.push_back(vt);
			all.push_back(vt);
		}

		sort(all.begin(), all.end(), cmp);
		st.push_back(all[0]);
		sort(all.begin() + 1, all.end(), [&](vertex a, vertex b) {
			return new_cmp(all[0], a, b);
			});
		st.push_back(all[1]);

		for (int i = 2; i < all.size(); i++) {
			while (st.size() >= 2) {
				vertex first = st.back();
				st.pop_back();
				vertex second = st.back();

				double temp = ccw(second, first, all[i]);
				if (temp >= 0) {
					st.push_back(first);
					break;
				}
			}
			st.push_back(all[i]);
		}

		check_line();
		make_complete();
		get_area();

		cout << fixed << setprecision(1) << min(a1, a2) << endl;

		a.clear();
		b.clear();
		all.clear();
		st.clear();
		tag.clear();
		complete1.clear();
		complete2.clear();
	}


	return 0;
}