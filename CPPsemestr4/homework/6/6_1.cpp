#include <iostream>
using namespace std;

class A {
    public:
    static int y;
    void f() const {cout << "f" << endl;}
};

int A::y;

int main () {
    A::y = 1;
    const A a;
    a.f();
    return 0;
}