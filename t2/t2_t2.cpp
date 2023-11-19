#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define N 1000 // Размер матрицы

int main() {
    system("chcp 65001");
    int A[N][N]; // Матрица A
    int B[N][N]; // Матрица B
    int C[N][N]; // Матрица C (результат)

    // Заполнение матриц A и B случайными значениями
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10; // Случайное число от 0 до 9
            B[i][j] = rand() % 10; // Случайное число от 0 до 9
        }
    }

    std::cout << "Матрица A:" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Матрица B:" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    int num_threads = omp_get_max_threads(); // Количество потоков
    double start_time = omp_get_wtime();
    // Параллельное выполнение по столбцам для студентов с четными номерами
    if (omp_get_thread_num() % 2 == 0) {
#pragma omp parallel for num_threads(num_threads)
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
            std::cout << "Поток " << omp_get_thread_num() << " выполнил столбец " << j << std::endl;
        }
    }

        // Параллельное выполнение по строкам для студентов с нечетными номерами
    else {
#pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
            std::cout << "Поток " << omp_get_thread_num() << " выполнил строку " << i << std::endl;
        }
    }
    double end_time = omp_get_wtime();
    // Вывод матрицы C (результата)
    std::cout << "Матрица C:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    double execution_time = end_time - start_time; // Вычисление времени выполнения
    std::cout << "Время выполнения: " << execution_time << " секунд" << std::endl;
    return 0;
}
