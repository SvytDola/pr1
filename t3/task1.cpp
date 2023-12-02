#include <iostream>
#include <omp.h>


const int num_threads = omp_get_max_threads();

double f(double x) {
    return x * x; // Здесь можно задать любую функцию
}

//В данном примере мы используем директиву #pragma omp parallel for для распараллеливания цикла вычисления суммы в методе трапеций и методе Симпсона.
//Директива reduction(+:sum) указывает, что каждый поток должен иметь свою локальную переменную sum, а затем все локальные суммы должны быть сложены в глобальную переменную sum.

// С помощью трапеций
double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
#pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
        std::cout << "Поток " << omp_get_team_num() << "выполнил функцию трапеций" << std::endl;
    }
    sum += (f(a) + f(b)) / 2.0;
    return h * sum;
}

// С помощью парабол
double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
#pragma omp parallel for reduction(+:sum) num_threads(num_threads)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
        std::cout << "Поток " << omp_get_team_num() << "выполнил функцию симпсона" << std::endl;
    }
    return h * sum / 3.0;
}

int main() {
    std::system("chcp 65001");

    std::cout << "Количество процессоров: " << num_threads << std::endl;

    int n; // Число интервалов
    std::cout << "Введите число интервалов: ";
    std::cin >> n;


    double a; // Нижний предел интегрирования
    double b; // Верхний предел интегрирования

    std::cout << "Введите нижний предел интегрирования: ";
    std::cin >> a;

    std::cout << "Введите верхний предел интегрирования: ";
    std::cin >> b;


    double result_trapezoidal = trapezoidal(a, b, n);
    double result_simpson = simpson(a, b, n);

    std::cout << "Метод трапеций: " << result_trapezoidal << std::endl;
    std::cout << "Метод Симпсона: " << result_simpson << std::endl;

    return 0;
}