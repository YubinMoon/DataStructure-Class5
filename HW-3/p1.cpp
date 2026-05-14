#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const double LEFT = -10.0;
const double RIGHT = 10.0;
const double EPS = 1e-10;

double f(double x) {
    return 6.7 * pow(x, 4) + 3.2 * pow(x, 3) - pow(x, 2) + x - 2.0;
}

double df(double x) {
    return 26.8 * pow(x, 3) + 9.6 * pow(x, 2) - 2.0 * x + 1.0;
}

double bisection(double (*func)(double), double left, double right) {
    double fLeft = func(left);

    for (int i = 0; i < 200 && right - left > EPS; ++i) {
        double mid = (left + right) / 2.0;
        double fMid = func(mid);

        if (fabs(fMid) < EPS) {
            return mid;
        }

        if (fLeft * fMid <= 0.0) {
            right = mid;
        } else {
            left = mid;
            fLeft = fMid;
        }
    }

    return (left + right) / 2.0;
}

bool isDuplicate(const vector<double>& values, double candidate) {
    for (double value : values) {
        if (fabs(value - candidate) < 1e-5) {
            return true;
        }
    }
    return false;
}

vector<double> findRoots(double (*func)(double), double left, double right, double step) {
    vector<double> roots;
    double x1 = left;
    double y1 = func(x1);

    for (double x2 = left + step; x2 <= right + EPS; x2 += step) {
        if (x2 > right) {
            x2 = right;
        }

        double y2 = func(x2);
        if (fabs(y1) < EPS && !isDuplicate(roots, x1)) {
            roots.push_back(x1);
        } else if (y1 * y2 < 0.0) {
            double root = bisection(func, x1, x2);
            if (!isDuplicate(roots, root)) {
                roots.push_back(root);
            }
        }

        x1 = x2;
        y1 = y2;
        if (x1 >= right) {
            break;
        }
    }

    return roots;
}

pair<double, double> findMinimum(double left, double right) {
    vector<double> candidates = {left, right};
    vector<double> criticalPoints = findRoots(df, left, right, 0.01);

    for (double x : criticalPoints) {
        candidates.push_back(x);
    }

    double bestX = candidates[0];
    double bestY = f(bestX);

    for (double x : candidates) {
        double y = f(x);
        if (y < bestY) {
            bestX = x;
            bestY = y;
        }
    }

    return {bestX, bestY};
}

void drawGraph(double left, double right, double yMin, double yMax) {
    const int width = 81;
    const int height = 25;
    vector<string> graph(height, string(width, ' '));

    auto toCol = [&](double x) {
        return static_cast<int>(round((x - left) / (right - left) * (width - 1)));
    };
    auto toRow = [&](double y) {
        return static_cast<int>(round((yMax - y) / (yMax - yMin) * (height - 1)));
    };

    int xAxis = toRow(0.0);
    int yAxis = toCol(0.0);

    if (0 <= xAxis && xAxis < height) {
        for (int col = 0; col < width; ++col) {
            graph[xAxis][col] = '-';
        }
    }
    if (0 <= yAxis && yAxis < width) {
        for (int row = 0; row < height; ++row) {
            graph[row][yAxis] = '|';
        }
    }
    if (0 <= xAxis && xAxis < height && 0 <= yAxis && yAxis < width) {
        graph[xAxis][yAxis] = '+';
    }

    for (int col = 0; col < width; ++col) {
        double x = left + (right - left) * col / (width - 1);
        double y = f(x);
        int row = toRow(y);
        if (0 <= row && row < height) {
            graph[row][col] = '*';
        }
    }

    cout << "\nASCII graph of f(x), x in [" << left << ", " << right << "]\n";
    cout << "Only y in [" << yMin << ", " << yMax << "] is shown so roots are visible.\n\n";

    for (int row = 0; row < height; ++row) {
        double yLabel = yMax - (yMax - yMin) * row / (height - 1);
        cout << setw(8) << fixed << setprecision(2) << yLabel << " | " << graph[row] << '\n';
    }

    cout << "          ";
    for (int i = 0; i < width + 2; ++i) {
        cout << '-';
    }
    cout << "\n            " << setw(8) << left << string(width - 16, ' ') << setw(8) << right << "\n";
}

int main() {
    cout << fixed << setprecision(8);
    cout << "Problem 1: f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2, x in [-10, 10]\n";

    drawGraph(LEFT, RIGHT, -10.0, 30.0);
    cout << fixed << setprecision(8);

    vector<double> roots = findRoots(f, LEFT, RIGHT, 0.01);
    cout << "\nMethod for f(x) = 0:\n";
    cout << "Scan the interval for sign changes, then apply the bisection method to each interval.\n";
    cout << "Roots found:\n";
    for (double root : roots) {
        cout << "x = " << setw(12) << root << ", f(x) = " << setw(14) << f(root) << '\n';
    }

    pair<double, double> minimum = findMinimum(LEFT, RIGHT);
    cout << "\nMethod for minimum value:\n";
    cout << "Find critical points where f'(x) = 0, then compare f(x) at those points and at both endpoints.\n";
    cout << "Minimum on [-10, 10]: x = " << minimum.first << ", f(x) = " << minimum.second << '\n';

    return 0;
}
