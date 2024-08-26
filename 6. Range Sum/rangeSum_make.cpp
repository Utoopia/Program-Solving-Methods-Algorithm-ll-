#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define endl '\n'
using namespace std;

ifstream fin("3nplus1.inp");
ofstream fout("3nplus1.out");

int main() {
	int N;
	cin >> N;
	vector<int> v(1);
	for (int i = 0; i < N; i++) {
		long long temp;
		cin >> temp;
		v.push_back(temp);
	}
	
	while (true) {
		char command;
		long long a, b, temp = 0;

		cin >> command >> a >> b;

		if (command == 'q') { break; }
		else if (command == 'c') { v[a] = b; }
		else if (command == 's') {
			for (int i = a; i <= b; i++) { temp += v[i]; }
			cout << temp << endl;
		}
	}

	return 0;
}