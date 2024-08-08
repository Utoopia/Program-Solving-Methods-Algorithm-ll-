#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>
#define endl '\n'
using namespace std;

ifstream fin("trip.inp");
ofstream fout("trip.out");

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        double result1 = 0.0;
        double result2 = 0.0;

        double* money = new double[n];
        double average = 0.0;

        for (int i = 0; i < n; i++) {
            cin >> money[i];
            average += money[i];
        }
        average /= n;

        for (int i = 0; i < n; i++) {
            double sub = (int)((money[i] - average) * 100) / 100.0;
            if (sub < 0) {
                result1 -= sub;
            }
            else {
                result2 += sub;
            }
        }

        cout.precision(2);
        if (result1 > result2) {
            cout << "$" << fixed << result1 << endl;
        }
        else {
            cout << "$" << fixed << result2 << endl;
        }
        cin >> n;
    }
    return 0;
}
