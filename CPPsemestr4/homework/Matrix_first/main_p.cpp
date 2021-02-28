#include "matrix.hpp"

int main()
{
    SparseMatrix m1(10, 20); // матрица 10 на 20
    m1[4][2] = 42; // установить значение 42 для элемента в строке 4, столбце 2
    *(*(m1 + 5) + 3) = 42; 
    std::cout << "m1[4][2]: " << m1[4][2] << std::endl;
    std::cout << "m1[5][3]: " << *(*(m1 + 5) + 3) << std::endl;
    const SparseMatrix m2 = m1; // сохранение копии m1
    double v1 = m2[4][2]; // получение значения элемента из 4й строки, 2 столбца
    std::cout << "v1: " << v1 << std::endl;
    double v2 = *(*(m2 + 4) + 2); // аналогично
    std::cout << "v2: " << v2 << std::endl;
    SparseMatrix sum = m1 + m2; // вычислить сумму двух матриц 10x20.
    double v3 = m1.getNumber(5, 5); // v3 == 0
    std::cout << "v1: " << v3 << std::endl;
    bool bb = (m1 == m2); // сравнить две матрицы на поэлементное совпадение
    std::cout << "bb: " << bb << std::endl;
    return 0;
}