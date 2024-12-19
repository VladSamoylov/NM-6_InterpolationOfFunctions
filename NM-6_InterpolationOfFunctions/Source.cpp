#include <iostream>
#include <functional>
#include <vector>

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_PURPLE "\033[35m"
#define ANSI_COLOR_LIGHTBLUE "\033[94m"

using namespace std;

/**
 * @brief Функція реалізації лінійної інтерполяції
 * @param Xa Змінна для якої потрібно обчислити наближене значення функції
 * @param x Вузли інтерполяції
 * @param y Значення функції в вузлах інтерполяції
 * @param n Кількість точок
 */
void LinearInterpolation(const double& Xa, const vector<double>& x, const vector<double>& y, const int& n) {

	if (x[n - 1] < Xa || x[0] > Xa) throw "Error: <x* must be selected in the interval>";
	double Ya = 0;
	for (int i = 0; i < n - 1; i++) {
		if (Xa >= x[i] && Xa <= x[i + 1]) {
			Ya = (Xa - x[i + 1]) / (x[i] - x[i + 1]) * y[i] + (Xa - x[i]) / (x[i + 1] - x[i]) * y[i + 1];
			break;
		}
	}
	cout << "Function value at a point x* : (" << ANSI_COLOR_LIGHTBLUE << Xa << ANSI_COLOR_RESET << ") = " << ANSI_COLOR_PURPLE << Ya << ANSI_COLOR_RESET << " by Linear Interpolation" << endl;
}

/**
 * @brief Функція реалізації квадратичної інтерполяції
 * @param Xa Змінна для якої потрібно обчислити наближене значення функції 
 * @param x Вузли інтерполяції
 * @param y Значення функції в вузлах інтерполяції
 * @param n Кількість точок
 */
void QuadraticInterpolation(const double& Xa, const vector<double>& x, const vector<double>& y, const int& n) {

	if (x[n - 1] < Xa || x[0] > Xa) throw "Error: <x* must be selected in the interval>";
	double Ya = 0;
	int z = 0;
	for (int i = 0; i < n - 1; i++) {
		if (Xa >= x[i] && Xa <= x[i + 1]) z = i;
	}
	if (z + 2 < n) {
		for (int i = z; i <= z + 2; i++) {
			double p1 = 1;
			double p2 = 1;
			for (int k = z; k <= z + 2; k++) {
				if (k != i) {
					p1 *= Xa - x[k];
					p2 *= x[i] - x[k];
				}
			}
			Ya += y[i] * p1 / p2;
		}
	}
	else {
		for (int i = z - 1; i <= z + 1; i++) {
			double p1 = 1;
			double p2 = 1;
			for (int k = z - 1; k <= z + 1; k++) {
				if (k != i) {
					p1 *= Xa - x[k];
					p2 *= x[i] - x[k];
				}
			}
			Ya += y[i] * p1 / p2;
		}
	}
	
	cout << "Function value at a point x* : (" << ANSI_COLOR_LIGHTBLUE << Xa << ANSI_COLOR_RESET << ") = " << ANSI_COLOR_PURPLE << Ya << ANSI_COLOR_RESET << " by Quadratic Interpolation" << endl;
}

/**
 * @brief Функція реалізації інтерполяції по Лагранжу
 * @param Xa Змінна для якої потрібно обчислити наближене значення функції 
 * @param x Вузли інтерполяції
 * @param y Значення функції в вузлах інтерполяції
 * @param n Кількість точок
 */
void LagrangianInterpolation(const double& Xa, const vector<double>& x, const vector<double>& y, const int& n) {

	if (x[n - 1] < Xa || x[0] > Xa) throw "Error: <x* must be selected in the interval>";
	double Ya = 0;
	for (int i = 0; i < n; i++) {
		double p1 = 1;
		double p2 = 1;
		for (int k = 0; k < n; k++) {
			if (k != i) {
				p1 *= (Xa - x[k]);
				p2 *= (x[i] - x[k]);
			}
		}
		Ya += y[i] * p1 / p2;
	}
	cout << "Function value at a point x* : (" << ANSI_COLOR_LIGHTBLUE << Xa << ANSI_COLOR_RESET << ") = " << ANSI_COLOR_PURPLE << Ya << ANSI_COLOR_RESET << " by Lagrangian Interpolation" << endl;
	
}

/**
 * @brief Функція, яка обчислює один базовий поліном Лагранжа для конкретного індексу і в процесі інтерполяції
 * @param x Вузли інтерполяції
 * @param i Індекс вузла, для якого потрібно обчислити базовий поліном
 * @return Базовий поліном Лагранжа
 */
vector<double> ComputeLagrangeBasis(const vector<double>& x, int i) {

	const int n = x.size();
	vector<double> basis(n, 0);
	basis[0] = 1;

	for (int j = 0; j < n; j++) {
		if (j != i) {
			for (int k = n - 1; k >= 0; k--) {
				if (k > 0) basis[k] = basis[k - 1] - x[j] * basis[k];
				else basis[k] = 0 - x[j] * basis[k];
			}
			double dev = x[i] - x[j];
			for (int k = 0; k < n; k++) {
				basis[k] /= dev;
			}
		}
	}
	return basis;
}

/**
 * @brief Функція, яка будує многочлен Лагранжа, що наближає таблично задану функцію
 * @param x Вузли інтерполяції
 * @param y Значення функції в вузлах інтерполяції
 * @return Многочлен Лагранжа
 */
vector<double> BuildLagrangePolynomial(const vector<double>& x, const vector<double>& y) {

	const int n = x.size();
	vector<double> polynomial(n, 0);

	for (int i = 0; i < n; i++) {
		vector<double> basis = ComputeLagrangeBasis(x, i);
		for (int j = 0; j < n; j++) {
			polynomial[j] += y[i] * basis[j];
		}
	}

	return polynomial;
}

/**
 * @brief Функція, яка виводить аналітичний вираз полінома, побудований за допомогою методу Лагранжа
 * @param polynomial Многочлен Лагранжа
 */
void BuiltPolynomial(const vector<double>& polynomial) {

	const int n = polynomial.size();
	cout << "P(x) = " << ANSI_COLOR_GREEN;
	for (int i = n - 1; i >= 0; i--) {
		if (i != n - 1) cout << " + ";
		if (i == 0 || abs(polynomial[i]) != i) cout << polynomial[i];
		if (i > 0) cout << "x";
		if (i > 1) cout << "^" << i;
	}cout << ANSI_COLOR_RESET << endl;
}

int main() {

	const int n = 5;
	vector<double> x = { -2, -1, 0, 1, 2 };
	vector<double> y = { 9.9, 5.1, 1.9, 1.1, 1.9 };
	const double Xa = 0.333;

	try {
		LinearInterpolation(Xa, x, y, n);
		QuadraticInterpolation(Xa, x, y, n);
		LagrangianInterpolation(Xa, x, y, n);
		BuiltPolynomial(BuildLagrangePolynomial(x, y));
	}
	catch (const char* err) {
		cerr << ANSI_COLOR_RED << err << ANSI_COLOR_RESET << endl;
	}
	

	return 0;
}