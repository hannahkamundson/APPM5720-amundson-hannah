#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

double leg_scal(double x, int N);
double leg_der_scal(double x, int N);
double get_gauss_node(double x_guess, int N);
double get_guess(int j, int N);
double get_weight(double x, int N);

int main() {
    int N = 25;
    int NP = N + 1;
    vector<double> x(NP);
    vector<double> w(NP);
    double sum = 0;

    for (int i = 0; i <= N; i++) {
        double guess = get_guess(i, N);
        double gauss_node = get_gauss_node(guess, N);

        x[i] = gauss_node;
        w[i] = get_weight(gauss_node, N);

        //cout << "For " << i << " the gauss node is " << gauss_node << " and the weight is " << w[i] << ".\n";
        sum += w[i];
    }

    cout << "The sum of the weights is " << sum << ".";

    return 0;
}

double get_weight(double x, int N) {
    double bottom = (1 - x * x) * (leg_der_scal(x, N)) * (leg_der_scal(x, N));

    return 2/bottom;
}

double get_guess(int j, int N) {
    return cos((2 * j + 1) * M_PI / (2 * (N+1)));
}

double leg_scal(double x, int N) {
    int k = 2;
    // Start off putting them one behind so that it will get moved to reduce code
    double l_0;
    double l_1 = 0;
    double l_2 = x;

    while (k <= N) {
        l_0 = l_1;
        l_1 = l_2;
        l_2 = ((2 * (k) + 1) * x * l_1) - ((k)/(k+1) * l_0);
        k++;
    }

    return l_2;
}

double leg_der_scal(double x, int N) {
    int k = 2;
    // Start off putting them one behind so that it will get moved to reduce code
    double l_der_0;
    double l_der_1 = 0;
    double l_der_2 = 1;

    while (k <= N) {
        l_der_0 = l_der_1;
        l_der_1 = l_der_2;
        l_der_2 = -(2 * k + 1) * leg_scal(x, k-1) - l_der_0;
        k++;
    }

    return l_der_2;
}

double get_gauss_node(double x_guess, int N) {
    double x = x_guess;

    for (int i = 0; i < 15; i++) {
        x = x - leg_scal(x, N)/leg_der_scal(x, N);
    }

    return x;
}