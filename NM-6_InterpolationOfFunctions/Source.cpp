#include <iostream>
#include <functional>
#include <vector>

using namespace std;

void LinearInterpolation(const double& Xa, const vector<double>& x, const vector<double>& y, const int& n) {

	double Ya;
	for (int i = 0; i < n; i++) {
		if (Xa > x[i] && Xa < x[i + 1]) {
			Ya = (Xa - x[i + 1]) / (x[i] - x[i + 1]) * y[i] + (Xa - x[i]) / (x[i + 1] - x[i]) * y[i + 1];
		}
	}
	cout << "Function value at a point x* (";
}

int main() {

	int n = 5;
	vector<double> x = { -2, -1, 0, 1, 2 };
	vector<double> y = { 9.9, 5.1, 1.9, 1.1, 1.9 };
	double Xa = 0.4;

	return 0;
}