#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#define endl '\n'
using namespace std;

ifstream fin("grid.inp");
ofstream fout("grid.out");

struct gd {
	long long dataa[12] = { 0, };
};
gd gdd;

vector <gd> v;
vector <vector<gd>> out;
bool path[1001][1001] = { false };
bool blocked[1001][1001] = { false };


static void calc() {
	int x, y, a, b, k;
	fin >> x >> y >> a >> b >> k;

	for (int i = 0; i < y + 1; i++) { v.push_back(gdd); }
	for (int i = 0; i < x + 1; i++) { out.push_back(v); }

	//gdd.dataa
	for (int i = 0; i < a; i++) {
		int temp1, temp2;
		fin >> temp1 >> temp2;
		path[temp1][temp2] = true;
	}

	for (int i = 0; i < b; i++) {
		int temp1, temp2;
		fin >> temp1 >> temp2;
		blocked[temp1][temp2] = true;
	}

	if (!blocked[0][0]) { out[0][0].dataa[0] = 1; }

	for (int i = 1; i < y + 1; i++) {
		if (!blocked[0][i]) {
			if (!path[0][i]) {
				out[0][i].dataa[0] = out[0][i - 1].dataa[0];
				out[0][i].dataa[1] = out[0][i - 1].dataa[1];
				out[0][i].dataa[2] = out[0][i - 1].dataa[2];
				out[0][i].dataa[3] = out[0][i - 1].dataa[3];
				out[0][i].dataa[4] = out[0][i - 1].dataa[4];
				out[0][i].dataa[5] = out[0][i - 1].dataa[5];
				out[0][i].dataa[6] = out[0][i - 1].dataa[6];
				out[0][i].dataa[7] = out[0][i - 1].dataa[7];
				out[0][i].dataa[8] = out[0][i - 1].dataa[8];
				out[0][i].dataa[9] = out[0][i - 1].dataa[9];
				out[0][i].dataa[10] = out[0][i - 1].dataa[10];
			}
			else {
				out[0][i].dataa[0] = 0;
				out[0][i].dataa[1] = out[0][i - 1].dataa[0];
				out[0][i].dataa[2] = out[0][i - 1].dataa[1];
				out[0][i].dataa[3] = out[0][i - 1].dataa[2];
				out[0][i].dataa[4] = out[0][i - 1].dataa[3];
				out[0][i].dataa[5] = out[0][i - 1].dataa[4];
				out[0][i].dataa[6] = out[0][i - 1].dataa[5];
				out[0][i].dataa[7] = out[0][i - 1].dataa[6];
				out[0][i].dataa[8] = out[0][i - 1].dataa[7];
				out[0][i].dataa[9] = out[0][i - 1].dataa[8];
				out[0][i].dataa[10] += out[0][i - 1].dataa[9];
			}
		}
	}

	for (int i = 1; i < x + 1; i++) {
		if (!blocked[i][0]) {
			if (!path[i][0]) {
				out[i][0].dataa[0] = out[i - 1][0].dataa[0] % 1000000007;
				out[i][0].dataa[1] = out[i - 1][0].dataa[1] % 1000000007;
				out[i][0].dataa[2] = out[i - 1][0].dataa[2] % 1000000007;
				out[i][0].dataa[3] = out[i - 1][0].dataa[3] % 1000000007;
				out[i][0].dataa[4] = out[i - 1][0].dataa[4] % 1000000007;
				out[i][0].dataa[5] = out[i - 1][0].dataa[5] % 1000000007;
				out[i][0].dataa[6] = out[i - 1][0].dataa[6] % 1000000007;
				out[i][0].dataa[7] = out[i - 1][0].dataa[7] % 1000000007;
				out[i][0].dataa[8] = out[i - 1][0].dataa[8] % 1000000007;
				out[i][0].dataa[9] = out[i - 1][0].dataa[9] % 1000000007;
				out[i][0].dataa[10] = out[i - 1][0].dataa[10] % 1000000007;
			}
			else {
				out[i][0].dataa[0] = 0;
				out[i][0].dataa[1] = out[i - 1][0].dataa[0] % 1000000007;
				out[i][0].dataa[2] = out[i - 1][0].dataa[1] % 1000000007;
				out[i][0].dataa[3] = out[i - 1][0].dataa[2] % 1000000007;
				out[i][0].dataa[4] = out[i - 1][0].dataa[3] % 1000000007;
				out[i][0].dataa[5] = out[i - 1][0].dataa[4] % 1000000007;
				out[i][0].dataa[6] = out[i - 1][0].dataa[5] % 1000000007;
				out[i][0].dataa[7] = out[i - 1][0].dataa[6] % 1000000007;
				out[i][0].dataa[8] = out[i - 1][0].dataa[7] % 1000000007;
				out[i][0].dataa[9] = out[i - 1][0].dataa[8] % 1000000007;
				out[i][0].dataa[10] += out[i - 1][0].dataa[9] % 1000000007;
			}
		}
	}

	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {
			if (!blocked[i][j]) {
				if (!path[i][j]) {
					out[i][j].dataa[0] = (out[i - 1][j].dataa[0] + out[i][j - 1].dataa[0]) % 1000000007;
					out[i][j].dataa[1] = (out[i - 1][j].dataa[1] + out[i][j - 1].dataa[1]) % 1000000007;
					out[i][j].dataa[2] = (out[i - 1][j].dataa[2] + out[i][j - 1].dataa[2]) % 1000000007;
					out[i][j].dataa[3] = (out[i - 1][j].dataa[3] + out[i][j - 1].dataa[3]) % 1000000007;
					out[i][j].dataa[4] = (out[i - 1][j].dataa[4] + out[i][j - 1].dataa[4]) % 1000000007;
					out[i][j].dataa[5] = (out[i - 1][j].dataa[5] + out[i][j - 1].dataa[5]) % 1000000007;
					out[i][j].dataa[6] = (out[i - 1][j].dataa[6] + out[i][j - 1].dataa[6]) % 1000000007;
					out[i][j].dataa[7] = (out[i - 1][j].dataa[7] + out[i][j - 1].dataa[7]) % 1000000007;
					out[i][j].dataa[8] = (out[i - 1][j].dataa[8] + out[i][j - 1].dataa[8]) % 1000000007;
					out[i][j].dataa[9] = (out[i - 1][j].dataa[9] + out[i][j - 1].dataa[9]) % 1000000007;
					out[i][j].dataa[10] = (out[i - 1][j].dataa[10] + out[i][j - 1].dataa[10]) % 1000000007;
				}
				else {
					out[i][j].dataa[0] = 0;
					out[i][j].dataa[1] = (out[i - 1][j].dataa[0] + out[i][j - 1].dataa[0]) % 1000000007;
					out[i][j].dataa[2] = (out[i - 1][j].dataa[1] + out[i][j - 1].dataa[1]) % 1000000007;
					out[i][j].dataa[3] = (out[i - 1][j].dataa[2] + out[i][j - 1].dataa[2]) % 1000000007;
					out[i][j].dataa[4] = (out[i - 1][j].dataa[3] + out[i][j - 1].dataa[3]) % 1000000007;
					out[i][j].dataa[5] = (out[i - 1][j].dataa[4] + out[i][j - 1].dataa[4]) % 1000000007;
					out[i][j].dataa[6] = (out[i - 1][j].dataa[5] + out[i][j - 1].dataa[5]) % 1000000007;
					out[i][j].dataa[7] = (out[i - 1][j].dataa[6] + out[i][j - 1].dataa[6]) % 1000000007;
					out[i][j].dataa[8] = (out[i - 1][j].dataa[7] + out[i][j - 1].dataa[7]) % 1000000007;
					out[i][j].dataa[9] = (out[i - 1][j].dataa[8] + out[i][j - 1].dataa[8]) % 1000000007;
					out[i][j].dataa[10] = (out[i - 1][j].dataa[9] + out[i][j - 1].dataa[9] + out[i - 1][j].dataa[10] + out[i][j - 1].dataa[10]) % 1000000007;
				}	//a랑 b의 개수 조건은 없음 이거생각							  
			}
		}
	}

	int output = 0;
	for (int i = k; i < 11; i++) {
		output = (output + out[x][y].dataa[i]) % 1000000007;
	}
	fout << output << endl;
	v.clear();
	out.clear();
	for (int i = 0; i < 1001; i++) {
		for (int j = 0; j < 1001; j++) {
			path[i][j] = false;
			blocked[i][j] = false;
		}
	}
}

int main() {
	int T;
	fin >> T;
	for (int i = 0; i < T; i++) {
		calc();
	}


	return 0;
}