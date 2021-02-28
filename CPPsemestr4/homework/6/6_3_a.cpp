#include <iostream>
using namespace std;

class A {
public://добавить модификатор доступа
    static int i;
    void f() {//убрать static, (или добавить static к void g())
        g();
        cout << "f()" << endl;
    }
    void g();
    void h() const {
        i = i + 1;
    } 
};

void A::g()
{
        if (i >= 0)
        i = -1, f();
        cout << "g()" << endl;
}

int A::i = 1;

int main () {
    A::i = 1;
    A a;
    a.f();
    a.h();
    a.i = 0;
    return 0;
}