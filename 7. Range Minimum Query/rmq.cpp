#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#define endl '\n'
using namespace std;

ifstream fin("rmq.inp");
ofstream fout("rmq.out");

long long make_tree(vector<long long>& origin, vector<long long>& tree, int current, int start, int end) {
	if (start == end) { return tree[current] = start; }

	int mid = (start + end) / 2;

	long long left_index = make_tree(origin, tree, current * 2, start, mid);
	long long right_index = make_tree(origin, tree, current * 2 + 1, mid + 1, end);

	if (origin[left_index] > origin[right_index]) {
		return tree[current] = right_index;
	}
	else {
		return tree[current] = left_index;
	}
}

long long find_min(vector<long long>& origin, vector<long long>& tree, int current, int start, int end, int left, int right) {
	if (left > end || right < start) { return -1; }
	if (left <= start && end <= right) {
		return tree[current];
	}
	long long lmin = find_min(origin, tree, current * 2, start, (start + end) / 2, left, right);
	long long rmin = find_min(origin, tree, current * 2 + 1, (start + end) / 2 + 1, end, left, right);
	if (lmin == -1) return rmin; 
	if (rmin == -1) return lmin;
	if (origin[lmin] > origin[rmin]) { return rmin; }
	else { return lmin; }
}

void change(vector<long long>& origin, vector<long long>& tree, int current, int start, int end, int idx, long long val) {
	if (idx < start || idx > end) { return; }
	if (start == end) {
		origin[idx] = val;
		tree[current] = idx;
		return;
	}
	change(origin, tree, current * 2, start, (start + end) / 2, idx, val);
	change(origin, tree, current * 2 + 1, (start + end) / 2 + 1, end, idx, val);
	if (origin[tree[current * 2]] > origin[tree[current * 2 + 1]]) { tree[current] = tree[current * 2 + 1]; }
	else { tree[current] = tree[current * 2]; }
}

void start() {
	int N;
	fin >> N;

	vector <long long> origin(N);
	vector <long long> tree(N * 4);

	for (int i = 0; i < N; i++) {
		int temp;
		fin >> temp;
		origin[i] = temp;
	}

	make_tree(origin, tree, 1, 0, N - 1);

	long long output = 0;
	while (true) {
		char command;
		long long a, b, idx = 0;

		fin >> command >> a >> b;

		if (command == 'q') {
			idx = find_min(origin, tree, 1, 0, N - 1, a, b);
			output += (idx % 100000);
		}

		else if (command == 'c') { change(origin, tree, 1, 0, N - 1, a, b); }

		else if (command == 's') { break; }
	}
	fout << output % 100000 << endl;

	return;
}

int main() {
	start();

	return 0;
}

