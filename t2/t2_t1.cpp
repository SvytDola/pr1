#include <iostream>
#include <omp.h>
#include "unordered_map"

using namespace std;

int main() {
    system("chcp 65001");
    // Проверка поддержки OpenMP
#ifdef _OPENMP
    std::cout << "OpenMP поддерживается\n";
#else
    printf("OpenMP не поддерживается\n");
    return 0;
#endif
    std::unordered_map<unsigned,std::string> map{
            {199810,"1.0"},
            {200203,"2.0"},
            {200505,"2.5"},
            {200805,"3.0"},
            {201107,"3.1"},
            {201307,"4.0"},
            {201511,"4.5"},
            {201811,"5.0"},
            {202011,"5.1"},
            {202111,"5.2"}
    };
    // Определение версии OpenMP
    std::cout <<  "OpenMP version: " << map.at(_OPENMP) << std::endl;

    // Определение количества ядер процессоров
    int numProcessors = omp_get_max_threads() / 2;
    printf("Количество ядер процессора: %d\n", numProcessors);

    return 0;
}
