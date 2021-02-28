#include <iostream>
using namespace std;

class A {
    int number;
public:
    A(int);
    int get();
    int &  operator *=(const A &);
};

A::A(int num) {
    number = num;
}

int A::get() {
    return number;
}

int &  A::operator *=(const A & num) {
    return number = number * num.number;
}

int main () {
    A a1 (5), a2 = 3;
    a1 *= 10;
    a2 *= a1 *= 2;
    cout << a1.get() << a2.get() << endl;
    return 0;
}