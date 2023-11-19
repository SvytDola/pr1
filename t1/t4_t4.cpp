#include <iostream>
#include <vector>

using namespace std;

// Функция для разделения массива на две части
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high]; // Выбираем последний элемент как опорный
    int i = (low - 1); // Индекс элемента, который меньше или равен опорному

    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++;
            // Меняем arr[i] и arr[j]
            swap(arr[i], arr[j]);
        }
    }

    // Меняем arr[i+1] и arr[high] (опорный)
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Функция быстрой сортировки
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        // Получаем индекс разделения (опорного элемента)
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем две части массива
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    system("chcp 65001");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    cout << "Отсортированный массив:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
