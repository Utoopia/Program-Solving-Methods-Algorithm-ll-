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

ifstream fin("cycle.inp");
ofstream fout("cycle.out");

struct dataNflag {
	int data;
	bool flag = true;
};

int main() {
	int T, N;
	fin >> T;
	for (int i = 0; i < T; i++) {
		int cycle = 0;
		fin >> N;

		vector <dataNflag> v(1);
		dataNflag df;
		for (int j = 0; j < N; j++) {
			fin >> df.data;
			v.push_back(df);
		}

		for (int next = 1; next < N + 1; next++) {
			while (v[next].flag) {
				v[next].flag = false;
				next = v[next].data;
				if (v[next].flag == false) { cycle++; }
			}
		}
		fout << cycle << endl;
		v.clear();
	}

	return 0;
}