#include <iostream>
using std::cout;
using std::endl;
class I {
    int i;
    public:
    I() : i(5) { cout << "fist" << endl; }
    I(int a) : i(a) { cout << "lance " << i << endl; }
    I(const I & other) : i(other.i) { cout << "dagger " << i << endl; }
    ~I() { cout << "pistole" << endl; }
    int Get() { return i; }
    void operator+=(const I & op) { i+=op.i; }
};

void f(I & x, I y) {//Конструктор копирования в y, "dagger 730"
    y += 1000;//int-> I, конструктор преобразования, "lance 1000", деструктор временного объекта "pistole"
    x += y;
    //Деструктор для y, "pistole"
}

int main() {
    I i1; // Конструктор по умолчанию, "fist"
    I i2(30);// Конструктор преобразования, "lance 30"
    i2 += 700;//int-> I, конструктор преобразования, "lance 700", деструктор временного объекта "pistole"
    f(i1, i2);
    cout << i1.Get() << ' ' << i2.Get() << endl;//1735, 730
    return 0;
    //Деструкторы для i1 и i2, "pistole" "pistole"
}
// fist
// lance 30
// lance 700
// pistole
// dagger 730
// lance 1000
// pistole
// pistole
// 1735 730
// pistole
// pistol