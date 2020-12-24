#include <iostream>
#include <random>
const int N = 20;
const double fi = 1.618;

double randPoint(double a, double b) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(a, b);
  return dist(gen);
}
double f(double x) { return -0.5 * x + 2; }
static double mnhtn(const std::pair<double, double> &s,
                    const std::pair<double, double> &f) {
  return abs(s.first - f.first) + abs(s.second - s.second);
}
class Function {
  std::vector<double> X;
  std::vector<double> F;

public:
  Function(int a, int b) {
    double part = double(b - a) / (N - 1);
    for (int i = 0; i < N; i++) {
      X.push_back(a + i * part);
      F.push_back(f(X[i]) + randPoint(-0.2, 0.2));
      std::cout << "(" << X[i] << "," << F[i] << ")" << std::endl;
    }
    investigation();
  }
  void withoutNoise() {
    for (int i = 0; i < N; i++) {
      F.push_back(f(X[i]));
    }
    investigation();
  }

  double minSq(double c, double d) {
    double mms = 0;
    for (int i = 0; i < N; i++) {
      mms += (F[i] - (c * X[i] + d)) * (F[i] - (c * X[i] + d));
    }
    return mms;
  }
  double cInvestigation(double d) {
    double c11 = -3;
    double c22 = 3;
    double c1 = c22 - ((c22 - c11) / fi);
    double c2 = c11 + ((c22 - c11) / fi);
    while ((c22 - c11) / 2 >= 0.1) {
      if (minSq(c1, d) > minSq(c2, d)) {
        c11 = c1;
        c1 = c2;
        c2 = c22 - (c1 - c11);
      }
      if (minSq(c1, d) < minSq(c2, d)) {
        c22 = c2;
        c2 = c1;
        c1 = c11 + (c22 - c2);
      }
    }
    return (c22 + c11) / 2;
  }

  double investigation() {
    double d;
    double c;
    double minD = 7;
    double minC = 3;
    for (int t = 0; t < 60; t++) {
      d = randPoint(-1, 5);
      c = cInvestigation(d);
      if (minSq(c, d) < minSq(minC, minD)) {
        minC = c;
        minD = d;
      }
    }
    std::cout << "с* = " << minC << "  d* = " << minD << std::endl;
  }
};

int main() {
  Function func(-2, 1);
  func.withoutNoise();
  return 0;
}
