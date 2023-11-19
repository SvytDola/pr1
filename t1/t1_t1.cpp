#include <iostream>
#include <vector>

using namespace std;

// Функция для перемножения двух матриц
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int n = matrix1.size();
    int m = matrix2[0].size();
    int commonDimension = matrix2.size();

    // Проверка совместимости размеров матриц для перемножения
    if (matrix1[0].size() != commonDimension) {
        throw invalid_argument("Невозможно перемножить матрицы: число столбцов первой матрицы не равно числу строк второй матрицы.");
    }

    // Создаем пустую матрицу для результата
    vector<vector<int>> result(n, vector<int>(m, 0));

    // Перемножаем матрицы
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < commonDimension; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    system("chcp 65001");
    int n;
    cout << "Введите размерность матрицы n: ";
    cin >> n;

    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));

    cout << "Введите элементы первой матрицы:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix1[i][j];
        }
    }

    cout << "Введите элементы второй матрицы:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix2[i][j];
        }
    }

    try {
        vector<vector<int>> result = multiplyMatrices(matrix1, matrix2);

        cout << "Результат перемножения матриц:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << result[i][j] << ' ';
            }
            cout << endl;
        }
    } catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
