#include <iostream>
#include <vector>
#include <cstdlib> // Для использования функции rand()
#include <ctime>
#include <omp.h>

using namespace std;

vector<vector<int>> create_random_matrix(int size);

void print_matrix(const std::vector<std::vector<int>> &matrix);

vector<vector<int>> matrix_multiplication(
        const vector<vector<int>> &matrix1,
        const vector<vector<int>> &matrix2);

vector<vector<int>>
matrix_multiplication_parallel(const vector<vector<int>> &matrix1, const vector<vector<int>> &matrix2);

int main() {
    system("chcp 65001");
    cout << "Размер матриц: " << endl;
    int n;
    cin >> n;

    vector<vector<int>> matrix1 = create_random_matrix(n);
    cout << "Матрица 1:" << endl;
    print_matrix(matrix1);

    vector<vector<int>> matrix2 = create_random_matrix(n);
    cout << "Матрица 2:" << endl;
    print_matrix(matrix2);

    double start_time = omp_get_wtime();
    const vector<vector<int>> &multiplication = matrix_multiplication(matrix1, matrix2);
    cout << "Полученная матрица после перемножения матриц 1 и 2:" << endl;
    print_matrix(multiplication);
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time; // Вычисление времени выполнения


    double start_time2 = omp_get_wtime();
    const vector<vector<int>> &multiplication2 = matrix_multiplication_parallel(matrix1, matrix2);
    cout << "Полученная матрица после перемножения матриц 1 и 2:" << endl;
    print_matrix(multiplication2);
    double end_time2 = omp_get_wtime();
    double execution_time2 = end_time2 - start_time2; // Вычисление времени выполнения


    std::cout << "Время выполнения в однопоточном режиме: " << execution_time << " секунд" << std::endl;
    std::cout << "Время выполнения в многопоточном режиме: " << execution_time2 << " секунд" << std::endl;
    return 0;
}

void print_matrix(const std::vector<std::vector<int>> &matrix) {
    if (matrix.size() > 100) {
        return;
    }
    for (const auto &row: matrix) {
        for (int element: row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

vector<vector<int>> create_random_matrix(int size) {
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    vector<vector<int>> matrix(size, vector<int>(size)); // Создание матрицы заданных размеров
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100; // Генерация случайного числа от 0 до 99 и запись в ячейку матрицы
        }
    }
    return matrix;
}


vector<vector<int>> matrix_multiplication(const vector<vector<int>> &matrix1, const vector<vector<int>> &matrix2) {
    int m1 = matrix1.size();
    int n1 = matrix1[0].size();
    int n2 = matrix2[0].size();

    vector<vector<int>> result(m1, vector<int>(n2, 0));

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
        std::cout << "Поток " << omp_get_thread_num() << " выполнил строку " << i << std::endl;
    }
    return result;
}


vector<vector<int>>
matrix_multiplication_parallel(const vector<vector<int>> &matrix1, const vector<vector<int>> &matrix2) {
    int N = matrix1.size();
    int n1 = matrix1[0].size();
    int n2 = matrix2[0].size();
    vector<vector<int>> result(N, vector<int>(n2, 0));
    int num_threads = omp_get_max_threads(); // Количество потоков

    if (omp_get_thread_num() % 2 == 0) {
#pragma omp parallel for num_threads(num_threads)
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                result[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
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
                for (int k = 0; k < N; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
            std::cout << "Поток " << omp_get_thread_num() << " выполнил строку " << i << std::endl;
        }
    }
    return result;
}
