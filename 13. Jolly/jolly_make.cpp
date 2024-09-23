#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cmath>
#define endl '\n'
using namespace std;
typedef long long ll;

ifstream fin("rectangles.inp");
ofstream fout("rectangles.out");

vector <int> v;
unordered_map <int, bool> ab;

int main() {
	while (true) {
		int N;
		cin >> N;
		for (int i = 0; i < N; i++) {
			int temp;
			cin >> temp;
			v.push_back(temp);
		}
		for (int i = 1; i < N; i++) {
			ab.insert({ abs(v[i - 1] - v[i]), true });
		}
		for (int i = 1; i < N; i++) {
			if (ab.find(i) == ab.end()) {
				cout << "Not jolly" << endl;
				break;
			}
			if (i == N - 1 && ab.find(i) != ab.end()) {
				cout << "Jolly" << endl;
			}
		}
		v.clear();
		ab.clear();
	}

	return 0;
}