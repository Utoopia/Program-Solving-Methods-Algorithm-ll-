#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#define endl '\n'
using namespace std;

ifstream fin("trip.inp");
ofstream fout("trip.out");

vector <double> v;

void input(int n) {
	double inp;
	for (int i = 0; i < n; i++) {
		fin >> inp;
		v.push_back(inp);
	}
}

double calc(int n) {
	double output1 = 0.0, output2 = 0.0, sum = 0.0;

	for (int i = 0; i < n; i++) {
		sum += v[i];
	}

	double avg = sum / n;

	for (int i = 0; i < n; i++) {
		double temp = (int)((v[i] - avg) * 100) / 100.0;

		if (temp < 0) { output1 -= temp; }
		else { output2 += temp; }
	}

	if (output1 > output2) { return output1; }
	else { return output2; }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (true) {
		int n;
		fin >> n;

		if (n == 0) { break; }
		else {
			input(n);
			fout.precision(2);
			fout << "$" << fixed << calc(n) << endl;
			v.clear();
		}
	}

	return 0;
}