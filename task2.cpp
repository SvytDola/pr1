#include <thread>
#include <future>
#include <iostream>
#include <cmath>


using namespace std;

// Функция, для которой вычисляется интеграл
double func(double x) {
    return x * x; // Пример: интеграл x^2 от 0 до 1 равен 1/3
}

// Метод трапеций (итеративный)
double integrateTrapezoidalIterative(double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        result += func(x);
    }
    return result * h;
}

// Метод прямоугольников (итеративный)
double integrateRectangularIterative(double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        result += func(x);
    }
    return result * h;
}

// Метод трапеций (рекурсивный)
double integrateTrapezoidalRecursive(double a, double b, int n) {
    if (n == 0) {
        return 0.5 * (func(a) + func(b)) * (b - a);
    }
    double h = (b - a) / pow(2, n);
    double sum = 0.0;
    for (int i = 1; i < pow(2, n); ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    return 0.5 * integrateTrapezoidalRecursive(a, a + (b - a) / pow(2, n), n - 1) +
           0.5 * integrateTrapezoidalRecursive(a + (b - a) / pow(2, n), b, n - 1) +
           sum * h;
}

// Метод прямоугольников (рекурсивный)
double integrateRectangularRecursive(double a, double b, int n) {
    if (n == 0) {
        return func(a) * (b - a);
    }
    double h = (b - a) / pow(2, n);
    double sum = 0.0;
    for (int i = 0; i < pow(2, n); ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    return integrateRectangularRecursive(a, a + (b - a) / pow(2, n), n - 1) +
           sum * h;
}

int main() {
    system("chcp 65001");

    double a, b;
    int n;

    cout << "Введите нижний предел интегрирования (a): ";
    cin >> a;

    cout << "Введите верхний предел интегрирования (b): ";
    cin >> b;

    cout << "Введите количество разбиений (n): ";
    cin >> n;

    auto futureTrapezoidalIterativeResult = std::async(&integrateTrapezoidalIterative, a, b, n);
    auto futureRectangularIterativeResult = std::async(&integrateRectangularIterative, a, b, n);
    auto futureTrapezoidalRecursiveResult = std::async(&integrateTrapezoidalRecursive, a, b, n);
    auto futureRectangularRecursiveResult = std::async(&integrateRectangularRecursive, a, b, n);


    cout << "Итеративный метод трапеций: " << futureTrapezoidalIterativeResult.get() << endl;
    cout << "Итеративный метод прямоугольников: " << futureRectangularIterativeResult.get() << endl;
    cout << "Рекурсивный метод трапеций: " << futureTrapezoidalRecursiveResult.get() << endl;
    cout << "Рекурсивный метод прямоугольников: " << futureRectangularRecursiveResult.get() << endl;


    return 0;
}
