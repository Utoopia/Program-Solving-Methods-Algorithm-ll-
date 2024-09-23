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

ifstream fin("jolly.inp");
ofstream fout("jolly.out");

vector <int> v;
unordered_map <int, bool> ab;
 
bool input_data(int N) {
	for (int i = 1; i < N; i++) {
		if (ab.find(abs(v[i - 1] - v[i])) == ab.end()) { ab.insert({ abs(v[i - 1] - v[i]), true }); }
		else {
			fout << "Not Jolly" << endl;
			return false;
		}
	}
	return true;
}

int main() {
	while (true) {
		int N;
		fin >> N;
		if (fin.eof()) { break; }
		for (int i = 0; i < N; i++) {
			int temp;
			fin >> temp;
			v.push_back(temp);
		}
		
		bool x = input_data(N);

		if (x) {
			for (int i = 1; i < N; i++) {
				if (ab.find(i) == ab.end()) {
					fout << "Not Jolly" << endl;
					break;
				}
				if (i == N - 1 && ab.find(i) != ab.end()) {
					fout << "Jolly" << endl;
				}
			}
		}
		v.clear();
		ab.clear();
	}

	return 0;
}