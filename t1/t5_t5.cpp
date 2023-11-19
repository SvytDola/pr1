#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для выполнения поразрядной сортировки
void radixSort(vector<int> &arr) {
    // Находим максимальное число, чтобы узнать количество битов
    int max_num = *max_element(arr.begin(), arr.end());

    // Определяем максимальное количество битов в числе
    int max_bits = 0;
    while (max_num > 0) {
        max_num >>= 1;
        max_bits++;
    }

    // Количество корзин для сортировки (2^max_bits)
    int num_bins = 1 << max_bits;

    // Маска для извлечения битов
    int bit_mask = 1;

    // Создаем корзины для сортировки
    vector<vector<int>> bins(num_bins);

    // Проходим по каждому биту
    for (int bit = 0; bit < max_bits; bit++) {
        bit_mask = 1 << bit;
        // Распределяем числа по корзинам
        for (int num : arr) {
            if (num & bit_mask) {
                bins[1].push_back(num);
            } else {
                bins[0].push_back(num);
            }
        }

        // Объединяем корзины в один вектор
        arr.clear();
        for (int i = 0; i < num_bins; i++) {
            arr.insert(arr.end(), bins[i].begin(), bins[i].end());
            bins[i].clear();
        }
    }
}

int main() {
    system("chcp 65001 > nul");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите целые числа:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        int temp = arr[i];
        string str;
        while (temp) {
            str += char('0' + temp % 2);
            temp /= 2;
        }
        std::reverse(str.begin(), str.end());
        cout << str << " ";
    }
    cout << endl;

    radixSort(arr);

    cout << "Отсортированный массив:" << endl;
    for (int i = 0; i < n; i++) {
        int temp = arr[i];
        string str;
        while (temp) {
            str += char('0' + temp % 2);
            temp /= 2;
        }
        std::reverse(str.begin(), str.end());
        cout << str << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
