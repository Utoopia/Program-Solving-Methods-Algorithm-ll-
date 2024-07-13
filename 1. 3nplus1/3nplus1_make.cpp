#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define endl '\n'
using namespace std;

ifstream fin("3nplus1.inp");
ofstream fout("3nplus1.out");

int cycle(int N) {
	int count = 1;

	while (N != 1) {
		if (N % 2 == 0) {
			N = N / 2;
			count++;
		}

		else {
			N = 3 * N + 1;
			count++;
		}
	}

	return count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int st, ed;
	while (cin >> st >> ed) {

		int output = 0;

		for (int i = min(st, ed); i < max(st, ed) + 1; i++) { output = max(output, cycle(i)); }

		cout << st << ' ' << ed << ' ' << output << endl;
	}

	return 0;
}