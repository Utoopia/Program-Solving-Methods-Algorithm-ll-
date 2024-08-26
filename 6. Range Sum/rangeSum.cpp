#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define endl '\n'
using namespace std;

ifstream fin("rangeSum.inp");
ofstream fout("rangeSum.out");

int main() {
	int N;
	fin >> N;
	vector<int> v(1);
	for (int i = 0; i < N; i++) {
		long long temp;
		fin >> temp;
		v.push_back(temp);
	}

	while (true) {
		char command;
		long long a, b, temp = 0;

		fin >> command >> a >> b;

		if (command == 'q') { break; }
		else if (command == 'c') { v[a] = b; }
		else if (command == 's') {
			for (int i = a; i <= b; i++) { temp += v[i]; }
			fout << temp << endl;
		}
	}

	return 0;
}