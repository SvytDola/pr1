#include <iostream>
#include <vector>

using namespace std;

int main() {
    system("chcp 65001");
    // Определяем размеры матрицы
    int rows, cols;
    cout << "Введите количество строк матрицы: ";
    cin >> rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> cols;

    // Создаем исходную матрицу и заполняем её значениями
    vector<vector<int>> source_matrix(rows, vector<int>(cols));
    cout << "Введите элементы исходной матрицы:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> source_matrix[i][j];
        }
    }

    // Создаем новую матрицу для копии
    vector<vector<int>> copied_matrix(rows, vector<int>(cols));

    // Копируем элементы с использованием буферной переменной
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            copied_matrix[i][j] = source_matrix[i][j];
        }
    }

    // Выводим скопированную матрицу
    cout << "Скопированная матрица:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << copied_matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
