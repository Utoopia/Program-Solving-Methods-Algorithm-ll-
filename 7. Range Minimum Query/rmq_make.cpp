#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#define endl '\n'
using namespace std;

ifstream fin("rmq.inp");
ofstream fout("rmq.out");

// 세그먼트 트리 구성 함수
long long make_tree(vector<long long>& origin, vector<long long>& tree, int current, int start, int end) {
    if (start == end) { return tree[current] = start; }

    int mid = (start + end) / 2;

    // 왼쪽 자식과 오른쪽 자식의 인덱스를 구해서 최솟값을 가진 인덱스를 현재 노드에 할당
    long long left_index = make_tree(origin, tree, current * 2, start, mid);
    long long right_index = make_tree(origin, tree, current * 2 + 1, mid + 1, end);

    if (origin[left_index] > origin[right_index]) {
        return tree[current] = right_index;
    }
    else {
        return tree[current] = left_index;
    }
}

// 구간 내 최솟값을 찾는 함수
long long find_min(vector<long long>& origin, vector<long long>& tree, int current, int start, int end, int left, int right) {
    if (left > end || right < start) { return -1; } // 구간이 겹치지 않을 경우 -1을 반환
    if (left <= start && end <= right) {
        return tree[current]; // 현재 노드가 구간 내에 완전히 포함될 경우 해당 인덱스 반환
    }
    long long lmin = find_min(origin, tree, current * 2, start, (start + end) / 2, left, right);
    long long rmin = find_min(origin, tree, current * 2 + 1, (start + end) / 2 + 1, end, left, right);
    if (lmin == -1) return rmin; // 왼쪽 구간이 없는 경우 오른쪽 구간의 최솟값 반환
    if (rmin == -1) return lmin; // 오른쪽 구간이 없는 경우 왼쪽 구간의 최솟값 반환
    if (origin[lmin] > origin[rmin]) { return rmin; }
    else { return lmin; }
}

// 세그먼트 트리 업데이트 함수
void change(vector<long long>& origin, vector<long long>& tree, int current, int start, int end, int idx, long long val) {
    if (idx < start || idx > end) { return; }
    if (start == end) {
        origin[idx] = val;
        tree[current] = idx;
        return;
    }
    change(origin, tree, current * 2, start, (start + end) / 2, idx, val);
    change(origin, tree, current * 2 + 1, (start + end) / 2 + 1, end, idx, val);
    if (origin[tree[current * 2]] > origin[tree[current * 2 + 1]]) {
        tree[current] = tree[current * 2 + 1];
    }
    else {
        tree[current] = tree[current * 2];
    }
}

void start() {
    int N;
    cin >> N;

    vector<long long> origin(N);
    vector<long long> tree(N * 4);

    // 입력 받기
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        origin[i] = temp;
    }

    // 세그먼트 트리 구성
    make_tree(origin, tree, 1, 0, N - 1);

    int output = 0;
    while (true) {
        char command;
        int a, b, idx = 0;

        cin >> command >> a >> b;

        if (command == 'q') {
            // 최솟값을 찾아 인덱스 출력
            idx = find_min(origin, tree, 1, 0, N - 1, a, b);
            output += (idx % 100000);
        }
        else if (command == 'c') {
            // 값 업데이트
            change(origin, tree, 1, 0, N - 1, a, b);
        }
        else if (command == 's') {
            break; // 종료
        }
    }
    cout << output % 100000 << endl;

    return;
}

int main() {
    start();
    return 0;
}
